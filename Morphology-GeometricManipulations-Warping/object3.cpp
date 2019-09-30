/*Name: Royston Marian Mascarenhas 
   Submission date: 12TH February, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

//threshold is calculated manually after observing the cdf in the output console

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<random>
#include<cstdlib>
#include<fstream>
using namespace std;

const int width = 690;
const int height = 500;
const int n = 1;



int main(int argc, char *argv[])

{
	cout<<"here";
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "pro2gram_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 3; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[height][width][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//unsigned char ImageG [height][width][1];
	float temp;
	int nHeight = height + 2*n ,nWidth = width + 2*n;
	short ***ImageG1 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG1[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG1[i][j] = new short[1];
		} 	
	}
	
	short **ImageG2pre = new short*[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG2pre[i] = new short[nWidth];
	}
	
	short **ImageP1 = new short*[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageP1[i] = new short[nWidth];
	}
	
	short ***ImageM1 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageM1[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageM1[i][j] = new short[1];
		} 	
	}
	
	short ***ImageG2 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG2[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG2[i][j] = new short[1];
		} 	
	}
	
	short ***ImageG3 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG3[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG3[i][j] = new short[1];
		} 	
	}
		
	unsigned char ***ImageG = new unsigned char**[height]; 
	for(int i=0;i<height;i++){
	    ImageG[i] = new unsigned char*[width];
	    for (int j=0;j<width;j++){
	    	ImageG[i][j] = new unsigned char[1];
		} 	
	}
	
	int ***gradmg1 = new int**[height]; 
	for(int i=0;i<height;i++){
	    gradmg1[i] = new int*[width];
	    for (int j=0;j<width;j++){
	    	gradmg1[i][j] = new int[1];
		} 	
	}
	
	
	

 	for (int i=0;i<height;i++)
 	{
 		for(int j=0;j<width;j++)
 		{
 		temp =(float(Imagedata[i][j][0]) + float(Imagedata[i][j][1]) + float(Imagedata[i][j][2]))/3.0;	
 		ImageG[i][j][0] = (unsigned char)(temp);
		}
	}
	
	
	//**********************************BOUNDARY EXTENSION************************************************************
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			ImageG1[i][j][0] = ImageG[i-n][j-n][0];
		}
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			ImageG1[i][j][0] = ImageG1[n][j][0];
		}
	}
	
	for(int i=nHeight-n;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			ImageG1[i][j][0] = ImageG1[nHeight-n-1][j][0];
		}
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<nHeight;j++)
		{
			ImageG1[j][i][0] = ImageG1[j][n][0];
		}
	}
	for(int i=nWidth-n;i<nWidth;i++)
	{
		for(int j=0;j<nHeight;j++)
		{
			ImageG1[j][i][0] = ImageG1[j][nWidth-n-1][0];
		}
	}
 	//******************************************************************************************************
	
	//***********************************************FINDING THE CDF***********************************
	
	cout<<"################";
	cout<<"ddddddddddddddddddddddddddddd";
	
	for (int i = 60; i<70 + n ;i++)
	{
		for (int j = 60; j<70 + n ;j++)
		{
			cout<<ImageG1[i][j][0]<<" ";
		}
		cout<<endl;
	}
		cout<<"hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";

	unsigned char imageout[height][width][1];
			cout<<"hmmmmd77777mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";

	for(int i = n;i<height+n;i++){
		for(int j=n;j<width+n;j++){
			if ( (int(Imagedata[i][j][2])>30)){
				ImageG3[i][j][0] = 0;
			}
			else{
				ImageG3[i][j][0] = 1;
			}
		}
	}
		cout<<"hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";
	cout<<"ff";
	for (int i = n; i<height + n ;i++)
	{
		for (int j = n; j<width + n ;j++)
		{
			if (((ImageG1[i][j][0])>=65) and ((ImageG1[i][j][0])<=77))
			//if (((ImageG1[i][j][0])==73))
			{
				ImageG1[i][j][0] = 0;
				//imageout[i-n][j-n][0] = (unsigned char)0;
			}
			else
			{
				ImageG1[i][j][0] = 1;
				//imageout[i-n][j-n][0] =(unsigned char) 255;
			}
			
		}
	}
		cout<<"hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";
cout<<"ff";
	for(int i = n;i<height+n;i++){
		for(int j=n;j<width+n;j++){
			int t = ImageG1[i][j][0] || ImageG3[i][j][0];
			ImageG1[i][j][0] = t;
		}
	}
	
	/*for (int i = n; i<height + n ;i++)
	{
		for (int j = n; j<width + n ;j++)
		{
			ImG[i][j] = ImageG1[i][j][0]/255;
			ImageG1[i][j][0] = ImageG1[i][j][0]/255;
		}
	}*/
	
	
	
	int mask1[9] = {1,1,1,1,1,1,1,1,1};
	int i1_mask[9] = {1,1,1,1,0,1,1,1,1};
	int i2_mask[9] = {0,0,0,0,1,0,0,0,0};
	int fmod = 0;
	int flag5 = 0 ;
//for(int h = 0;h<10;h++)
//{
	/*if(flag5 == 1){
		for (int i = n; i<height + n ;i++)
		{
		for (int j = n; j<width + n ;j++)
			{
				ImageG1[i][j][0] = ImageG2[i][j][0];
			}
		}
			
		
	}*/
	
	/*for (int i = n; i<height + n ;i++)
	{
		for (int j = n; j<width + n ;j++)
		{
			int m = 0;
			fmod  = 0 ;
			for(int r = 0;r<1;r++){
				int i1 = 0, count = 0;
				for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						if ((ImageG1[k][l][0])==(i1_mask[i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				if (count == 9){
					m = 1;
					fmod = 1;
				}
			}
			
			if (fmod != 1){
			for(int r = 0;r<1;r++){
				int i1 = 0, count = 0;
				for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						if ((ImageG1[k][l][0])==(i2_mask[i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				if (count == 9){
					m = 0;
					fmod = 1;
				}
			}
			}
			
			if(fmod==1)
			{
				ImageG1[i][j][0] = m;
			}
			else
			{
				ImageG1[i][j][0] = ImageG1[i][j][0];
			}
			
		}
	}
	flag5 = 1;
}*/
	//	cout<<"hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm";

for (int i = n; i<height + n ;i++)
	{
		for (int j = n; j<width + n ;j++)
		{
			int m = 0;
			fmod  = 0 ;
			for(int r = 0;r<1;r++){
				int i1 = 0, count = 0;
				for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						if ((ImageG1[k][l][0])==(mask1[i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				if (count == 9){
					m = 1;
					fmod = 1;
				}
			}
			
			if(fmod==1)
			{
				ImageG3[i][j][0] = m;
			}
			else{
				ImageG3[i][j][0] = 0;
			}
			
		}
	}
	cout<<"hghghgh";
	cout<<"asfds";
	cout<<"ggg";
	cout<<"fff";
	for (int i = n+1; i<height + n-1 ;i++)
	{
		for (int j = n+1; j<width + n-1 ;j++)
		{
			int m = 0;
			fmod  = 0 ;
			int i1 = 0, count = 0;
			int ar[25];
			int a1=0;
			for (int k = i-2;k<=i+2;k++){
				for(int l = j-2;l<=j+2;l++){
					ar[a1] = ImageG3[k][l][0];
					a1++;
				}
			}
				
			count = 0;
			for(int y = 0;y<25;y++){
			if(ar[y]==1){
				count = count + 1;
			}
			}
			if (count > 17){
				ImageG1[i][j][0] = 1;
			}
			else{
				ImageG1[i][j][0] = 0;
			}
			
		}
	}
	
		cout<<"heeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<endl;

	int i1_mask2[4][25] = {{0,0,0,0,0,
							0,0,0,0,0,
							0,1,1,1,0,
							0,0,0,1,0,
							0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
						{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1}};

	
	

	cout<<"fffffrrrrrrrrrrrrrrrrrrrrrrrr";
	for (int i = n + int(height/10); i<height + n -  3 ;i++)
	{
		for (int j = n + int(width/10); j<width + n - 3 ;j++)
		{
			fmod  = 0 ;
			for(int r = 0;r<4;r++){
				int i1 = 0, count = 0;
				for (int k = i-2;k<=i+2;k++){
					for(int l = j-2;l<=j+2;l++){
						if ((ImageG1[k][l][0])==(i1_mask2[r][i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				if (count == 25 and r==0){
					ImageG1[i][j][0] = 0;
					ImageG1[i][j-1][0] = 0;
					ImageG1[i][j+1][0] = 0;
					ImageG1[i+1][j+1][0] = 0;	
				}
				else if(count == 25 and r==1){
					ImageG1[i][j][0] = 0;
					ImageG1[i+1][j][0] = 0;	
					//cout<<"danger";
					
				}
				else if(count==25 and r==2){
					ImageG1[i][j][0] = 0;
				}
				else if(count==25 and r==3){
					ImageG1[i][j][0] = 1;
				}
			}
			
			
			
		}
	}
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
	cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
	int cs1 = 0;
	int cs2 = 0;
	int cs3 = 0;
	int cs4 = 0;
	int cs5 = 0;
	int cs6 = 0;
	int cs7 = 0;
	int cs8 = 0;
	int cs9 = 0;
	int cs10 = 0;
	int cs11 = 0;
	
			for (int x = 0;x<133;x++){
				for (int y = 0;y<232;y++){
					if (ImageG1[x][y][0]==1){
						cs1++;
					}
				}
			}
			for (int x = 0;x<133;x++){
				for (int y = 232;y<457;y++){
					if (ImageG1[x][y][0]==1){
						cs2++;
					}
				}
			}
			
			for (int x = 0;x<133;x++){
				for (int y = 457;y<680;y++){
					if (ImageG1[x][y][0]==1){
						cs3++;
					}
				}
			}

			for (int x = 133;x<280;x++){
				for (int y = 0;y<232;y++){
					if (ImageG1[x][y][0]==1){
						cs4++;
					}
				}
			}
			
			
			for (int x = 133;x<280;x++){
				for (int y = 232;y<457;y++){
					if (ImageG1[x][y][0]==1){
						cs5++;
					}
				}
			}
			
			for (int x = 133;x<280;x++){
				for (int y = 457;y<680;y++){
					if (ImageG1[x][y][0]==1){
						cs6++;
					}
				}
			}
			
			
			for (int x = 280;x<390;x++){
				for (int y = 0;y<232;y++){
					if (ImageG1[x][y][0]==1){
						cs7++;
					}
				}
			}
			
			
			for (int x = 280;x<390;x++){
				for (int y = 232;y<457;y++){
					if (ImageG1[x][y][0]==1){
						cs8++;
					}
				}
			}
			for (int x = 280;x<390;x++){
				for (int y = 457;y<680;y++){
					if (ImageG1[x][y][0]==1){
						cs9++;
					}
				}
			}
									cout<<"%%%%%%%%%%";

			for (int x = 390;x<490;x++){
				for (int y = 0;y<360;y++){
					if (ImageG1[x][y][0]==1){
						cs10++;
					}
				}
			}
									cout<<"@)@)@)@)";

			
			for (int x = 390;x<490;x++){
				for (int y = 360;y<680;y++){
					if (ImageG1[x][y][0]==1){
						cs11++;
					}
				}
			}
	

cout<<"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";
cout<<endl<<"************************SIZE OF GRAINS*************************"<<endl;
float seeds[11] = {cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9,cs10,cs11};
for (int i= 0;i<11;i++){
	seeds[i] = seeds[i] / 5;
	
	
}
for (int i= 0;i<11;i++){
	cout<<"seed "<<i+1<<" has size "<<seeds[i]<<endl;
}
int tempi;
	int pos[11]={1,2,3,4,5,6,7,8,9,10,11};
	int len = 11;
    int temp1 = 0,temp2 = 0;
    cout<<"lll";
        for(int i=0; i < n; i++){
        	for(int j=1; j < (len-i); j++){
                if(seeds[j-1] > seeds[j]){
                    temp1 = seeds[j-1];
                    temp2 = pos[j-1];
                    seeds[j-1] = seeds[j];
                    pos[j-1] = pos[j];
                    seeds[j] = temp1;
                    pos[j]= temp2;
                }
	
}
}
cout<<endl<<"IN ASCENDING ORDER";
for (int i= 0;i<11;i++){
	cout<<"seed "<<pos[i]<<" has size "<<seeds[i]<<endl;
}
cout<<endl<<"************************SIZE OF GRAINS ENDS*************************"<<endl;
	cout<<"(((("<<endl;
		//short ImageG2pre [nHeight][nWidth];
	cout<<"^^^^^^^^^^";
		short s1[4][9] = {{0,0,1,0,1,0,0,0,0},
				{1,0,0,0,1,0,0,0,0},
				{0,0,0,0,1,0,1,0,0},
				{0,0,0,0,1,0,0,0,1}};
	
	short s2[4][9] = {{0,0,0,0,1,1,0,0,0},
					  {0,1,0,0,1,0,0,0,0},
					  {0,0,0,1,1,0,0,0,0},
					  {0,0,0,0,1,0,0,1,0}};
					  
					  
	short s3[8][9] = {{0,0,1,0,1,1,0,0,0},
					  {0,1,1,0,1,0,0,0,0},
					  {1,1,0,0,1,0,0,0,0},
					  {1,0,0,1,1,0,0,0,0},
					  {0,0,0,1,1,0,1,0,0},
					  {0,0,0,0,1,0,1,1,0},
					  {0,0,0,0,1,0,0,1,1},
					  {0,0,0,0,1,1,0,0,1}};
					  
	short stk4[4][9] = {{0,0,1,0,1,1,0,0,1},
					  {1,1,1,0,1,0,0,0,0},
					  {1,0,0,1,1,0,1,0,0},
					  {0,0,0,0,1,0,1,1,1}};
					  
	short st5[8][9] = {{1,1,0,0,1,1,0,0,0},
					  {0,1,0,0,1,1,0,0,1},
					  {0,1,1,1,1,0,0,0,0},
					  {0,0,1,0,1,1,0,1,0},
					  {0,1,1,0,1,1,0,0,0},
					  {1,1,0,1,1,0,0,0,0},
					  {0,0,0,1,1,0,1,1,0},
					  {0,0,0,0,1,1,0,1,1}};
					  
	short st6[2][9] = {{1,1,0,0,1,1,0,0,1},
					  {0,1,1,1,1,0,1,0,0}};
					  
	short stk6[8][9] = {{1,1,1,0,1,1,0,0,0},
					  {0,1,1,0,1,1,0,0,1},
					  {1,1,1,1,1,0,0,0,0},
					  {1,1,0,1,1,0,1,0,0},
					  {1,0,0,1,1,0,1,1,0},
					  {0,0,0,1,1,0,1,1,1},
					  {0,0,0,0,1,1,1,1,1},
					  {0,0,1,0,1,1,0,1,1}};

	short stk7[4][9] = {{1,1,1,0,1,1,0,0,1},
					  {1,1,1,1,1,0,1,0,0},
					  {1,0,0,1,1,0,1,1,1},
					  {0,0,1,0,1,1,1,1,1}};

	short stk8[4][9] = {{0,1,1,0,1,1,0,1,1},
					  {1,1,1,1,1,1,0,0,0},
					  {1,1,0,1,1,0,1,1,0},
					  {0,0,0,1,1,1,1,1,1}};
					  
	short stk9[8][9] = {{1,1,1,0,1,1,0,1,1},
					  {0,1,1,0,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0},
					  {1,1,1,1,1,1,0,0,1},
					  {1,1,1,1,1,0,1,1,0},
					  {1,1,0,1,1,0,1,1,1},
					  {1,0,0,1,1,1,1,1,1},
					  {0,0,1,1,1,1,1,1,1}};
					  
	short stk10[4][9] = {{1,1,1,0,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,1},
					  {1,1,1,1,1,0,1,1,1},
					  {1,0,1,1,1,1,1,1,1}};
	
	int flag2 = 0, flag1 = 0;
	cout<<"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
			
	for (int i=n;i<height+n;i++){
		for (int j=n;j<width+n;j++){
			if(ImageG1[i][j][0] == 255){
				ImageG1[i][j][0] = (ImageG1[i][j][0])/ 255;
							}
						}
					}

	/*for (int i=0;i<nHeight;i++){
		for (int j=0;j<nWidth;j++){
			if(ImageG1[i][j][0] != 1 and ImageG1[i][j][0] != 0){
				cout<<"**FAIL**"<<ImageG1[i][j][0];
							}
						}
					}*/
	int c = 0;
	while(flag1==0){
	//for (int b = 0;b<1;b++){
	if (flag2 == 1){
	for (int i=n;i<height+1;i++)
	{
		for (int j=n;j<width+1;j++)
		{
			ImageG1[i][j][0] = ImageG2[i][j][0];
		}
	}
	
	}
	
	
	c = c + 1;
	if (c > 60)
	{
		cout<<"c is "<<c<<endl;
	}

	
	for (int i=n;i<height+1;i++)
	{
		for (int j=n;j<width+1;j++)
		{
			int m = 0;
			/*if (i==119 and j==104)
			{
				cout<<"caught you "<<ImageG1[i][j][0]<<" m is "<<m<<endl;
			for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						cout<<ImageG1[k][l][0]<<" ";
					}
				}
			cout<<endl;
		    }*/
		    
			for(int r = 0;r<4;r++){
				int i1 = 0, count = 0;
				for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						//cout<<"I"<<ImageG1[k][l][0]<<" ";
						//cout<<"M"<<s1[r][i1]<<" ";
						if ((ImageG1[k][l][0])==(s1[r][i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				//cout<<endl<<"count is "<<count; 
				if (count == 9){
					m = 1;
					if (i==119 and j==104){ cout<<endl<<"MATCH IN S1 "<<endl;}
				}
				//cout<<endl;
			}
						
			//cout<<" m is "<<m;
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageG1[k][l][0])==(s2[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN S2 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Ms3-"<<s3[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(s3[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN S3 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk4-"<<stk4[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk4[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk4 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mst5-"<<st5[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(st5[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN St5 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mst6-"<<st6[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(st6[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN St6 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk6-"<<stk6[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk6[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk6 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk7-"<<stk7[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk7[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk7 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk8[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk8 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk9-"<<stk9[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk9[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					
					
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk9 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk9-"<<stk9[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk10[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk10 "<<endl;}
					}
					//cout<<endl;
				}
			}
			//cout<<" m is "<<m;
			if (i==119 and j==104)
			{
				cout<<"caught you "<<ImageG1[i][j][0]<<" m is "<<m<<endl;
				cout<<endl;
		    }
			ImageM1 [i][j][0] = m; 	
			
		}
	}
	
	
	
	
	
	for (int i=1;i<height+1;i++){
		for (int j=1;j<width+1;j++){
			if(ImageM1[i][j][0] != 1 and ImageM1[i][j][0] != 0){
				cout<<"**FAILOOOO "<<(int)ImageM1[i][j][0]<<" "<<i<<" "<<j<<"***";
			}
		}
	}
	
	for (int i=1;i<height+1;i++)
	{
		for (int j=1;j<width+1;j++)
		{
			int m = ImageM1[i][j][0];
			
			int a = 0, b= 0, c = 0, d = 2;
			
			int p = 0;
			if (i==120 and j==106)
			{
				cout<<"caught you P "<<ImageM1[i][j][0]<<" p is "<<p<<endl;
			for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						cout<<ImageM1[k][l][0]<<" ";
					}
				}
			cout<<endl;
		    }
			
			int spur[2][9] = {{0,0,m,0,m,0,0,0,0},{m,0,0,0,m,0,0,0,0}};
			for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(spur[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN Spur "<<endl;}
					}
					//cout<<endl;
				}
			
			int single4c [2][9] = {{0,0,0,0,m,0,0,m,0},{0,0,0,0,m,m,0,0,0}};
			if(p!=1){
			for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(single4c[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN Single4c "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		int lcluster [8][9] = {{0,0,m,0,m,m,0,0,0},
									{0,m,m,0,m,0,0,0,0},
									{m,m,0,0,m,0,0,0,0},
									{m,0,0,m,m,0,0,0,0},
									{0,0,0,m,m,0,m,0,0},
									{0,0,0,0,m,0,m,m,0},
									{0,0,0,0,m,0,0,m,m},
									{0,0,0,0,m,m,0,0,m}};
		if(p!=1){
			for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(lcluster[r][i1])){
								count = count + 1;
							}
								i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN lcluster "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		int con4off [4][9] ={{0,m,m,m,m,0,0,0,0},
								{m,m,0,0,m,m,0,0,0},
								{0,m,0,0,m,m,0,0,m},
								{0,0,m,0,m,m,0,m,0}};
		if(p!=1){
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(con4off[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN con4off "<<endl;}
						//break;
					}
					//cout<<endl;
				}	
		}
		
		int spurcorn [4][9] = {{0,a,m,0,m,b,m,0,0},
								{m,b,0,a,m,0,0,0,m},
								{0,0,m,a,m,0,m,b,0},
								{m,0,0,0,m,b,0,a,m}};
		//a
		spurcorn[0][1]=1; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=0;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 1; b= 0;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}	
		}
		
		//a
		spurcorn[0][1]=0; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=1;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 0; b= 1;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		//a
		spurcorn[0][1]=1; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=1;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 1; b= 1;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}
	}
	
	int cornclust [9] = {m,m,d,m,m,d,d,d,d};
	if(p!=1){
			 //corner cluster
			for(int r = 0;r<1;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if (cornclust[i1] == 0 or cornclust[i1] == 1){
								if ((ImageM1[k][l][0])==(cornclust[i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
				
					if (count == 4){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN cornclust "<<endl;}
					}
				}
		}
		
		int teebranch [8][9]={{d,m,0,m,m,m,d,0,0},
								{0,m,d,m,m,m,0,0,d},
								{0,0,d,m,m,m,0,m,d},
								{d,0,0,m,m,m,d,m,0},
								{d,m,d,m,m,0,0,m,0},
								{0,m,0,m,m,0,d,m,d},
								{0,m,0,0,m,m,d,m,d},
								{d,m,d,0,m,m,0,m,0}};
		if(p!=1){
			d = 2; //teebranch
			for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if (teebranch[r][i1] == 0 or teebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(teebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					if (count == 7){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN teebranch "<<endl;}
					}
				}
		}
			//*******VEEBRANCH************************************
		int veebranch [4][9] = {{m,d,m,d,m,d,a,b,c},
								{m,d,c,d,m,b,m,d,a},
								{c,b,a,d,m,d,m,d,m},
								{a,d,m,b,m,d,c,d,m}};
		//a
		veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
		
		//a
		veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		//a
		veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		//a
		veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}

						//break;
					}
					//cout<<endl;
				}
		}
	
		//a
		veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
	
		//a
		veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
												if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}

						//break;
					}
					//cout<<endl;
				}
		}
	
		//a
		veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
		//b
		veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
		//c
		veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
		
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 6){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
	
	//***DIAGBRANCH	
		int diagbranch [4][9] = {{d,m,0,0,m,m,m,0,d},
								{0,m,d,m,m,0,d,0,m},
								{d,0,m,m,m,0,0,m,d},
								{m,0,d,0,m,m,d,m,0}};
		if (i==120 and j==106){	
		cout<<"culprit ";
		for (int c1 = 0;c1<9;c1++){
			cout<<diagbranch[0][c1]<<" ";
		}
	}
		if(p!=1){
			//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (diagbranch[r][i1] == 0 or diagbranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(diagbranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 7){
						p = 1;
												if (i==120 and j==106){ cout<<endl<<"MATCH IN diagbranch "<<r<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
			
		ImageP1[i][j] = p ;
		if (i==120 and j==106)
			{
				cout<<"caught you "<<ImageP1[i][j]<<" p is "<<p<<endl;
				cout<<endl;
		    }	
			
		}
	}
					
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
				int xf = ImageG1[i][j][0];
				int mf = ImageM1[i][j][0];
				if (mf==1)
				{
					mf = 0;
				}
				else 
				{
					mf = 1;
				}
				int pf = ImageP1[i][j];
				ImageG2 [i][j][0] = xf & (mf | pf);
		}
	}
	

	
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
				int xf = ImageG1[i][j][0];
				int mf = ImageM1[i][j][0];
				if (mf==1)
				{
					mf = 0;
				}
				else 
				{
					mf = 1;
				}
				int pf = ImageP1[i][j];
				ImageG2 [i][j][0] = xf & (mf | pf);
		}
	}
	
	int count_final = 0;
	if (flag2==1)
	{
		for (int i=n;i<height+n;i++)
		{
			for(int j=n;j<width+n;j++)
			{
				if (ImageG2pre[i][j] == ImageG2[i][j][0])
				{
					count_final = count_final + 1;
				}
			}
		}
		if (count_final == height * width){
			flag1 = 1;
			cout<<"count_finao is "<<count_final;
		}
	}
		
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			ImageG2pre[i][j] = ImageG2[i][j][0];
		}
	}
	flag2 = 1;
}


	
	cout<<"comeonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";
	cout<<"comeononononononon";
	for (int i = 150; i<160 + n ;i++)
	{
		for (int j = 110; j<120 + n ;j++)
		{
			cout<<ImageG1[i][j][0]<<" ";
		}
		cout<<endl;
	}
	
	
	cout<<"***********"<<endl;
	
	int l_count = 0;
	for (int i=n;i<height+n - 5;i++)
	{
		for(int j=n;j<width+n - 5;j++)
		{
			if(ImageG2pre[i][j] == 1){
				l_count ++;
			}
		}
	}
	cout<<endl<<"********************************"<<endl<<"The final count of grains is "<<l_count<<endl<<"*************************"<<endl;
	
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			imageout[i-n][j-n][0] = (unsigned char)(ImageG2pre[i][j]*255);
		}
	}
	
	/*for (int i = 0; i<height  ;i++)
	{
		for (int j = 0; j<width  ;j++)
		{
			imageout[i][j][0] = (unsigned char)(int)(ImageG[i][j][0]);
		}
	}*/
	for (int i = 60; i<70 + n ;i++)
	{
		for (int j = 60; j<70 + n ;j++)
		{
			cout<<(int)imageout[i][j][0]<<" ";
		}
		cout<<endl;
	}
	
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageG1[i][j];

		delete[] ImageG1[i];
	}
	delete[] ImageG1;

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageG2[i][j];

		delete[] ImageG2[i];
	}
	delete[] ImageG2;
	
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageG3[i][j];

		delete[] ImageG3[i];
	}
	delete[] ImageG3;
		
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] gradmg1[i][j];

		delete[] gradmg1[i];
	}
	delete[] gradmg1;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] ImageG[i][j];

		delete[] ImageG[i];
	}
	delete[] ImageG;
	
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageM1[i][j];

		delete[] ImageM1[i];
	}
	delete[] ImageM1;
	
	for (int i = 0; i < nHeight; i++)
	{

		delete[] ImageP1[i];
	}
	delete[] ImageP1;
	
	for (int i = 0; i < nHeight; i++)
	{

		delete[] ImageG2pre[i];
	}
	delete[] ImageG2pre;
	
	if (!(file=fopen(argv[2],"wb"))) { 	// Write image data (filename specified by second argument) from image data matrix
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*1, file);
	fclose(file);

	return 0;
}



