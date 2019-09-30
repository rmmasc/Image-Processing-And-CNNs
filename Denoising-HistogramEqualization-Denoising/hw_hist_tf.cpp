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
#include <fstream>
#include <string>


using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;

	
	
	//**
	
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
	unsigned char imageout[400][400][1];
	int i,j,k,m,temp,count=0,z,l,num;
	int unique_val = 256;
	int check1=0;
	float check2 = 0.0;
    float freq[unique_val][5];
    int size = 400;
    int skipmatrix[size][size];
    
    for (l=0;l<unique_val;l++)
    {	
    	freq[l][0]=l;
    	freq[l][1]=0;
    	freq[l][2]=0;
    	freq[l][3]=0;
    	freq[l][4]=0;

	}
	
	for(i=0;i<size;i++)  //calculate the frequency of elements
	{
       for(j=0; j<size;j++) 
	   {
          count=0;
          num=Imagedata[i][j][0];
          if(skipmatrix[i][j]!=1) 
		  {
          for(k=0;k<size;k++) 
		  {
            for(m=0;m<size;m++) 
			{
              if(Imagedata[i][j][0]==Imagedata[k][m][0]) 
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
	outfile.open("rose_mix_after_hist.csv");
	for(i=0;i<256;i++)
	{
		    outfile << freq[i][0] << "," << freq[i][1] << std::endl;

	}
	outfile.close();
	
	for(z=0;z<unique_val;z++)
    {
   	cout<<freq[z][0]<<" : "<<freq[z][1]<<" : "<<freq[z][2]<<" : "<<freq[z][3]<<" : "<<freq[z][4]<<endl;
    }
	

	//assigning pixels to output
	for(i=0;i<256;i++) 
	{
	   for (k=0;k<size;k++)
       {
       		for(m=0;m<size;m++)
       		{
       			if (Imagedata[k][m][0]==freq[i][0])
       			{
       				imageout[k][m][0] = int(freq[i][4]);
				}
			}
	   }
	}
	
	
	if (!(file=fopen(argv[2],"wb"))) {
	cout << "Cannot open file: " << argv[2] << endl;
	exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), 400*400*1, file);
	fclose(file);
	
	   
		
	return 0;
}
