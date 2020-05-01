#!/usr/bin/env python
# Python program explaining  
# load() function  
  
import numpy as geek 
import matplotlib.pyplot as plt 
  
b = geek.load('hits.npy') 
  
print("size of b is:",b.size)
print("shape of b is:",b.shape)
print("ndim of b is:",b.ndim)
print(b)
print(b[0,0,0])
print(b[0,3,0])
print("b is printed from hits.npy")
x = b[:,0,0]
y = b[:,0,1]
z = b[:,0,2]
lamb = b[:,2,3]

#fig = plt.figure(figsize=(12, 4))
#ax2.hist(age, bins='auto')
print(x.shape)
print(y.shape)
print(lamb.shape)
axs = plt.subplots(2, 2, figsize=(5, 5))
axs[0, 0].hist(x,50,(-200,200.))
axs[1, 0].scatter(x, y)
axs[0, 1].hist(lamb,50,(50,800.))
axs[1, 1].hist(z)
axs.show()
