
import serial
import pickle
from datetime import datetime


arduino_port = "COM3" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName="analog-data.csv" #name of the CSV file generated

def collectSamples(ser,SAMPLES):
    sample_data = []
    while len(sample_data)<SAMPLES+1:
        getData=str(ser.readline())
        data = getData.split(',')
        data[0]=data[0][2:]
        data[-1]=data[-1][0]
        if len(data)>2:
            sample_data.append(data)
            print(data)
    return sample_data

def savePickle(filename,data):
    date = datetime.now()
    date = date.strftime("%d/%m/%Y %H:%M:%S")
    with open(filename+"-"+date+'.pickle', 'wb') as handle:
        pickle.dump(data, handle, protocol=pickle.HIGHEST_PROTOCOL)

if __name__ =="__main__":
    SAMPLES = 50
    ser = serial.Serial(arduino_port, baud)
    print("Connected to Arduino port:" + arduino_port)
    data = collectSamples(ser,SAMPLES)
    savePickle("butane",data)


# #add the data to the file
# file = open(fileName, "a") #append the data to the file
# file.write(data + "\\n") #write data with a newline

# #close out the file
# file.close()

# samples = 10 #how many samples to collect
# print_labels = False
# line = 0 #start at 0 because our header is 0 (not real data)
# while line <= samples:
#     # incoming = ser.read(9999)
#     # if len(incoming) > 0:
#     if print_labels:
#         if line==0:
#             print("Printing Column Headers")
#         else:
#             print("Line " + str(line) + ": writing...")
#     getData=str(ser.readline())
#     data=getData[0:][:-2]
#     print(data)

#     file = open(fileName, "a")
#     file.write(data + "\\n") #write data with a newline
#     line = line+1

# print("Data collection complete!")
# file.close()