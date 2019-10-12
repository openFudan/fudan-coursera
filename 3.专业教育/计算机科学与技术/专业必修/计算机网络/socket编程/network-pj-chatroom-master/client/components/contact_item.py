from tkinter import *
from pprint import pprint


class ContactItem(Frame):
    def __init__(self, parent, onclick):
        Frame.__init__(self, parent)

        def handle_on_click(e):
            e.widget = self
            onclick(e)

        Frame.config(self, background='white', borderwidth=2, relief=GROOVE)
        # == Line 1

        self.title_frame = Frame(self, bg='white')
        self.title_frame.pack(side=TOP, fill=X, expand=True, anchor=W, pady=(1, 1), padx=3)

        self.title = Label(self.title_frame, text="Title", bg='white')
        self.title.pack(side=LEFT, fill=None, anchor=W)

        self.last_message_time = Label(self.title_frame, text="date", font=('', 8), fg='#999', bg='white')
        self.last_message_time.pack(side=RIGHT, anchor=E)

        # == Line 2

        self.message_frame = Frame(self, bg='white')
        self.message_frame.pack(side=TOP, fill=X, expand=True, anchor=W, pady=(0, 5), padx=3)

        self.unread_message_count = Label(self.message_frame, text="0", font=('', 9), fg='white', bg='red')
        self.unread_message_count.pack(side=RIGHT, anchor=E, fill=None, expand=False, ipadx=4)
        self.unread_message_count.pack_forget()

        self.last_message = Label(self.message_frame, text="recent message", font=('', 9), fg='#666', bg='white')
        self.last_message.pack(side=LEFT, fill=X, expand=True, anchor=W)

        # propagate click event to parent..
        self.title.bind("<Button>", handle_on_click)
        self.last_message_time.bind("<Button>", handle_on_click)
        self.last_message.bind("<Button>", handle_on_click)
        self.unread_message_count.bind("<Button>", handle_on_click)
        self.message_frame.bind("<Button>", handle_on_click)
        self.title_frame.bind("<Button>", handle_on_click)

        self.pack()
        return
