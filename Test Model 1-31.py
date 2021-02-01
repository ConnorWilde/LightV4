#Written 1/31
#Connor Wilde

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



output_train = pd.read_csv(
    "https://storage.googleapis.com/download.tensorflow.org/data/abalone_train.csv",
    names=["Length", "Diameter", "Height", "Whole weight", "Shucked weight",
           "Viscera weight", "Shell weight", "Age"])

output_train.head()

#Put into an array

output_features = output_train.copy()
output_lables = output_features.pop('Age') #My equivilant of age will be a user set output. Seperate it as the value to predict

output_features = np.array(output_features) #Not giving special weight for any one sensor input
output_features #Sensor Data

light_output = tf.keras.Sequential([
  layers.Dense(16),
  layers.Dense(16),
  layers.Dense(1)
])

# Add optimizer, loss function, and metrics to model and compile it
#Preset for compiling for microcontrollers
light_output.compile(optimizer='rmsprop', loss='mae', metrics=['mae'])

test = light_output.fit(output_features, output_lables, epochs=10)

#plot training history
loss = test.history['loss']


epochs = range(1, len(loss) + 1)

plt.plot(epochs, loss, 'bo', label='training loss')
plt.plot(epochs, loss, 'r', label='validation loss')
plt.title('training and validation loss')
plt.legend
plt.show

predictions = light_output.predict("13")

plt.clf()
plt.title('compare prediction to actual')
plt.plot(x_test,y_test, 'b.', label='Actual')
plt.plot(x_test,predictions, 'r.', label='Predicted')

plt.legend()
plt.show