/*Name: Royston Marian Mascarenhas 

   Submission date: 03rd March, 2019*/
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

const int width = 550;
const int height = 691;
const int n = 1;



int main(int argc, char *argv[])

{
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
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[height][width][1];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*1, file);
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
	
	short ***ImageG1pre = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG1pre[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG1pre[i][j] = new short[1];
		} 	
	}
	
	short ***ImageG = new short**[height]; 
	for(int i=0;i<height;i++){
	    ImageG[i] = new short*[width];
	    for (int j=0;j<width;j++){
	    	ImageG[i][j] = new short[1];
		} 	
	}	

 	for (int i=0;i<height;i++)
 	{
 		for(int j=0;j<width;j++)
 		{
 		ImageG[i][j][0] =(short(Imagedata[i][j][0])/255);	
 		//ImageG[i][j][0] = (temp/255);
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
	short is_mask[5][9] = {{1,1,1,1,0,1,1,1,1},
						/*{1,0,0,0,0,0,1,0,0},
						{0,0,1,0,0,0,0,0,1},
						{1,0,1,0,0,0,0,0,0},
						{0,0,0,0,0,0,1,0,1}*/
						{1,1,0,1,0,0,1,1,0},
						{0,1,1,0,0,1,0,1,1},
						{0,0,0,1,0,1,1,1,1},
						{1,1,1,1,0,1,0,0,0}
						};
	int flag2 = 0, flag1 = 0;	
	//short ImageG1pre [nHeight][nWidth];
	cout<<"just neighbors"<<endl;
	for (int i=280;i<281;i++){
		for(int j=93;j<94;j++){
			for(int r = 0;r<5;r++){
				cout<<" m is "<<(int)Imagedata[i][j][0]<<endl;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							cout<<endl<<(int)Imagedata[k][l][0]<<" ";
					}
				}
			}
		}
	}
	
		cout<<"just neighbors end "<<endl;
		cout<<ImageG[280][89][0]<<endl;
	
	int fmod;
	int pcount = 0;
	for(int b=0;b<1;b++)
	{
	
	for (int i=n;i<height+1;i++){
		for (int j=n;j<width+1;j++){
			fmod = 0;
			int m = 0 ;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageG1[k][l][0])==(is_mask[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					if (count == 9){
						m = 1;
						pcount ++;
						fmod = 1;
						cout<<"doneitonce ";
					}
					
				}
				if(fmod==1){
						ImageG1[i][j][0] = m;
					}
		}
	}
	cout<<endl<<"**"<<pcount<<"**";
		
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			ImageG1pre[i][j][0] = ImageG1[i][j][0];
		}
	}
	flag2 = 1;
}

	unsigned char imageout[height][width][1];
	for (int i = 0; i<height  ;i++)
	{
		for (int j = 0; j<width  ;j++)
		{
			imageout[i][j][0] = (unsigned char)(int)(ImageG1 [i+n][j+n][0]*255);
		}
	}
	
	
	
	cout<<"this";
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
			delete[] ImageG1pre[i][j];

		delete[] ImageG1pre[i];
	}
	delete[] ImageG1pre;
	

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



