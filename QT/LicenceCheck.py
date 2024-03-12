'''
C++ FILES: 
Descripttion: 
version: 
Author: TheiiKu
Date: 2023-11-24 09:34:58
LastEditors: TheiiKu
LastEditTime: 2024-01-16 12:49:35
afterAnnotation: CRATED IN JLU SENSOR LAB
'''
import os
import time
import datetime
import datetime
import os
import wmi
import hashlib
from pyDes import des, PAD_PKCS5, ECB

import json
class LicenceChecker():
    def __init__(self):
        super().__init__()
        self.LicencePath     = "./LIC/Licence"
        self.CPU_Serial      = self.get_CPU_Serial()
        self.Mac_adress      = self.get_Mac_adress()
        self.Board_Serial    = self.get_Board_Serial()
        self.MachineCode     = self.get_MachineCode()
        self.SoftWare        = "Gyrflacon"
        self.LocalTime       = time.time()

        self.LicenceEnc         =   None
        self.LicenceDec         =   None
        
        self.LicenceMachineCode     = None
        self.LicenceStartTime       = None
        self.LicenceFinishTime      = None
        self.LicenceSoftWare        = None
        self.Available       = None
    
        self.LicenceAvailableRemain = None

        self.Des_key         = "!n@)H:Yd" 
        
        self.CheckAll()
    def get_CPU_Serial(self):
            m_wmi = wmi.WMI()
            cpu_info = m_wmi.Win32_Processor()
            if len(cpu_info) > 0:
                serial_number = cpu_info[0].ProcessorId
            
            return serial_number
    
    def get_Mac_adress(self):
            mac_buffer =''
            m_wmi = wmi.WMI()
            for network in m_wmi.Win32_NetworkAdapterConfiguration():
                mac_address = network.MacAddress
                if mac_address != None:
                    mac_buffer = mac_buffer + mac_address +','
      
            return mac_buffer
    
    def get_Board_Serial(self):
        m_wmi = wmi.WMI()
        disk_info = m_wmi.Win32_PhysicalMedia()
        if len(disk_info) > 0:
            serial_number = disk_info[0].SerialNumber.strip()
        return serial_number
    
    def get_MachineCode(self):
        ComputerInfo = self.CPU_Serial  + self.Board_Serial
        ComputerInfoByte = ComputerInfo.encode('UTF-8')
        #计算机唯一等长机器码
        MachineCode   =  hashlib.md5(ComputerInfoByte ).hexdigest()
        return MachineCode
    
    def CheckAll(self):
         self.CheckLicence()
         self.LicenceDecrypt()
         self.ReadLicence()
         self.EnableSoftware()
         return self.Available
    #检查是否有Licence -> 解码Licence
    def CheckLicence(self):
        if os.path.exists(self.LicencePath):
             
             with open(self.LicencePath, "r", encoding='UTF-8')as f:
                #读取密码
                self.LicenceEnc = f.read()
                #print(self.LicenceEnc)
                #暂时允许运行
                self.Available = True
                
                #解码Licence

             return True
        else :
             self.Available = False
             return False
    
    #解码Licence密码 -> 解析json
    def LicenceDecrypt(self):

        des_obj = des(self.Des_key, ECB, self.Des_key, padmode=PAD_PKCS5)
        
        if self.LicenceEnc:
            self.LicenceEnc= bytes.fromhex(self.LicenceEnc) # 这里中文要转成字节
            self.LicenceDec = des_obj.decrypt(self.LicenceEnc)  # 用对象的decrypt方法解密
            
            self.Available = True
            return self.LicenceDec

        else:
            self.Available = False
            return False
    #解析json -> 验证json
    def ReadLicence(self):
        if self.Available:
            LicenceDecBufer = json.loads(self.LicenceDec)
            self.LicenceMachineCode = LicenceDecBufer["MachineCode"]
            self.LicenceStartTime   = LicenceDecBufer["StartTime"]
            self.LicenceFinishTime  = LicenceDecBufer["FinTime"]
            self.LicenceSoftWare    = LicenceDecBufer["Software"]

           
            
             
    def EnableSoftware(self):
        #print('START :' , self.LicenceStartTime)
        #print('NOW   :' ,self.LocalTime)
        #print('FINISH:' ,self.LicenceFinishTime)
        if self.MachineCode == self.LicenceMachineCode:
            
            if self.LicenceStartTime  <= self.LocalTime <= self.LicenceFinishTime :
                self.LicenceAvailableRemain  = datetime.datetime.fromtimestamp(self.LicenceFinishTime) - datetime.datetime.fromtimestamp(self.LocalTime)   
                if self.SoftWare == self.LicenceSoftWare:
                    self.Available = True
                else:
                    print("software error")
                    self.Available = False
            else :
                print("LIC out of date")
                self.Available = False  
        else:
            print("machine is not registed")
            self.Available = False  


#print(check.CheckLicence())