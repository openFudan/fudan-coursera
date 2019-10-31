# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import os
from pylab import *
from shaoshupai.minoritygame import *
from numpy import *

import sys

simulation=[0]
class Ui_Form(object):

    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(856, 712)
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(280, 10, 301, 61))
        font = QtGui.QFont()
        font.setPointSize(18)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(660, 50, 151, 31))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(660, 80, 91, 31))
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(60, 120, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.label_6 = QtWidgets.QLabel(Form)
        self.label_6.setGeometry(QtCore.QRect(60, 410, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_6.setFont(font)
        self.label_6.setObjectName("label_6")
        self.lineEdit = QtWidgets.QLineEdit(Form)
        self.lineEdit.setGeometry(QtCore.QRect(230, 210, 113, 25))
        self.lineEdit.setObjectName("lineEdit")
        self.label_5 = QtWidgets.QLabel(Form)
        self.label_5.setGeometry(QtCore.QRect(100, 160, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.pushButton = QtWidgets.QPushButton(Form)
        self.pushButton.setGeometry(QtCore.QRect(100, 350, 81, 34))
        self.pushButton.setObjectName("pushButton")
        self.label_7 = QtWidgets.QLabel(Form)
        self.label_7.setGeometry(QtCore.QRect(100, 200, 91, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_7.setFont(font)
        self.label_7.setObjectName("label_7")
        self.label_8 = QtWidgets.QLabel(Form)
        self.label_8.setGeometry(QtCore.QRect(100, 230, 101, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_8.setFont(font)
        self.label_8.setObjectName("label_8")
        self.label_9 = QtWidgets.QLabel(Form)
        self.label_9.setGeometry(QtCore.QRect(100, 260, 81, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_9.setFont(font)
        self.label_9.setObjectName("label_9")
        self.label_10 = QtWidgets.QLabel(Form)
        self.label_10.setGeometry(QtCore.QRect(100, 290, 81, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_10.setFont(font)
        self.label_10.setObjectName("label_10")
        self.lineEdit_2 = QtWidgets.QLineEdit(Form)
        self.lineEdit_2.setGeometry(QtCore.QRect(230, 240, 113, 25))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.lineEdit_3 = QtWidgets.QLineEdit(Form)
        self.lineEdit_3.setGeometry(QtCore.QRect(230, 270, 113, 25))
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.lineEdit_4 = QtWidgets.QLineEdit(Form)
        self.lineEdit_4.setGeometry(QtCore.QRect(230, 300, 113, 25))
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.label_11 = QtWidgets.QLabel(Form)
        self.label_11.setGeometry(QtCore.QRect(90, 490, 101, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.label_12 = QtWidgets.QLabel(Form)
        self.label_12.setGeometry(QtCore.QRect(90, 550, 81, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_12.setFont(font)
        self.label_12.setObjectName("label_12")
        self.label_13 = QtWidgets.QLabel(Form)
        self.label_13.setGeometry(QtCore.QRect(90, 520, 81, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.lineEdit_6 = QtWidgets.QLineEdit(Form)
        self.lineEdit_6.setGeometry(QtCore.QRect(220, 530, 113, 25))
        self.lineEdit_6.setObjectName("lineEdit_6")
        self.label_14 = QtWidgets.QLabel(Form)
        self.label_14.setGeometry(QtCore.QRect(90, 450, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_14.setFont(font)
        self.label_14.setObjectName("label_14")
        self.lineEdit_7 = QtWidgets.QLineEdit(Form)
        self.lineEdit_7.setGeometry(QtCore.QRect(220, 560, 113, 25))
        self.lineEdit_7.setObjectName("lineEdit_7")
        self.lineEdit_8 = QtWidgets.QLineEdit(Form)
        self.lineEdit_8.setGeometry(QtCore.QRect(220, 500, 113, 25))
        self.lineEdit_8.setObjectName("lineEdit_8")
        self.pushButton_2 = QtWidgets.QPushButton(Form)
        self.pushButton_2.setGeometry(QtCore.QRect(90, 600, 81, 34))
        self.pushButton_2.setObjectName("pushButton_2")
        self.label_15 = QtWidgets.QLabel(Form)
        self.label_15.setGeometry(QtCore.QRect(460, 160, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_15.setFont(font)
        self.label_15.setObjectName("label_15")
        self.pushButton_3 = QtWidgets.QPushButton(Form)
        self.pushButton_3.setGeometry(QtCore.QRect(90, 650, 81, 34))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_4 = QtWidgets.QPushButton(Form)
        self.pushButton_4.setGeometry(QtCore.QRect(190, 650, 81, 34))
        self.pushButton_4.setObjectName("pushButton_4")
        self.textBrowser = QtWidgets.QTextBrowser(Form)
        self.textBrowser.setGeometry(QtCore.QRect(460, 421, 281, 231))
        self.textBrowser.setObjectName("textBrowser")
        self.pushButton_5 = QtWidgets.QPushButton(Form)
        self.pushButton_5.setGeometry(QtCore.QRect(290, 650, 81, 34))
        self.pushButton_5.setObjectName("pushButton_5")
        self.pushButton_6 = QtWidgets.QPushButton(Form)
        self.pushButton_6.setGeometry(QtCore.QRect(460, 350, 61, 34))
        self.pushButton_6.setObjectName("pushButton_6")
        self.label_16 = QtWidgets.QLabel(Form)
        self.label_16.setGeometry(QtCore.QRect(460, 210, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_16.setFont(font)
        self.label_16.setObjectName("label_16")
        self.label_17 = QtWidgets.QLabel(Form)
        self.label_17.setGeometry(QtCore.QRect(460, 260, 201, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_17.setFont(font)
        self.label_17.setObjectName("label_17")
        self.lineEdit_5 = QtWidgets.QLineEdit(Form)
        self.lineEdit_5.setGeometry(QtCore.QRect(670, 170, 71, 25))
        self.lineEdit_5.setObjectName("lineEdit_5")
        self.label_18 = QtWidgets.QLabel(Form)
        self.label_18.setGeometry(QtCore.QRect(750, 170, 91, 31))
        self.label_18.setObjectName("label_18")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "博弈模拟器"))
        self.label.setText(_translate("Form", "少数派博弈模拟器"))
        self.label_2.setText(_translate("Form", "作者：熊倩 黄力"))
        self.label_3.setText(_translate("Form", "版本：1.0"))
        self.label_4.setText(_translate("Form", "用户不参与博弈："))
        self.label_6.setText(_translate("Form", "用户参与博弈："))
        self.label_5.setText(_translate("Form", "请指定以下参数："))
        self.pushButton.setText(_translate("Form", "查看结果"))
        self.label_7.setText(_translate("Form", "迭代步数："))
        self.label_8.setText(_translate("Form", "博弈者数量："))
        self.label_9.setText(_translate("Form", "记忆长度："))
        self.label_10.setText(_translate("Form", "策略个数："))
        self.label_11.setText(_translate("Form", "博弈者数量："))
        self.label_12.setText(_translate("Form", "策略个数："))
        self.label_13.setText(_translate("Form", "记忆长度："))
        self.label_14.setText(_translate("Form", "请指定以下参数："))
        self.pushButton_2.setText(_translate("Form", "指定参数"))
        self.label_15.setText(_translate("Form", "查看博弈者i的信息："))
        self.pushButton_3.setText(_translate("Form", "待家里"))
        self.pushButton_4.setText(_translate("Form", "去酒吧"))
        self.pushButton_5.setText(_translate("Form", "终止博弈"))
        self.pushButton_6.setText(_translate("Form", "查看"))
        self.label_16.setText(_translate("Form", "查看个人信息："))
        self.label_17.setText(_translate("Form", "查看全局信息："))
        self.label_18.setText(_translate("Form", "（输入i）"))

    def Onpushbutton(self):         #响应函数
        T = self.lineEdit.text()
        N = self.lineEdit_2.text()
        m = self.lineEdit_3.text()
        s = self.lineEdit_4.text()
        self.close()
        os.system('python draw.py' + ' ' + T + ' ' + N + ' ' + m + ' ' + s)

    def Onpushbutton_2(self):      # bulid simulation environment
        #for simulation（default arguments）
        T = 20
        N = self.lineEdit_8.text()
        m = self.lineEdit_6.text()
        s = self.lineEdit_7.text()
        self.T = T # number of steps to run each time
        self.N = N # number of Agents
        self.m = m # memory length
        self.s = s # number of strategies for each Agent
        self.Agents = [Agent(s, m) for _ in range(self.N)] # initialize the Agents
        self.W = [random.choice([-1,1]) for _ in range(self.m)] # initialize global info (i.e. the winning actions)
        self.A = [] # actions sum list

    def Onpushbutton_3(self):
        state = int(''.join([str(sign(x + 1)) for x in self.W[-self.m:]]), 2)
        for u in self.Agents: u.act(state)
        self.Agents[0].action= -1
        a = sum(array([u.action for u in self.Agents]))
        self.A.append(a)
        self.W.append(random.choice([-1, 1]) if a == 0 else -int(sign(a)))
        for u in self.Agents: u.update(self.W[-1])
        myshow.textBrowser.append('您选择待在家里。')

    def Onpushbutton_4(self):
        state = int(''.join([str(sign(x + 1)) for x in self.W[-self.m:]]), 2)
        for u in self.Agents: u.act(state)
        self.Agents[0].action = 1
        a = sum(array([u.action for u in self.Agents]))
        self.A.append(a)
        self.W.append(random.choice([-1, 1]) if a == 0 else -int(sign(a)))
        for u in self.Agents: u.update(self.W[-1])
        myshow.textBrowser.append('您选择去酒吧。')

    def Onpushbutton_5(self):

        print(1)

    def Onpushbutton_6(self):
        i=int(self.lineEdit_5.text())

        if(i>=self.N):
            myshow.textBrowser.append('i超出博弈者个数。')
        else:
            myshow.textBrowser.append('i号博弈者策略：')
            for x in range(self.s):
                myshow.textBrowser.append(self.Agents[i].Strgies[x].rules)
            myshow.textBrowser.append('人员差分历史记录：')
            myshow.textBrowser.append(self.A)
            myshow.textBrowser.append('胜利行为历史记录：')
            myshow.textBrowser.append(self.W)


class mywindow(QtWidgets.QWidget,Ui_Form):      #实例化窗口
    def __init__(self):
        super(mywindow,self).__init__()
        self.setupUi(self)                      #绘制界面
        self.pushButton.clicked.connect(self.Onpushbutton)      #对事件和响应函数建立连接
        self.pushButton_2.clicked.connect(self.Onpushbutton_2)
        self.pushButton_3.clicked.connect(self.Onpushbutton_3)
        self.pushButton_4.clicked.connect(self.Onpushbutton_4)
        self.pushButton_5.clicked.connect(self.Onpushbutton_5)
        self.pushButton_6.clicked.connect(self.Onpushbutton_6)

app = QtWidgets.QApplication(sys.argv)
myshow = mywindow()
myshow.show()
sys.exit(app.exec_())

#if __name__=="__main__":    #文件主函数入口
