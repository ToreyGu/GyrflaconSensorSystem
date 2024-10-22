# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1137, 651)
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        MainWindow.setFont(font)
        MainWindow.setTabShape(QtWidgets.QTabWidget.Triangular)
        MainWindow.setDockNestingEnabled(True)
        MainWindow.setUnifiedTitleAndToolBarOnMac(False)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.splitter_2 = QtWidgets.QSplitter(self.centralwidget)
        self.splitter_2.setGeometry(QtCore.QRect(730, 170, 201, 211))
        self.splitter_2.setOrientation(QtCore.Qt.Vertical)
        self.splitter_2.setObjectName("splitter_2")
        self.dialTimeScale = QtWidgets.QDial(self.splitter_2)
        self.dialTimeScale.setMinimum(60)
        self.dialTimeScale.setMaximum(600)
        self.dialTimeScale.setSingleStep(10)
        self.dialTimeScale.setInvertedAppearance(False)
        self.dialTimeScale.setInvertedControls(False)
        self.dialTimeScale.setWrapping(False)
        self.dialTimeScale.setNotchesVisible(True)
        self.dialTimeScale.setObjectName("dialTimeScale")
        self.splitter = QtWidgets.QSplitter(self.splitter_2)
        self.splitter.setOrientation(QtCore.Qt.Horizontal)
        self.splitter.setObjectName("splitter")
        self.dialTimeStart = QtWidgets.QDial(self.splitter)
        self.dialTimeStart.setMaximum(100)
        self.dialTimeStart.setSingleStep(1)
        self.dialTimeStart.setNotchesVisible(True)
        self.dialTimeStart.setObjectName("dialTimeStart")
        self.dial_3 = QtWidgets.QDial(self.splitter)
        self.dial_3.setMaximum(120)
        self.dial_3.setSingleStep(5)
        self.dial_3.setObjectName("dial_3")
        self.labelResult = QtWidgets.QLabel(self.centralwidget)
        self.labelResult.setGeometry(QtCore.QRect(10, 480, 271, 131))
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setPointSize(28)
        self.labelResult.setFont(font)
        self.labelResult.setText("")
        self.labelResult.setObjectName("labelResult")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(720, 530, 91, 21))
        self.label_5.setText("")
        self.label_5.setObjectName("label_5")
        self.splitter_8 = QtWidgets.QSplitter(self.centralwidget)
        self.splitter_8.setGeometry(QtCore.QRect(730, 30, 201, 131))
        self.splitter_8.setOrientation(QtCore.Qt.Vertical)
        self.splitter_8.setObjectName("splitter_8")
        self.splitter_3 = QtWidgets.QSplitter(self.splitter_8)
        self.splitter_3.setOrientation(QtCore.Qt.Vertical)
        self.splitter_3.setObjectName("splitter_3")
        self.splitter_7 = QtWidgets.QSplitter(self.splitter_3)
        self.splitter_7.setOrientation(QtCore.Qt.Vertical)
        self.splitter_7.setObjectName("splitter_7")
        self.label = QtWidgets.QLabel(self.splitter_7)
        font = QtGui.QFont()
        font.setFamily("UD Digi Kyokasho NK-R")
        font.setPointSize(12)
        self.label.setFont(font)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.progressBarChipTemp = QtWidgets.QProgressBar(self.splitter_7)
        self.progressBarChipTemp.setProperty("value", 0)
        self.progressBarChipTemp.setAlignment(QtCore.Qt.AlignJustify|QtCore.Qt.AlignVCenter)
        self.progressBarChipTemp.setTextDirection(QtWidgets.QProgressBar.BottomToTop)
        self.progressBarChipTemp.setObjectName("progressBarChipTemp")
        self.splitter_6 = QtWidgets.QSplitter(self.splitter_8)
        self.splitter_6.setOrientation(QtCore.Qt.Horizontal)
        self.splitter_6.setObjectName("splitter_6")
        self.splitter_4 = QtWidgets.QSplitter(self.splitter_6)
        self.splitter_4.setOrientation(QtCore.Qt.Vertical)
        self.splitter_4.setObjectName("splitter_4")
        self.label_2 = QtWidgets.QLabel(self.splitter_4)
        font = QtGui.QFont()
        font.setFamily("UD Digi Kyokasho NK-R")
        font.setPointSize(10)
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.lcdNumberCOM = QtWidgets.QLCDNumber(self.splitter_4)
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setStyleStrategy(QtGui.QFont.PreferDefault)
        self.lcdNumberCOM.setFont(font)
        self.lcdNumberCOM.setDigitCount(6)
        self.lcdNumberCOM.setSegmentStyle(QtWidgets.QLCDNumber.Flat)
        self.lcdNumberCOM.setProperty("intValue", 0)
        self.lcdNumberCOM.setObjectName("lcdNumberCOM")
        self.splitter_5 = QtWidgets.QSplitter(self.splitter_6)
        self.splitter_5.setOrientation(QtCore.Qt.Vertical)
        self.splitter_5.setObjectName("splitter_5")
        self.label_3 = QtWidgets.QLabel(self.splitter_5)
        font = QtGui.QFont()
        font.setFamily("UD Digi Kyokasho NK-R")
        font.setPointSize(10)
        self.label_3.setFont(font)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.lcdNumberBaudrate = QtWidgets.QLCDNumber(self.splitter_5)
        self.lcdNumberBaudrate.setDigitCount(6)
        self.lcdNumberBaudrate.setSegmentStyle(QtWidgets.QLCDNumber.Flat)
        self.lcdNumberBaudrate.setObjectName("lcdNumberBaudrate")
        self.splitter_9 = QtWidgets.QSplitter(self.centralwidget)
        self.splitter_9.setGeometry(QtCore.QRect(730, 380, 201, 51))
        self.splitter_9.setOrientation(QtCore.Qt.Horizontal)
        self.splitter_9.setObjectName("splitter_9")
        self.pushButtonOpenCOM = QtWidgets.QPushButton(self.splitter_9)
        self.pushButtonOpenCOM.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pushButtonOpenCOM.setObjectName("pushButtonOpenCOM")
        self.pushButtonCloseCom = QtWidgets.QPushButton(self.splitter_9)
        self.pushButtonCloseCom.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pushButtonCloseCom.setObjectName("pushButtonCloseCom")
        self.ChartSensor = QChartView(self.centralwidget)
        self.ChartSensor.setGeometry(QtCore.QRect(10, 30, 711, 451))
        self.ChartSensor.setObjectName("ChartSensor")
        self.labelTimeScale = QtWidgets.QLabel(self.centralwidget)
        self.labelTimeScale.setGeometry(QtCore.QRect(940, 60, 91, 31))
        self.labelTimeScale.setText("")
        self.labelTimeScale.setObjectName("labelTimeScale")
        self.pushButtonAnalyse = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonAnalyse.setGeometry(QtCore.QRect(730, 440, 201, 41))
        self.pushButtonAnalyse.setObjectName("pushButtonAnalyse")
        self.labelCH1 = QtWidgets.QLabel(self.centralwidget)
        self.labelCH1.setGeometry(QtCore.QRect(620, 40, 81, 21))
        self.labelCH1.setObjectName("labelCH1")
        self.labelCH2 = QtWidgets.QLabel(self.centralwidget)
        self.labelCH2.setGeometry(QtCore.QRect(620, 60, 81, 21))
        self.labelCH2.setObjectName("labelCH2")
        self.labelCH3 = QtWidgets.QLabel(self.centralwidget)
        self.labelCH3.setGeometry(QtCore.QRect(620, 80, 81, 16))
        self.labelCH3.setObjectName("labelCH3")
        self.label_6 = QtWidgets.QLabel(self.centralwidget)
        self.label_6.setGeometry(QtCore.QRect(590, 40, 31, 16))
        self.label_6.setObjectName("label_6")
        self.label_9 = QtWidgets.QLabel(self.centralwidget)
        self.label_9.setGeometry(QtCore.QRect(590, 60, 31, 16))
        self.label_9.setObjectName("label_9")
        self.label_10 = QtWidgets.QLabel(self.centralwidget)
        self.label_10.setGeometry(QtCore.QRect(590, 80, 31, 16))
        self.label_10.setObjectName("label_10")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(950, 430, 141, 51))
        self.pushButton.setObjectName("pushButton")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(950, 190, 131, 21))
        self.label_4.setObjectName("label_4")
        self.label_7 = QtWidgets.QLabel(self.centralwidget)
        self.label_7.setGeometry(QtCore.QRect(950, 270, 131, 21))
        self.label_7.setObjectName("label_7")
        self.label_8 = QtWidgets.QLabel(self.centralwidget)
        self.label_8.setGeometry(QtCore.QRect(950, 350, 131, 21))
        self.label_8.setObjectName("label_8")
        self.label_11 = QtWidgets.QLabel(self.centralwidget)
        self.label_11.setGeometry(QtCore.QRect(940, 40, 101, 21))
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setPointSize(12)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.doubleSpinBoxCH1 = QtWidgets.QDoubleSpinBox(self.centralwidget)
        self.doubleSpinBoxCH1.setGeometry(QtCore.QRect(950, 220, 141, 41))
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setPointSize(12)
        self.doubleSpinBoxCH1.setFont(font)
        self.doubleSpinBoxCH1.setMinimum(-100.0)
        self.doubleSpinBoxCH1.setMaximum(100.0)
        self.doubleSpinBoxCH1.setObjectName("doubleSpinBoxCH1")
        self.doubleSpinBoxCH2 = QtWidgets.QDoubleSpinBox(self.centralwidget)
        self.doubleSpinBoxCH2.setGeometry(QtCore.QRect(950, 300, 141, 41))
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setPointSize(12)
        self.doubleSpinBoxCH2.setFont(font)
        self.doubleSpinBoxCH2.setMinimum(-100.0)
        self.doubleSpinBoxCH2.setMaximum(100.0)
        self.doubleSpinBoxCH2.setObjectName("doubleSpinBoxCH2")
        self.doubleSpinBoxCH3 = QtWidgets.QDoubleSpinBox(self.centralwidget)
        self.doubleSpinBoxCH3.setGeometry(QtCore.QRect(950, 380, 141, 41))
        font = QtGui.QFont()
        font.setFamily("Adobe Heiti Std")
        font.setPointSize(12)
        self.doubleSpinBoxCH3.setFont(font)
        self.doubleSpinBoxCH3.setMinimum(-100.0)
        self.doubleSpinBoxCH3.setMaximum(100.0)
        self.doubleSpinBoxCH3.setObjectName("doubleSpinBoxCH3")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1137, 21))
        self.menubar.setObjectName("menubar")
        self.menuInfo = QtWidgets.QMenu(self.menubar)
        self.menuInfo.setObjectName("menuInfo")
        self.menuSettings = QtWidgets.QMenu(self.menubar)
        self.menuSettings.setObjectName("menuSettings")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionContast_us = QtWidgets.QAction(MainWindow)
        self.actionContast_us.setObjectName("actionContast_us")
        self.actionGyrflaconSensorSystem = QtWidgets.QAction(MainWindow)
        self.actionGyrflaconSensorSystem.setObjectName("actionGyrflaconSensorSystem")
        self.actionCOM_Setting = QtWidgets.QAction(MainWindow)
        self.actionCOM_Setting.setObjectName("actionCOM_Setting")
        self.actionLicenseCode = QtWidgets.QAction(MainWindow)
        self.actionLicenseCode.setObjectName("actionLicenseCode")
        self.menuInfo.addAction(self.actionContast_us)
        self.menuInfo.addAction(self.actionGyrflaconSensorSystem)
        self.menuInfo.addSeparator()
        self.menuInfo.addAction(self.actionLicenseCode)
        self.menuSettings.addAction(self.actionCOM_Setting)
        self.menubar.addAction(self.menuSettings.menuAction())
        self.menubar.addAction(self.menuInfo.menuAction())

        self.retranslateUi(MainWindow)
        self.actionContast_us.triggered.connect(MainWindow.OpenContactus) # type: ignore
        self.actionGyrflaconSensorSystem.triggered.connect(MainWindow.OpenSysinfo) # type: ignore
        self.actionLicenseCode.triggered.connect(MainWindow.OpenActiveSoftware) # type: ignore
        self.actionCOM_Setting.triggered.connect(MainWindow.OpenCOMSetting) # type: ignore
        self.pushButtonOpenCOM.clicked.connect(MainWindow.ConnectCOM) # type: ignore
        self.pushButtonCloseCom.clicked.connect(MainWindow.DisconnectCOM) # type: ignore
        self.dialTimeScale.valueChanged['int'].connect(MainWindow.SetTimeScale) # type: ignore
        self.dialTimeStart.valueChanged['int'].connect(MainWindow.SetTimeStart) # type: ignore
        self.pushButtonAnalyse.clicked.connect(MainWindow.AnalyseChart) # type: ignore
        self.dial_3.valueChanged['int'].connect(MainWindow.SetValueScale) # type: ignore
        self.pushButton.clicked.connect(MainWindow.SetBiasVal) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Gyrflacon Sensor System Professional"))
        self.label.setText(_translate("MainWindow", "CPU Temperature"))
        self.progressBarChipTemp.setFormat(_translate("MainWindow", "%p℃"))
        self.label_2.setText(_translate("MainWindow", "COM"))
        self.label_3.setText(_translate("MainWindow", "BAUDRATE"))
        self.pushButtonOpenCOM.setText(_translate("MainWindow", "OPENCOM"))
        self.pushButtonCloseCom.setText(_translate("MainWindow", "CLOSECOM"))
        self.pushButtonAnalyse.setText(_translate("MainWindow", "ANALYSE CHART"))
        self.labelCH1.setText(_translate("MainWindow", "No Signal"))
        self.labelCH2.setText(_translate("MainWindow", "No Signal"))
        self.labelCH3.setText(_translate("MainWindow", "No Signal"))
        self.label_6.setText(_translate("MainWindow", "CH1:"))
        self.label_9.setText(_translate("MainWindow", "CH2:"))
        self.label_10.setText(_translate("MainWindow", "CH3:"))
        self.pushButton.setText(_translate("MainWindow", "Bias Adjust"))
        self.label_4.setText(_translate("MainWindow", "Channel 1 bias (mV)"))
        self.label_7.setText(_translate("MainWindow", "Channel 2 bias (mV)"))
        self.label_8.setText(_translate("MainWindow", "Channel 3 bias (mV)"))
        self.label_11.setText(_translate("MainWindow", "TimeScale"))
        self.menuInfo.setTitle(_translate("MainWindow", "Info"))
        self.menuSettings.setTitle(_translate("MainWindow", "Settings"))
        self.actionContast_us.setText(_translate("MainWindow", "Contast us"))
        self.actionGyrflaconSensorSystem.setText(_translate("MainWindow", "About Gyrflacon System"))
        self.actionCOM_Setting.setText(_translate("MainWindow", "COM Setting"))
        self.actionLicenseCode.setText(_translate("MainWindow", "ActiveSoftware"))
from PyQt5.QtChart import QChartView
