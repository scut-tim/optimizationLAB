
#include<stdio.h>
#include<malloc.h>
#include <string.h>
#include<time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
int count0 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
unsigned char Clamp2Byte(int n) {
	return (((255 - n) >> 31) | (n & ~(n >> 31)));
}
void Convolution2D(unsigned char * data,
                   unsigned int width, unsigned int height,
                   unsigned int channels, int * filter,
                   unsigned char filterW, unsigned char cfactor, unsigned char bias) {

		unsigned char * tmpData = (unsigned char * ) malloc(width * height * channels);
		int factor = 256 / cfactor;
		int halfW = filterW / 2;
		if (channels == 3 || channels == 4) {
			
			clock_t start,end;
			start = clock();
			for (int y = 0; y < height; y++) {
				int y1 = y - halfW + height;
				for (int x = 0; x < width; x++) {
					int x1 = x - halfW + width;
					int r = 0;
					int g = 0;
					int b = 0;
					unsigned int p = (y * width + x) * channels;
					for (unsigned int fx = 0; fx < filterW; fx++) {
						int dx = (x1 + fx) % width;
						int fidx = fx * (filterW);
						for (unsigned int fy = 0; fy < filterW; fy++) {
							//clock_t startIN,endIN;
							//startIN = clock();
							int pos = (((y1 + fy) % height) * width + dx) * channels;
							int * pfilter = & filter[fidx + (fy)];
							r += data[pos] * ( * pfilter);
							g += data[pos + 1] * ( * pfilter);
							b += data[pos + 2] * ( * pfilter);
							//endIN = clock();
														
							
						//	if(endIN - startIN < 1)count0++;
							
						//	if(endIN - startIN == 1)count1++;
						//	if(endIN - startIN == 2)count2++;
						//	if(endIN - startIN > 2) count3++;


						}
					}
					tmpData[p] = Clamp2Byte(((factor * r) >> 8) + bias);
					tmpData[p + 1] = Clamp2Byte(((factor * g) >> 8) + bias);
					tmpData[p + 2] = Clamp2Byte(((factor * b) >> 8) + bias);
				}
			}end = clock(); printf("run time with no neon: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
			//printf("clock times 1: %d, clock times 2: %d clock times 0: %d clock times 3: %d",count1,count2,count0,count3);
		} else
		if (channels == 1) {
			for (int y = 0; y < height; y++) {
				int y1 = y - halfW + height;
				for (int x = 0; x < width; x++) {
					int r = 0;
					unsigned int p = (y * width + x);
					int x1 = x - halfW + width;
					for (unsigned int fx = 0; fx < filterW; fx++) {
						int dx = (x1 + fx) % width;
						int fidx = fx * (filterW);
						for (unsigned int fy = 0; fy < filterW; fy++) {
							int pos = (((y1 + fy) % height) * width + dx);
							int szfilter = filter[fidx + (fy)];
							r += data[pos] * szfilter;


						}
					}
					tmpData[p] = Clamp2Byte(((factor * r) >> 8) + bias);
				}
			}
		}
		memcpy(data, tmpData, width * height * channels);
		//int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
        stbi_write_bmp("write1.bmp",512,512,3,tmpData);
		free(tmpData);
	}


int main(){
    int w,h,n;
    unsigned char *imgData = stbi_load("Lenna.bmp",&w,&h,&n,0);

    unsigned int imgWidth = 512;
    unsigned int imgHeight = 512;
    unsigned int imgChannels = 3;


//int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);


    //边缘
    int edges1filter[25] = {
        -1, 0, 0, 0, 0,
        0, -2, 0, 0, 0,
        0, 0, 6, 0, 0,
        0, 0, 0, -2, 0,
        0, 0, 0, 0, -1,
    };


int sharpen2filter[25] = { -1, -1, -1, -1, -1, -1, 2, 2, 2, -1, -1, 2, 8, 2, -1, -1, 2, 2, 2, -1, -1, -1, -1, -1, -1, };
int MotionBlurfilter[81] = 
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
int edges2filter[9] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };
	
    Convolution2D(imgData, imgWidth, imgHeight, imgChannels, edges1filter, 5, 1, 0);
    printf("done..............\n");
    stbi_image_free(imgData);
}
