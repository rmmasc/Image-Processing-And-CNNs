/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file



/*
Name: Royston Marian Mascarenhas 

   Submission date: 22nd January, 2019
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

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
	unsigned char Imagedata[256][256][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 256*256*3, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char imageout[256][256][3];
	int Imagedata1[256][256][BytesPerPixel];
	unsigned char ImageR[256][256][1];
	unsigned char imageoutR[256][256][1];
	unsigned char imageoutR1[256][256][1];
	unsigned char ImageG[256][256][1];
	unsigned char imageoutG[256][256][1];
	unsigned char imageoutG1[256][256][1];
	unsigned char ImageB[256][256][1];
	unsigned char imageoutB[256][256][1];
	unsigned char imageoutB1[256][256][1];
	int kernel_size = 5;
	int i,j,k,l,h=256,w=256;
	int temp1 =0;
	int N = 5;
	float sigma = 5;
	float temp2= 0, temp3 = 0;
	int w1 = floor((float(kernel_size)/2));
	//int w1 = floor((sqrt(float(kernel_size))) / 2); //window extension
	cout<<"window_ext is "<<w1;
	float kernel [kernel_size];
	float weight=0,weight_sum = 0;
	
	for (i=0;i<256;i++)
	{
		for (j=0;j<256;j++)
		{
				ImageR [i][j][0] = Imagedata[i][j][0];
				ImageG [i][j][0] = Imagedata[i][j][1];
				ImageB [i][j][0] = Imagedata[i][j][2];
		}
	}
	
	//*******************************RED*****************************************************************************
	//LOW PASS MEAN / UNIFORM FILTER: removes uniform noise
	/*for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			Imagedata1[i][j][0]=int(ImageR[i][j][0]);
		}
	}
	cout<<"here";
	w1 = 2;
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			imageoutR[i][j][0] = (unsigned char)(weight*(Imagedata1[i-w1][j-w1][0] + Imagedata1[i-w1][j][0] + Imagedata1[i-w1][j + w1][0] +
			Imagedata1[i][j-w1][0] + Imagedata1[i][j][0] + Imagedata1[i][j+w1][0] +
			Imagedata1[i+1][j-w1][0] + Imagedata1[i+w1][j][0] + Imagedata1[i+w1][j+w1][0]));
		}
	} 
	cout<<"before gauss";*/

	//Low Pass (Gaussian Filter) Removes Uniform Noise
	for (i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			//temp = Imagedata[i][j][0];
			temp2 = 0;
			weight_sum = 0;
			for (k=i-w1;k<=i+2;k++)
			{
				for (l=j-2;l<=j+2;l++)
				{
					weight = (1/(sqrt(2*M_PI)*sigma)) *exp ( -  ( ( pow( k - i , 2 )   +    pow( l - j , 2 ) )/ ( 2 * pow ( sigma , 2 ) ) ) );
					//weight = exp(- ( ( ( pow ( k - i , 2 ) ) + ( pow( l - j  , 2 ) ) / 2 * ( sigma ^ 2 ) ) );
					temp1 = int(ImageR[k][l][0]) * weight;
					weight_sum = weight_sum + weight;
					temp2 = temp2 + temp1;	
				}
			}
			imageoutR [i][j][0] = (unsigned char)(temp2/weight_sum); 
		}
	}
	cout<<"after gauss";
	//Low Pass Median Filter Removes Impulse Noise
	int window_median = 3;
	int x;
	int t;
	int wm = pow(window_median,2);
	cout<<wm;
	int arr [wm];
	//int *d = arr;
	int n;
	for (i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			n=0;
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					arr[n] = (int)imageoutR[k][l][0];
    				n++;
				}
			}
			sort(arr, arr + wm);
			t = wm/2;
			imageoutR1[i][j][0]=arr[t];
	}
	}
	
	//*******************************GREEN*****************************************************************************
	//LOW PASS MEAN / UNIFORM FILTER: removes uniform noise
	/*for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			Imagedata1[i][j][0]=int(ImageR[i][j][0]);
		}
	}
	cout<<"here";
	w1 = 2;
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			imageoutR[i][j][0] = (unsigned char)(weight*(Imagedata1[i-w1][j-w1][0] + Imagedata1[i-w1][j][0] + Imagedata1[i-w1][j + w1][0] +
			Imagedata1[i][j-w1][0] + Imagedata1[i][j][0] + Imagedata1[i][j+w1][0] +
			Imagedata1[i+1][j-w1][0] + Imagedata1[i+w1][j][0] + Imagedata1[i+w1][j+w1][0]));
		}
	} 
	cout<<"before gauss";*/

	//Low Pass (Gaussian Filter) Removes Uniform Noise
	for (i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			//temp = Imagedata[i][j][0];
			temp2 = 0;
			weight_sum = 0;
			for (k=i-w1;k<=i+2;k++)
			{
				for (l=j-2;l<=j+2;l++)
				{
					weight = (1/(sqrt(2*M_PI)*sigma)) *exp ( -  ( ( pow( k - i , 2 )   +    pow( l - j , 2 ) )/ ( 2 * pow ( sigma , 2 ) ) ) );
					//weight = exp(- ( ( ( pow ( k - i , 2 ) ) + ( pow( l - j  , 2 ) ) / 2 * ( sigma ^ 2 ) ) );
					temp1 = int(ImageG[k][l][0]) * weight;
					weight_sum = weight_sum + weight;
					temp2 = temp2 + temp1;	
				}
			}
			imageoutG [i][j][0] = (unsigned char)(temp2/weight_sum); 
		}
	}
	cout<<"after gauss";
	//Low Pass Median Filter Removes Impulse Noise
	
	arr [wm] = {0};
	//int *d = arr;

	for (i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			n=0;
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					arr[n] = (int)imageoutG[k][l][0];
    				n++;
				}
			}
			sort(arr, arr + wm);
			t = wm/2;
			imageoutG1[i][j][0]=arr[t];
	}
	}
	
	//*******************************BLUE*****************************************************************************
	//LOW PASS MEAN / UNIFORM FILTER: removes uniform noise
	/*for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			Imagedata1[i][j][0]=int(ImageR[i][j][0]);
		}
	}
	cout<<"here";
	w1 = 2;
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			imageoutR[i][j][0] = (unsigned char)(weight*(Imagedata1[i-w1][j-w1][0] + Imagedata1[i-w1][j][0] + Imagedata1[i-w1][j + w1][0] +
			Imagedata1[i][j-w1][0] + Imagedata1[i][j][0] + Imagedata1[i][j+w1][0] +
			Imagedata1[i+1][j-w1][0] + Imagedata1[i+w1][j][0] + Imagedata1[i+w1][j+w1][0]));
		}
	} 
	cout<<"before gauss";*/

	//Low Pass (Gaussian Filter) Removes Uniform Noise
	for (i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			//temp = Imagedata[i][j][0];
			temp2 = 0;
			weight_sum = 0;
			for (k=i-w1;k<=i+2;k++)
			{
				for (l=j-2;l<=j+2;l++)
				{
					weight = (1/(sqrt(2*M_PI)*sigma)) *exp ( -  ( ( pow( k - i , 2 )   +    pow( l - j , 2 ) )/ ( 2 * pow ( sigma , 2 ) ) ) );
					//weight = exp(- ( ( ( pow ( k - i , 2 ) ) + ( pow( l - j  , 2 ) ) / 2 * ( sigma ^ 2 ) ) );
					temp1 = int(ImageB[k][l][0]) * weight;
					weight_sum = weight_sum + weight;
					temp2 = temp2 + temp1;	
				}
			}
			imageoutB [i][j][0] = (unsigned char)(temp2/weight_sum); 
		}
	}
	cout<<"after gauss";
	//Low Pass Median Filter Removes Impulse Noise
	
	//int *d = arr;
	arr [wm] = {0};
	for (i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			n=0;
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					arr[n] = (int)imageoutB[k][l][0];
    				n++;
				}
			}
			sort(arr, arr + wm);
			t = wm/2;
			imageoutB1[i][j][0]=arr[t];
	}
	}
	
	//merging all three
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			imageout[i][j][0] = imageoutR1[i][j][0];
 			imageout[i][j][1] = imageoutG1[i][j][0];
			imageout[i][j][2] = imageoutB1[i][j][0];

		}
	}
	cout<<"wdfasdg";
	// Write image data (filename specified by second argument) from image data matrix
	cout << endl;
	
	
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
			cout<<(int)imageout[i][j][0]<<" ";
		}
			
	}
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 256*256*3, file);
	fclose(file);

	return 0;
}
