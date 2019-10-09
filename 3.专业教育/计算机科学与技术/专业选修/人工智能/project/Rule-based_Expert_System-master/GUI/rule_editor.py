#!/usr/bin/python
# encoding:utf-8
# -*- Mode: Python -*-
# Author: Soros Liu <soros.liu1029@gmail.com>

# ==================================================================================================
# Copyright 2016 by Soros Liu
#
#                                                                          All Rights Reserved
"""

"""
import wx
__author__ = 'Soros Liu'


class EditorFrame(wx.Frame):
    """

    """
    def __init__(self, parent, id, title, size):
        wx.Frame.__init__(self, parent, id, title,
                          style=wx.DEFAULT_FRAME_STYLE ^ (wx.RESIZE_BORDER | wx.MINIMIZE_BOX |
                                                          wx.MAXIMIZE_BOX))
        self.SetSize(size)
        self.Center()
        self.ps = wx.StaticText(self, label='IF part using \'AND\' to combine antecedent. Please ONE antecedent per line',
                                pos=(10, 5), size=(40 ,100))
        self.ifLabel = wx.StaticText(self, label='IF: ', pos=(10, 30), size=(40, 50))
        self.thenLabel = wx.StaticText(self, label='THEN: ', pos=(10, 250), size=(40, 50))
        self.descriptionLabel = wx.StaticText(self, label='Description: ', pos=(10, 280), size=(40, 50))
        self.ifText = wx.TextCtrl(self, pos=(100, 30), size=(490, 210), style=wx.TE_MULTILINE)
        self.thenText = wx.TextCtrl(self, pos=(100, 250), size=(490, 25))
        self.descriptionText = wx.TextCtrl(self, pos=(100, 280), size=(490, 25))
        self.createButton = wx.Button(self, label='Create', pos=(85, 320), size=(130, 30))
        self.createButton.Bind(wx.EVT_BUTTON, self.create_rule)
        self.cancelButton = wx.Button(self, label='Cancel', pos=(385, 320), size=(130, 30))
        self.cancelButton.Bind(wx.EVT_BUTTON, self.cancel_creation)

    def create_rule(self, event):
        with open('../rules/rules.txt', 'a') as f:
            f.write(self.__create_formatted_rule__())

    def cancel_creation(self, event):
        self.Close()

    def __create_formatted_rule__(self):
        s = ''
        line_no = self.ifText.GetNumberOfLines()
        s += '{\nIF: ['
        for i in range(line_no-1):
            s += ("'%s', " % self.ifText.GetLineText(i))
        s += ("'%s']\nTHEN: " % self.ifText.GetLineText(line_no-1))
        s += ("'%s'\nDESCRIPTION: '%s'\n}\n" % (self.thenText.GetLineText(0), self.descriptionText.GetLineText(0)))
        return s


if __name__ == '__main__':
    app = wx.App()
    EditorFrame(None, -1, title='Create Rule', size=(600, 400))
    app.MainLoop()
