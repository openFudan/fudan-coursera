from pprint import pprint
from common.message import MessageType, _serialize_dict
from server.broadcast import broadcast
import server.memory
from common.util import md5
from server.util import database
from server.memory import *
import time


# {target_type:int(0=私聊 1=群聊),target_id:int,message:str}

def run(sc, parameters):
    # pprint(parameters)
    user_id = sc_to_user_id[sc]
    sender = database.get_user(user_id)

    # target只是dispatch用

    # target_id延后做，对于发送方和接收方不一样
    message = {"message": parameters['message'], 'sender_id': user_id,
               'sender_name': sender['nickname'],
               'target_type': parameters['target_type'],
               'time': int(round(time.time() * 1000))}

    if parameters['target_type'] == 0:
        # 私聊
        if not database.is_friend_with(user_id, parameters['target_id']):
            sc.send(MessageType.general_failure, '还不是好友')
            return

        # 给发送方发回执
        message['target_id'] = parameters['target_id']
        user_id_to_sc[user_id].send(MessageType.on_new_message, message)
        database.add_to_chat_history(user_id, message['target_id'], message['target_type'],
                                     _serialize_dict(message),
                                     True)

        # 给接收方发消息，存入聊天记录
        message['target_id'] = user_id
        sent = False
        if parameters['target_id'] in user_id_to_sc:
            sent = True
            user_id_to_sc[parameters['target_id']].send(MessageType.on_new_message, message)

        database.add_to_chat_history(parameters['target_id'], message['target_id'], message['target_type'],
                                     _serialize_dict(message),
                                     sent)

    if parameters['target_type'] == 1:
        # 群聊
        message['target_id'] = parameters['target_id']

        if not database.in_room(user_id, parameters['target_id']):
            sc.send(MessageType.general_failure, '还没有加入该群')
            return

        users_id = database.get_room_members_id(parameters['target_id'])

        for user_id in users_id:
            sent = False
            if user_id in user_id_to_sc:
                user_id_to_sc[user_id].send(MessageType.on_new_message, message)
                sent = True

            database.add_to_chat_history(user_id, message['target_id'], message['target_type'],
                                         _serialize_dict(message),
                                         sent)
