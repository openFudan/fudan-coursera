import _tkinter
import tkinter as tk
from tkinter import messagebox
from common.message import MessageType
from pprint import pprint
import client.memory
from client.forms.register_form import RegisterForm
from client.forms.contacts_form import ContactsForm
import select
import _thread
from tkinter import *
from tkinter import Toplevel
import client.util.socket_listener


class LoginForm(tk.Frame):
    def remove_socket_listener_and_close(self):
        client.util.socket_listener.remove_listener(self.socket_listener)
        self.master.destroy()

    def destroy_window(self):
        client.memory.tk_root.destroy()

    def socket_listener(self, data):
        if data['type'] == MessageType.login_failed:
            messagebox.showerror('登入失败', '登入失败，请检查用户名密码')
            return

        if data['type'] == MessageType.login_successful:
            client.memory.current_user = data['parameters']
            self.remove_socket_listener_and_close()

            contacts = Toplevel(client.memory.tk_root, takefocus=True)
            ContactsForm(contacts)

            return

    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        master.resizable(width=False, height=False)
        master.geometry('300x100')
        self.label_1 = Label(self, text="用户名")
        self.label_2 = Label(self, text="密码")

        self.username = Entry(self)
        self.password = Entry(self, show="*")

        self.label_1.grid(row=0, sticky=E)
        self.label_2.grid(row=1, sticky=E)
        self.username.grid(row=0, column=1, pady=(10, 6))
        self.password.grid(row=1, column=1, pady=(0, 6))

        self.buttonframe = Frame(self)
        self.buttonframe.grid(row=2, column=0, columnspan=2, pady=(4, 6))

        self.logbtn = Button(self.buttonframe, text="登入", command=self.do_login)
        self.logbtn.grid(row=0, column=0)

        self.registerbtn = Button(self.buttonframe, text="注册", command=self.show_register)
        self.registerbtn.grid(row=0, column=1)

        self.pack()
        self.master.title("聊天室")

        self.sc = client.memory.sc
        # self.sc.send(MessageType.client_echo, 0)
        client.util.socket_listener.add_listener(self.socket_listener)

    def do_login(self):
        username = self.username.get()
        password = self.password.get()
        if not username:
            messagebox.showerror("出错了", "用户名不能为空")
            return
        if not password:
            messagebox.showerror("出错了", "密码不能为空")
            return

        self.sc.send(MessageType.login, [username, password])

    def show_register(self):
        register_form = Toplevel()
        RegisterForm(register_form)
