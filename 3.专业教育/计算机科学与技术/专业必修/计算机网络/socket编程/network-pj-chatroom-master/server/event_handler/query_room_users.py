from pprint import pprint
from common.message import MessageType
from server.broadcast import broadcast
import server.memory
from common.util import md5
from server.util import database
from server.util import add_target_type


def run(sc, parameters):
    user_id = server.memory.sc_to_user_id[sc]
    if not database.in_room(user_id, parameters):
        sc.send(MessageType.general_failure, '不在群里')
        return
    sc.send(MessageType.query_room_users_result, [database.get_room_members(parameters), parameters])
