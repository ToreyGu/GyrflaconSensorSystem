from PyQt5 import QtCore, QtGui, QtWidgets
import sys
from UiAboutSystem import Ui_AboutSystem


class SystemPage(QtWidgets.QMainWindow ,  Ui_AboutSystem):
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