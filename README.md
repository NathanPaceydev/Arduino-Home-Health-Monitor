# Arduino-Home-Health-Monitor
Arduino based project using the DHT and MQ135 sensors to measure temperature, humidity and hazardous gas with a space. 
Features of this project include the ability to set certain thresholds for LED's and Warning Messages for the LCD Screen, Live plots of each sensors readings through the arduino serial plotter and integration through the local comport to python for additional data extrapolation and management.

DHT.h and DHT.cpp is the header file and the sensors specific library to ensure accurate readings and calibration.

Offline.uno is the main driver file.

CSVWriting.py is the python file to grab the arduino data as it is being sent from the board.



![PXL_20210321_194006888 MP](https://user-images.githubusercontent.com/64051575/134821310-ff8e3bc7-cdbe-4192-a875-dd6d77955f6d.jpg)
