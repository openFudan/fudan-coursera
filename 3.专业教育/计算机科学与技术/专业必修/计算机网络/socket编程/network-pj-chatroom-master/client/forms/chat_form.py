import tkinter as tk
from tkinter import *

import client.memory
from client.util.socket_listener import *
from tkinter.scrolledtext import ScrolledText
from tkinter import colorchooser
from tkinter import simpledialog
from tkinter import filedialog
from PIL import Image, ImageTk
from io import BytesIO
from client.util import socket_listener
import binascii


class ChatForm(tk.Frame):
    font_color = "#000000"
    font_size = 10
    user_list = []
    tag_i = 0

    def remove_listener_and_close(self):
        remove_message_listener(self.message_listener)
        client.util.socket_listener.remove_listener(self.socket_listener)
        self.master.destroy()
        if self.target['id'] in client.memory.window_instance[self.target['type']]:
            del client.memory.window_instance[self.target['type']][self.target['id']]

    def message_listener(self, data):
        self.digest_message(data)

    def socket_listener(self, data):
        if data['type'] == MessageType.query_room_users_result:
            if data['parameters'][1] != self.target['id']:
                return
            # [id, nickname, online, username]
            self.user_list = data['parameters'][0]
            self.refresh_user_listbox()

        if data['type'] == MessageType.room_user_on_off_line:
            # [room_id, user_id, online]
            if data['parameters'][0] != self.target['id']:
                return
            for i in range(0, len(self.user_list)):
                if self.user_list[i][0] == data['parameters'][1]:
                    self.user_list[i][2] = data['parameters'][2]

            self.refresh_user_listbox()

    def refresh_user_listbox(self):
        # [id, nickname, online, username]
        self.user_listbox.delete(0, END)
        self.user_list.sort(key=lambda x: x[2])

        for user in self.user_list:
            self.user_listbox.insert(0, user[1] + ("(在线)" if user[2] else "(离线)"))
            self.user_listbox.itemconfig(0, {'fg': ("green" if user[2] else "#999")})

    def digest_message(self, data):
        time = datetime.datetime.fromtimestamp(
            int(data['time']) / 1000
        ).strftime('%Y-%m-%d %H:%M:%S')
        self.append_to_chat_box(data['sender_name'] + "  " + time + '\n',
                                ('me' if client.memory.current_user['id'] == data[
                                    'sender_id'] else 'them'))
        # type 0 - 文字消息 1 - 图片消息
        if data['message']['type'] == 0:
            self.tag_i += 1
            self.chat_box.tag_config('new' + str(self.tag_i),
                                     lmargin1=16,
                                     lmargin2=16,
                                     foreground=data['message']['fontcolor'],
                                     font=(None, data['message']['fontsize']))
            self.append_to_chat_box(data['message']['data'] + '\n',
                                    'new' + str(self.tag_i))
        if data['message']['type'] == 1:
            client.memory.tk_img_ref.append(ImageTk.PhotoImage(data=data['message']['data']))
            self.chat_box.image_create(END, image=client.memory.tk_img_ref[-1], padx=16, pady=5)
            self.append_to_chat_box('\n', '')

    def user_listbox_double_click(self, _):
        if len(self.user_listbox.curselection()) == 0:
            return None
        index = self.user_listbox.curselection()[0]
        selected_user_id = self.user_list[len(self.user_list) - 1 - index][0]
        selected_user_nickname = self.user_list[len(self.user_list) - 1 - index][1]
        selected_user_username = self.user_list[len(self.user_list) - 1 - index][3]
        if selected_user_id == client.memory.current_user['id']:
            return
        client.memory.contact_window[0].try_open_user_id(selected_user_id, selected_user_nickname,
                                                         selected_user_username)
        # pprint(selected_user_id)
        return

    def __init__(self, target, master=None):
        super().__init__(master)
        self.master = master
        self.target = target
        self.user_listbox = tk.Listbox(self, bg='#EEE')
        client.util.socket_listener.add_listener(self.socket_listener)
        client.memory.unread_message_count[self.target['type']][self.target['id']] = 0
        client.memory.contact_window[0].refresh_contacts()
        master.resizable(width=True, height=True)
        master.geometry('660x500')
        master.minsize(520, 370)
        self.sc = client.memory.sc

        if self.target['type'] == 0:
            self.master.title(self.target['nickname'])

        if self.target['type'] == 1:
            self.master.title("群:" + str(self.target['id']) + " " + self.target['room_name'])
            self.sc.send(MessageType.query_room_users, self.target['id'])

        self.right_frame = tk.Frame(self, bg='white')

        self.user_listbox.bind('<Double-Button-1>', self.user_listbox_double_click)
        if self.target['type'] == 1:
            self.user_listbox.pack(side=LEFT, expand=False, fill=BOTH)
        self.right_frame.pack(side=LEFT, expand=True, fill=BOTH)

        self.input_frame = tk.Frame(self.right_frame, bg='white')

        self.input_textbox = ScrolledText(self.right_frame, height=10)
        self.input_textbox.bind("<Control-Return>", self.send_message)
        self.input_textbox.bind_all('<Key>', self.apply_font_change)

        self.send_btn = tk.Button(self.input_frame, text='发送消息(Ctrl+Enter)', command=self.send_message)
        self.send_btn.pack(side=RIGHT, expand=False)

        self.font_btn = tk.Button(self.input_frame, text='字体颜色', command=self.choose_color)
        self.font_btn.pack(side=LEFT, expand=False)

        self.font_btn = tk.Button(self.input_frame, text='字体大小', command=self.choose_font_size)
        self.font_btn.pack(side=LEFT, expand=False)

        self.image_btn = tk.Button(self.input_frame, text='发送图片', command=self.send_image)
        self.image_btn.pack(side=LEFT, expand=False)

        self.chat_box = ScrolledText(self.right_frame, bg='white')
        self.input_frame.pack(side=BOTTOM, fill=X, expand=False)
        self.input_textbox.pack(side=BOTTOM, fill=X, expand=False, padx=(0, 0), pady=(0, 0))
        self.chat_box.pack(side=BOTTOM, fill=BOTH, expand=True)
        self.chat_box.bind("<Key>", lambda e: "break")
        self.chat_box.tag_config("default", lmargin1=10, lmargin2=10, rmargin=10)
        self.chat_box.tag_config("me", foreground="green", spacing1='5')
        self.chat_box.tag_config("them", foreground="blue", spacing1='5')
        self.chat_box.tag_config("message", foreground="black", spacing1='0')
        self.chat_box.tag_config("system", foreground="grey", spacing1='0',
                                 justify='center',
                                 font=(None, 8))

        self.pack(expand=True, fill=BOTH)

        add_message_listener(self.target['type'], self.target['id'], self.message_listener)
        master.protocol("WM_DELETE_WINDOW", self.remove_listener_and_close)

        # 历史消息显示
        if target['id'] in client.memory.chat_history[self.target['type']]:
            for msg in client.memory.chat_history[self.target['type']][target['id']]:
                self.digest_message(msg)

            self.append_to_chat_box('- 以上是历史消息 -\n', 'system')

    def append_to_chat_box(self, message, tags):
        self.chat_box.insert(tk.END, message, [tags, 'default'])
        self.chat_box.update()
        self.chat_box.see(tk.END)

    def send_message(self, _=None):
        message = self.input_textbox.get("1.0", END)
        if not message or message.replace(" ", "").replace("\r", "").replace("\n", "") == '':
            return
        self.sc.send(MessageType.send_message,
                     {'target_type': self.target['type'], 'target_id': self.target['id'],
                      'message': {
                          'type': 0,
                          'data': message.strip().strip('\n'),
                          'fontsize': self.font_size,
                          'fontcolor': self.font_color
                      }
                      })
        self.input_textbox.delete("1.0", END)
        return 'break'

    def choose_color(self):
        _, self.font_color = colorchooser.askcolor(initialcolor=self.font_color)
        self.apply_font_change(None)

    def choose_font_size(self):
        result = simpledialog.askinteger("设置", "请输入字体大小", initialvalue=self.font_size)
        if result is None:
            return
        self.font_size = result
        self.apply_font_change(None)

    def apply_font_change(self, _):
        try:
            self.input_textbox.tag_config('new', foreground=self.font_color, font=(None, self.font_size))
            self.input_textbox.tag_add('new', '1.0', END)
        except:
            pass

    def send_image(self):
        filename = filedialog.askopenfilename(filetypes=[("Image Files",
                                                          ["*.jpg", "*.jpeg", "*.png", "*.gif", "*.JPG", "*.JPEG",
                                                           "*.PNG", "*.GIF"]),
                                                         ("All Files", ["*.*"])])
        if filename is None or filename == '':
            return
        with open(filename, "rb") as imageFile:
            f = imageFile.read()
            b = bytearray(f)

            self.sc.send(MessageType.send_message,
                         {'target_type': self.target['type'], 'target_id': self.target['id'],
                          'message': {'type': 1, 'data': b}})
