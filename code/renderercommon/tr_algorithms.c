

#include "tr_common.h"
#include "float.h"

/****************************
Algorithms
****************************/

int pas3mean(int columns, int rows, byte *targa_rgba, int row, int column)
{
		int arow=row;
		int acolumn=column;
		
		int total=0;
			byte *pixbuf;

		
for(row=rows-1; row>=arow+3; row--) 
		{
				pixbuf = targa_rgba + row*columns*4;
			for(column=0; column<acolumn+3; column++) 
			{
				total+=*pixbuf++;
				total+=*pixbuf++;
				total+=*pixbuf++;
				pixbuf++;
				
			}
			}
		return total/9;
}

#define DIVNUM 15


/**
 * 2 passes blur filter
 * @see http://www.filtermeister.com/tutorials/blur02.html
 */

/*void blur(int columns, int rows, byte *targa_rgba)
{

		// 4x4 kernel
	int	kernelwidth = 4, kernelheight = 4,
		x, y, z, xlook, ylook,
		sum, amount,
		// number of channels (R,G,B, skip alpha)
		channels = 3;

	// Temporary image
	byte*	t;

	// Allocate
	t = (byte*)malloc(sizeof(byte)*rows*columns*4);

	// First pass
	for (y=0; y < rows; y++){
		for (x=0; x < columns; x++){
			for (z= 0; z < channels; z++) {
				sum=0; amount=0;
				for (xlook=0; xlook<kernelwidth; xlook++)
				{
					switch(z){
						case 0:
							sum += getImageR(targa_rgba, (x+xlook-kernelwidth/2), y, columns, rows);
							break;
						case 1:
							sum += getImageG(targa_rgba, (x+xlook-kernelwidth/2), y, columns, rows);
							break;
						case 2:
							sum += getImageB(targa_rgba, (x+xlook-kernelwidth/2), y, columns, rows);
							break;
					}
					//sum+= src((x+xlook-kernelwidth/2),y,z);
					amount++;
				}; //accumulate pixels in a raw
				switch(z){
					// R
					case 0:
						setImageR(t,x,y,columns,rows,(byte)(sum/amount));
						break;
					// G
					case 1:
						setImageG(t,x,y,columns,rows,(byte)(sum/amount));
						break;
					// B
					case 2:
						setImageB(t,x,y,columns,rows,(byte)(sum/amount));
						break;

				}
			}
		}
	}
	// Second pass
	for (y=0; y < rows; y++) {
		for (x=0; x < columns; x++) {
			for (z= 0; z < channels; z++) {
				sum=0; amount=0;
				for (ylook=0; ylook<kernelheight; ylook++)
				{
					switch(z){
						case 0:
							sum+= getImageR(t,x,(y+ylook-kernelheight/2),columns,rows);
							break;
						case 1:
							sum+= getImageG(t,x,(y+ylook-kernelheight/2),columns,rows);
							break;
						case 2:
							sum+= getImageB(t,x,(y+ylook-kernelheight/2),columns,rows);
							break;
					}
					amount++;
				}; //accumulate pixels in a column
				switch(z){
					// R
					case 0:
						setImageR(targa_rgba,x,y,columns,rows,(byte)(sum/amount)); //divide the sum onto kernel size
						break;
					// G
					case 1:
						setImageG(targa_rgba,x,y,columns,rows,(byte)(sum/amount)); //divide the sum onto kernel size
						break;
					// B
					case 2:
						setImageB(targa_rgba,x,y,columns,rows,(byte)(sum/amount)); //divide the sum onto kernel size
						break;
				}

			}
		}
	}

	free(t);


}*/
void blur(int columns, int rows, byte *targa_rgba)
{
	int		row, column;
	float red,green,blue;
	float ared,agreen,ablue;
	
	ared=agreen=ablue=128;
	
		//for(row=rows-1; row>=0; row--) 
		for(row=0; row<rows; row++) 
		{
			//pixbuf = targa_rgba + row*columns*4;
			for(column=0; column<columns; column++) 
			{
				red=0;
				red+=getImageR(targa_rgba,column-1,row-1,columns,rows);
				red+=getImageR(targa_rgba,column,row-1,columns,rows);
				red+=getImageR(targa_rgba,column+1,row-1,columns,rows);
				red+=getImageR(targa_rgba,column-1,row,columns,rows);
				red+=getImageR(targa_rgba,column,row,columns,rows);
				red+=getImageR(targa_rgba,column+1,row,columns,rows);
				red+=getImageR(targa_rgba,column-1,row+1,columns,rows);
				red+=getImageR(targa_rgba,column,row+1,columns,rows);
				red+=getImageR(targa_rgba,column+1,row+1,columns,rows);
				
				red/=9;
				red*=2;
				red+=ared;
				red/=3;
				
				red=(int)red/DIVNUM;
				red*=DIVNUM;
				red+=(DIVNUM/2);
				ared=red;
				
				setImageR(targa_rgba, column, row, columns, rows, (byte)red);
				////////////////////
							green=0;
				green+=getImageG(targa_rgba,column-1,row-1,columns,rows);
				green+=getImageG(targa_rgba,column,row-1,columns,rows);
				green+=getImageG(targa_rgba,column+1,row-1,columns,rows);
				green+=getImageG(targa_rgba,column-1,row,columns,rows);
				green+=getImageG(targa_rgba,column,row,columns,rows);
				green+=getImageG(targa_rgba,column+1,row,columns,rows);
				green+=getImageG(targa_rgba,column-1,row+1,columns,rows);
				green+=getImageG(targa_rgba,column,row+1,columns,rows);
				green+=getImageG(targa_rgba,column+1,row+1,columns,rows);
				
				green/=9;
				green*=2;
				green+=agreen;
				green/=3;
				
				green=(int)green/DIVNUM;
				green*=DIVNUM;
				green+=(DIVNUM/2);
				agreen=green;
				setImageG(targa_rgba, column, row, columns, rows, (byte)green);
				////////////////////////
							blue=0;
				blue+=getImageB(targa_rgba,column-1,row-1,columns,rows);
				blue+=getImageB(targa_rgba,column,row-1,columns,rows);
				blue+=getImageB(targa_rgba,column+1,row-1,columns,rows);
				blue+=getImageB(targa_rgba,column-1,row,columns,rows);
				blue+=getImageB(targa_rgba,column,row,columns,rows);
				blue+=getImageB(targa_rgba,column+1,row,columns,rows);
				blue+=getImageB(targa_rgba,column-1,row+1,columns,rows);
				blue+=getImageB(targa_rgba,column,row+1,columns,rows);
				blue+=getImageB(targa_rgba,column+1,row+1,columns,rows);
				
				blue/=9;
				
				blue*=2;
				blue+=ablue;
				blue/=3;
				
				blue=(int)blue/DIVNUM;
				blue*=DIVNUM;
				blue+=(DIVNUM/2);
				
				ablue=blue;
				setImageB(targa_rgba, column, row, columns, rows, (byte)blue);
				
				// "halftoning"
				/*if((row%5==0)&&(column%5==1))
				{
					gris=0;
					gris+=red;
					gris+=green;
					gris+=blue;
					gris/=3;
					
					gris=255-gris;
					if(gris<0)
						gris=0;
						
						setImageR(targa_rgba, column, row, columns, rows, (byte)gris);
						setImageG(targa_rgba, column, row, columns, rows, (byte)gris);
						setImageB(targa_rgba, column, row, columns, rows, (byte)gris);
					
				}*/
			

			}
		}

}


/**
 * Converts the texture to a white image.
 */
void whiteTexture(int columns, int rows, byte *targa_rgba) {
	int		row, column;

	for(row=0;row<rows;row++){
		for(column=0;column<columns;column++){
			// Don't count fully transparent pixels
			if(getImageA(targa_rgba,column,row,columns,rows)==0)
				continue;
			setImageR(targa_rgba,column,row,columns,rows,255);
			setImageG(targa_rgba,column,row,columns,rows,255);
			setImageB(targa_rgba,column,row,columns,rows,255);
		}
	}
}/*
void whiteTexture(int columns, int rows, byte *targa_rgba){
	byte	*pixbyf;
	int		row, column;
	byte	rMean=0, gMean=0, bMean=0;
	int		pixels=0;

	for(row=0;row<rows;row++){
		for(column=0;column<columns;column++){
			// Don't count fully transparent pixels
			if(getImageA(targa_rgba,column,row,columns,rows)==255)
				continue;
			// Sum pixels values
			rMean+=getImageR(targa_rgba,column,row,columns,rows);
			gMean+=getImageG(targa_rgba,column,row,columns,rows);
			bMean+=getImageB(targa_rgba,column,row,columns,rows);
			pixels++;
		}
	}

	// Calculate average
	if(pixels>0){
		rMean/=pixels;
		gMean/=pixels;
		bMean/=pixels;
	}
	else{
		return;
	}

	for(row=0;row<rows;row++){
		for(column=0;column<columns;column++){
				setImageR(targa_rgba,column,row,columns,rows,rMean);
				setImageG(targa_rgba,column,row,columns,rows,gMean);
				setImageB(targa_rgba,column,row,columns,rows,bMean);
		}
	}
}*/

/**
 * Performs the real kuwahara filter on the bitmap.
 */
void kuwahara(int columns, int rows, byte *targa_rgba)
{
	byte channel;
	int size = 10;
	int index1,index2;
	int width = columns-4;
	int height = rows-4;
	int size2 = (size+1)/2;
	int offset = (size-1)/2;
	const int width2 = columns + offset;
	const int height2 = rows + offset;
	int x1start = 2;
	int y1start = 2;
	int x2, y2;
	int sum, sum2, n, v=0, xbase, ybase;
	int y1,x1;
	int xbase2=0, ybase2=0;
	float var, min;
	float** mean, **variance;

	blur(columns, rows, targa_rgba);

	// I hate malloc I hate malloc I hate malloc I hate malloc I hate malloc I hate malloc 
	mean = (float**)malloc(sizeof(float*)*width2);
	for(index1=0;index1<width2;index1++)
		mean[index1] = (float*)malloc(sizeof(float)*height2);

	variance = (float**)malloc(sizeof(float*)*width2);
	for(index2=0;index2<width2;index2++)
		variance[index2] = (float*)malloc(sizeof(float)*height2);

	// For each channel (R,G,B)
	for(channel=0;channel<2;channel++){
		for (y1=y1start-offset; y1<y1start+height; y1++) {

			for (x1=x1start-offset; x1<x1start+width; x1++) {
				sum=0; sum2=0; n=0;
				for (x2=x1; x2<x1+size2; x2++) {
					for (y2=y1; y2<y1+size2; y2++) {
						//v = i(x2, y2);
						switch(channel){
							case 0:
								v = getImageR(targa_rgba,x2,y2,columns,rows);
								break;
							case 1:
								v = getImageG(targa_rgba,x2,y2,columns,rows);
								break;
							case 2:
								v = getImageB(targa_rgba,x2,y2,columns,rows);
								break;
						}
						//v = *targa_rgba + y2*columns*4+x2*4;
						v/=10;
						v*=10;
						sum += v;
						sum2 += v*v;
						n++;
					}
				}
				//cerr << "Accedo" << endl;
				mean[x1+offset][y1+offset] = (float)(sum/n);
				variance[x1+offset][y1+offset] = (float)((n*sum2-sum*sum)/n);
			}
		}

		for (y1=y1start; y1<y1start+height; y1++) {
			/*if ((y1%20)==0)
				cout << (0.7+0.3*(y1-y1start)/height);*/
			for (x1=x1start; x1<x1start+width; x1++) {
				min =  FLT_MAX;
				xbase = x1; ybase=y1;
				var = variance[xbase][ybase];
				if (var<min){
					min= var;
					xbase2=xbase;
					ybase2=ybase;
				}
				xbase = x1+offset;
				var = variance[xbase][ybase];
				if (var<min){
					min= var;
					xbase2=xbase;
					ybase2=ybase;
				}
				ybase = y1+offset;
				var = variance[xbase][ybase];
				if (var<min){
					min= var;
					xbase2=xbase;
					ybase2=ybase;
				}
				xbase = x1;
				var = variance[xbase][ybase];
				if (var<min){
					min= var;
					xbase2=xbase;
					ybase2=ybase;
				}
				//i(x1, y1)=(int)(mean[xbase2][ybase2]+0.5);
				switch(channel){
					case 0:
						setImageR(targa_rgba,x1,y1,columns,rows,(byte)(mean[xbase2][ybase2]+0.5));
						break;
					case 1:
						setImageG(targa_rgba,x1,y1,columns,rows,(byte)(mean[xbase2][ybase2]+0.5));
						break;
					case 2:
						setImageB(targa_rgba,x1,y1,columns,rows,(byte)(mean[xbase2][ybase2]+0.5));
						break;
				}
			}
		}
	}
	// Fuck mean & variance, this is hell (!+) Bad Religion
	for(index1=0;index1<width2;index1++)
		free(mean[index1]);
	free(mean);

	for(index2=0;index2<width2;index2++)
		free(variance[index2]);
	free(variance);
	
	blur(columns, rows, targa_rgba);  
   }

//RED
byte getImageR(byte *targa_rgba, int x, int y, int columns, int rows)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
	
	if(columns<x)
		x=x%columns;
	
	if(x<0)
		x*=-1;
	
	pixbuf+=(x*4);
	
	return *pixbuf;
}

void setImageR(byte *targa_rgba, int x, int y, int columns, int rows, byte value)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
	
	pixbuf+=(x*4);
	
	*pixbuf=value;
}
//GREEN
byte getImageG(byte *targa_rgba, int x, int y, int columns, int rows)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
		if(columns<x)
		x=x%columns;
	
	if(x<0)
		x*=-1;
	
	pixbuf+=(x*4);
	
	pixbuf++;
	return *pixbuf;
}

void setImageG(byte *targa_rgba, int x, int y, int columns, int rows, byte value)
{
	byte	*pixbuf;

	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);

	pixbuf = targa_rgba + y*columns*4;
	
	pixbuf+=(x*4);
	pixbuf++;
	*pixbuf=value;
}
//BLUE
byte getImageB(byte *targa_rgba, int x, int y, int columns, int rows)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
		if(columns<x)
		x=x%columns;
	
	if(x<0)
		x*=-1;
	
	pixbuf+=(x*4);
	pixbuf+=2;
	return *pixbuf;
}

void setImageB(byte *targa_rgba, int x, int y, int columns, int rows, byte value)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
	pixbuf+=(x*4);
	pixbuf+=2;
	*pixbuf=value;
}
//ALPHA
byte getImageA(byte *targa_rgba, int x, int y, int columns, int rows)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
	pixbuf+=(x*4);
	pixbuf+=3;
	return *pixbuf;
}

void setImageA(byte *targa_rgba, int x, int y, int columns, int rows, byte value)
{
	byte	*pixbuf;
	
	x*=((x<0)?-1:1);
	y*=((y<0)?-1:1);
	
	pixbuf = targa_rgba + y*columns*4;
	
	pixbuf+=(x*4);
	pixbuf+=3;
	*pixbuf=value;
}
