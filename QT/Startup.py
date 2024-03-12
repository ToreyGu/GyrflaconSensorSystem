'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2023-11-24 14:52:41
LastEditors: TheiiKu
LastEditTime: 2024-02-20 21:01:40
afterAnnotation: CRATED IN JLU SENSOR LAB
'''
import typing
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
from PyQt5.QtCore import QObject, QTimerEvent,QTimer, Qt ,QThread , pyqtSignal , QBasicTimer
from PyQt5.QtWidgets import QWidget
from UiWelcome import Ui_Welcome

from time import sleep

"""
开机界面Ui

开机
                      并发执行
processBar animation ->Thread 1 ->task 1 
           emit()    <-         ->task 2 
                                ->task 3
ProcessBar full

main Page


"""

from enum import Enum

#状态码枚举
class LicInitStatus(Enum):
    
    checkStart              = 0 
    checkLicenceStart       = 1
    licenceAvailable        = 2 
    licenceNotAvailable     = 3 
    encodingMachineStart    = 4 
    encodingMachineFinish   = 5
    decodingLicenceStart    = 6
    decodingLicenceFinish   = 7

class WelcomePage(QtWidgets.QMainWindow ,  Ui_Welcome ):
    def __init__(self) :
        super().__init__()
       
        self.setupUi(self)
        
        #透明化
        self.setAttribute(Qt.WA_TranslucentBackground, True)
        #无框
        self.setWindowFlags( Qt.FramelessWindowHint)

        self.InitProgram()

        self.processTimer = QTimer()
        self.processTimer.timeout.connect(self.TimerAddStep)
        #_________________varis______________________
        self.step  = 0 #进度条计数变量

    def InitProgram(self):
        self.threadInit = InitThread()
        #进度动画
        self.threadInit.LicenceAvailableSignal.connect(self.updateProcessbar)
        #打开页面
        self.threadInit.OpenPageSiganl.connect(self.EnterPage)
        self.threadInit.start()

        pass
    #检测是否有licence
    def updateProcessbar(self , statuscode):

        self.progressBarLoad.setValue(self.step)
        if statuscode == 0 :
            self.processTimer.start(20)
            #self.processTimer.timeout.connect(self.timerEvent)
            self.labelinfo.setText("Checking Necessary File ...")
            pass
        
        if statuscode == 1 :
            self.step = 0
            self.processTimer.start(10)
            self.labelinfo.setText("Prepare Peripheral ...")
            pass
        
    def ReadLicenceAvailable(self):
        self.progressBarLoad.setValue(self.step)  # 设置进度条的值
        if self.step < 100:
            self.step += 1
        pass

    #进入主程序
    def EnterPage(self , statuscode):
        #关闭过场动画
        self.close()
        
        if statuscode:
            import main
            self.page = main.MainPage()
            self.page.show()
        else :
            import ActiveSoftware
            self.page = ActiveSoftware.ActiveSoftwarePage()
            self.page.show()
        pass
    
    def TimerAddStep(self):
        self.progressBarLoad.setValue(self.step)  # 设置进度条的值
        if self.step < 100:
            self.step += 1
        pass
class InitThread(QThread):
    #定义信号
    #licence检测
    #传回状态码

    LicenceAvailableSignal = pyqtSignal(int)
    OpenPageSiganl = pyqtSignal(int)
      

    def __init__(self) -> None:
        super().__init__()

    #线程实际操作过程
    def run(self) -> None:
        self.taskCheckLicAvailable()
        pass
        

    def taskCheckLicAvailable(self):


       self.LicenceAvailableSignal.emit(0)

       QThread.sleep(1)
       #from LicenceCheck import LicenceChecker
       #checker = LicenceChecker()

       self.LicenceAvailableSignal.emit(1)

       self.taskPreparePeripheral()

       #self.OpenPageSiganl.emit(checker.Available)
       self.OpenPageSiganl.emit(1)
       pass

    def taskPreparePeripheral(self):
       sleep(3)
       pass

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    my_pyqt_form = WelcomePage()
    my_pyqt_form.show()
    sys.exit(app.exec_())