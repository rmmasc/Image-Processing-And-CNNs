/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

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
	unsigned char Imagedata[300][390][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 300*390*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char imageout[300][390][3];
	int i,j,k;
	float temp1;
	
	for (i=0;i<10;i++)
	{
		cout<<endl;
		for(j=0;j<10;j++)
		{
			cout<<" ** ";
			cout<<(int)Imagedata[i][j][0]<<" ";
		}
	}
	//Imagedata = (unsigned int)(imageout);
	for (i=0;i<300;i++)
	{
		for(j=0;j<390;j++)
			{
			if (i%2 == 0 and j%2 == 0) //top green
				{
					//red, green and blue values 
					temp1= 0.5*(float(Imagedata[i][j+1][0]) + float(Imagedata[i][j-1][0]));
					//cout<<"temp1"<<temp1<<"temp1";
					imageout[i][j][0] = (unsigned char)(int(temp1));
					//cout<<" ??** "<<imageout[i][j][0]<<" **?? ";
					imageout[i][j][1] = Imagedata[i][j][0];
					temp1=0.5*(float(Imagedata[i+1][j][0]) + float(Imagedata[i-1][j][0]));	
					imageout[i][j][2] = (unsigned char)(int(temp1)); 
					 
				}
			else if  (i%2 != 0 and j%2 != 0) //bottom green
				{
					//red, green and blue values
					temp1 =  0.5 * (float(Imagedata[i+1][j][0]) + float(Imagedata[i-1][j][0]));
					imageout[i][j][0] = (unsigned char)(int(temp1));
					imageout[i][j][1] = Imagedata[i][j][0];	
					temp1 = 0.5* (float(Imagedata[i][j+1][0]) + float(Imagedata[i][j-1][0]));
					imageout[i][j][2] =	(unsigned char)(int(temp1)); 		
				}
			else if (i%2 == 0 and j%2 != 0) //red
				{
					//red, green and blue values 
					imageout[i][j][0] = Imagedata[i][j][0];
					temp1 = 0.25 * (float(Imagedata[i][j+1][0]) + float(Imagedata[i][j-1][0]) + float(Imagedata[i+1][j][0]) + float(Imagedata[i-1][j][0]));
					imageout[i][j][1] =(unsigned char)(int(temp1)); 
					temp1 = 0.25 * (float(Imagedata[i+1][j+1][0]) + float(Imagedata[i+1][j-1][0]) + float(Imagedata[i-1][j+1][0]) + float(Imagedata[i-1][j-1][0]));
					imageout[i][j][2] =	(unsigned char)(int(temp1));
				}
			else if (i%2 != 0 and j%2 == 0) //blue
				{
					//red, green and blue values
					temp1 = 0.25*(float(Imagedata[i+1][j+1][0]) + float(Imagedata[i+1][j-1][0]) + float(Imagedata[i-1][j+1][0]) + float(Imagedata[i-1][j-1][0]));
					imageout[i][j][0] = (unsigned char)(int(temp1));
					temp1 = 0.25*(float(Imagedata[i][j+1][0]) + float(Imagedata[i][j-1][0]) + float(Imagedata[i+1][j][0]) + float(Imagedata[i-1][j][0]));
					imageout[i][j][1] =(unsigned char)(int(temp1));
					imageout[i][j][2] = Imagedata[i][j][0];
				}
		}
	}
	
	
	cout<<"*******************************";
	for (i=0;i<10;i++)
	{
		cout<<endl;
		for(j=0;j<10;j++)
		{
			cout<<" ** ";
			for(k=0;k<3;k++)
			{
				cout<<(int)imageout[i][j][k]<<" ";
			}
		}
	}
	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 300*390*3, file);
	fclose(file);

	return 0;
}
