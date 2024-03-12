#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@filename              :Untitled-1.ipynb
@createFileTime        :2023/06/27 16:59:30
@author                :Torey Gu 
@version               :1.0
@description           :

'''


import serial
import pandas as pd
from numpy import empty 
from numpy import empty 
from numpy import delete
from time import strftime , localtime , time
from openpyxl import load_workbook
import serial.tools.list_ports 
import re
import json

class COMHost():
    def __init__(self ):
        super(COMHost, self).__init__()

        self.COMPort                = None          #   Serial port number "COM_x" in WINDOWS "ttyS_x" in linux
        self.Baudrate               = None          #   Baudrate of peripheral Device(string)
        self.DataDir                = './data'      #   dataset Path
        self._Serial                = None          #   A Serial.serial() instance used in This class
        self.COMNum                 = None
        self.SerialDevices          = []            #   all connected COM Number in computer
        self.SerialDescription      = []            #   Description of every Com devices
        self.SerialID               = []            #   Pure COM Number for QT 
        self._SerialOpenFlag        = False         #   The Serial Open Flag
        self._SerialBufferLength    = 123           #   Buffer Length in our Communication protocol
        self._SerialBufferData      = None    #   The actual data contents of the buffer
        self._SerialBufferFlag      = False         #   The buffer receives information flag 
        self._SerialFile            = None          #   file name of dataset
        self._SerialFileFlag        = False         #   The File receives information flag
        self._SerialStreamFlag      = False         #   Data transfer mode flag : 0 for Singal Mode , 1 for Stream Mode

    def getCOMInfo(self):
        # get Com Number and Com description
        # [Com DEVICE ],[ Com Number ],[Com Description]
        comlist = serial.tools.list_ports.comports()   
        i = 0
        
        self.SerialDevices.clear()            #   all connected COM Number in computer
        self.SerialDescription.clear()           #   Description of every Com devices
        self.SerialID.clear()          
        
        for i in range(len(comlist)):
            self.SerialDevices.append(comlist[i].device)    
            self.SerialDescription.append(comlist[i].description)      
            self.SerialID.append(re.findall("\d+\.?\d*",comlist[i].device))       
        return self.SerialDevices , self.SerialID , self.SerialDescription
    
    def openCOMPort(self ):
        #self.COMPort     =  COMPort
        #self.Baudrate    =  Baudrate
        # open COM port 
        self._Serial  = serial.Serial(self.COMPort, int(self.Baudrate))
        
        if self._Serial.isOpen(): 
                self._Serial.write("uu".encode('utf-8'))
                self._SerialOpenFlag = True
                print(self.COMPort ,'OPEN SUCCESS')
        else :
            print(self.COMPort ,'OPEN Failed')

    def openCOMPortManual(self ,  COMPort, Baudrate):
        #self.COMPort     =  COMPort
        #self.Baudrate    =  COMPort
        # open COM port 
        self._Serial  = serial.Serial(COMPort, Baudrate)
        
        if self._Serial.isOpen(): 
                self._Serial.write("uu".encode('utf-8'))
                self._SerialOpenFlag = True
                print(COMPort ,'OPEN SUCCESS')
        else :
            print(COMPort ,'OPEN Failed')



    #this Function must run alignCombuffer() befor it was invoked
    #this function only run once when it was invoked , it must run in a loop to make sure datastream is real-time stream
    """
    EXAMPLE:

    def openDataStream():
        COM.alignCOMBuffer()
        while FLAG_ON is True:
            COM.getCOMBuffer()
            process(COM._SerialBufferData)
    """

    #run this function before entering the loop of getting buffer 
    def alignCOMBuffer(self):
        while  self._Serial.read() != b'\r':
            #trap loop ，do nothing until next data stream come
            pass

    def getCOMBuffer(self):
        buffer = ''
        # Filte data based on communication protocols and available Buffer Flag
        #process program , load every byte to buffer until '\r' '\n' apperad
        while True:
            com_input = self._Serial.read()
            if com_input != b'\r' :   
                buffer = buffer + str(com_input, encoding='utf-8')
            else:
                self._Serial.read()
                #send buffer
                self._SerialBufferData = buffer
                #clear buffer 
                #self.analyzeCOMBuffer()
                break
        return buffer

    #a function to analyze Buffer format , add project protocol here  
    def analyzeCOMBuffer(self):
        self._SerialBufferData = json.loads(self._SerialBufferData)
        pass


    def getStreamStatus(self):
        #get device Data Status (Stream/Single -> True/Flase)
        if self._SerialBufferData[7] == 49:
            self._SerialStreamFlag = True
            return True
        else : 
            self._SerialStreamFlag = False
            return False
        
    def setFile(self):
        # Name the dataset file using system local time (Y_m_d_H_M_S)
        Localtime = strftime('%Y_%m_%d_%H_%M_%S',localtime(time()))
        df=pd.DataFrame()
        self._SerialFile = self.DataDir +'/'+ Localtime +'.xlsx'
        df.to_excel(self._SerialFile)
        print('Done!!')

    def saveXlsxData(self , data):
        # Save a row of data to xlsx file
        original_data = pd.read_excel(self._SerialFile)
        data = pd.DataFrame(data)
        save_data = pd.concat([original_data, data], axis=0)
        save_data.to_excel(self._SerialFile, index=False)
        
    def setFileHead(self):
        #set a Filehead for dataset files
        self.setFile()
        datasetHeader       = {'u3value':[], 
                               'u4value':[], 
                               'u5value':[], 
                               'u6value':[], 
                               'u7value':[],
                               'u8value':[],
                               'humi':[],
                               'StreamMode':[],
                               'PictureName':[]}
        self.saveXlsxData(datasetHeader  )
        print('File Head Created')
        self.cleanCOMBuffer()

    def saveSerialData(self , Path):
        #save the Serial Buffer data to dataset file and zero the buffer flag
        self.getStreamStatus()
        datastream      =      {'u3value':[self._SerialBufferData[0]], 
                               'u4value':[self._SerialBufferData[1]], 
                               'u5value':[self._SerialBufferData[2]], 
                               'u6value':[self._SerialBufferData[3]], 
                               'u7value':[self._SerialBufferData[4]],
                               'u8value':[self._SerialBufferData[5]],
                               'humi':[self._SerialBufferData[6]],
                               'StreamMode':[self._SerialStreamFlag],
                               'PictureName':[Path]} 
        if (self._SerialBufferFlag):
            self.saveXlsxData(datastream)
        self.cleanCOMBuffer()
    
    def BufferIsReady(self):
        #get IF Buffer is ready  
        return self._SerialBufferFlag
    
    def closeSerial(self):
        #close the serial system
        self._Serial.close()
        self._SerialOpenFlag        = False
        print('Serial Closed')
