


/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
int* decToBinary(int n) 
{ 
    // array to store binary number 
    int binaryNum[100]; 
  	int size;
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
  	
    // printing binary array in reverse order 
    /*if(n < 2){
    	size = 1;
	}
	else if (n < 4 and n >= 2)
	{
		size = 2;
	}
	else if (n < 8 and n >= 4)
	{
		size = 3;
	}
	else if (n < 16 and n >= 8)
	{
		size = 4;
	}
	else if (n < 32 and n >= 16)
	{
		size = 5;
	}
	
	fill = 5 - size;
	
	for(int i = 0;i<size;i++)
	{
		
	 } */
        //cout << binaryNum[j]; 
	
	return binaryNum;
	
} 

// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

//eliminating extrea filters for shrinking

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int width = 375;
const int height = 375;
const int n = 1;

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
	fread(Imagedata, sizeof(unsigned char), height*width*1, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
 	int nHeight = height + 2*n ,nWidth = width + 2*n;
 	unsigned char imageout [height][width][1];
 	//unsigned char ImageG1 [nHeight][nWidth][1];
	short ***ImageG1 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageG1[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageG1[i][j] = new short[1];
		} 	
	}
	short ***ImageM1 = new short**[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageM1[i] = new short*[nWidth];
	    for (int j=0;j<nWidth;j++){
	    	ImageM1[i][j] = new short[1];
		} 	
	}
	
	short **ImageP1 = new short*[nHeight]; 
	for(int i=0;i<nHeight;i++){
	    ImageP1[i] = new short[nWidth];
	}
	
	short ImageG2 [nHeight][nWidth];
	short ImageG2pre [nHeight][nWidth];

	//**********************************BOUNDARY EXTENSION************************************************************
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			ImageG1[i][j][0] = (float)Imagedata[i-n][j-n][0];
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
	

	/*for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			cout<<(int)Imagedata[i][j][0]<<" ";
		}
		cout<<endl;
	}
	cout<<"***********************************************"<<endl;
	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			cout<<(int)ImageG1[i][j][0]<<" ";
		}
		cout<<endl;
	}*/
 	//******************************************************************************************************
	
	short s1[4][9] = {{0,0,1,0,1,0,0,0,0},
				{1,0,0,0,1,0,0,0,0},
				{0,0,0,0,1,0,1,0,0},
				{0,0,0,0,1,0,0,0,1}};
	
	short s2[4][9] = {{0,0,0,0,1,1,0,0,0},
					  {0,1,0,0,1,0,0,0,0},
					  {0,0,0,1,1,0,0,0,0},
					  {0,0,0,0,1,0,0,1,0}};
					  
					  
	short s3[8][9] = {{0,0,1,0,1,1,0,0,0},
					  {0,1,1,0,1,0,0,0,0},
					  {1,1,0,0,1,0,0,0,0},
					  {1,0,0,1,1,0,0,0,0},
					  {0,0,0,1,1,0,1,0,0},
					  {0,0,0,0,1,0,1,1,0},
					  {0,0,0,0,1,0,0,1,1},
					  {0,0,0,0,1,1,0,0,1}};
					  
	short stk4[4][9] = {{0,0,1,0,1,1,0,0,1},
					  {1,1,1,0,1,0,0,0,0},
					  {1,0,0,1,1,0,1,0,0},
					  {0,0,0,0,1,0,1,1,1}};
					  
	short st5[8][9] = {{1,1,0,0,1,1,0,0,0},
					  {0,1,0,0,1,1,0,0,1},
					  {0,1,1,1,1,0,0,0,0},
					  {0,0,1,0,1,1,0,1,0},
					  {0,1,1,0,1,1,0,0,0},
					  {1,1,0,1,1,0,0,0,0},
					  {0,0,0,1,1,0,1,1,0},
					  {0,0,0,0,1,1,0,1,1}};
					  
	short st6[2][9] = {{1,1,0,0,1,1,0,0,1},
					  {0,1,1,1,1,0,1,0,0}};
					  
	short stk6[8][9] = {{1,1,1,0,1,1,0,0,0},
					  {0,1,1,0,1,1,0,0,1},
					  {1,1,1,1,1,0,0,0,0},
					  {1,1,0,1,1,0,1,0,0},
					  {1,0,0,1,1,0,1,1,0},
					  {0,0,0,1,1,0,1,1,1},
					  {0,0,0,0,1,1,1,1,1},
					  {0,0,1,0,1,1,0,1,1}};

	short stk7[4][9] = {{1,1,1,0,1,1,0,0,1},
					  {1,1,1,1,1,0,1,0,0},
					  {1,0,0,1,1,0,1,1,1},
					  {0,0,1,0,1,1,1,1,1}};

	short stk8[4][9] = {{0,1,1,0,1,1,0,1,1},
					  {1,1,1,1,1,1,0,0,0},
					  {1,1,0,1,1,0,1,1,0},
					  {0,0,0,1,1,1,1,1,1}};
					  
	short stk9[8][9] = {{1,1,1,0,1,1,0,1,1},
					  {0,1,1,0,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,0},
					  {1,1,1,1,1,1,0,0,1},
					  {1,1,1,1,1,0,1,1,0},
					  {1,1,0,1,1,0,1,1,1},
					  {1,0,0,1,1,1,1,1,1},
					  {0,0,1,1,1,1,1,1,1}};
					  
	short stk10[4][9] = {{1,1,1,0,1,1,1,1,1},
					  {1,1,1,1,1,1,1,0,1},
					  {1,1,1,1,1,0,1,1,1},
					  {1,0,1,1,1,1,1,1,1}};
	
	int flag2 = 0, flag1 = 0;

			
	for (int i=n;i<height+n;i++){
		for (int j=n;j<width+n;j++){
			if(ImageG1[i][j][0] == 255){
				ImageG1[i][j][0] = (ImageG1[i][j][0])/ 255;
							}
						}
					}

	/*for (int i=0;i<nHeight;i++){
		for (int j=0;j<nWidth;j++){
			if(ImageG1[i][j][0] != 1 and ImageG1[i][j][0] != 0){
				cout<<"**FAIL**"<<ImageG1[i][j][0];
							}
						}
					}*/
	int c = 0;
	while(flag1==0){
	//for (int b = 0;b<1;b++){
	if (flag2 == 1){
	for (int i=n;i<height+1;i++)
	{
		for (int j=n;j<width+1;j++)
		{
			ImageG1[i][j][0] = ImageG2[i][j];
		}
	}
	
	}
	
	
	c = c + 1;
	if (c > 60)
	{
		cout<<"c is "<<c<<endl;
	}

	
	for (int i=n;i<height+1;i++)
	{
		for (int j=n;j<width+1;j++)
		{
			int m = 0;
			/*if (i==119 and j==104)
			{
				cout<<"caught you "<<ImageG1[i][j][0]<<" m is "<<m<<endl;
			for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						cout<<ImageG1[k][l][0]<<" ";
					}
				}
			cout<<endl;
		    }*/
		    
			for(int r = 0;r<4;r++){
				int i1 = 0, count = 0;
				for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						//cout<<"I"<<ImageG1[k][l][0]<<" ";
						//cout<<"M"<<s1[r][i1]<<" ";
						if ((ImageG1[k][l][0])==(s1[r][i1])){
							count = count + 1;
						}
						i1++;
					}
				}
				//cout<<endl<<"count is "<<count; 
				if (count == 9){
					m = 1;
					if (i==119 and j==104){ cout<<endl<<"MATCH IN S1 "<<endl;}
				}
				//cout<<endl;
			}
						
			//cout<<" m is "<<m;
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageG1[k][l][0])==(s2[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN S2 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Ms3-"<<s3[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(s3[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN S3 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk4-"<<stk4[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk4[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk4 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mst5-"<<st5[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(st5[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN St5 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mst6-"<<st6[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(st6[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN St6 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk6-"<<stk6[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk6[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk6 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk7-"<<stk7[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk7[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk7 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk8[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk8 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			if (m!=1){
				for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk9-"<<stk9[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk9[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					
					
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk9 "<<endl;}
					}
					//cout<<endl;
				}
			}
			
			
			if (m!=1){
				for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk9-"<<stk9[r][i1]<<" ";
							if ((ImageG1[k][l][0])==(stk10[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						m = 1;
						if (i==119 and j==104){ cout<<endl<<"MATCH IN Stk10 "<<endl;}
					}
					//cout<<endl;
				}
			}
			//cout<<" m is "<<m;
			if (i==119 and j==104)
			{
				cout<<"caught you "<<ImageG1[i][j][0]<<" m is "<<m<<endl;
				cout<<endl;
		    }
			ImageM1 [i][j][0] = m; 	
			
		}
	}
	
	
	
	
	
	for (int i=1;i<height+1;i++){
		for (int j=1;j<width+1;j++){
			if(ImageM1[i][j][0] != 1 and ImageM1[i][j][0] != 0){
				cout<<"**FAILOOOO "<<(int)ImageM1[i][j][0]<<" "<<i<<" "<<j<<"***";
			}
		}
	}
	
	for (int i=1;i<height+1;i++)
	{
		for (int j=1;j<width+1;j++)
		{
			int m = ImageM1[i][j][0];
			
			int a = 0, b= 0, c = 0, d = 2;
			
			int p = 0;
			if (i==120 and j==106)
			{
				cout<<"caught you P "<<ImageM1[i][j][0]<<" p is "<<p<<endl;
			for (int k = i-1;k<=i+1;k++){
					for(int l = j-1;l<=j+1;l++){
						cout<<ImageM1[k][l][0]<<" ";
					}
				}
			cout<<endl;
		    }
			
			int spur[2][9] = {{0,0,m,0,m,0,0,0,0},{m,0,0,0,m,0,0,0,0}};
			for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(spur[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN Spur "<<endl;}
					}
					//cout<<endl;
				}
			
			int single4c [2][9] = {{0,0,0,0,m,0,0,m,0},{0,0,0,0,m,m,0,0,0}};
			if(p!=1){
			for(int r = 0;r<2;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(single4c[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN Single4c "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		int lcluster [8][9] = {{0,0,m,0,m,m,0,0,0},
									{0,m,m,0,m,0,0,0,0},
									{m,m,0,0,m,0,0,0,0},
									{m,0,0,m,m,0,0,0,0},
									{0,0,0,m,m,0,m,0,0},
									{0,0,0,0,m,0,m,m,0},
									{0,0,0,0,m,0,0,m,m},
									{0,0,0,0,m,m,0,0,m}};
		if(p!=1){
			for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if ((ImageM1[k][l][0])==(lcluster[r][i1])){
								count = count + 1;
							}
								i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN lcluster "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		int con4off [4][9] ={{0,m,m,m,m,0,0,0,0},
								{m,m,0,0,m,m,0,0,0},
								{0,m,0,0,m,m,0,0,m},
								{0,0,m,0,m,m,0,m,0}};
		if(p!=1){
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(con4off[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN con4off "<<endl;}
						//break;
					}
					//cout<<endl;
				}	
		}
		
		int spurcorn [4][9] = {{0,a,m,0,m,b,m,0,0},
								{m,b,0,a,m,0,0,0,m},
								{0,0,m,a,m,0,m,b,0},
								{m,0,0,0,m,b,0,a,m}};
		//a
		spurcorn[0][1]=1; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=0;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 1; b= 0;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}	
		}
		
		//a
		spurcorn[0][1]=0; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=1;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 0; b= 1;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}
		}
		
		//a
		spurcorn[0][1]=1; spurcorn[1][3]= spurcorn[0][1]; spurcorn[2][3]= spurcorn[0][1]; spurcorn[3][7]= spurcorn[0][1];
		//b
		spurcorn[0][5]=1;spurcorn[1][1]= spurcorn[0][5]; spurcorn[2][7]= spurcorn[0][5]; spurcorn[3][5]= spurcorn[0][5];
		if(p!=1){
			a = 1; b= 1;
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							//cout<<"I"<<ImageG1[k][l][0]<<" ";
							//cout<<"Mstk8-"<<stk8[r][i1]<<" ";
							if ((ImageM1[k][l][0])==(spurcorn[r][i1])){
								count = count + 1;
							}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						p = 1;
						if (i==120 and j==106){ cout<<endl<<"MATCH IN spurcorn "<<endl;}
						//break;
					}
					//cout<<endl;
				}
	}
	
	int cornclust [9] = {m,m,d,m,m,d,d,d,d};
	if(p!=1){
			for(int n1 = 0;n1<32;n1++)
			{
			int size = 5;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			cornclust[2] = dr[0];
			cornclust[5] = dr[1];
			cornclust[6] = dr[2];
			cornclust[7] = dr[3];
			cornclust[8] = dr[4];
			
			 //corner cluster
			for(int r = 0;r<1;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if (cornclust[i1] == 0 or cornclust[i1] == 1){
								if ((ImageM1[k][l][0])==(cornclust[i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
				
					if (count == 9){
						p = 1;
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN cornclust "<<endl;}
					}
				}
		}
		}
		
		
		if(p!=1){
			for(int n1 = 0;n1<4;n1++)
			{
			int size = 2;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int teebranch [8][9]={{d1,m,0,m,m,m,d2,0,0},
								{0,m,d1,m,m,m,0,0,d2},
								{0,0,d1,m,m,m,0,m,d2},
								{d1,0,0,m,m,m,d2,m,0},
								{d1,m,d2,m,m,0,0,m,0},
								{0,m,0,m,m,0,d1,m,d2},
								{0,m,0,0,m,m,d1,m,d2},
								{d1,m,d2,0,m,m,0,m,0}};
			d = 2; //teebranch
			for(int r = 0;r<8;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
							if (teebranch[r][i1] == 0 or teebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(teebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					if (count == 9){
						p = 1;
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN teebranch "<<endl;}
					}
				}
		}
	}
			//*******VEEBRANCH************************************
		
		
		
		
		if(p!=1){
			for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
		
		if(p!=1){
			for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
		
	if(p!=1){
			for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
		
	if(p!=1){
			for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=0;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
	
	if(p!=1){
		for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=0;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
	
		if(p!=1){
			for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=0;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
	
	if(p!=1){
		for(int n1 = 0;n1<8;n1++)
			{
			int size = 3;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int d3 = dr[2];
			int veebranch [4][9] = {{m,d1,m,d2,m,d3,a,b,c},
									{m,d1,c,d2,m,b,m,d3,a},
									{c,b,a,d1,m,d2,m,d3,m},
									{a,d1,m,b,m,d2,c,d3,m}};
			//a
			veebranch[0][6]=1;veebranch[1][8]=veebranch[0][6];veebranch[2][2]=veebranch[0][6];veebranch[3][0]=veebranch[0][6];
			//b
			veebranch[0][7]=1;veebranch[1][5]=veebranch[0][7];veebranch[2][1]=veebranch[0][7];veebranch[3][3]=veebranch[0][7];
			//c
			veebranch[0][8]=1;veebranch[1][2]=veebranch[0][8];veebranch[2][0]=veebranch[0][8];veebranch[3][6]=veebranch[0][8];
				//d = 2; a= 0; b = 0; c = 1; //Veebranch
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (veebranch[r][i1] == 0 or veebranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(veebranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
	
	//***DIAGBRANCH	
	if(p!=1){
		for(int n1 = 0;n1<4;n1++)
			{
			int size = 2;
			int dr[size];
			int* ptr = decToBinary(n1);
			if (n1==0){
				for(int h=0;h<size;h++){
		    		dr[h] = 0;
				}
			}
			else if(n1>0 and n1 < 2){
		    	for(int h=0;h<size-1;h++){
		    		dr[h] = 0;
				}
				dr[size -1] = ptr[0];
			}
			else if (n1 < 4 and n1 >= 2)
			{
				for(int h=0;h<size-2;h++){
		    		dr[h] = 0;
				}
				int e=1;
				for(int h=size-2;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 8 and n1 >= 4)
			{
				for(int h=0;h<size-3;h++){
		    		dr[h] = 0;
				}
				int e=2;
				for(int h=size-3;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 16 and n1 >= 8)
			{
					for(int h=0;h<size-4;h++){
		    		dr[h] = 0;
				}
				int e=3;
				for(int h=size-4;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}
			}
			else if (n1 < 32 and n1 >= 16)
			{
				int e=4;
				for(int h=0;h<size;h++){
		    		dr[h] = ptr[e];
		    		e--;
				}	
			}
			int d1 = dr[0];
			int d2 = dr[1];
			int diagbranch [4][9] = {{d1,m,0,0,m,m,m,0,d2},
								{0,m,d1,m,m,0,d2,0,m},
								{d1,0,m,m,m,0,0,m,d2},
								{m,0,d1,0,m,m,d2,m,0}};
			for(int r = 0;r<4;r++){
					int i1 = 0, count = 0;
					for (int k = i-1;k<=i+1;k++){
						for(int l = j-1;l<=j+1;l++){
						if (diagbranch[r][i1] == 0 or diagbranch[r][i1] == 1){
								if ((ImageM1[k][l][0])==(diagbranch[r][i1])){
								count = count + 1;
							
							}
							
						}
							i1++;
						}
					}
					//cout<<endl<<"count is "<<count; 
					if (count == 9){
						//if (i==120 and j==106){ cout<<endl<<"MATCH IN veebranch "<<endl;}
						p = 1;
						//break;
					}
					//cout<<endl;
				}
		}
	}
		
			
		ImageP1[i][j] = p ;
		/*if (i==120 and j==106)
			{
				cout<<"caught you "<<ImageP1[i][j]<<" p is "<<p<<endl;
				cout<<endl;
		    }*/
				
			
		}
	}
					
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
				int xf = ImageG1[i][j][0];
				int mf = ImageM1[i][j][0];
				if (mf==1)
				{
					mf = 0;
				}
				else 
				{
					mf = 1;
				}
				int pf = ImageP1[i][j];
				ImageG2 [i][j] = xf & (mf | pf);
		}
	}
	

	
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
				int xf = ImageG1[i][j][0];
				int mf = ImageM1[i][j][0];
				if (mf==1)
				{
					mf = 0;
				}
				else 
				{
					mf = 1;
				}
				int pf = ImageP1[i][j];
				ImageG2 [i][j] = xf & (mf | pf);
		}
	}
	
	int count_final = 0;
	if (flag2==1)
	{
		for (int i=n;i<height+n;i++)
		{
			for(int j=n;j<width+n;j++)
			{
				if (ImageG2pre[i][j] == ImageG2[i][j])
				{
					count_final = count_final + 1;
				}
			}
		}
		if (count_final == height * width){
			flag1 = 1;
			cout<<"count_finao is "<<count_final;
		}
	}
		
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			ImageG2pre[i][j] = ImageG2[i][j];
		}
	}
	flag2 = 1;
}

	
	
	for (int i=118;i<130;i++)
	{
		for(int j=103;j<115;j++)
		{
			cout<<ImageG1[i][j][0]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"*************************************************"<<ImageG1[119][104][0]<<endl;
	for (int i=119;i<130;i++)
	{
		for(int j=104;j<115;j++)
		{
			cout<<ImageM1[i][j][0]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"*************************************************"<<endl;
	for (int i=119;i<130;i++)
	{
		for(int j=104;j<115;j++)
		{
			cout<<ImageP1[i][j]<<" ";
		}
		cout<<endl;
	}
	
	int c_m=0;
	for (int i=1;i<height + 1;i++)
	{
		for(int j=1;j<width + 1;j++)
		{
			if(ImageM1[i][j][0]== 1){
				c_m = c_m +1;
			}
		}
		
	}
	cout<<"count of m is "<<c_m<<endl;
	
	int c_p=0;
	for (int i=1;i<height + 1;i++)
	{
		for(int j=1;j<width + 1;j++)
		{
			if(ImageP1[i][j]== 1){
				c_p = c_p +1;
			}
		}
		
	}
	cout<<"count of p is "<<c_p<<endl;
	
	
	int c_g=0;
	for (int i=1;i<height + 1;i++)
	{
		for(int j=1;j<width + 1;j++)
		{
			if(ImageG2[i][j]== 1){
				c_g = c_g +1;
			}
		}
		
	}
	cout<<"count of g is "<<c_g<<endl;
	
	for (int i=n;i<height+n;i++)
	{
		for(int j=n;j<width+n;j++)
		{
			imageout[i-n][j-n][0] = (unsigned char)(ImageG2pre[i][j]*255);
		}
	}
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageG1[i][j];

		delete[] ImageG1[i];
	}
	delete[] ImageG1;
	
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
			delete[] ImageM1[i][j];

		delete[] ImageM1[i];
	}
	delete[] ImageM1;
	
	for (int i = 0; i < nHeight; i++)
	{

		delete[] ImageP1[i];
	}
	delete[] ImageP1;

	cout<<endl<<height<<"  "<<width<<"  "<<BytesPerPixel<<"  "<<n<<"  ";
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*1, file);
	fclose(file);


	return 0;
}


