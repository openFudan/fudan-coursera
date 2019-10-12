#!/usr/bin/env python

import socket
from pprint import pprint

from common.util import long_to_bytes
import enum
from struct import pack, unpack


# 每个序列化片段的格式：
# |--VAR_TYPE(1 Byte)--|--DATA_LEN(4 Bytes)--|--DATA--|

# |-- 4 Byte messageType --|-- Array of parameters --|
# for each item in array of params
# |-- 1 Byte Type of params --|-- 4 Bytes Length of body --|-- N Byte Body--|

class MessageType(enum.IntEnum):
    # === Client Action 1-100
    # [username, password]
    login = 1
    # [username, password, nickname]
    register = 2
    client_echo = 3
    # username:str
    add_friend = 4
    resolve_friend_request = 5

    # {target_type:int(0=私聊 1=群聊),target_id:int,message:str}
    send_message = 6

    # id:int
    join_room = 7
    # name:str
    create_room = 8
    # id:int
    query_room_users = 9

    bad = 10

    # === Server Action 101-200
    login_successful = 100
    register_successful = 101
    incoming_friend_request = 102
    contact_info = 103
    chat_history = 104
    server_echo = 105
    # [successful:bool,err_msg:str]
    add_friend_result = 106
    # [online:bool,friend_user_id:int]
    friend_on_off_line = 107
    notify_chat_history = 108
    # [target_type:int(0=私聊 1=群聊),target_id:int,message:str,sender_id:int,sender_name:str,time:int]
    on_new_message = 109
    server_kick = 110
    query_room_users_result = 111
    # [room_id, user_id, online]
    room_user_on_off_line = 112
    login_bundle = 113

    # === Failure 201-300
    login_failed = 201
    username_taken = 202
    # err_msg:str
    general_failure = 203
    # msg:str
    general_msg = 204


def _get_message_type_from_value(value):
    return MessageType(value)


VAR_TYPE = {
    1: 'int',
    2: 'float',
    3: 'str',
    4: 'list',
    5: 'dict',
    6: 'bool',
    7: 'bytearray',
}

VAR_TYPE_INVERSE = {
    'int': 1,
    'float': 2,
    'str': 3,
    'list': 4,
    'dict': 5,
    'bool': 6,
    'bytearray': 7
}


def _serialize_int(int):
    body = long_to_bytes(int)
    return bytes([VAR_TYPE_INVERSE['int']]) + pack('!L', len(body)) + body


def _serialize_bool(value):
    body = value
    return bytes([VAR_TYPE_INVERSE['bool']]) + pack('!L', 1) + bytes([1 if value else 0])


def _serialize_float(float):
    body = pack('f', float)
    return bytes([VAR_TYPE_INVERSE['float']]) + pack('!L', len(body)) + body


def _serialize_str(str):
    body = str.encode()
    return bytes([VAR_TYPE_INVERSE['str']]) + pack('!L', len(body)) + body


def _serialize_bytes(body):
    return bytes([VAR_TYPE_INVERSE['bytearray']]) + pack('!L', len(body)) + body


def _serialize_list(list):
    # |--Body (self-evident length)--|--Body (self-evident length)--|--Body (self-evident length)--|...
    body = bytearray()
    for i in range(0, len(list)):
        body += _serialize_any(list[i])
    return bytes([VAR_TYPE_INVERSE['list']]) + pack('!L', len(body)) + body


def _serialize_dict(dict):
    # |--Length of Key(1Byte)--|--Key--|--Body (self-evident length)--|
    # |--Length of Key(1Byte)--|--Key--|--Body (self-evident length)--|
    # ...

    body = bytearray()

    for item_key, value in dict.items():
        item_body = _serialize_any(value)
        key_length = len(item_key)

        body += bytes([key_length])
        body += str.encode(item_key)
        body += item_body

    return bytes([VAR_TYPE_INVERSE['dict']]) + pack('!L', len(body)) + body


_serialize_by_type = [None, _serialize_int, _serialize_float, _serialize_str, _serialize_list, _serialize_dict,
                      _serialize_bool, _serialize_bytes]


def _serialize_any(obj):
    if obj is None:
        return bytearray([0])
    type_byte = VAR_TYPE_INVERSE[type(obj).__name__]
    return _serialize_by_type[type_byte](obj)


def serialize_message(message_type, parameters):
    result = bytes([message_type.value])
    result += _serialize_any(parameters)
    return result


def _deserialize_int(bytes):
    return int.from_bytes(bytes, 'big')


def _deserialize_bool(value):
    return True if value[0] else False


def _deserialize_float(bytes):
    return unpack('!f', bytes)[0]


def _deserialize_str(bytes):
    return bytes.decode()


def _deserialize_bytes(body):
    return bytearray(body)


def _deserialize_list(bytes):
    # |--Body (self-evident length)--|--Body (self-evident length)--|--Body (self-evident length)--|...
    byte_reader = ByteArrayReader(bytes)
    ret = []
    while (not byte_reader.empty()):
        body_type = byte_reader.read(1)[0]
        body = byte_reader.read(int.from_bytes(byte_reader.read(4), byteorder='big'))
        body = _deserialize_by_type[body_type](body)
        ret.append(body)
    return ret


def _deserialize_dict(bytes):
    # |--Length of Key(1Byte)--|--Key--|--Body (self-evident length)--|
    # |--Length of Key(1Byte)--|--Key--|--Body (self-evident length)--|
    # ...
    byte_reader = ByteArrayReader(bytes)
    ret = {}
    while (not byte_reader.empty()):
        len_key = byte_reader.read(1)
        key = byte_reader.read(len_key[0])

        body_type = byte_reader.read(1)[0]
        body = byte_reader.read(int.from_bytes(byte_reader.read(4), byteorder='big'))
        body = _deserialize_by_type[body_type](body)
        ret[key.decode()] = body
    return ret


_deserialize_by_type = [None, _deserialize_int, _deserialize_float, _deserialize_str, _deserialize_list,
                        _deserialize_dict, _deserialize_bool, _deserialize_bytes]


def _deserialize_any(bytes):
    byte_reader = ByteArrayReader(bytes)
    type = byte_reader.read(1)[0]

    if type == 0:
        return None

    body_len = int.from_bytes(byte_reader.read(4), 'big')
    return _deserialize_by_type[type](byte_reader.read(body_len))


def deserialize_message(data):
    ret = {}
    byte_reader = ByteArrayReader(data)
    ret['type'] = _get_message_type_from_value(byte_reader.read(1)[0])

    ret['parameters'] = _deserialize_any(byte_reader.read_to_end())

    return ret


class ByteArrayReader:
    def __init__(self, byte_array):
        self.byte_array = byte_array
        self.pointer = 0

    def read(self, length):
        buffer = self.byte_array[self.pointer: self.pointer + length]
        self.pointer += length
        return buffer

    def read_to_end(self):
        buffer = self.byte_array[self.pointer: len(self.byte_array)]
        self.pointer = len(self.byte_array)
        return buffer

    def empty(self):
        return len(self.byte_array) == self.pointer
