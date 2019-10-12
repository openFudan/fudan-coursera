from server.memory import *


def broadcast(message_type, parameters):
    for sc in scs:
        sc.send(message_type, parameters)
