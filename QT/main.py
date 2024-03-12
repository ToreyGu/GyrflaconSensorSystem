'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2023-11-23 15:59:27
LastEditors: TheiiKu
LastEditTime: 2024-01-18 19:22:31
afterAnnotation: CRATED IN JLU SENSOR LAB

'''
import queue
import json

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtChart import QDateTimeAxis,QValueAxis,QSplineSeries,QChart,QChartView
from PyQt5.QtCore import QObject, QThread , pyqtSignal
from PyQt5.QtCore import QDateTime,Qt,QTimer

from PyQt5.QtWidgets import QMessageBox
import sys

from hwdrivers.SerialCom import COMHost

from UiMainwindow import Ui_MainWindow

import numpy as np

import os

import joblib



class SensorThread(QThread):
    #创建信号
    SensorSignal = pyqtSignal(str)
    
    def __init__(self):
        super().__init__() 
        #线程控制变量
        self.RunThread = True 

    def run(self):
        SeneorSingalStream = ''
        COMBuffer.alignCOMBuffer()
        
        """ 业务代码 """
        while self.RunThread:
            SeneorSingalStream = COMBuffer.getCOMBuffer()
            self.SensorSignal.emit(SeneorSingalStream)

    def stop(self):
        self.RunThread = False

class MachineLearningThread(QThread):
    #创建信号
    MlSignal = pyqtSignal(str)
    
    def __init__(self):
        super().__init__() 
        #线程控制变量
        self.RunThread = True 
        self.Model = None
        self.input = None
        #输入模型的响应
        self.ValueCH1 = None
        self.ValueCH2 = None
        self.ValueCH3 = None

    def run(self):
        
        if os.path.exists('model/model.pkl') :
            model = joblib.load('model/model.pkl')
            result = model.predict(self.CalCharacter())
            self.MlSignal.emit(str(result))
            pass
    def CalCharacter(self):
        character1 = self.CharacterDiv(self.ValueCH2,self.ValueCH1)
        character2 = self.CharacterDiv(self.ValueCH3,self.ValueCH2)
        character3 = self.CharacterDiv(self.ValueCH3,self.ValueCH1)
        character4 = self.CharacterDiv(self.ValueCH2 * self.ValueCH2,self.ValueCH1* self.ValueCH3)
        character5 = self.CharacterDiv(self.ValueCH3 * self.ValueCH3,self.ValueCH1* self.ValueCH2)
        character6 = self.CharacterDiv(self.ValueCH1 * self.ValueCH1,self.ValueCH2* self.ValueCH3)
        character7 = self.CharacterDiv(self.ValueCH2 * self.ValueCH2,self.ValueCH1)
        character8 = self.CharacterDiv(self.ValueCH3 * self.ValueCH3,self.ValueCH2)
        character9 = self.CharacterDiv(self.ValueCH3 * self.ValueCH3,self.ValueCH1)
        Input = np.array([character1 , character2 , character3 , character4 , character5  , character6 , character7 , character8 , character9])
        Input = Input.reshape(1, -1)
        return Input
        

    #防止除以0
    def CharacterDiv(self , val1 , val2):
        if val2 == 0:
            return 0 
        else :
            return val1/val2
        
class AnalyseThread(QThread):
    #创建信号
    AnalyseResultSignal = pyqtSignal(str)
    AnalyseSpeciesSignal = pyqtSignal(int)
    AnalyseConfidenceSignal = pyqtSignal(float)
    def __init__(self):
        super().__init__() 
        
    def run(self):
        result = self.MachineLearningnalyse()
        self.AnalyseResultSignal.emit(result)

    def MachineLearningnalyse(self):
        #todo
        #这里接入Sklearn模型分析，并返回字符串数据

        pass


class MainPage(QtWidgets.QMainWindow ,  Ui_MainWindow ):
    #定义串口硬件对象的全局变量
    global COMBuffer 
    COMBuffer = COMHost()

    def __init__(self):
        

        super().__init__()
        self.setupUi(self)
        COMBuffer.getCOMInfo()
        self.pushButtonOpenCOM.setEnabled(True)
        self.pushButtonCloseCom.setEnabled(False)
        #用于主程序调度的线程缓存对象
        self.Mainthread = QThread()
        #传感器测量线程
        self.SensorThread_WORK = SensorThread()
        #移动传感器线程到总线程
        #线程启动操作
        #FatherThread   -> ChildThread1.run 
        #               -> ChildThread2.run
        self.SensorThread_WORK.moveToThread(self.Mainthread)

        #创建传感器线程信号对应的槽
        #signal -> handelsignal 
        self.SensorThread_WORK.SensorSignal.connect(self.HandelSensorResult)
        
        #机器学习线程
        self.MachineLearningThread_WORK = MachineLearningThread()
        self.MachineLearningThread_WORK.MlSignal.connect(self.HandelMlResult) 


        #定时刷新曲线
        self.ChartTimeScale = 60 
        self.ChartValueScale = 0
        self.ChartTimeStart = 0
        self.IntervalChartRefresh = 1000
        self.TimerChart = QTimer(self)
        self.TimerChart.timeout.connect(self.UpdateChartGraph)
        #FIFO 数据定义
        self.FIFOSize = 300
        self.FIFOSensorData_CH1 = []
        self.FIFOSensorData_CH2 = []
        self.FIFOSensorData_CH3 = []
        #滑动窗口缓存
        self.WindowSensorData_CH1 = []
        self.WindowSensorData_CH2 = []
        self.WindowSensorData_CH3 = [] 

        #信号偏置
        self.BiasCH1 = 0
        self.BiasCH2 = 0
        self.BiasCH3 = 0

        self.ChartInit()

        self.SetTimeScaleLabel()
        self.CheckModelEexist()

        self.pushButtonAnalyse.setEnabled(False)
    def CheckModelEexist(self):
        if not os.path.exists('model/'): #判断所在目录下是否有该文件名的文件夹
            os.mkdir('model/') 
            self.pushButtonAnalyse.setEnabled(False) 
            msg_box = QMessageBox(QMessageBox.Critical, 'Model Error', 'No model file in model dir !')
            msg_box.exec_()
        else :  
            if os.path.exists('model/model.pkl') :
                self.pushButtonAnalyse.setEnabled(True)
            else :
                self.pushButtonAnalyse.setEnabled(False) 
                msg_box = QMessageBox(QMessageBox.Critical, 'Model Error', 'No model file in model dir !')
                msg_box.exec_()

    def FIFOUpdate(self , FIFOList , FIFOData):
        if len(FIFOList) <= self.FIFOSize:
            FIFOList.append(FIFOData)
        else :
            #防止数据溢出导致全部FIFO被删除
            del FIFOList [0:len(FIFOList) - self.FIFOSize + 1]
            FIFOList.append(FIFOData)
    #启动线程
    def StartMainthread(self):
        self.SensorThread_WORK.start(self.IntervalChartRefresh)
    #关闭线程
    def StopMainthread(self):
        self.SensorThread_WORK.terminate()
    
    #传感线程回调函数
    def HandelSensorResult(self , str):
        self.UpdateChartData(str)

    #机器学习回调函数
    def HandelMlResult(self , str ):
        print(str)
        if str == '[1]':
            self.labelResult.setText('Propanol')
        if str == '[3]':
            self.labelResult.setText('Acetone')
        if str == '[4]':
            self.labelResult.setText('Isoprene')
        if str == '[5]':
            self.labelResult.setText('Formaldehyde')
        if str == '[6]':
            self.labelResult.setText('Pentane')
        if str == '[7]':
            self.labelResult.setText('AceticAcid')
    #实时曲线控件
    def ChartInit(self):
        #创建图表
        self.TimeScale = self.ChartTimeScale
        self.ValueScale = self.ChartValueScale
        self.chartSensor = QChart()
        self.chartSensor.setGeometry(50, 30, 671, 411)
        #添加实时曲线对象
        self.SeriesSeneor_CH1 = QSplineSeries()
        self.SeriesSeneor_CH1.setUseOpenGL(True)
        self.SeriesSeneor_CH1.setName("Sensor Channel 1 ")

        self.SeriesSeneor_CH2 = QSplineSeries()
        self.SeriesSeneor_CH2.setUseOpenGL(True)
        self.SeriesSeneor_CH2.setName("Sensor Channel 2 ")

        self.SeriesSeneor_CH3 = QSplineSeries()
        self.SeriesSeneor_CH2.setUseOpenGL(True)
        self.SeriesSeneor_CH3.setName("Sensor Channel 3 ")
        #添加曲线到图表
        self.chartSensor.addSeries(self.SeriesSeneor_CH1)
        self.chartSensor.addSeries(self.SeriesSeneor_CH2)
        self.chartSensor.addSeries(self.SeriesSeneor_CH3)
        #建立X轴Y轴
        self.axisX = QValueAxis()
        self.axisY = QValueAxis()
        #设定坐标轴范围
        self.axisX.setMin(self.ChartTimeStart)
        self.axisX.setMax(self.TimeScale)
        self.axisY.setMin(self.ValueScale)	
        self.axisY.setMax(10) #设置y轴最大值
        #添加坐标轴
        self.chartSensor.addAxis(self.axisX,Qt.AlignBottom)
        self.chartSensor.addAxis(self.axisY,Qt.AlignLeft)
        #曲线绑定坐标轴
        self.SeriesSeneor_CH1.attachAxis(self.axisX)
        self.SeriesSeneor_CH1.attachAxis(self.axisY)
        self.SeriesSeneor_CH2.attachAxis(self.axisX)
        self.SeriesSeneor_CH2.attachAxis(self.axisY)
        self.SeriesSeneor_CH3.attachAxis(self.axisX)
        self.SeriesSeneor_CH3.attachAxis(self.axisY)

        #显示图表，需要先在QTdesigner里升格
        self.ChartSensor.setChart(self.chartSensor)
        pass
    #更新曲线
    def UpdateSeries(self):

        self.SeriesSeneor_CH1.clear()
        self.SeriesSeneor_CH2.clear()
        self.SeriesSeneor_CH3.clear()
        
        self.RefreshSeries(self.FIFOSensorData_CH1 , self.SeriesSeneor_CH1)
        self.RefreshSeries(self.FIFOSensorData_CH2 , self.SeriesSeneor_CH2)
        self.RefreshSeries(self.FIFOSensorData_CH3 , self.SeriesSeneor_CH3)

    def RefreshSeries(self , FIFOSensorData , SeriesSeneor):
            for i in range(len(FIFOSensorData)):
                SeriesSeneor.append(i , FIFOSensorData[i])

    #信息页面
    def OpenSysinfo(self):
        #必须加self，不然不会接入主线程，窗口闪退

        import SystemInfo
        self.page = SystemInfo.SystemPage()
        self.page.show()
        pass
    
    def OpenContactus(self):
        
        #必须加self，不然不会接入主线程，窗口闪退

        import Contactus

        self.page = Contactus.ContactPage()
        self.page.show()

        pass
    def OpenActiveSoftware(self):
        import ActiveSoftware
        
        self.page = ActiveSoftware.ActiveSoftwarePage()
        self.page.show()
        pass

    def OpenCOMSetting(self):
        import ComSetting
        self.page = ComSetting.ComSettingPage()
        #连接该页面发射信号对应的槽
        self.page.Signal_COM.connect(self.ExternalSetLCDCOM)
        self.page.Signal_Baudrate.connect(self.ExternalSetLCDBaudrate)  

        self.page.show()
        pass
    
    #供其他页面调用的函数，用于更改LCD数值
    def ExternalSetLCDCOM(self,COMNum):
        self.lcdNumberCOM.display(COMNum)
        pass
    
    def ExternalSetLCDBaudrate(self,Baudrate ):
        self.lcdNumberBaudrate.display(Baudrate)
        pass
    
    def ConnectCOM(self):
        #判断是否配置串口参数
        if((not (COMBuffer.COMPort is None)) and (not (COMBuffer.Baudrate is None))):
            self.StartMeasuring()            
        else:
            #警告框
            msg_box = QMessageBox(QMessageBox.Critical, 'Hardware error', 'You have not config your COM correctly , please check your COM settings and signal cable connection.')
            msg_box.exec_()

    def DisconnectCOM(self):
        self.StopMeasuring()
    
    #按键控件
        
    #开始测量
    def StartMeasuring(self):
        
        COMBuffer.openCOMPort()
        self.pushButtonOpenCOM.setEnabled(False)
        self.pushButtonCloseCom.setEnabled(True)
        self.pushButtonAnalyse.setEnabled(True)
        self.TimerChart.start()
        self.StartMainthread()
    #结束测量
    def StopMeasuring(self):
        COMBuffer.closeSerial()
        self.pushButtonOpenCOM.setEnabled(True)
        self.pushButtonCloseCom.setEnabled(False)
        self.TimerChart.stop()
        self.StopMainthread()

    def AnalyseChart(self):
        self.WindowSensorData_CH1 = self.GetWindowData(self.FIFOSensorData_CH1)
        self.WindowSensorData_CH2 = self.GetWindowData(self.FIFOSensorData_CH2)
        self.WindowSensorData_CH3 = self.GetWindowData(self.FIFOSensorData_CH3)
        #debug
        if (self.WindowSensorData_CH1 is not None) and (self.WindowSensorData_CH2 is not None) and (self.WindowSensorData_CH3 is not None):
 
        #这里接机器学习线程
            self.MachineLearningThread_WORK.ValueCH1 = min(self.WindowSensorData_CH1)
            self.MachineLearningThread_WORK.ValueCH2 = min(self.WindowSensorData_CH2)
            self.MachineLearningThread_WORK.ValueCH3 = min(self.WindowSensorData_CH3)
            self.MachineLearningThread_WORK.start()
        pass
    def GetWindowData(self ,FIFOSensorData) :
        if(self.ChartTimeStart) < len(FIFOSensorData):
            WindowData = FIFOSensorData[ int(self.ChartTimeStart) : min(len(FIFOSensorData),self.ChartTimeScale)]
        else:
            WindowData = []
            msg_box = QMessageBox(QMessageBox.Critical, 'No data input error', 'No Data in Chart')
            msg_box.exec_()
        return WindowData
    #仪表旋钮控件函数
    def SetTimeScale(self,TimeScale):
        self.ChartTimeScale = TimeScale
        self.ChartInit()
        self.SetTimeScaleLabel()

    def SetTimeScaleLabel(self):
        self.labelTimeScale.setText(str(self.ChartTimeScale))

    def SetTimeStart(self , TimeStart ):
        self.ChartTimeStart = self.ChartTimeScale * TimeStart/100
        self.ChartInit()

    def SetValueScale(self , ValueScale):
        self.ChartValueScale =0 - ValueScale
        self.ChartInit()

    #解码数据流
    def DecodeJson(self , jsonstream):
        stream = json.loads(jsonstream)
        if(stream['cmd'] == 'VAL1'):
            self.FIFOUpdate(self.FIFOSensorData_CH1 , float(stream['data']) + self.BiasCH1)
            self.labelCH1.setText(str(stream['data']+ self.BiasCH1))
        if(stream['cmd'] == 'VAL2'):
            self.FIFOUpdate(self.FIFOSensorData_CH2 , float(stream['data']) + self.BiasCH2)
            self.labelCH2.setText(str(stream['data']+ self.BiasCH2))
        if(stream['cmd'] == 'VAL3'):
            self.FIFOUpdate(self.FIFOSensorData_CH3 , float(stream['data']) + self.BiasCH3)
            self.labelCH3.setText(str(stream['data']+ self.BiasCH3))
        if(stream['cmd'] == 'CHT'):
            self.progressBarChipTemp.setValue(float(stream['data']))
        return stream
    #将数据流更新到缓存区
    def UpdateChartData(self,jsonstream):
        self.DecodeJson(jsonstream)
        pass
    
    #更新曲线
    def UpdateChartGraph(self):
        self.UpdateSeries()
        pass

    def SetBiasVal(self):
        #先减去偏置电压，恢复数据
        self.FIFOSensorData_CH1 = self.RefreshBias(self.FIFOSensorData_CH1 ,0 - self.BiasCH1 )
        self.FIFOSensorData_CH2 = self.RefreshBias(self.FIFOSensorData_CH2 ,0 - self.BiasCH2 )
        self.FIFOSensorData_CH3 = self.RefreshBias(self.FIFOSensorData_CH3 ,0 - self.BiasCH3 )
        #再加上偏置电压，产生新数据
        self.BiasCH1 = self.doubleSpinBoxCH1.value()
        self.BiasCH2 = self.doubleSpinBoxCH2.value()
        self.BiasCH3 = self.doubleSpinBoxCH3.value()
        self.FIFOSensorData_CH1 = self.RefreshBias(self.FIFOSensorData_CH1 ,self.BiasCH1 )
        self.FIFOSensorData_CH2 = self.RefreshBias(self.FIFOSensorData_CH2 ,self.BiasCH2 )
        self.FIFOSensorData_CH3 = self.RefreshBias(self.FIFOSensorData_CH3 ,self.BiasCH3 )
        pass

    def RefreshBias(self , FIFOSensorData , Bias):
        result = [] 
        for data in FIFOSensorData:
            new_FIFOSensorData = data + Bias
            result.append(new_FIFOSensorData)
        return result
