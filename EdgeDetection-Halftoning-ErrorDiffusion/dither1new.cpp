/*Name: Royston Marian Mascarenhas 
   Submission date: 12th February, 2019*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<random>
#include<cstdlib>
using namespace std;

const int width = 400;
const int height = 600;
const int Ireq = 2; //*****************ORDER OF DITHERING MATRIX IS HERE
//const int n = 1;



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
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char imageout [height][width][1];

	//*********************************GENERATE DITHER MATRIX************************************************
	int I2 [2][2] = {{1,2},{3,0}};
	int I2f [4];
	int z = 0;
	for (int i = 0;i<=1;i++)
	{
		for(int j =0;j<=1;j++)
		{
			I2f[z] = I2[i][j];
			z++;
		}
	}
	int I4 [4][4];
	/*int q = 0;
	for (int i = 0;i<2;i++)
	{
		for(int j =0;j<2;j++)
		{
			I4[i][j] = 4*I2f[q]+1;
			q ++;
		}
	}
	q = 0;
	for (int i = 0;i<2;i++)
	{
		for(int j =2;j<4;j++)
		{
			I4[i][j] = 4*I2f[q]+2;
			q ++;
		}
	}
	q = 0;
	for (int i = 2;i<4;i++)
	{
		for(int j =0;j<2;j++)
		{
			I4[i][j] = 4*I2f[q]+3;
			q++;
		}
	}
	q = 0;
	for (int i = 2;i<4;i++)
	{
		for(int j =2;j<4;j++)
		{
			I4[i][j] = 4*I2f[q];
			q++;
		}
	}*/
	int n1 = 4;
	int q = 0;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I4[i][j] = 4*I2f[q]+1;
			q ++;
		}
	}
	q = 0;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I4[i][j] = 4*I2f[q]+2;
			q ++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I4[i][j] = 4*I2f[q]+3;
			q++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I4[i][j] = 4*I2f[q];
			q++;
		}
	}
	//**** I8
	int I4f[16];
	z = 0; // flatten into 1d array
	for (int i = 0;i<4;i++)
	{
		for(int j =0;j<4;j++)
		{
			I4f[z] = I4[i][j];
			z++;
		}
	}
	int I8 [8][8];
	q = 0;
	n1 = 8;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I8[i][j] = 4*I4f[q]+1;
			q ++;
		}
	}
	q = 0;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I8[i][j] = 4*I4f[q]+2;
			q ++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I8[i][j] = 4*I4f[q]+3;
			q++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I8[i][j] = 4*I4f[q];
			q++;
		}
	}
	//**************I16
	int I8f[64];
	z = 0; // flatten into 1d array
	for (int i = 0;i<8;i++)
	{
		for(int j =0;j<8;j++)
		{
			I8f[z] = I8[i][j];
			z++;
		}
	}
	int I16 [16][16];
	q = 0;
	n1 = 16;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I16[i][j] = 4*I8f[q]+1;
			q ++;
		}
	}
	q = 0;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I16[i][j] = 4*I8f[q]+2;
			q ++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I16[i][j] = 4*I8f[q]+3;
			q++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I16[i][j] = 4*I8f[q];
			q++;
		}
	}
	
	// ************ I 32
	
	
	int I16f[256];
	z = 0; // flatten into 1d array
	for (int i = 0;i<16;i++)
	{
		for(int j =0;j<16;j++)
		{
			I16f[z] = I16[i][j];
			z++;
		}
	}
	/*for (int i = 0;i<16;i++)
	{
		for(int j =0;j<16;j++)
		{
			cout<<I16[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int j =0;j<256;j++)
		{
			cout<<I16f[j]<<" ";
		}
	cout<<endl<<"**************************"<<endl;*/
	int I32 [32][32];
	q = 0;
	n1 = 32;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I32[i][j] = 4*I16f[q]+1;
			q ++;
		}
	}
	q = 0;
	for (int i = 0;i<(n1/2);i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I32[i][j] = 4*I16f[q]+2;
			q ++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =0;j<(n1/2);j++)
		{
			I32[i][j] = 4*I16f[q]+3;
			q++;
		}
	}
	q = 0;
	for (int i = (n1/2);i<n1;i++)
	{
		for(int j =(n1/2);j<n1;j++)
		{
			I32[i][j] = 4*I16f[q];
			q++;
		}
	}
	/*
	for (int i = 0;i<32;i++)
	{
		for(int j =0;j<32;j++)
		{
			cout<<I32[i][j]<<" ";
		}
		cout<<endl;
	}*/
	
	int DitherMatrix[Ireq][Ireq];	
	switch (Ireq)
	{
		case 2:
			{
				for (int i=0;i<Ireq;i++)
				{
					for (int j=0;j<Ireq;j++)
					{
						DitherMatrix[i][j]= I2[i][j];
					}

				}
				break;
			}
		case 4:
			{
				for (int i=0;i<Ireq;i++)
				{
					for (int j=0;j<Ireq;j++)
					{
						DitherMatrix[i][j]= I4[i][j];
					}

				}
				break;
			}
		case 32:
			{
				for (int i=0;i<Ireq;i++)
				{
					for (int j=0;j<Ireq;j++)
					{
						DitherMatrix[i][j]= I32[i][j];
					}

				}
				break;
			}
		default:
			cout<<endl<<"INVALID VALUE. PLEASE ENTER ONLY  2,8 OR 32 AS IREQ FOR THE ORDER OF DITHERING MATRIX"<<endl;
			break;
	}
	cout<<"Dither Matrix"<<endl;
	
				cout<<endl;
				
	float **Tmatrix = new float*[Ireq]; 
	for(int i=0;i<Ireq;i++){
	    Tmatrix[i] = new float[Ireq];	
	}
	
	for (int i=0;i<Ireq;i++)
	{
		for(int j=0;j<Ireq;j++)
		{
			Tmatrix[i][j] = (DitherMatrix[i][j] + 0.5) * (255.0/(Ireq*Ireq));
		}
	}
	for (int i=0;i<Ireq;i++)
				{
					for (int j=0;j<Ireq;j++)
					{
						/*int t = Tmatrix[i][j];
						if(t>255 or t<0) {
							cout<<"FAIL ";
						}*/
						cout<<Tmatrix[i][j]<<" ";
					}
					cout<<endl;
				}	
	for(int i = 0;i < height;i++){
		for(int j=0;j<width;j++){
			float temp1 = (float) Imagedata[i][j][0];
			float temp2 =  (float) Tmatrix[i%Ireq][j%Ireq];
			/*if(temp1>temp2){
			}
			else 
			{
				imageout[i][j][0]= 0;
			}*/
			if (temp1>=0 and temp1 <=temp2){
				imageout[i][j][0] = (unsigned char)0;
			}
			else if(temp1 > temp2 and temp1 < 256){
				imageout[i][j][0] = (unsigned char)255;
			}
			
		}
	}
	for (int i = 0; i < Ireq; i++)
	{
		delete[] Tmatrix[i];
	}

	delete[] Tmatrix;
	
	//cout<<endl<<(int)ImageG1[221][307][0];
	//<<endl<<(int)gradientX[221][307][0];

	if (!(file=fopen(argv[2],"wb"))) { 	// Write image data (filename specified by second argument) from image data matrix
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*1, file);
	fclose(file);

	return 0;
}
