'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2024-01-05 21:31:38
LastEditors: TheiiKu
LastEditTime: 2024-01-11 16:43:01
afterAnnotation: CRATED IN JLU SENSOR LAB
'''
from PyQt5 import QtCore, QtGui, QtWidgets
import main
import sys
from UiComSetting import Ui_ComSetting

class ComSettingPage(QtWidgets.QMainWindow ,  Ui_ComSetting):
    #降低耦合，使用信号->槽方式通信
    Signal_COM = QtCore.pyqtSignal(int)
    Signal_Baudrate = QtCore.pyqtSignal(int)

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.addComDescription()
        self.clearComboBox()
        main.COMBuffer.getCOMInfo()
        self.refreshCom()
    def refreshCom(self):
        #配置串口端口
        if self.comboBoxCOM.currentText():
            main.COMBuffer.COMPort = main.COMBuffer.SerialDevices[self.comboBoxCOM.currentIndex()]
            main.COMBuffer.COMNum  = main.COMBuffer.SerialID[self.comboBoxCOM.currentIndex()][0]
        pass
    def setBaudrate(self):
        #配置串口波特率
        if self.comboBoxBaudrate.currentText():
            main.COMBuffer.Baudrate =int(self.comboBoxBaudrate.currentText())
        pass
    def setCom(self):
        #发射信号
        self.Signal_COM.emit(int(main.COMBuffer.COMNum))
        self.Signal_Baudrate.emit(int(main.COMBuffer.Baudrate))
        self.close()
        pass
    def reject(self):
        self.clearComboBox()
        main.COMBuffer.COMPort = None
        main.COMBuffer.Baudrate = None        
        pass

    def addComDescription(self):
        #添加串口信息到下拉框
        self.comboBoxCOM.addItems(main.COMBuffer.SerialDescription)
        pass
    
    def clearComboBox(self):
        #下拉框默认为空
        self.comboBoxBaudrate.setCurrentIndex(-1)
        self.comboBoxCOM.setCurrentIndex(-1)
        pass