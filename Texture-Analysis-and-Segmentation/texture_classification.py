
# -*- coding: utf-8 -*-
"""
Created on Sat Mar  9 12:25:22 2019

@author: Royston M M 
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

def boundary_ext(Imagedata):
    ImageG = np.zeros((nheight,nwidth))
    for i in range(n,height+n):
        for j in range(n,width+n):
            ImageG[i,j] = Imagedata[i-n,j-n]

    for i in range(0,n):
        for j in range(0,nwidth):
            ImageG[i,j] = ImageG[n,j]
    	
    for i in range(nheight-n,nheight):
        for j in range(0,nwidth):
            ImageG[i,j] = ImageG[nheight-n-1,j]
    
    for i in range(0,n):
        for j in range(0,nheight):
            ImageG[j,i] = ImageG[j,n]
            
    for i in range(nwidth-n,nwidth):
        for j in range(0,nheight):
            ImageG[j,i] = ImageG[j,nwidth-n-1]
    return ImageG
#******************************************************************************       
   
#****************************AVERAGE ENERGY************************************
def avg_energy(Ime1):
    sume = 0.0;
    for i in range(0,height):
        for j in range(0,width):
            sume = sume + np.square(Ime1[i,j]);
    return (sume/(height*width));
#******************************************************************************
#***********************SUBTRACTING OFF THE MEAN*******************************
def sub_mean(ImageS):
    sum = 0
    Imagetemp = np.zeros((height,width))
    for i in range(0,height):
        for j in range(0,width):
            sum = sum + ImageS[i,j]
    Imean = sum/(height*width)
    #print("Imean "+str(Imean))
    #ImageS.setflags(write=1)
    for i in range(0,height):
        for j in range(0,width):
            Imagetemp[i,j] = ImageS[i,j] - Imean
    return Imagetemp
#******************************************************************************
    
#**********************APPLYING LAWS FILTER************************************
def apply_laws(Im1,fil):
    Im2 = np.zeros((height,width));
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
    return Im2

'''def apply_laws(Im1,fil1):
    Im2 = np.zeros((height,width))
    fil = fil1.flatten()
    for i in range(n,height+n):
        for j in range(n,width+n):
            temp = 0;
            x = 0;
            for k in range(i-2,i+3):
                for l in range(j-2,j+3):
                    temp = temp + Im1[k,l]*fil[x];
                    x = x+1;
            Im2[i-n,j-n]= temp
    return Im2'''
        
#******************************************************************************
#*************************GET THE 25D VECTOR REP*******************************
#*************************GET THE 25D VECTOR REP*******************************
def get_vec(TIm1):
    t_vec = np.zeros(o);
    TIm3 = np.zeros((height,width));
    #dim1
    TIm3 = apply_laws(TIm1,L5L5)
    avg_l5l5 = avg_energy(TIm3)
    #dim 2 
    TIm3 = apply_laws(TIm1,L5E5)
    avg_l5e5 = avg_energy(TIm3)
    #dim3
    TIm3 = apply_laws(TIm1,L5S5)
    avg_l5s5 = avg_energy(TIm3)
    #dim4
    TIm3 = apply_laws(TIm1,L5W5)
    avg_l5w5 = avg_energy(TIm3)
    #dim5
    TIm3 = apply_laws(TIm1,L5R5)
    avg_l5r5 = avg_energy(TIm3)
    #dim6
    TIm3 = apply_laws(TIm1,E5E5)
    avg_e5e5 = avg_energy(TIm3)
    #dim7
    TIm3 = apply_laws(TIm1,E5L5)
    avg_e5l5 = avg_energy(TIm3)
    #dim8
    TIm3 = apply_laws(TIm1,E5S5)
    avg_e5s5 = avg_energy(TIm3)
    #dim9
    TIm3 = apply_laws(TIm1,E5W5)
    avg_e5w5 = avg_energy(TIm3)
    #dim10
    TIm3 = apply_laws(TIm1,E5R5)
    avg_e5r5 = avg_energy(TIm3)
    #dim11
    TIm3 = apply_laws(TIm1,S5S5)
    avg_s5s5 = avg_energy(TIm3)
    #dim12
    TIm3 = apply_laws(TIm1,S5L5)    
    avg_s5l5 = avg_energy(TIm3)
    #dim13
    TIm3 = apply_laws(TIm1,S5E5)
    avg_s5e5 = avg_energy(TIm3)
    #dim14
    TIm3 = apply_laws(TIm1,S5W5)
    avg_s5w5 = avg_energy(TIm3)
    #dim15
    TIm3 = apply_laws(TIm1,S5R5)
    avg_s5r5 = avg_energy(TIm3)
    #dim16
    TIm3 = apply_laws(TIm1,W5W5)
    avg_w5w5 = avg_energy(TIm3)
    #dim17
    TIm3 = apply_laws(TIm1,W5L5)
    avg_w5l5 = avg_energy(TIm3)
    #dim18
    TIm3 = apply_laws(TIm1,W5E5)
    avg_w5e5 = avg_energy(TIm3)
    #dim19
    TIm3 = apply_laws(TIm1,W5S5)
    avg_w5s5 = avg_energy(TIm3)
    #dim20
    TIm3 = apply_laws(TIm1,W5R5)
    avg_w5r5 = avg_energy(TIm3)
    #dim21
    TIm3 = apply_laws(TIm1,R5R5)
    avg_r5r5 = avg_energy(TIm3)
    #dim22
    TIm3 = apply_laws(TIm1,R5L5)
    avg_r5l5 = avg_energy(TIm3)
    #dim23
    TIm3 = apply_laws(TIm1,R5E5)
    avg_r5e5 = avg_energy(TIm3)
    #dim24
    TIm3 = apply_laws(TIm1,R5S5)
    avg_r5s5 = avg_energy(TIm3)
    #dim25
    TIm3 = apply_laws(TIm1,R5W5)
    avg_r5w5 = avg_energy(TIm3)
    '''t_vec = np.array([avg_l5l5,avg_e5e5,avg_s5s5,avg_w5w5,avg_r5r5, (avg_l5e5+avg_e5l5)/2,
            (avg_l5s5+avg_s5l5)/2,(avg_l5w5+avg_w5l5)/2,(avg_l5r5+avg_r5l5)/2,
            (avg_w5r5+avg_r5w5)/2,(avg_s5e5+avg_e5s5)/2,
            (avg_e5w5+avg_w5e5)/2,(avg_e5r5+avg_r5e5)/2,(avg_s5w5+avg_w5s5)/2,
            (avg_s5r5+avg_r5s5)/2]);'''
    t_vec = np.array([avg_l5l5,avg_l5e5,avg_l5s5,avg_l5w5,avg_l5r5,
                      avg_e5l5,avg_e5e5,avg_e5s5,avg_e5w5,avg_e5r5,
                      avg_s5l5,avg_s5e5,avg_s5s5,avg_s5w5,avg_s5r5,
                      avg_w5l5,avg_w5e5,avg_w5s5,avg_w5r5,avg_w5w5,
                      avg_r5l5,avg_r5e5,avg_r5s5,avg_r5w5,avg_r5r5]);
    return t_vec;
    

#******************************************************************************


#******************************DECLARATIONS************************************
n=2
height = 128
width = 128
nwidth = height + 2*n
nheight = width + 2*n

L5 = np.array([1,4,6,4,1])
E5 = np.array([-1,-2,0,2,1])
S5 = np.array([-1,0,2,0,-1])
W5 = np.array([-1,2,0,-2,1])
R5 = np.array([1,-4,6,-4,1])
o = 25;

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

T1 = np.zeros((nheight,nwidth))
T2 = np.zeros((height,width))
T3 = np.zeros((height,width))
Text1 = read_image("texture1.raw",128,128,0)
Text1.setflags(write=1)
T2 = sub_mean(Text1)
T1 = boundary_ext(T2)
t_vec_t1 = np.zeros(o);
t_vec_t2 = np.zeros(o);
t_vec_t3 = np.zeros(o);
t_vec_t4 = np.zeros(o);
t_vec_t5 = np.zeros(o);
t_vec_t6 = np.zeros(o);
t_vec_t7 = np.zeros(o);
t_vec_t8 = np.zeros(o);
t_vec_t9 = np.zeros(o);
t_vec_t10 = np.zeros(o);
t_vec_t11 = np.zeros(o);
t_vec_t12 = np.zeros(o);


t_vec_t1 = get_vec(T1);

Text1 = read_image("texture2.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t2 = get_vec(T1);

Text1 = read_image("texture3.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t3 = get_vec(T1);

Text1 = read_image("texture4.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t4 = get_vec(T1);

Text1 = read_image("texture5.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t5 = get_vec(T1);

Text1 = read_image("texture6.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t6 = get_vec(T1);

Text1 = read_image("texture7.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t7 = get_vec(T1);

Text1 = read_image("texture8.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t8 = get_vec(T1);

Text1 = read_image("texture9.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t9 = get_vec(T1);

Text1 = read_image("texture10.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t10 = get_vec(T1);

Text1 = read_image("texture11.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t11 = get_vec(T1);

Text1 = read_image("texture12.raw",128,128,0);
T2 = sub_mean(Text1);
T1 = boundary_ext(T2);
t_vec_t12 = get_vec(T1);

Data = np.zeros((12,o));
Data_norm = np.zeros((12,o));


Data[0,:] = t_vec_t1;
Data[1,:] = t_vec_t2;
Data[2,:] = t_vec_t3;
Data[3,:] = t_vec_t4;
Data[4,:] = t_vec_t5;
Data[5,:] = t_vec_t6;
Data[6,:] = t_vec_t7;
Data[7,:] = t_vec_t8;
Data[8,:] = t_vec_t9;
Data[9,:] = t_vec_t10;
Data[10,:] = t_vec_t11;
Data[11,:] = t_vec_t12;

#*****************************NORMALIZATION************************************
mean_list = []
var_list = []

#get the means and the variances
for i in range(0,12):
    buff = Data[i,:]
    mean_list.append(np.mean(buff))
    var_list.append(np.std(buff))
    
#normalize
for i in range(0,12):
    for j in range(0,o):
        Data_norm[i,j] = (Data[i,j] - mean_list[i])/var_list[i];
        

#******************************************************************************  

#*******************************PCA********************************************
from sklearn.decomposition import PCA
pca = PCA(n_components=3)
pca.fit(Data_norm)
Data_new = pca.transform(Data_norm)

#******************************************************************************
init_c = np.array([Data_new[4,:],Data_new[7,:],Data_new[8,:],Data_new[5,:]])
from sklearn.cluster import KMeans  
import pandas as pd
df = pd.DataFrame(Data_new)
kmeans = KMeans(4,init_c,n_init=10)
#kmeans = KMeans(4)
kmeans.fit(df)
labels = kmeans.predict(X=df)
centroids = kmeans.cluster_centers_
'''
t1_vec = np.array([avg_l5l5,avg_e5e5,avg_s5s5,avg_w5w5,avg_r5r5,
((avg_l5e5+avg_e5l5)/2),
((avg_l5s5+avgs5l5)/2),((avgl5w5+avg_w5l5)/2),((avg_l5r5+avg_r5l5)/2),
((avg_l5r5,avg_r5l5)/2),((avg_w5r5+avg_r5w5)/2),((avg_e5s5+avg_e5s5)/2),
((avg_e5w5+avg_w5e5)/2),((avg_e5r5+avg_r5e5)/2),((avg_s5w5+avg_w5s5)/2),
((avg_s5r5+avg_r5s5)/2)]);
'''

#plt.matshow(T3,cmap='gray')
print("EOF reached: Success");

label0 = []
label1 = []
label2 = []
label3 = []
for i in range(0,12):
    if labels[i] == 0:
        label0.append(i+1)
    if labels[i] == 1:
        label1.append(i+1)
    if labels[i] == 2:
        label2.append(i+1)
    if labels[i] == 3:
        label3.append(i+1)
print("label 0 : "+str(label0))
print("label 1 : "+str(label1))
print("label 2 : "+str(label2))
print("label 3 : "+str(label3))



from mpl_toolkits.mplot3d import Axes3D


fig = plt.figure(figsize=(7,7))
ax = fig.add_subplot(111, projection='3d')

bub = np.array([Data_new[0,:],Data_new[4,:],Data_new[6,:]])
stw = np.array([Data_new[1,:],Data_new[7,:],Data_new[9,:]])
bri = np.array([Data_new[2,:],Data_new[8,:],Data_new[10,:]])
brk = np.array([Data_new[3,:],Data_new[5,:],Data_new[11,:]])
cen = np.array([centroids[0,:],centroids[1,:],centroids[2,:],centroids[3,:]])

ax.scatter(bub[:,0], bub[:,1], bub[:,2], c='r', marker='o')
#ax.text("1", "2", "3", color='red')
ax.scatter(stw[:,0], stw[:,1], stw[:,2], c='b', marker='s')
ax.scatter(bri[:,0], bri[:,1], bri[:,2], c='m', marker='*')
ax.scatter(brk[:,0], brk[:,1], brk[:,2], c='g', marker='^')
ax.scatter(cen[:,0], cen[:,1], cen[:,2], c='k', marker='D')

ax.set_xlabel('Principal Component 1')
ax.set_ylabel('Principal Component 2')
ax.set_zlabel('Principal Component 3')

plt.show()


