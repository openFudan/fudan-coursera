from pprint import pprint
from common.message import MessageType
from server.broadcast import broadcast
import server.memory
from common.util import md5

from server.util import database


def run(sc, parameters):
    parameters[0] = parameters[0].strip().lower()
    c = database.get_cursor()
    r = c.execute('SELECT * from users where username=?', [parameters[0]])
    rows = r.fetchall()
    if len(rows) > 0:
        sc.send(MessageType.username_taken)
        return

    c = database.get_cursor()
    c.execute('INSERT into users (username,password,nickname) values (?,?,?)',
              [parameters[0], md5(parameters[1]), parameters[2]])
    sc.send(MessageType.register_successful, c.lastrowid)
