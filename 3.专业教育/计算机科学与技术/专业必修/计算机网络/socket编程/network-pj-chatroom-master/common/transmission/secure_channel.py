import math
import os
import socket
import struct

from Crypto.Cipher import AES

from common.config import get_config
from common.cryptography import crypt
from common.message import serialize_message, deserialize_message, ByteArrayReader
from common.util import long_to_bytes
from pprint import pprint


# Format of message transmitted through Secure Channel
# |--Length of Message Body(4Bytes)--|--Length of AES padding (1Byte)--|--AES IV (16Bytes)--|--Message Body (CSON)--|

class SecureChannel:
    def __init__(self, socket, shared_secret):
        socket.setblocking(0)
        self.socket = socket
        self.shared_secret = shared_secret
        return

    def send(self, message_type, parameters=None):
        iv1 = bytes(os.urandom(16))
        data_to_encrypt = serialize_message(message_type, parameters)
        length_of_message = len(data_to_encrypt)
        padding_n = math.ceil(length_of_message / 16) * 16 - length_of_message
        for i in range(0, padding_n):
            data_to_encrypt += b'\0'

        encryption_suite = AES.new(self.shared_secret, AES.MODE_CBC, iv1)
        encrypted_message = encryption_suite.encrypt(data_to_encrypt)
        length_of_encrypted_message = len(encrypted_message)

        # pprint([length_of_encrypted_message,
        #         struct.pack('L', length_of_encrypted_message), bytes([padding_n]), iv1, encrypted_message])
        # pprint(['sending', self.socket, message_type, parameters])

        self.socket.send(
            struct.pack('!L', length_of_encrypted_message) + bytes([padding_n]) + iv1 + encrypted_message)
        return

    def on_data(self, data_array):
        # 用select循环socket.recv，当收到一个完整的数据块后（收到后length_of_encrypted_message+1+16个字节后），
        # 把 bytes([padding_n]) + iv1 + encrypted_message 传给本函数
        br = ByteArrayReader(data_array)

        # pprint(['recv', 'first_4_bytes', first_4_bytes, length_of_encrypted_message])
        padding_n = br.read(1)[0]
        # pprint(['recv', 'padding_n', padding_n])

        iv = br.read(16)
        # pprint(['recv', 'iv', iv])
        # incomplete
        bytes_received = 0
        data = br.read_to_end()

        decryption_suite = AES.new(self.shared_secret, AES.MODE_CBC, iv)
        decrypted_data = decryption_suite.decrypt(data)

        if padding_n != 0:
            decrypted_data = decrypted_data[0:-padding_n]
        # pprint(['recv', 'decrypted_data', decrypted_data])

        return deserialize_message(decrypted_data)

    def close(self):
        self.socket.close()


def establish_secure_channel_to_server():
    config = get_config()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect((config['client']['server_ip'], int(config['client']['server_port'])))

    # 首次连接，用diffle hellman交换密钥
    s.send(long_to_bytes(crypt.my_secret))

    # 首次连接，收到服务器diffle hellman交换密钥
    data = s.recv(1024)
    their_secret = int.from_bytes(data, byteorder='big')

    # 计算出共同密钥
    shared_secret = crypt.get_shared_secret(their_secret)

    sc = SecureChannel(s, shared_secret)

    return sc


def accept_client_to_secure_channel(socket):
    conn, addr = socket.accept()

    # 首次连接，客户端会发送diffle hellman密钥
    data = conn.recv(1024)
    their_secret = int.from_bytes(data, byteorder='big')

    # 把服务器的diffle hellman密钥发送给客户端
    conn.send(long_to_bytes(crypt.my_secret))

    # 计算出共同密钥
    shared_secert = crypt.get_shared_secret(their_secret)
    sc = SecureChannel(conn, shared_secert)

    return sc
