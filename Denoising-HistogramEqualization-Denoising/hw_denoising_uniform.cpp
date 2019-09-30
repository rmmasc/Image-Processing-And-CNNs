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
#include <math.h>

using namespace std;

unsigned char convolved(unsigned char test[9], float *p) {
    float temp1=0, temp2=0;
    for (int i=0;i<9;i++)
	{
			temp1 = float(test[i]) * (*p);
			temp2 = temp2 + temp1;			
			//cout <<"This is "<<int(test[i][j])<<" * "<<*p<<" at "<<p<<" and cum sum is "<<temp2<<endl;
			p++;
	}
	temp2 = temp2/8;
	return temp2;
}

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
	unsigned char Imagedata[256][256][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 256*256*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char imageout[256][256][BytesPerPixel];
	int Imagedata1[256][256][BytesPerPixel];
	int kernel_size = 9;
	int i,j,k,l,h=256,w=256;
	int temp1 =0;
	float temp2= 0, temp3 = 0;
	int w1 = floor((sqrt(float(kernel_size))) / 2); //window extension
	cout<<"window_ext is "<<w1;
	float kernel [kernel_size];
	float weight = 1/float(kernel_size);
	for (i=0;i<kernel_size;i++)
	{
		kernel[i] = 1;
	}
	
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			Imagedata1[i][j][0]=int(Imagedata[i][j][0]);
		}
	}
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			imageout[i][j][0] = (unsigned char)(weight*(Imagedata1[i-w1][j-w1][0] + Imagedata1[i-w1][j][0] + Imagedata1[i-w1][j + w1][0] +
			Imagedata1[i][j-w1][0] + Imagedata1[i][j][0] + Imagedata1[i][j+w1][0] +
			Imagedata1[i+1][j-w1][0] + Imagedata1[i+w1][j][0] + Imagedata1[i+w1][j+w1][0]));
		}
	}
	cout<<"wdfasdg";
	// Write image data (filename specified by second argument) from image data matrix
	cout << endl;
	

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 256*256*1, file);
	fclose(file);

	return 0;
}
