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
	int i,j,k,l,h0=256,w0=256,h=260,w=260,x,y;
	int Imagedata1[256][256][BytesPerPixel];
	int Imagedata2[260][260][BytesPerPixel];
	int kernel_size = 5;
	int temp4 =0;
	int N = 5;
	float temp1 = 0, temp2= 0, temp3 = 0, temp5 = 0, h_par = 25;
	int w1 = floor((float(kernel_size)/2));
	w1 = 2;
	float e_dist, a = 40;
	float gnn; //gaussian kernel
	//int w1 = floor((sqrt(float(kernel_size))) / 2); //window extension
	cout<<"window_ext is "<<w1;
	float kernel [kernel_size];
	float fijkl=0,fijkl_sum = 0;
	
	//***************************BOUNDARY REFLECTIONS*************************************
	//Filling the image into a template array of size original_row +2 x original column + 2
	for (i=246;i<256;i++)
	{
		cout<<endl;
		for(j=246;j<256;j++)
		{
			cout<<" ** ";
			cout<<(int)Imagedata[i][j][0]<<" ";
		}
	}
	
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
	cout<<"*********************   *************";
	for (i=250;i<260;i++)
	{
		cout<<endl;
		for(j=250;j<260;j++)
		{
			cout<<" ** ";
			cout<<(int)Imagedata2[i][j][0]<<" ";
		}
	}
	
	for (i=0;i<256;i++)
	{
		//cout<<"entering i";
		for(j=0;j<256;j++)
		{
			//cout<<"entering j"<<endl;
			//temp = Imagedata[i][j][0];
			temp5 = 0.0;
			fijkl_sum = 0.0;
			for (k=i-3;k<=i+3;k++)
			{
				//cout<<"entering k"<<endl;
				for (l=j-3;l<=j+3;l++)
				{
					//cout<<"entering l"<<endl;
					e_dist = 0.0;
					for (x=k-1;x<=k+1;x++)
					{
						//cout<<"entering x"<<endl;
						for (y=l-1;y<=l+1;y++)
						{
							//cout<<"entering y"<<endl;
							gnn = (1.0/(sqrt(2*M_PI)*a)) * exp(-((pow(x,2)+pow(y,2))/(2*pow(a,2))));
							//cout<<"gnn is "<<gnn;
							temp1 = float(Imagedata[i-x][j-y][0])-float(Imagedata[k-x][l-y][0]);
							//cout<<endl<<"temp1 is "<<temp1;
							temp2 = gnn*pow(temp1,2);
							//cout<<endl<<"temp2 is "<<temp2;							
							e_dist = e_dist + temp2;
							//cout<<endl<<"e_dist is "<<e_dist;
						}
					}
					fijkl = exp(-(e_dist)/(pow(h_par,2)));
					//weight = exp(- ( ( ( pow ( k - is , 2 ) ) + ( pow( l - j  , 2 ) ) / 2 * ( sigma ^ 2 ) ) );
					temp4 = int(Imagedata[k][l][0]) * fijkl;
					fijkl_sum = fijkl_sum + fijkl;
					temp5 = temp5 + temp4;	
				}
			}
			imageout [i][j][0] = (unsigned char)(temp5/fijkl_sum); 
		}
	}

	cout<<"wdfasdg";
	// Write image data (filename specified by second argument) from image data matrix
	cout << endl;
	
	cout<<"DONEDONEDONEDONEDONEDONE";
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
			cout<<(int)imageout[i][j][0]<<" ";
			}
		cout<<endl;	
	}
	
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 256*256*1, file);
	fclose(file);

	return 0;
}
