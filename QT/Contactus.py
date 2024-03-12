'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2023-11-23 20:37:31
LastEditors: TheiiKu
LastEditTime: 2024-01-17 15:14:20
afterAnnotation: CRATED IN JLU SENSOR LAB
'''
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
from UiContactUs import Ui_ContactUs

class ContactPage(QtWidgets.QMainWindow ,  Ui_ContactUs):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        
    def openGithub(self):

        import webbrowser
        webbrowser.open("https://github.com/ToreyGu")
        pass
    def openLabweb(self):
        import webbrowser
        webbrowser.open("https://sensors.jlu.edu.cn/")
        pass