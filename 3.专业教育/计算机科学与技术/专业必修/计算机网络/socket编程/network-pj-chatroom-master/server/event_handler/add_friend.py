from pprint import pprint
from common.message import MessageType
from server.broadcast import broadcast
import server.memory
from common.util import md5
from server.util import database
from server.memory import *


def run(sc, parameters):
    user_id = sc_to_user_id[sc]

    # parameters = username

    c = database.get_cursor()
    username = parameters.strip().lower()

    r = c.execute('SELECT id from users where username=?', [username]).fetchall()

    if len(r) == 0:
        sc.send(MessageType.add_friend_result, [False, '用户名不存在'])
        return

    uid = r[0][0]

    if uid == user_id:
        sc.send(MessageType.add_friend_result, [False, '不能加自己为好友'])
        return

    c = database.get_cursor()
    r = c.execute('SELECT 1 from friends where from_user_id=? and to_user_id=?', [user_id, uid]).fetchall()

    if len(r) != 0:
        sc.send(MessageType.add_friend_result, [False, '已经是好友/已经发送过好友请求'])
        return

    c = database.get_cursor()
    c.execute('insert into friends (from_user_id,to_user_id,accepted) values (?,?,0)', [user_id, uid]).fetchall()

    sc.send(MessageType.add_friend_result, [True, ''])

    if uid in user_id_to_sc:
        user_id_to_sc[uid].send(MessageType.incoming_friend_request, database.get_user(user_id))
