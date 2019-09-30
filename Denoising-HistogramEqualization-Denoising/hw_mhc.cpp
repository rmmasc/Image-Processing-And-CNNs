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
	unsigned char imageout[304][394][3];
	unsigned char imageout2[300][390][3];
	unsigned char Imagedata1[304][390][BytesPerPixel];
	unsigned char Imagedata2[304][394][BytesPerPixel];
	float Im3[304][390][1];
	int temp[4];

	int i,j,k,l,m;
	float temp1;
	
	//***************************BOUNDARY REFLECTIONS*************************************
	//Filling the image into a template array of size original_row +2 x original column + 2
	for (i=2;i<302;i++)
	{
		for (j=2;j<392;j++)
		{
			Imagedata2[i][j][0] = Imagedata[i-2][j-2][0];
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
	for (i=0;i<2;i++)
	{
		for (j=2;j<392;j++)
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
	
	for (i=302;i<304;i++)
	{
		for (j=2;j<392;j++)
		{
			if(i==302)
			{
				Imagedata2[i][j][0]=Imagedata2[300][j][0];
			}
			if(i==303)
			{
				Imagedata2[i][j][0]=Imagedata2[299][j][0];
			}
		}
	}
	
	//Reflecting the columns
	
	for (i=0;i<2;i++)
	{
		for (j=2;j<302;j++)
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
	
	for (i=392;i<394;i++)
	{
		for (j=2;j<302;j++)
		{
			if(i==392)
			{
				Imagedata2[j][i][0]=Imagedata2[j][390][0];
			}
			if(i==393)
			{
				Imagedata2[j][i][0]=Imagedata2[j][389][0];
			}
		}
	}
	
	//reflections for the corners
	//upper left corner
	for (i=0;i<2;i++)
	{
		for (j=0;j<2;j++)
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
	
	for (i=302;i<304;i++)
	{
		for (j=0;j<2;j++)
		{
				if ((i == 302 && j == 0) || (i == 303 && j == 1))
				{
					Imagedata2[i][j][0] = Imagedata2[i-3][j+3][0];
				}
				else if (i == 302 && j == 1)
				{
					Imagedata2[i][j][0] = Imagedata2[i-2][j+2][0];
				}
				else if (i == 303 && j == 0)
				{
					Imagedata2[i][j][0] = Imagedata2[i-4][j+4][0];
				}
		}
	}
	
	//upper right corner
	
	for (i=0;i<2;i++)
	{
		for (j=392;j<394;j++)
		{
				if ((i == 0 && j == 392) || (i == 1 && j == 393))
				{
					Imagedata2[i][j][0] = Imagedata2[i+3][j-3][0];
				}
				else if (i == 0 && j == 393)
				{
					Imagedata2[i][j][0] = Imagedata2[i+4][j-4][0];
				}
				else if (i == 1 && j == 392)
				{
					Imagedata2[i][j][0] = Imagedata2[i+2][j-2][0];
				}
		}
	}
	//lower right corner	
	for (i=302;i<304;i++)
	{
		for (j=392;j<394;j++)
		{
				if ((i == 302 && j == 393) || (i == 303 && j == 392))
				{
					Imagedata2[i][j][0] = Imagedata2[i-3][j-3][0];
				}
				else if (i == 303 && j == 393)
				{
					Imagedata2[i][j][0] = Imagedata2[i-4][j-4][0];
				}
				else if (i == 302 && j == 392)
				{
					Imagedata2[i][j][0] = Imagedata2[i-2][j-2][0];
				}
		}
	}
	
	for (i=0;i<10;i++)
	{
		cout<<endl;
		for(j=384;j<394;j++)
		{
			cout<<" ** ";
			cout<<(int)Imagedata2[i][j][0]<<" ";
		}
	}
	
	cout<<endl;
	
	for (i=0;i<304;i++)
	{
		for (j=0;j<394;j++)
		{
			Im3[i][j][0] = (float)Imagedata2[i][j][0];
		}
	}
	//Imagedata = (unsigned int)(imageout);
	for (i=2;i<302;i++)
	{
		for(j=2;j<392;j++)
			{
			if (i%2 == 0 and j%2 == 0) //top green
				{
					//red, green and blue values 
					imageout[i][j][0] = (unsigned char)((1/8.0)*float(((0.5)*Im3[i-2][j][0] + (-1)*Im3[i-1][j-1][0] + (-1)*Im3[i-1][j+1][0] + (-1)*Im3[i][j-2][0] + 
					4*Im3[i][j-1][0]+ 5*Im3[i][j][0] + 4*Im3[i][j+1][0] + (-1)*Im3[i][j+2][0] + (-1)*Im3[i+1][j-1][0] + (-1)*Im3[i+1][j+1][0] + 0.5*Im3[i+2][j][0])));
					imageout[i][j][1] = (unsigned char)Im3[i][j][0];
					imageout[i][j][2] = (unsigned char)((1/8.0)*float(((-1)*Im3[i-2][j][0] + (-1)*Im3[i-1][j-1][0] + 4*Im3[i-1][j][0] + (-1)*Im3[i-1][j+1][0] + (0.5)*Im3[i][j-2][0] + 
					+ 5*Im3[i][j][0] + (0.5)*Im3[i][j+2][0] + (-1)*Im3[i+1][j-1][0] + 4*Im3[i+1][j][0] + (-1)*Im3[i+1][j+1][0] + (-1)*Im3[i+2][j][0])));
					
					 
				}
			else if  (i%2 != 0 and j%2 != 0) //bottom green
				{
					//red, green and blue values
					imageout[i][j][0] = (unsigned char)((1/8.0)*float(((-1)*Im3[i-2][j][0] + (-1)*Im3[i-1][j-1][0] + 4*Im3[i-1][j][0] + (-1)*Im3[i-1][j+1][0] + (0.5)*Im3[i][j-2][0] + 
					+ 5*Im3[i][j][0] + (0.5)*Im3[i][j+2][0] + (-1)*Im3[i+1][j-1][0] + 4*Im3[i+1][j][0] + (-1)*Im3[i+1][j+1][0] + (-1)*Im3[i+2][j][0])));
					imageout[i][j][1] = (unsigned char)Im3[i][j][0];
					imageout[i][j][2] = (unsigned char)((1/8.0)*float((0.5*Im3[i-2][j][0] + (-1)*Im3[i-1][j-1][0] + (-1)*Im3[i-1][j+1][0] + (-1)*Im3[i][j-2][0] + 
					4*Im3[i][j-1][0] + 5*Im3[i][j][0] + 4*Im3[i][j+1][0] + (-1)*Im3[i][j+2][0] + (-1)*Im3[i+1][j-1][0] + (-1)*Im3[i+1][j+1][0] + 0.5*Im3[i+2][j][0])));
							
				}
			else if (i%2 == 0 and j%2 != 0) //red
				{
					//red, green and blue values 
					imageout[i][j][0] = (unsigned char)Im3[i][j][0];
					imageout[i][j][1] = (unsigned char)((1/8.0)*float(((-1)*Im3[i-2][j][0] + (2)*Im3[i-1][j][0] + (-1)*Im3[i][j-2][0] + 2*Im3[i][j-1][0]+ 4*Im3[i][j][0] + 2*Im3[i][j+1][0] + (-1)*Im3[i][j+2][0] 
					+ 2*Im3[i+1][j][0] + (-1)*Im3[i+2][j][0])));
					imageout[i][j][2] = (unsigned char)((1/8.0)*float(((-1.5)*Im3[i-2][j][0] + 2*Im3[i-1][j-1][0] + 2*Im3[i-1][j+1][0] + (-1.5)*Im3[i][j-2][0] + 
					+ 6*Im3[i][j][0] + (-1.5)*Im3[i][j+2][0] + 2*Im3[i+1][j-1][0] + 2*Im3[i+1][j+1][0] + (-1.5)*Im3[i+2][j][0])));
					
				}
			else if (i%2 != 0 and j%2 == 0) //blue
				{
					//red, green and blue values
					imageout[i][j][0] = (unsigned char)((1/8.0)*float(((-1.5)*Im3[i-2][j][0] + 2*Im3[i-1][j-1][0] + 2*Im3[i-1][j+1][0] + (-1.5)*Im3[i][j-2][0] + 
					+ 6*Im3[i][j][0] + (-1.5)*Im3[i][j+2][0] + 2*Im3[i+1][j-1][0] + 2*Im3[i+1][j+1][0] + (-1.5)*Im3[i+2][j][0])));
					imageout[i][j][1] = (unsigned char)((1/8.0)*float((-1)*Im3[i-2][j][0] + (2)*Im3[i-1][j][0] + (-1)*Im3[i][j-2][0] + 2*Im3[i][j-1][0]+ 4*Im3[i][j][0] + 2*Im3[i][j+1][0] + (-1)*Im3[i][j+2][0] 
					+ 2*Im3[i+1][j][0] + (-1)*Im3[i+2][j][0]));
					imageout[i][j][2] = (unsigned char)Im3[i][j][0];
					
				
				}
		}
	}
	
	for (i=2;i<302;i++)
	{
		for (j=2;j<392;j++)
		{
			for (k=0;k<3;k++)
			{
				imageout2[i-2][j-2][k] = imageout[i][j][k];
			}
		}
	}

	cout<<"DONE";
	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout2, sizeof(unsigned char), 300*390*3, file);
	fclose(file);

	return 0;
}
