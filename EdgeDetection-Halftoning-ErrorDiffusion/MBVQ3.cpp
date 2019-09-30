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
#include<string>

using namespace std;

const int width = 500;
const int height = 375;
const int n = 2;

int GetMBVQ(float R, float G, float B){
	int mbvq;
	if((R+G) > 255){
				if((G+B) > 255){
					if((R+G+B) > 510){
						 mbvq = 1; //return CMYW;
						}
					else{
						mbvq = 2; //return MYGC;
						}
				}
				else{
					mbvq = 3; //return RGMY;
					}
				}
			else{
				if(!((G+B) > 255)){
					if(!((R+G+B) > 255)){
						mbvq = 4; //return KRGB;
					} 
					else{
						mbvq = 5; //return RGBM;
						}
				}
				else{
					mbvq = 6; //return CMGB
				}
				
			}
		
	return mbvq;
}

int GetNearestVertex(int mbvq,float R,float G,float B)
{
	int vertex;
	//cout<<"mbvq is "<<mbvq<<endl;
	// No.1 for CMYW
    if (mbvq == 1){
    	//cout<<"here"<<R<<" "<<G<<" "<<B<<"and 1"<<endl;
        vertex = 4;//'white';
        if (B < 0.5){
            if (B <= R){
                if (B <= G){
                    vertex = 7; //= 'yellow';
                }
            }
        }
        if (G < 0.5){
            if (G <= B){
                if (G <= R){
                    vertex = 6;//'magenta';
                }
            }
        }
        if (R < 0.5){
            if (R <= B){
                if (R <= G){
                    vertex = 5;//'cyan';
                }
            }
        }
    }

	//cout<<"last vertex is "<<vertex<<endl;
// No.2 for MYGC
    if (mbvq == 2){
    	//cout<<"here"<<R<<" "<<G<<" "<<B<<"and 2"<<endl;
        vertex = 6;//'magenta'; 
        if (G >= B){
            if (R >= B){
                if (R >= 0.5){
                    vertex = 7;//'yellow';
                }
                else{
                    vertex = 2;//'green';
                }
            }
        }
        if (G >= R){
            if (B >= R){
                if (B >= 0.5){
                    vertex = 5;//'cyan'; 
            	}
                else{
                    vertex = 2;//'green';
                }
            }
        }
    }

        	//cout<<"last vertex is "<<vertex<<endl;

// No.3 for RGMY
    if (mbvq == 3){
    	//cout<<"here"<<R<<" "<<G<<" "<<B<<"and 3"<<endl;
        if (B > 0.5){
            if (R > 0.5){
                if (B >= G){
                    vertex = 6;//'magenta';
                }
                else{
                    vertex = 7;//'yellow';
                }
            }
            else{
                if (G > B + R){
                    vertex = 2;//'green';
                }
                else{
                    vertex = 6;//'magenta';
                }
            }
    	}
        else{
            if (R >= 0.5){
                if (G >= 0.5){
                    vertex = 7;//'yellow';
                }
                else{
                    vertex = 1;//'red';
            	}
            }
            else{
                if (R >= G){
                    vertex = 1;//'red';
            	}
                else{
                    vertex = 2;//'green';
            	}
            }
        }
    }
	
        	//cout<<"last vertex is "<<vertex<<" changed "<<endl;

// No.4 for KRGB
    if (mbvq == 4){
    	//cout<<"here"<<R<<" "<<G<<" "<<B<<"and 4"<<endl;
        vertex = 8;//'black';
        if (B > 0.5){
            if (B >= R){
                if (B >= G){
                    vertex = 3;//'blue';
                }
            }
        }
        if (G > 0.5){
            if (G >= B){
                if (G >= R){
                    vertex = 2;//'green';
                }
            }
        }
        if (R > 0.5){
            if (R >= B){
                if (R >= G){
                    vertex = 1;//'red';
                }
            }
        }
    }

	        	//cout<<"last vertex is "<<vertex<<endl;

// No.5 for RGBM
    if (mbvq == 5)
    {
    	//cout<<"here"<<R<<" "<<G<<" "<<B<<"and 5"<<endl;
        vertex = 2;//'green';
        if (R > G){
            if (R >= B){
                if (B < 0.5){
                    vertex = 1;//'red';
                }
                else{
                    vertex = 6;//'magenta';
                }
            }
        }
        if (B > G){
            if (B >= R){
                if (R < 0.5){
                    vertex = 3;//'blue';
            	}
                else{
                    vertex = 6;//'magenta';
                }
            }
        }
    }

	//cout<<"last vertex is "<<vertex<<endl;
// No.6 for CMGB
    if (mbvq == 6){
    	    //	cout<<"here"<<R<<" "<<G<<" "<<B<<"and 6"<<endl;
        if (B > 0.5){
            if ( R > 0.5){
                if (G >= R){
                    vertex = 5;//'cyan';
            	}
                else{
                    vertex = 6;//'magenta';
                }
            }
            else{
                if (G > 0.5){
                    vertex = 5;//'cyan';
            	}
                else{
                    vertex = 3;//'blue';
                }
         	    }
            }
        else{
            if ( R > 0.5){
                if (R - G + B >= 0.5){
                    vertex = 5;//'magenta';
                }
                else{
                    vertex = 2;//'green';
                }
            }
            else{
                if (G >= B){
                    vertex = 2;//'green';
                }
                else{
                    vertex = 3;//'blue';
            	}
                }
            }
	}
        	//cout<<"last vertex is "<<vertex<<endl;
        return vertex;

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

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*3, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
 	//float sample [height][width][3];
	float ***sample = new float**[height]; 
	for(int i=0;i<height;i++){
	    sample[i] = new float*[width];
	    for (int j=0;j<width;j++){
	    	sample[i][j] = new float[3];
		} 	
	}
	/*for(int i=0;i<height;i++){
		for (int j=0;j<width;j++){
	    sample[i][j] = new int[1];
		}
	}*/
	int mbvq;
	float R,G,B,R1,G1,B1,R2,G2,B2;
	int vertex;
	unsigned char imageout[height][width][3];
	float floydM1[9] = {0,0,0,0,0,7/16.0,3/16.0,5/16.0,1/16.0};
 	float floydM2[9] = {0,0,0,7/16.0,0,0,1/16.0,5/16.0,3/16.0};
 	float *floydp1 = floydM1;
 	float *floydp2 = floydM2;
	float pixel_store[8][3] = {{255,0,0},{0,255,0},{0,0,255},{255,255,255},{0,255,255},{255,0,255},{255,255,0},{0,0,0}};
 	for (int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			sample[i][j][0] = (float)Imagedata[i][j][0];
			sample[i][j][1] = (float)Imagedata[i][j][1];
			sample[i][j][2] = (float)Imagedata[i][j][2];

 		}
 	}	
	for (int i=1;i<height-1;i++)
	{
		if (i%2==0)
 		{
			for(int j=1;j<width-1;j++)
			{
				R = sample[i][j][0];
				G = sample[i][j][1];
				B = sample[i][j][2];
				//cout<<R<<" "<<G<<" "<<B<<endl;
				mbvq = GetMBVQ(R,G,B);
				R2 = R;
				G2 = G;
				B2 = B;
				R = R/255;
				G = G/255;
				B = B/255;
				//cout<<R<<" "<<G<<" "<<B<<endl;
				vertex = GetNearestVertex(mbvq,R,G,B);		
				for(int k=0;k<3;k++)
        		{
        			sample[i][j][k]=pixel_store[vertex-1][k];
				}
				//cout<<mbvq<<"***"<<vertex<<endl;
				R1 = pixel_store[vertex-1][0];
				G1 = pixel_store[vertex-1][1];
				B1 = pixel_store[vertex-1][2];
				
				float errR = R2 - R1;
				float errG = G2 - G1;
				float errB = B2 - B1;
				//cout<<errR<<"||"<<errG<<"||"<<errB<<endl;
				for (int k=i-1;k<=i+1;k++)
						{
							for(int l=j-1;l<=j+1;l++)
							{	
								//cout<<"b"<<sample[k][l][0]<<"**";
								sample[k][l][0] = sample[k][l][0]  + (((*floydp1) * errR));
								sample[k][l][1] = sample[k][l][1]  + (((*floydp1) * errG));
								sample[k][l][2] = sample[k][l][2]  + (((*floydp1) * errB));
								floydp1++;
								//cout<<"a"<<sample[k][l][0]<<"  ";
							}
							//cout<<endl;
						}
						floydp1 = floydp1 - 9;
		        }
		
		}
		
		if (i%2!=0)
 		{
			for(int j=width-2;j>=1;j--)
			{
				R = sample[i][j][0];
				G = sample[i][j][1];
				B = sample[i][j][2];
				//cout<<R<<" "<<G<<" "<<B<<endl;
				mbvq = GetMBVQ(R,G,B);
				R2 = R;
				G2 = G;
				B2 = B;
				R = R/255;
				G = G/255;
				B = B/255;
				vertex = GetNearestVertex(mbvq,R,G,B);		
				for(int k=0;k<3;k++)
        		{
        			sample[i][j][k]=pixel_store[vertex-1][k];
				}
		
				R1 = pixel_store[vertex-1][0];
				G1 = pixel_store[vertex-1][1];
				B1 = pixel_store[vertex-1][2];
				
				float errR = R2 - R1;
				float errG = G2 - G1;
				float errB = B2 - B1;
				
				for (int k=i-1;k<=i+1;k++)
						{
							for(int l=j-1;l<=j+1;l++)
							{
								sample[k][l][0] = sample[k][l][0]  + (((*floydp2) * errR));
								sample[k][l][1] = sample[k][l][1]  + (((*floydp2) * errG));
								sample[k][l][2] = sample[k][l][2]  + (((*floydp2) * errB));
								floydp2++;
							}
						}
						floydp2 = floydp2 - 9;
		        }
		
		}
	}	
	
	for (int i =1;i<10;i++)
	{
		for (int j=1;j<10;j++)
		{
			for(int k =0;k<3;k++)
			{
				//cout<<sample[i][j][k]<<" ";
				if(sample[i][j][k]<0 or sample[i][j][k]>255)
				{
					cout<<"FAIL";
				}
			}
			//cout<<"**";
		}
		//cout<<endl;	
	}
	
	for (int i =1;i<height-1;i++)
	{
		for (int j=1;j<width-1;j++)
		{
			for(int k =0;k<3;k++)
			{
				imageout[i][j][k] = (unsigned char)sample[i][j][k];
			}
		}
	}
	
			//cout<<R<<" "<<G<<" "<<B<<endl;
			//cout<<R<<"  "<<G<<"  "<<B<<endl;
			//cout<<mbvq<<"****"<<vertex<<endl;
//***************************GET NEARTEST VERTEX************************************************
			
            
        
	//cout<<sample[50][50][0]<<"  "<<sample[50][50][1]<<"  "<<sample[50][50][2]<<"**"<<mbvq<<"  "<<vertex;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			delete[] sample[i][j];

		delete[] sample[i];
	}
	delete[] sample;

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*3, file);
	fclose(file);


	return 0;
}


