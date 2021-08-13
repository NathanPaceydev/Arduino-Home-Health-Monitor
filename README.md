# Arduino-Home-Health-Monitor
Arduino based project using the DHT and MQ135 sensors to measure temperature, humidity and hazardous gas with a space. 
Features of this project include the ability to set certain thresholds for LED's and Warning Messages for the LCD Screen, Live plots of each sensors readings through the arduino serial plotter and integration through the local comport to python for additional data extrapolation and management.

DHT.h and DHT.cpp are additional files to ensure the DHT sensor is properly reading and calibrated in the current system.
Offline.uno is the main driver file.
