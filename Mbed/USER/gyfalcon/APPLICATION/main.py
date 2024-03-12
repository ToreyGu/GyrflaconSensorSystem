#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@filename              :DataProcess.ipynb
@createFileTime        :2023/02/27 16:44:34
@author                :THEIIKU
@version               :1.0
@description           :A Data Process Program Based on Sklearn
Created in JLU SENSORLAB
'''

import sklearn
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import xlrd
from mpl_toolkits import mplot3d
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler
from sklearn.decomposition import PCA
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import precision_score, recall_score, f1_score, confusion_matrix, classification_report
from sklearn.model_selection import cross_val_score

import matplotlib.colors as mcolors

from sklearn import tree
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier

from tqdm import tqdm
from tqdm.auto import trange

class LoadData(object):
    # 定义一个载入xls文件的类
    def __init__(self):
        self._worksheet     = None
        self._accuracy      = None
        self._predict       = []
        self.debuginfo      = True
        
        self.dataStart              = 0 
        self.dataFinish             = 0
        self.dataDimension          = 0 

        self.dataSpeciesCode        = 0
        self.dataSpeciesName        = 0 

        self.MartixRaw              =None
        self.MartixPCA              =None
        self.MartixSpecies          =None
        self.MartixName             =None
        
    
        self.input_demision_extension   = False
        self.input_scaler               = StandardScaler()
        self.input_pca                  = True
        self.path   =   None
                         

    def loadWorkSheet(self , path):
        self.path = path
        self._worksheet = xlrd.open_workbook(self.path)

    def inputConfig(self , demision_extension = False , scaler  = False , pca = False):
        self.input_demision_extension = demision_extension
        self.input_scaler             = scaler
        self.input_pca                = pca

    def setDataRow(self , start ,finish):
        self.dataStart = start
        self.dataFinish = finish
        self.dataDimension = self.dataFinish - self.dataStart + 1

    def setSpeciesCode(self , spicesCode ):
        self.dataSpeciesCode = spicesCode
    
    def setSpeciesName(self , spicesName):
        self.dataSpeciesName = spicesName

    
    def getRow(self, row):
        cols = []
        sheet_names = self._worksheet.sheet_names()
        for sheet_name in sheet_names:
            sheet = self._worksheet.sheet_by_name(sheet_name)
            # 获取第二列内容， 数据格式为此数据的原有格式（原：字符串，读取：字符串；  原：浮点数， 读取：浮点数）
            cols.append(sheet.col_values(row))
            return np.array(cols)[:, 1:].T
    # 获取部分矩阵

    def loadMartix(self):
        self.MartixRaw      = self.getRangeMatrix(self.dataStart,self.dataFinish)
        self.MartixSpecies  = self.getRow(self.dataSpeciesCode)
        self.MartixName     = self.getRow(self.dataSpeciesName)
        self.MartixRaw =self.MartixRaw.astype(float)
        if self.input_demision_extension:
            self.MartixRaw = self.input_demision_extension.fit_transform(self.MartixRaw)
        if self.input_scaler:
            self.MartixRaw = self.input_scaler.fit_transform(self.MartixRaw) 
        if self.input_pca:
            self.MartixPCA = self.pcaData2D(self.MartixRaw,scaler=StandardScaler())
            pass

        self.MartixSpecies = self.MartixSpecies.astype(float)
        self.MartixSpecies = self.MartixSpecies.astype(int)
        
        self.MartixName =  self.MartixName.astype(str)

    
 

    def getPartMatrix(self, startPosition, steps=3, intervals=2):
        # 输入起始位置（startPosition） ， 步数（steps），和间隔（intervals）
        matrix = self.getRow(startPosition)
        for step in range(steps-1):
            matrix = np.hstack((matrix, self.getRow(
                startPosition + (step+1)*intervals)))
        return matrix
    # 获取完整矩阵

    def getMatrix(self, startPosition, steps=3, intervals=2):
        # 输入起始位置（startPosition） ， 步数（steps），和间隔（intervals）
        FullMatrix = self.getPartMatrix(startPosition, steps)
        for interval in range(intervals-1):
            FullMatrix = np.vstack(
                (FullMatrix, self.getPartMatrix(startPosition + interval+1)))
        return FullMatrix

    def getRangeMatrix(self, StartPosition, StopPosition):
        # 通过列数获得矩阵
        self.dataStart  =  StartPosition
        self.dataFinish   =  StopPosition
        self.dataDimension = self.dataFinish - self.dataStart +1
        rangeMatrix = self.getRow(StartPosition)
        while StartPosition < StopPosition:
            rangeMatrix = np.hstack(
                (rangeMatrix, self.getRow(StartPosition + 1)))
            StartPosition += 1
        return rangeMatrix

    def drawBundary(self,  data_input, model, pixel=50):
        # 画模型边界
        data_input1_max = max(data_input[:, 0])
        data_input1_min = min(data_input[:, 0])
        data_input2_max = max(data_input[:, 1])
        data_input2_min = min(data_input[:, 1])
        scanx = np.linspace(data_input1_min-1, data_input1_max+1, int(
            pixel*(data_input1_max-data_input1_min)))
        scany = np.linspace(data_input2_min-1, data_input2_max+1, int(
            pixel*(data_input2_max-data_input2_min)))
        predict = []
        for i in scany:
            temp = []
            for q in scanx:

                temp.append(model.predict([[q, i]])[0])

            predict.append(temp)
        plt.contourf(scanx, scany, predict, cmap=plt.cm.Accent, alpha=0.2)
        plt.show()

    def pcaData2D(self, matrix, scaler):
        # pca处理为2维数组
        matrix = scaler.fit_transform(matrix)
        pca = PCA(n_components=2)
        matrix = pca.fit_transform(matrix)
        # plt.scatter(matrix[:,0] , matrix[:,1])
        return matrix

    def attachMatrix(self, FrontMatrix, BackMatrix):
        # 拼接矩阵
        attachedMatrix = np.hstack((FrontMatrix, BackMatrix))
        return attachedMatrix

    def drawPcaScatters(self, fullMatrix, spicesList, title=None):
        # 绘制散点图
        # colors = list(mcolors.TABLEAU_COLORS.keys())
        '''
        for data in fullMatrix:
            plt.scatter(float(data[0]), float(
                data[1]), color=mcolors.TABLEAU_COLORS[colors[int(float(data[2]))]])
        '''

        '''
        df = pd.DataFrame(fullMatrix)
        df.plot.scatter(df[:,0], df[:,1], c=df[:,2], colormap='jet')
        '''
        width = 3

        pca1 = np.array(fullMatrix[:, 0]).astype(float)
        pca2 = np.array(fullMatrix[:, 1]).astype(float)
        # matpyplot.plt.scatter输入的数据必须是python的float类型
        # x ， y 坐标向量
        colors = fullMatrix[:, 2]
        spicesIndex = np.unique(fullMatrix[:, 3], return_index=True)[1]
        spicesIndex = np.sort(spicesIndex)
        # 必须先将索引排序，不然仍是顺序数组
        # print(spicesIndex)
        # 不排序，返回一个索引
        spicesName = []
        for i in range(len(spicesIndex)):
            index = spicesIndex[i]
            spicesName.append(fullMatrix[index, 3])
        plt.figure(figsize=(12, 9), dpi=300)
        # 画布大小的单位是inchs 默认dpi = 100 不要调大
        """
        plt.xlabel('PCA1')
        plt.ylabel('PCA2')
        """
        scatter = plt.scatter(pca1, pca2, c=[colors], cmap=plt.cm.Accent)
        # print(spicesName)
        # colors必须为2维，不然会报错
        # s是点的大小，下个版本放置在configs.py
        font1 = {'family': 'Times New Roman', 'weight': 'normal', 'size': 20}
        # scatter = plt.scatter(fullMatrix[:, 0].reshape(-1,1), fullMatrix[:, 1].reshape(-1,1), color=mcolors.TABLEAU_COLORS[colors[int(float(fullMatrix[:, 2]))]])
        plt.title(title)
        plt.legend(handles=scatter.legend_elements()[
                   0], labels=spicesName, prop=font1, loc='upper right')
        plt.yticks(fontproperties='Times New Roman', size=18)
        plt.xticks(fontproperties='Times New Roman', size=18)
        ax = plt.gca()  # 获得坐标轴的句柄
        ax.spines['bottom'].set_linewidth(width)
        ax.spines['left'].set_linewidth(width)
        ax.spines['top'].set_linewidth(width)
        ax.spines['right'].set_linewidth(width)

    def initCal(self):
        # 初始化内部变量
        if self._accuracy or self._predict is not None:
            self._accuracy = None
            self._predict = []

    def accuracyCal(self, fullMatrix, model):
        # 计算准确率
        self.initCal()
        accuracy = 0
        self._predict = model.predict(fullMatrix[:, 0:-2])
        for i in range(len(self._predict)):
            if self._predict[i] == fullMatrix[i, -1]:
                accuracy += 1
        self._accuracy = float(accuracy/len(self._predict))
        if self.debuginfo:
            print('Accuracy in %s model is: %3.2f Percent' %
                (model, (self._accuracy * 100)))

    def crossCal(self, fullMatrix, model, epoch=10):
        scores = cross_val_score(
            model, fullMatrix[:, 0:-2], fullMatrix[:, -1], cv=epoch)
        if self.debuginfo:
            print("Accuracy of %s model is: %0.2f (+/- %0.2f)" %
                (model, scores.mean(), scores.std() * 2))
        return scores.mean(), (2*scores.std())
    
    from tqdm import tqdm
    from tqdm.auto import trange
    def SVC_BEST_PARAMETER( self ,  c_interval = 0.2 , gamma_interval = 0.2 , c_start = 0.1 ,gamma_start = 0.1 ,c_step = 500 , gamma_step = 50 ):
        print("----------SEARCHING SVC BEST MODEL------------")
        self.debuginfo = False
        BEST_CVAL = 0
        BEST_GAMMA = 0
        BEST_ACCURATE = 0 
        input_martix = self.attachMatrix(self.MartixRaw, self.MartixSpecies)
        p_bar = tqdm(range(c_step), desc="SVC RBF BEST PARAMETER SCANING: ",  ncols=100)
        for i in p_bar :
            C_VALUE = c_start+c_interval*i
            for j in trange(gamma_step  ,desc= "STEP SCANING",leave=False):
                GAMMA_VALUE =gamma_start + gamma_interval*j
                svc_model = SVC(kernel='rbf', random_state=1,
                        gamma=GAMMA_VALUE, C=C_VALUE)
                svc_model.fit(self.MartixRaw, self.MartixSpecies[:,0])
                #print("C value : ", C_VALUE )
                crosscal = self.crossCal(input_martix , svc_model)
                if crosscal[0] > BEST_ACCURATE:
                    BEST_GAMMA = GAMMA_VALUE
                    BEST_ACCURATE = crosscal[0]
                    BEST_CVAL = C_VALUE
                
        print("SVC RBF SCAN Finished!")
        print("BEST C = ",BEST_CVAL ,"BEST GAMMA = ",BEST_GAMMA, "ACCURACY =" , BEST_ACCURATE )
        self.debuginfo = True

    def SVL_BEST_PARAMETER(self , c_interval = 0.2 , gamma_interval = 0.2 , c_start = 0.1 ,gamma_start = 0.1 ,c_step = 500 , gamma_step = 50 ):
        print("----------SEARCHING SVC BEST MODEL------------")
        self.debuginfo = False
        BEST_CVAL = 0
        BEST_GAMMA = 0
        BEST_ACCURATE = 0 
        input_martix = self.attachMatrix(self.MartixRaw, self.MartixSpecies)
        p_bar = tqdm(range(c_step), desc="SVC LIN BEST PARAMETER SCANING: ",  ncols=100)
        for i in p_bar :
            C_VALUE = c_start+c_interval*i
            for j in trange(gamma_step  ,desc= "STEP SCANING",leave=False):
                GAMMA_VALUE =gamma_start + gamma_interval*j
                svc_model = SVC(kernel='linear', random_state=1,
                        gamma=GAMMA_VALUE, C=C_VALUE)
                svc_model.fit(self.MartixRaw, self.MartixSpecies[:,0])
                #print("C value : ", C_VALUE )
                crosscal = self.crossCal(input_martix , svc_model)
                if crosscal[0] > BEST_ACCURATE:
                    BEST_GAMMA = GAMMA_VALUE
                    BEST_ACCURATE = crosscal[0]
                    BEST_CVAL = C_VALUE
                
        print("SVC LIN SCAN Finished!")
        print("BEST C = ",BEST_CVAL ,"BEST GAMMA = ",BEST_GAMMA, "ACCURACY =" , BEST_ACCURATE )
        self.debuginfo = True


    def KNN_BEST_PARAMETER(self,  n_step = 20 ):
        print("----------SEARCHING KNN BEST MODEL------------")
        self.debuginfo = False
        BEST_N = 0
        BEST_ACCURATE = 0 
        input_martix = self.attachMatrix(self.MartixRaw, self.MartixSpecies)
        p_bar = tqdm(range(n_step), desc="KNN BEST PARAMETER SCANING: ",  ncols=100)
        for i in p_bar :
            N_VALUE = 1 + i 
            KNN_model = KNeighborsClassifier(n_neighbors=N_VALUE)
            KNN_model.fit(self.MartixRaw, self.MartixSpecies[:,0])
            crosscal = self.crossCal(input_martix ,KNN_model)
            if crosscal[0] > BEST_ACCURATE:
                BEST_N  = N_VALUE 
                BEST_ACCURATE = crosscal[0]
        print("KNN SCAN Finished!")
        print("BEST N = ",BEST_N , "ACCURACY =" , BEST_ACCURATE )
        self.debuginfo = True

    #在这里step改为维度-1
    def LDA_BEST_PARAMETER(self  ):
        print("----------SEARCHING LDA BEST MODEL------------")
        self.debuginfo = False
        BEST_N = 0
        BEST_ACCURATE = 0 
        input_martix = self.attachMatrix(self.MartixRaw, self.MartixSpecies)
        p_bar = tqdm(range(self.dataDimension-1), desc="LDA BEST PARAMETER SCANING: ",  ncols=100)
        for i in p_bar :
            N_VALUE = 1 + i 
            LDA_model = LinearDiscriminantAnalysis(n_components=N_VALUE)
            LDA_model.fit(self.MartixRaw, self.MartixSpecies[:,0])
            crosscal = self.crossCal(input_martix ,LDA_model)
            if crosscal[0] > BEST_ACCURATE:
                BEST_N  = N_VALUE 
                BEST_ACCURATE = crosscal[0]
        print("LDA SCAN Finished!")
        print("BEST N = ",BEST_N , "ACCURACY =" , BEST_ACCURATE )
        self.debuginfo = True

    def LR_BEST_PARAMETER(self, c_interval = 0.01,  c_start = 0.1 ,c_step = 1000 ):
        import warnings
        warnings.filterwarnings("ignore")
        print("----------SEARCHING LR BEST MODEL------------")
        self.debuginfo = False
        BEST_CVAL = 0
        BEST_ACCURATE = 0 
        input_martix = self.attachMatrix(self.MartixRaw, self.MartixSpecies)
        p_bar = tqdm(range(c_step), desc="LR RBF BEST PARAMETER SCANING: ",  ncols=100)
        for i in p_bar :
            C_VALUE = c_start+c_interval*i
            LR_model = LogisticRegression(C=C_VALUE, random_state=10)
            LR_model.fit(self.MartixRaw, self.MartixSpecies[:,0])
            crosscal = self.crossCal(input_martix ,LR_model)
            if crosscal[0] > BEST_ACCURATE:
                BEST_CVAL  = C_VALUE
                BEST_ACCURATE = crosscal[0]
        print("LR SCAN Finished!")
        print("BEST C = ",BEST_CVAL , "ACCURACY =" , BEST_ACCURATE )
        self.debuginfo = True



        

    def BerRBM():
        #使用受限玻尔兹曼机预处理数据
        pass

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", help="display a square of a given number")
args = parser.parse_args()
print(args.square**2)
