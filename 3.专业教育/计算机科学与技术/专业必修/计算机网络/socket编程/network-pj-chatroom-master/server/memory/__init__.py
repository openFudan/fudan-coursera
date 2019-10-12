sc_to_user_id = {}
user_id_to_sc = {}
socket_to_sc = {}

# 不一定是登入状态，只是连接
scs = []

chat_history = []


def remove_sc_from_socket_mapping(sc):
    if sc in sc_to_user_id:
        uid = sc_to_user_id[sc]
        del sc_to_user_id[sc]
        if uid in user_id_to_sc:
            del user_id_to_sc[uid]

    if sc in scs:
        scs.remove(sc)

    if sc.socket in socket_to_sc:
        del socket_to_sc[sc.socket]
