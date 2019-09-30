/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

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
	int i,j,k,l,h0=256,w0=256,h=260,w=260;
	int Imagedata1[256][256][BytesPerPixel];
	int Imagedata2[260][260][BytesPerPixel];
	int kernel_size = 56
	;
	int temp1 =0;
	float sigmac = 20, sigmas = 30;
	float factor ;
	float temp2= 0, temp3 = 0;
	int w1 = floor((float(kernel_size)/2));
	//int w1 = floor((sqrt(float(kernel_size))) / 2); //window extension
	cout<<"window_ext is "<<w1;
	float kernel [kernel_size];
	float weight=0,weight_sum = 0;
	
	//***************************BOUNDARY REFLECTIONS*************************************
	//Filling the image into a template array of size original_row +2 x original column + 2

	
	for (i=w1;i<h-w1;i++)
	{
		for (j=w1;j<w-w1;j++)
		{
			Imagedata2[i][j][0] = Imagedata[i-w1][j-w1][0];
		}
	}
	
	
	
	/*cout<<"HERE";
	for (i=294;i<304;i++)
	{
		cout<<endl;
		for(j=384;j<394;j++)
		{
			cout<<" ** ";
			cout<<(int)Imagedata2[i][j][0]<<" ";
		}
	}*/
	
	cout<<endl;
	
	//Reflecting the rows 
	cout<<endl;
	for (i=0;i<w1;i++)
	{
		for (j=w1;j<w-w1;j++)
		{
			if(i==0)
			{
				Imagedata2[i][j][0]=Imagedata2[4][j][0];
			}
			if(i==1)
			{
				Imagedata2[i][j][0]=Imagedata2[3][j][0];
			}
		}
	}
	
	for (i=h-w1;i<h;i++)
	{
		for (j=w1;j<w-w1;j++)
		{
			if(i==h-w1)
			{
				Imagedata2[i][j][0]=Imagedata2[h0][j][0];
			}
			if(i==h-(w1-1))
			{
				Imagedata2[i][j][0]=Imagedata2[h0-1][j][0];
			}
		}
	}
	
	//Reflecting the columns
	
	for (i=0;i<w1;i++)
	{
		for (j=w1;j<h-w1;j++)
		{
			if(i==0)
			{
				Imagedata2[j][i][0]=Imagedata2[j][4][0];
			}
			if(i==1)
			{
				Imagedata2[j][i][0]=Imagedata2[j][3][0];
			}
		}
	}
	
	for (i=w-w1;i<w;i++)
	{
		for (j=w1;j<h-w1;j++)
		{
			if(i==w-w1)
			{
				Imagedata2[j][i][0]=Imagedata2[j][w0][0];
			}
			if(i==w-(w1-1))
			{
				Imagedata2[j][i][0]=Imagedata2[j][w0-1][0];
			}
		}
	}
	
	//reflections for the corners
	//upper left corner
	for (i=0;i<w1;i++)
	{
		for (j=0;j<w1;j++)
		{
			if (i==j)
			{
				if (i == 0)
				{
					Imagedata2[i][j][0] = Imagedata2[i+4][j+4][0];
				}
				else if (i == 1)
				{
					Imagedata2[i][j][0] = Imagedata2[i+2][j+2][0];
				}
			}
			else if (i!=j)
			{
				Imagedata2[i][j][0] = Imagedata2[i+3][j+3][0];
			}
		}
	}
	//lower left corner
	
	for (i=h-w1;i<h;i++)
	{
		for (j=0;j<w1;j++)
		{
				if ((i == h-w1 && j == 0) || (i == h - (w1-1) && j == 1))
				{
					Imagedata2[i][j][0] = Imagedata2[i-3][j+3][0];
				}
				else if (i == h-w1 && j == 1)
				{
					Imagedata2[i][j][0] = Imagedata2[i-2][j+2][0];
				}
				else if (i == h - (w1-1) && j == 0)
				{
					Imagedata2[i][j][0] = Imagedata2[i-4][j+4][0];
				}
		}
	}
	
	//upper right corner
	
	for (i=0;i<w1;i++)
	{
		for (j=w-w1;j<w;j++)
		{
				if ((i == 0 && j == (w-w1)) || (i == 1 && j == w-(w1-1)))
				{
					Imagedata2[i][j][0] = Imagedata2[i+3][j-3][0];
				}
				else if (i == 0 && j == w-(w1-1))
				{
					Imagedata2[i][j][0] = Imagedata2[i+4][j-4][0];
				}
				else if (i == 1 && j == w -w1)
				{
					Imagedata2[i][j][0] = Imagedata2[i+2][j-2][0];
				}
		}
	}
	//lower right corner	
	for (i= h-w1 ;i<h;i++)
	{
		for (j=w-w1;j<w;j++)
		{
				if ((i == h-w1 && j == w-(w1-1)) || (i == h-(w1-1) && j == w-w1))
				{
					Imagedata2[i][j][0] = Imagedata2[i-3][j-3][0];
				}
				else if (i == h-(w1-1) && j == w-(w1-1))
				{
					Imagedata2[i][j][0] = Imagedata2[i-4][j-4][0];
				}
				else if (i == h-w1 && j == w-w1)
				{
					Imagedata2[i][j][0] = Imagedata2[i-2][j-2][0];
				}
		}
	}
	cout<<"***********";
	
	
	for (i=w1;i<h-w1;i++)
	{
		for(j=w1;j<w-w1;j++)
		{
			//temp = Imagedata[i][j][0];
			temp2 = 0;
			weight_sum = 0;
			for (k=i-w1;k<=i+w1;k++)
			{
				for (l=j-w1;l<=j+w1;l++)
				{
					factor = float(Imagedata2[i][j][0]) - float(Imagedata2[k][l][0]);
					factor = pow(factor,2)/( 2 * pow ( sigmac , 2 ));
					weight = exp ( -  ( ( pow( i - k , 2 )   +    pow( j - l , 2 ) )/ ( 2 * pow ( sigmac , 2 ) ) )
							- factor );
					//weight = exp(- ( ( ( pow ( k - is , 2 ) ) + ( pow( l - j  , 2 ) ) / 2 * ( sigma ^ 2 ) ) );
					temp1 = int(Imagedata2[k][l][0]) * weight;
					weight_sum = weight_sum + weight;
					temp2 = temp2 + temp1;	
				}
			}
			imageout [i-2][j-2][0] = (unsigned char)(temp2/weight_sum); 
		}
	}
	for (i=0;i<kernel_size;i++)
	{
		kernel[i] = 1;
	}
	
	
	cout<<"wdfasdg";
	// Write image data (filename specified by second argument) from image data matrix
	cout << endl;
	
	cout<<"DONEDONEDONEDONEDONEDONE";
	
	
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 256*256*1, file);
	fclose(file);

	return 0;
}
