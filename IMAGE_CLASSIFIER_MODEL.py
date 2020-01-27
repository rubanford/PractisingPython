#!/usr/bin/env python
# coding: utf-8

# In[1]:


import os
import cv2
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt


# In[2]:


os.getcwd()


# In[3]:


os.chdir(r'C:\Studies\ML\opencv\project\Testing_1')


# In[4]:


files = os.listdir()


# In[5]:


files[0]


# In[6]:


dataset_testing = []
label_testing = []


# ## Loop for creating dataset list from files

# In[7]:


count = 0
for i in range(len(files)):
    os.chdir(r'C:/Studies/ML/opencv/project/Testing_1/'+str(files[i]))
    imges = os.listdir()
    for i in imges:
        images = cv2.imread(str(i),0)
#         images = images.reshape(10,3000)
        label_testing.append(count)
        dataset_testing.append(images)
    count += 1


# In[8]:


len(dataset_testing)


# # Creating numpy arrays for images and labels

# In[9]:


data = np.array(dataset_testing)


# In[10]:


label = np.array(label_testing)


# In[11]:


data.shape


# In[12]:


label.shape


# In[13]:


data[0].shape


# # visualiztion using random values

# In[14]:


import random


# In[16]:


num = random.randint(0,8729)
print(num)
print('Label:'+ str(label[num])+'    checking...'+str(files[label[num]]))
plt.imshow(data[num])


# In[86]:


# import xlwt 
# from xlwt import Workbook 
  
# # Workbook is created 
# wb = Workbook() 
  
# # add_sheet is used to create sheet. 
# sheet1 = wb.add_sheet('Sheet 1') 


# In[72]:


# for i in range(len(dataset_testing)):
#     sheet1.write(i+1, 0, 'Label '+ str(files[int(dataset_testing[i][0])]))
#     sheet1.write(i+1, 1, ' '.join(map(str, dataset_testing[i][1])))
    
#     wb.save('xlwt test_data.xls') 


# # Creating model using tensorflow

# In[134]:


model = keras.Sequential([
    keras.layers.Flatten(input_shape=(100,100)),
    keras.layers.Dense(128, activation=tf.nn.swish),
    keras.layers.Dense(256, activation=tf.nn.swish),
    keras.layers.Dense(22, activation=tf.nn.softmax)
])


# In[135]:


model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])


# In[136]:


model.fit(data,label,epochs=15)


# In[20]:


os.chdir(r'C:\Studies\ML\opencv\fruits\Fruit-Images-Dataset-master\test-multiple_fruits')


# In[21]:


trying_2_test = os.listdir()


# In[34]:


from skimage.transform import resize


# In[160]:


num = random.randint(0,len(trying_2_test))
print(num)
t_2_t = cv2.imread(str(trying_2_test[num]),0)
print(trying_2_test[num])
plt.imshow(t_2_t)
# t_2_t_res = resize(t_2_t, (100, 100))
t_2_t_res = cv2.resize(t_2_t, dsize=(100, 100), interpolation=cv2.INTER_LANCZOS4)


# In[161]:


predictions = model.predict(t_2_t_res.reshape(1,100,100))


# In[162]:


predictions


# In[163]:


num = np.argmax(predictions)
print(num)
print('Label:'+ str(files[num]))
# plt.imshow(trying_2_test[num])


# In[ ]:


24567787


# In[ ]:





# In[201]:


os.chdir(r'C:\Studies\ML\opencv\fruits\Fruit-Images-Dataset-master\Training')


# In[202]:


testing_with_train = os.listdir()


# In[ ]:





# In[207]:


for j in testing_with_train:
    os.chdir(r'C:/Studies/ML/opencv/fruits/Fruit-Images-Dataset-master/Training/' +str(j))
    trying_2_test = os.listdir()
    t_2_t = cv2.imread(str(trying_2_test[5]),0)
    predictions = model.predict(t_2_t.reshape(1,100,100))
    num = np.argmax(predictions)
    print(j)
    print(num)
    print('Label:'+ str(files[num]))
    print('\n')
    
    
    


# In[208]:


model.save('with10epochs.pb')


# In[209]:


model.save('with10epochs.h5')


# In[ ]:




