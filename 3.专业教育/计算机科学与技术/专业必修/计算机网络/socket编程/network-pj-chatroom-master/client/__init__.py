import _thread
import tkinter as tk
from tkinter import messagebox

import client.memory
import client.util.socket_listener
from client.forms.login_form import LoginForm
from common.transmission.secure_channel import establish_secure_channel_to_server


def run():
    root = tk.Tk()
    client.memory.tk_root = root

    try:
        client.memory.sc = establish_secure_channel_to_server()

    except ConnectionError:
        messagebox.showerror("出错了", "无法连接到服务器")
        exit(1)

    _thread.start_new_thread(client.util.socket_listener.socket_listener_thread, (client.memory.sc, root))

    login = tk.Toplevel()
    LoginForm(master=login)

    root.withdraw()
    root.mainloop()
    try:
        root.destroy()
    except tk.TclError:
        pass
