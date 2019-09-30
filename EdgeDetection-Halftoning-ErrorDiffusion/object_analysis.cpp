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

const int width = 500;
const int height = 690;
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
	cout<<"df";

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char ImageG [height][width][1];
	float temp;
	int nHeight = height + 2*n ,nWidth = width + 2*n;
	float ***ImageG1 = new float**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG1[i] = new float*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG1[i][j] = new float[1];
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
 		ImageG[i][j][0] = (unsigned char)(temp + 0.5);
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
	int count=0,num;
	int unique_val = 256;
	int check1=0;
	float check2 = 0.0;
    float freq[unique_val][5];
        cout<<"some time now";

    short skipmatrix[height][width];
	for(int i=n;i<height+n;i++){
		for(int j=n;j<width+n;j++){
			gradmg1[i][j][0]=ImageG1[i][j][0];
		}
	}
	
	for (int l=0;l<unique_val;l++)
    {	
    	freq[l][0]=1;
    	freq[l][1]=0;
    	freq[l][2]=0;
    	freq[l][3]=0;
    	freq[l][4]=0;

	}
	for(int i=0;i<height;i++)  //calculate the frequency of elements
	{
       for(int j=0; j<width;j++) 
	   {
          count=0;
          num=gradmg1[i][j][0];
          if((skipmatrix[i][j])!=1) 
		  {
          for(int k=0;k<height;k++) 
		  {
            for(int m=0;m<width;m++) 
			{
              if(gradmg1[i][j][0]==gradmg1[k][m][0]) 
			  {
                skipmatrix[k][m]=1;
                count++;
              }
            }
          }
          freq[num][0]=num;
          freq[num][1]=count;
          }
       }
   }
	//calculate the probability
	for (int i=0;i<unique_val;i++)
	{
		check1 = freq[i][1]+check1;
		freq[i][2] = freq[i][1] / (height * width);
		check2 = freq[i][2]+check2;
	}
	
	//calculate the cumulative probability and map to 0-255
	for (int i=1;i<256;i++)
	{
		freq[i][3] = freq [i][2] + freq [i-1][3];
		freq[i][4]= freq[i][3]*255;	
	}		
	cout<<endl<<"The cumulative sum is "<<check1<<" and the cumulative probability is  "<<check2<<endl;
	
	
	for(int z=0;z<unique_val;z++)
    {
   	cout<<freq[z][0]<<" : "<<freq[z][1]<<" : "<<freq[z][2]<<" : "<<freq[z][3]<<" : "<<freq[z][4]<<endl;
    }
	
	/*ofstream outfile;
	outfile.open("cdftiger1.csv");
	for(int i=0;i<256;i++)
	{
		    outfile << i << "," << freq[i][3] << std::endl;

	}
	outfile.close();*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] ImageG1[i][j];

		delete[] ImageG1[i];
	}
	delete[] ImageG1;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] gradmg1[i][j];

		delete[] gradmg1[i];
	}
	delete[] gradmg1;

	if (!(file=fopen(argv[2],"wb"))) { 	// Write image data (filename specified by second argument) from image data matrix
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImageG, sizeof(unsigned char), height*width*1, file);
	fclose(file);

	return 0;
}



