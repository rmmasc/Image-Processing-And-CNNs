
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 12 11:45:52 2019

@author: Royston Marian Mascarenhas

"""
import numpy as np
from matplotlib import pyplot as plt

#function to read images
def read_image(ipath,height1,width1,display_flag):
    Img1 = open(ipath,'rb').read()
    Img1 = np.frombuffer(Img1,np.uint8)
    ImageP1 = Img1[0:height1*width1]
    ImageP1 = np.reshape(ImageP1,(height1,width1))
    if(display_flag==1):
        plt.matshow(ImageP1,cmap='gray')
    return ImageP1

#function to obtain tensor product between two 5x1 laws filters
def tensorprod(f_arr,arr):
    result = np.zeros((5,5))
    for i in range(0,5):
        for j in range(0,5):
            result[i,j] = f_arr[i]*arr[j];
    return result

#*****************************BOUNDARY EXTENSION*******************************

def boundary_ext(Imagedata,n):
    n_width = height + 2*n;
    n_height = width + 2*n;
    ImageG = np.zeros((n_height,n_width))
    for i in range(n,height+n):
        for j in range(n,width+n):
            ImageG[i,j] = Imagedata[i-n,j-n]

    for i in range(0,n):
        for j in range(0,n_width):
            ImageG[i,j] = ImageG[n,j]
    	
    for i in range(n_height-n,n_height):
        for j in range(0,n_width):
            ImageG[i,j] = ImageG[n_height-n-1,j]
    
    for i in range(0,n):
        for j in range(0,n_height):
            ImageG[j,i] = ImageG[j,n]
            
    for i in range(n_width-n,n_width):
        for j in range(0,n_height):
            ImageG[j,i] = ImageG[j,n_width-n-1]
    #ImageG = np.pad(Imagedata,n,'reflect');
    return ImageG
#******************************************************************************
#**********************APPLYING LAWS FILTER************************************
def apply_laws(Im1,fil,display_flag):
    n=n1;
    Im2 = np.zeros((height,width));
    ImDisp = np.zeros((height,width));
    for i in range(n,height+n):
        for j in range(n,width+n):
            temp = 0;
            x = 0
            for k in range(i-2,i+3):
                y = 0
                for l in range(j-2,j+3):
                    temp = temp + Im1[k,l]*fil[x,y]
                    y = y+1
                x = x+1
            Im2[i-n,j-n]= temp
            ImDisp[i-n,j-n]= temp
    if(display_flag==1):
        '''for x in range(0,height):
            for y in range(0,width):
                if ImDisp[x,y] < 0:
                    ImDisp[x,y] = 0;
                elif (ImDisp[x,y] > 255):
                    ImDisp[x,y] = 255;'''
        plt.matshow(ImDisp,cmap='gray')
    return Im2
#******************************************************************************

#*************************AVERAGE ENERGY PIXEL*********************************
def average_energy_pixel(ImP,feature_n):
    #print("energy: "+str(energy_method));
    ImP_R = [];
    w = int(n_p/2);
    n=n2;
    for i in range(n,height+n):
        for j in range(n,width+n):
            sample = ImP[i-w:i+w+1,j-w:j+w+1];
            if (energy_method == 1):
                samplef = sample**2;
            elif(energy_method == 2):
                samplef = abs(sample)
                #print("here")
            sumP = (np.sum(samplef)) / (n_p*n_p);
            ImP_R.append(sumP);
            #print(sumP)data
    for s in range (0,height*width):
        pixel_vectors[s,feature_n] = ImP_R[s];
    return(ImP_R);

'''def average_energy_pixel(ImP,feature_n):
    ImP_R = [];
    w = int(n_p/2);
    n=n2;
    for i in range(n,height+n):
        for j in range(n,width+n):
            sumP = 0;
            for k in range(i-w,i+w+1):
                for l in range(j-w,j+w+1):
                    sumP = sumP + np.square(ImP[k,l]);
            sumP = sumP / (n_p*n_p);
            ImP_R.append(sumP);
    for s in range (0,height*width):
        pixel_vectors[s,feature_n] = ImP_R[s];
    return(ImP_R);'''
#******************************************************************************



#******************************DECLARATIONS************************************
n1=2;
n2=5; #Boundary padding
height = 510
width = 510
nwidth = height + 2*n1
nheight = width + 2*n1
n_p = 11;
print(n_p)
print("Normalization L5L5")

L5 = np.array([1,4,6,4,1])
E5 = np.array([-1,-2,0,2,1])
S5 = np.array([-1,0,2,0,-1])
W5 = np.array([-1,2,0,-2,1])
R5 = np.array([1,-4,6,-4,1])
#******************************************************************************

L5L5 = tensorprod(L5,L5)
L5E5 = tensorprod(L5,E5)
L5S5 = tensorprod(L5,S5)
L5W5 = tensorprod(L5,W5)
L5R5 = tensorprod(L5,R5)
E5E5 = tensorprod(E5,E5)
E5L5 = tensorprod(E5,L5)
E5S5 = tensorprod(E5,S5)
E5W5 = tensorprod(E5,W5)
E5R5 = tensorprod(E5,R5)
S5S5 = tensorprod(S5,S5)
S5L5 = tensorprod(S5,L5)
S5E5 = tensorprod(S5,E5)
S5W5 = tensorprod(S5,W5)
S5R5 = tensorprod(S5,R5)
W5W5 = tensorprod(W5,W5)
W5L5 = tensorprod(W5,L5)
W5E5 = tensorprod(W5,E5)
W5S5 = tensorprod(W5,S5)
W5R5 = tensorprod(W5,R5)
R5R5 = tensorprod(R5,R5)
R5L5 = tensorprod(R5,L5)
R5E5 = tensorprod(R5,E5)
R5S5 = tensorprod(R5,S5)
R5W5 = tensorprod(R5,W5)

energy_method = int(input("Enter 1 to compute average energy of window by square method. Select 2 to  compute average energy of window by absolute method"));
I1 = read_image("comb.raw",510,510,1);
I2 = np.zeros((nheight,nwidth))
I3 = np.zeros((height,width))
pixel_vectors = np.zeros((height*width,25));
data = np.zeros((height*width,25));


I2 = boundary_ext(I1,n1);


#L5L5
I3 = apply_laws(I2,L5L5,0);
#print(I3[0:10,0:10])
I4 = boundary_ext(I3,n2);
#print("^^^^^^^^^");
#print(I4[0:10,0:10])
vec_L5L5 = average_energy_pixel(I4,0);


#L5E5
I3 = apply_laws(I2,L5E5,0);
I4 = boundary_ext(I3,n2);
vec_L5E5 = average_energy_pixel(I4,1);

#L5S5
I3 = apply_laws(I2,L5S5,0);
I4 = boundary_ext(I3,n2);
vec_L5S5 = average_energy_pixel(I4,2);

#L5W5
I3 = apply_laws(I2,L5W5,0);
I4 = boundary_ext(I3,n2);
vec_L5W5 = average_energy_pixel(I4,3);

#L5R5
I3 = apply_laws(I2,L5R5,0);
I4 = boundary_ext(I3,n2);
vec_L5R5 = average_energy_pixel(I4,4);

#---
#E5L5
I3 = apply_laws(I2,E5L5,0);
I4 = boundary_ext(I3,n2);
vec_E5L5 = average_energy_pixel(I4,5);

#E5E5
I3 = apply_laws(I2,E5E5,0);
I4 = boundary_ext(I3,n2);
vec_E5E5 = average_energy_pixel(I4,6);

#E5S5
I3 = apply_laws(I2,E5S5,0);
I4 = boundary_ext(I3,n2);
vec_E5S5 = average_energy_pixel(I4,7);

#E5W5
I3 = apply_laws(I2,E5W5,0);
I4 = boundary_ext(I3,n2);
vec_E5W5 = average_energy_pixel(I4,8);

#E5R5
I3 = apply_laws(I2,E5R5,0);
I4 = boundary_ext(I3,n2);
vec_E5R5 = average_energy_pixel(I4,9);

#---
#S5L5
I3 = apply_laws(I2,S5L5,0);
I4 = boundary_ext(I3,n2);
vec_S5L5 = average_energy_pixel(I4,10);

#S5E5
I3 = apply_laws(I2,S5E5,0);
I4 = boundary_ext(I3,n2);
vec_S5E5 = average_energy_pixel(I4,11);

#S5S5
I3 = apply_laws(I2,S5S5,0);
I4 = boundary_ext(I3,n2);
vec_S5S5 = average_energy_pixel(I4,12);

#S5W5
I3 = apply_laws(I2,S5W5,0);
I4 = boundary_ext(I3,n2);
vec_S5W5 = average_energy_pixel(I4,13);

#S5R5
I3 = apply_laws(I2,S5R5,0);
I4 = boundary_ext(I3,n2);
vec_S5R5 = average_energy_pixel(I4,14);
print("HALFWAY CHECK")
#---
#W5L5
I3 = apply_laws(I2,W5L5,0);
I4 = boundary_ext(I3,n2);
vec_W5L5 = average_energy_pixel(I4,15);

#W5E5
I3 = apply_laws(I2,W5E5,0);
I4 = boundary_ext(I3,n2);
vec_W5E5 = average_energy_pixel(I4,16);

#W5S5
I3 = apply_laws(I2,W5S5,0);
I4 = boundary_ext(I3,n2);
vec_W5S5 = average_energy_pixel(I4,17);

#W5W5
I3 = apply_laws(I2,W5W5,0);
I4 = boundary_ext(I3,n2);
vec_W5W5 = average_energy_pixel(I4,18);

#W5R5
I3 = apply_laws(I2,W5R5,0);
I4 = boundary_ext(I3,n2);
vec_W5R5 = average_energy_pixel(I4,19);

#---
#R5L5
I3 = apply_laws(I2,R5L5,0);
I4 = boundary_ext(I3,n2);
vec_R5L5 = average_energy_pixel(I4,20);

#R5E5
I3 = apply_laws(I2,R5E5,0);
I4 = boundary_ext(I3,n2);
vec_R5E5 = average_energy_pixel(I4,21);

#R5S5
I3 = apply_laws(I2,R5S5,0);
I4 = boundary_ext(I3,n2);
vec_R5S5 = average_energy_pixel(I4,22);

#R5W5
I3 = apply_laws(I2,R5W5,0);
I4 = boundary_ext(I3,n2); 
vec_R5W5 = average_energy_pixel(I4,23);

#R5R5
I3 = apply_laws(I2,R5R5,0);
I4 = boundary_ext(I3,n2);
vec_R5R5 = average_energy_pixel(I4,24);

data = pixel_vectors.copy();

#**************************NORMALIZATON****************************************
m_n = np.mean(pixel_vectors[:,0]);
std_n = np.std(pixel_vectors[:,0]);

for i in range(0,height*width):
    temp1 = pixel_vectors[i,0];
    for j in range(0,25):
        pixel_vectors[i,j] = pixel_vectors[i,j] /temp1;
        
'''mean_list = []
var_list = []
#get the means and the variances
for i in range(0,25):
    buff = pixel_vectors[:,i]
    mean_list.append(np.mean(buff))
    var_list.append(np.std(buff))
    
#normalize
for i in range(0,25):
    for j in range(0,height*width):
        pixel_vectors[j,i] = (pixel_vectors[j,i] - mean_list[i])/var_list[i];'''
'''mean_list = []
std_list = []
for i in range(0,25):
    mean_list.append(np.mean(pixel_vectors[:,i]))
    std_list.append(np.std(pixel_vectors[:,i]))

for i in range(0,25):
    for j in range(0,height*width):
        pixel_vectors[j,i] =  (pixel_vectors[j,i]-mean_list[i])/std_list[i];

pixel_vectors = pixel_vectors[:,1:25];'''

'''mean_list = []
std_list = []
for i in range(0,height*width):
    mean_list.append(np.mean(pixel_vectors[i,:]))
    std_list.append(np.std(pixel_vectors[i,:]))

for i in range(0,height*width):
    for j in range(0,25):
        pixel_vectors[i,j] =  (pixel_vectors[i,j]-mean_list[i])/std_list[i];

#pixel_vectors = pixel_vectors[:,1:25];'''
#******************************************************************************

#**************************SEGMENTATION****************************************
from sklearn.cluster import KMeans  
import pandas as pd
df = pd.DataFrame(pixel_vectors)
kmeans = KMeans(n_clusters=7)
kmeans.fit(df)
labels = kmeans.predict(df)
centroids = kmeans.cluster_centers_
#******************************************************************************
lab = labels.copy()
#********************************DENOTATION************************************
output = np.reshape(labels,(height,width));
for i in range(0,height):
    for j in range(0,width):
        if(output[i,j]==0):
            output[i,j] = 0;
        if(output[i,j]==1):
            output[i,j] = 42;
        if(output[i,j]==2):
            output[i,j] = 84;
        if(output[i,j]==3):
            output[i,j] = 126;
        if(output[i,j]==4):
            output[i,j] = 168;
        if(output[i,j]==5):
            output[i,j] = 210;
        if(output[i,j]==6):
            output[i,j] = 255;

plt.figure(figsize=(10,10)) #before interplation
plt.matshow(output,cmap='gray',fignum=1)
        
print("EOF Reached: Success");
