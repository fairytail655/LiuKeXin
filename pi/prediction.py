import time
import serial
from sklearn import svm
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.svm import LinearSVC
from sklearn.datasets import load_digits
from sklearn.preprocessing import StandardScaler
import pickle

x = open('svm.pkl','rb')
classifier = pickle.load(x)

ser = serial.Serial("/dev/ttyUSB0", 9600)
ser1 = serial.Serial("/dev/ttyAMA0", 9600)
inp = ser.readline()
selectionLength = 45

fuck2 = 0
fuck1 = 0

a= [0]*6
a = np.array(a)
former =0
while True:
    inp = ser.readline()
    try:
        inp2 = inp.decode()
        inp2 = [float(val) for val in inp2.split()]
        # print(inp2)
        inp2= np.array(inp2)
        inp2=inp2/65536
        a=np.append(a,inp2)
        if( len(a) == selectionLength*6):
            move = classifier.predict([a])
            a = a[6*10:]
            if(fuck2):
                fuck2-=1
            if(fuck1):
                fuck1-=1
            if((move == 1) and fuck2 ):
                continue
            if((move == 2) and fuck1):
                continue
            if(move == 1):
                fuck1 = 5
            if(move == 2):
                fuck2 = 5
            # if move[0]==former:
            #     continue
            # former = move[0]
            #ser1.write(move[0])
            if move == 3:
                ser1.write(b"3")
                print(3)
            elif move == 1:
                ser1.write(b"1")
                print(1)
            elif move == 0:
                ser1.write(b"0")
                print(0)
            else:
                ser1.write(b"2")
                print(2)
    except:
        print("error")

