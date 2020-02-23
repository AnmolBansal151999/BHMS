# -*- coding: utf-8 -*-
"""
Created on Sat Feb 22 02:34:13 2020

@author: Anmol
"""

import pandas as pd
#data = pd.read_csv(r"C:\Users\Anmol\Desktop\SEM 6 files\bhms\data.csv")
data2 = pd.read_csv(r"C:\Users\Anmol\Desktop\SEM 6 files\bhms\10400mah_DataSet.csv")
data2.head()
feature_cols = ['Voltage (V)']
pred_col = ['Charge_Capacity(Ah)']
X = data2[feature_cols]
y = data2[pred_col]
from sklearn.model_selection import train_test_split
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.25,random_state=0)
X_test = X_test.fillna(X_test.mean())
y_test = y_test.fillna(y_test.mean())
X_train = X_train.fillna(X_train.mean())
y_train = y_train.fillna(y_train.mean())
from sklearn.linear_model import LinearRegression
from sklearn import preprocessing
le = preprocessing.LabelEncoder()
#y[:,0] = le.fit_transform(y[:,0])
logreg = LinearRegression()
logreg.fit(X_train,y_train)
y_pred=logreg.predict(X_test)
import matplotlib.pyplot as plot
plot.scatter(y_train,X_train, color='red')
#plot.plot(X_train,logreg.predict(X_train), color='blue')
plot.show()
y_pred1 = (y_pred/10400)*100
plot.plot(y_pred1,X_test)
#plot.xlabel = ('Percentage Charge')
#plot.ylabel = ('Terminal Voltage')
plot.axis(ymin=0)
plot.show()