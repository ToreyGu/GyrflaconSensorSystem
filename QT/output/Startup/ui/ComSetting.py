from PyQt5 import QtCore, QtGui, QtWidgets
import sys
from ui.UiContactUs import Ui_ContactUs

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