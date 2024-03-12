'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2023-11-23 21:58:20B
LastEditors: TheiiKu
LastEditTime: 2024-01-10 19:02:22
afterAnnotation: CRATED IN JLU SENSOR LAB
'''
from PyQt5 import QtCore, QtGui, QtWidgets
import sys

from ui.UiActiveSoftware import Ui_ActiveSoftware

from swdrivers.LicenceCheck import LicenceChecker

import rsa
import wmi
import hashlib

import base64
import hashlib
from pyDes import *

import json
import time


class ActiveSoftwarePage(QtWidgets.QMainWindow ,  Ui_ActiveSoftware ):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.check = LicenceChecker()
        self.MACHINECODE.setText(self.check.MachineCode)

    def ActiveSoftware(self):
        #重新加载licence
        self.check.CheckAll()
        if self.check.Available :
            self.label.setText("Active Success !")
            self.labelTimeRemain.setText(str(self.check.LicenceAvailableRemain) +' REMAIN')
            import main
            self.page = main.MainPage()
            self.page.show()
        else :
            self.label.setText("Invalid Licence !")
        pass




    
