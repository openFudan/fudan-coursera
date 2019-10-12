from pprint import pprint
from common.message import MessageType
from server.broadcast import broadcast
import server.memory
from common.util import md5
from server.util import database
from server.util import add_target_type


def run(sc, parameters):
    user_id = server.memory.sc_to_user_id[sc]
    if database.in_room(user_id, parameters):
        sc.send(MessageType.general_failure, '已经在群里了')
        return
    room = database.get_room(parameters)
    if room is None:
        sc.send(MessageType.general_failure, '群不存在')
        return
    database.add_to_room(user_id, parameters)
    sc.send(MessageType.contact_info, add_target_type(room, 1))
