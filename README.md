
Gyrfalcon high-speed wired high-power gas sensing array series.Data acquisition for artificial olfactory systems implemented in artificial neural networks and traditional machine learning.
![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/91f9a599-c078-48df-bc9c-11b874f994c0)
# About Gyrfalcon
*Gyrfalcon(Haidongqing) is a large bird of prey in the family of Falconidae. It is known for its speed and hunting ability. Gyrfalcon(Haidongqing) is a popular bird in falconry and is often used by falconers to hunt smaller birds and mammals.In the past, Gyrfalcon(Haidongqing) was also known as the "Divine Eagle" and was considered a symbol of courage and power.*

# About System 
This system contains three parts : 
 (a) Sampling device 
 (b) Comm protocol
 (c) Host software
 ![Slide7](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/016da56b-a092-4367-8295-540999089945)

Sampling device was NRF52840's SAADC on chip using 12-bit resolution mode 
![2019121814033498](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/e74be2e5-ac11-4d33-abfe-7f218433fa5a)

# How To Use
STEP 1 
Connect system with a standard micro-USB cable(different version will have different micro-USB interface)
![dcd3c8f7440c1da285f1f5cf1e6e2ab](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/593f5234-bdd4-4971-a84e-1f52ca157c9b)
STEP 2 
Add pre-trained scikit-learn machine learning model model.pkl to model folder , if there is no model in folder, host software will not work.(This model can be trained by ezml paltform.)

![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/d13b36f1-a79c-40a9-8048-89b4b68e9358)
![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/85dfa88f-cf19-45c6-bcd6-bbabf305a52f)

STEP 3

If you have environment for QT& scikit-learn ,  you can use `python Startup.py` to open host software.
![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/ebb14d1c-9adf-423c-a67b-ee9f9a0051c7)

or you can find `.\dist\Startup\Startup.exe` to open windows software
![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/63737123-aed6-41d4-bf73-95640d41e06d)
![image](https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/b0859f2f-69c7-457c-adbd-57eadc9aa475)

# Demonstration
https://github.com/ToreyGu/GyrflaconSensorSystem/assets/77352146/da6dd903-a020-4d07-89f1-053f1a015e34

