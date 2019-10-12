current_user = {"id": 0, "nickname": ""}
sc = None
tk_root = None

window_instance = [{}, {}]
contact_window = []

# chat_history[target_type][target_id] =
# [{message:str,sender_id:int,sender_name:str,target_id:int,target_type:int,time:int}]
chat_history = [{}, {}]

# unread_message_count[target_type][target_id] = int
unread_message_count = [{}, {}]

# last_message[target_type][target_id] = str
last_message = [{}, {}]

# last_message_timestamp[target_type][target_id] = int
last_message_timestamp = [{}, {}]

tk_img_ref = []
