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
	
	/*short ***ImageG2 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG2[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG2[i][j] = new short[1];
		} 	
	}*/
	
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

	
	

	cout<<"fffff";
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
					cout<<"danger";				
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
	
	
	
	for (int i = 150; i<160 + n ;i++)
	{
		for (int j = 110; j<120 + n ;j++)
		{
			cout<<ImageG1[i][j][0]<<" ";
		}
		cout<<endl;
	}
	
	
	cout<<"***********"<<endl;
	
	for (int i = 0; i<height  ;i++)
	{
		for (int j = 0; j<width  ;j++)
		{
			imageout[i][j][0] = (unsigned char)(int)(ImageG1 [i+n][j+n][0]*255);
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

	/*for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageG2[i][j];

		delete[] ImageG2[i];
	}
	delete[] ImageG2;*/
	
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
	
	
	
	if (!(file=fopen(argv[2],"wb"))) { 	// Write image data (filename specified by second argument) from image data matrix
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*1, file);
	fclose(file);

	return 0;
}



