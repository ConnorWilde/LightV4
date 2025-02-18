# -*- coding: utf-8 -*-
"""New Model 1/31

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1CLFMuF46ol_9GVGma4V1zDYx-jE912ch
"""

import pandas as pd
import numpy as np

import matplotlib.pyplot as plt

# Make numpy values easier to read.
np.set_printoptions(precision=3, suppress=True)

import tensorflow as tf
from tensorflow.keras import layers
from tensorflow.keras.layers.experimental import preprocessing

#Some random google CSV that they use in a tutorial
#Mine will be similar



output_train = pd.read_csv("Street Train.csv",
    names=["set", "mode", "ambient", "Ax", "Ay", "Az", "Gx", "Gy", "GZ"])

output_train.head()

#Put into an array

output_features = output_train.copy()
output_lables = output_features.pop('set') #My equivilant of age will be a user set output. Seperate it as the value to predict

output_features = np.array(output_features) #Not giving special weight for any one sensor input
output_features #Sensor Data

output_features = output_features.astype(np.float) #convert to int

#Put testing into an array


output_test = pd.read_csv("Street Test.csv",
    names=["set", "mode", "ambient", "Ax", "Ay", "Az", "Gx", "Gy", "GZ"])

output_test.head()

output_features_test = output_test.copy()
output_lables_test = output_features_test.pop('set') #My equivilant of age will be a user set output. Seperate it as the value to predict

output_features_test = np.array(output_features_test) #Not giving special weight for any one sensor input
output_features_test #Sensor Data

output_features_test = output_features_test.astype(np.float) #convert to int

light_output = tf.keras.Sequential([
  layers.Dense(16),
  layers.Dense(128),
  layers.Dense(64),
  layers.Dense(16),
  layers.Dense(1)
])

# Add optimizer, loss function, and metrics to model and compile it
#Preset for compiling for microcontrollers
light_output.compile(optimizer='rmsprop', loss='mae', metrics=['mae'])

test = light_output.fit(output_features, output_lables, epochs=3)

#plot training history
loss = test.history['loss']


epochs = range(1, len(loss) + 1)

plt.plot(epochs, loss, 'bo', label='training loss')
plt.plot(epochs, loss, 'r', label='validation loss')
plt.title('training and validation loss')
plt.legend
plt.show

predictions = light_output.predict(output_features_test)

plt.clf()
plt.title('compare prediction to actual')
plt.plot(output_features_test,output_lables_test, 'b.', label='Actual')
plt.plot(predictions,output_lables_test, 'r.', label='Predicted')

plt.legend()
plt.show