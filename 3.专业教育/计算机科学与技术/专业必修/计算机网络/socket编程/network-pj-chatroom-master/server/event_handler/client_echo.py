from pprint import pprint
from common.message import MessageType
from server.broadcast import broadcast
import server.memory
from common.util import md5
from server.util import database


def run(sc, parameters):
    # pprint(['client echo', parameters])
    sc.send(MessageType.server_echo, parameters)
