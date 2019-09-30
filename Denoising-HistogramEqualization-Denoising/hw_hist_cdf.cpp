/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	cout.flush();
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
	unsigned char Imagedata[400][400][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 400*400*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char imageout[400][400][BytesPerPixel];
	short pixel_array[160000][3];
	int i,j,k,temp[1][3];
	short temp1[1][3],x,y;
	int count1=0,count2=0,count3=0;
	
	for(i=0;i<400;i++) 
		{
			for(j=0;j<400;j++) 
			{
				if(int(Imagedata[i][j][0])== 0)
				{
					count1++;
				}
			}
		}
	
	cout<<"Before filtering 0s are "<<count1<<"*********"<<endl;
	for(i=0;i<400;i++) 
		{
			for(j=0;j<400;j++) 
			{
				temp[0][0]=Imagedata[i][j][0];
				temp[0][1]=i;
				temp[0][2]=j;
				pixel_array[(i*400)+j][0]=temp[0][0];
				pixel_array[(i*400)+j][1]=temp[0][1];
				pixel_array[(i*400)+j][2]=temp[0][2];				
			}	
		}
	
	/*for (i=0;i<10;i++)
	{
		cout<<endl<<pixel_array[i][0]<<"******"<<pixel_array[i][1]<<"******"<<pixel_array[i][2]<<"******"<<endl;
	}*/
	//pixel_array = int(pixel_array);
	cout<<"done"<<"   "<<pixel_array[0][0]<<endl;
	cout<<(int)Imagedata[1][0][0]<<"    "<<(int)Imagedata[1][1][0]<<"  "<<pixel_array[400][0]<<"   "<<pixel_array[401][0];
	// Write image data (filename specified by second argument) from image data matrix
	
	
	for(i=0;i<160000;i++)
	{		
		for(j=i+1;j<160000;j++)
		{
			if(pixel_array[i][0]>pixel_array[j][0])
			{
				temp1[0][0]  =pixel_array[i][0];
				temp1[0][1]  =pixel_array[i][1];
				temp1[0][2]  =pixel_array[i][2];
				pixel_array[i][0]=pixel_array[j][0];
				pixel_array[i][1]=pixel_array[j][1];
				pixel_array[i][2]=pixel_array[j][2];
				pixel_array[j][0]=temp1[0][0];
				pixel_array[j][1]=temp1[0][1];
				pixel_array[j][2]=temp1[0][2];

			}
		}
	}
	
	for(i=0;i<256;i++)
	{
		for(j=0;j<625;j++)
		{
			pixel_array[(i*625)+j][0] = i;
			
		}
	}

	
	for (i=0;i<160000;i++)
	{
		if(pixel_array[i][0]==0)
		{
			count2++;
		}
	}
	
	cout<<"DURING filtering, in pixel array, 0s are "<<count2<<"*********"<<endl;

	for(i=0;i<160000;i++)
	{
		x = pixel_array[i][1];
		y = pixel_array[i][2];
		imageout[x][y][0] = pixel_array[i][0];
	}
		
	
	/*for (i=0;i<258;i++)
	{
		cout<<endl<<pixel_array[i][0]<<"******"<<pixel_array[i][1]<<"******"<<pixel_array[i][2]<<"******"<<endl;
	}*/
	for(i=0;i<400;i++) 
		{
			for(j=0;j<400;j++) 
			{
				if(int(imageout[i][j][0])== 1)
				{
					count3++;
				}
			}
		}
	
	cout<<"AFTER filtering 0s are "<<count3<<"*********"<<endl;
	int count=0,z,l,num;
	int unique_val = 256;
	int check1=0;
	int tempe;
	float check2 = 0.0;
    float freq[unique_val][5];
    int size = 400;
    int skipmatrix[size][size];
    int m;

		for(i=0;i<size;i++)  //calculate the frequency of elements
			{
		       for(j=0; j<size;j++) 
			   {
		          count=0;
		          num=imageout[i][j][0];
		          if(skipmatrix[i][j]!=1) 
				  {
		          for(k=0;k<size;k++) 
				  {
		            for(m=0;m<size;m++) 
					{
		              if(imageout[i][j][0]==imageout[k][m][0]) 
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
	for (i=0;i<unique_val;i++)
	{
		check1 = freq[i][1]+check1;
		freq[i][2] = freq[i][1] / (400 * 400);
		check2 = freq[i][2]+check2;
	}
	
	//calculate the cumulative probability and map to 0-255
	for (i=1;i<256;i++)
	{
		freq[i][3] = freq [i][2] + freq [i-1][3];
		freq[i][4]= freq[i][3]*255;	
	}		
	cout<<endl<<"The cumulative sum is "<<check1<<" and the cumulative probability is  "<<check2<<endl;
	
	// write required data into csv file to plot histogram
	ofstream outfile;
	outfile.open("rosey.csv");
	tempe = 0;
	for(i=0;i<256;i++)
	{		
			if (i==0)
			{
				//tempe = tempe + freq[0][1];
				outfile << freq[i][0] << "," << freq[i][1] << std::endl;
				continue;

			}
			tempe = tempe + freq[i-1][1];
		    outfile << freq[i][0] << "," << tempe << std::endl;

	}
	outfile.close();
	cout<<"done ****"; 	
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 400*400*1, file);
	fclose(file);

	return 0;
}	
