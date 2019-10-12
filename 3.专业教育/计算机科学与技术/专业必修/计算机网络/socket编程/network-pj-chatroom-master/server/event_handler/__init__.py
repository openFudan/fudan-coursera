from pprint import pprint
import server.event_handler.login
import server.event_handler.send_message
import server.event_handler.register
import server.event_handler.resolve_friend_request
import server.event_handler.client_echo
import server.event_handler.add_friend
import server.event_handler.join_room
import server.event_handler.create_room
import server.event_handler.query_room_users
import server.event_handler.bad
from common.message import MessageType

event_handler_map = {
    MessageType.login: login,
    MessageType.send_message: send_message,
    MessageType.register: register,
    MessageType.resolve_friend_request: resolve_friend_request,
    MessageType.client_echo: client_echo,
    MessageType.add_friend: add_friend,
    MessageType.join_room: join_room,
    MessageType.create_room: create_room,
    MessageType.query_room_users: query_room_users,
    MessageType.bad: bad,
}


def handle_event(sc, event_type, parameters):
    event_handler_map[event_type].run(sc, parameters)
