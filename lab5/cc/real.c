#include<time.h>
#include<stdio.h>
#include<malloc.h>
#include <string.h>
#include<arm_neon.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



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
			for (int y = 0; y < height; y+=4) {
				int y1 = y - halfW + height;

				for (int x = 0; x < width; x++) {
					int x1 = x - halfW + width;
					int r = 0;
					int g = 0;
					int b = 0;
                    int32x4_t rgb=vdupq_n_s32(0);
					unsigned int p = (y * width + x) * channels;
					for (unsigned int fx = 0; fx < filterW; fx++) {
						int dx = (x1 + fx) % width;
						int fidx = fx * (filterW);
						for (unsigned int fy = 0; fy < filterW; fy++) {
							int pos = (((y1 + fy) % height) * width + dx) * channels;
							// int * pfilter = & filter[fidx + (fy)];
                            int datax4[4];
                            for(int i=0;i<3;i++){
                                datax4[i]=data[pos+i];
                            }
                            datax4[3]=0;
                            int32x4_t datax4_32_s=vld1q_s32(datax4);
                            // printf("rgb:%d    ",rgb);
                            int32x4_t filterx4 = vdupq_n_s32(filter[fidx+(fy)]);//dup filter
                            // int32x4_t pfilterx4=vdupq_n_s32(* pfilter);
							// r += data[pos] * ( * pfilter);
							// g += data[pos + 1] * ( * pfilter);
							// b += data[pos + 2] * ( * pfilter);
                            // int32x4_t resrgb=vmulq_s32(rgb,pfilterx4);
                            // rgb=vaddq_s32(rgb,resrgb);
                            rgb = vmlaq_s32(rgb,datax4_32_s,filterx4);
						}
					}
                    r=vgetq_lane_s32 (rgb, 0);
                    // printf("r:%d\n",rgb);
                    g=vgetq_lane_s32 (rgb, 1);
                    b=vgetq_lane_s32 (rgb, 2);
					tmpData[p] = Clamp2Byte(((factor * r) >> 8) + bias);
					tmpData[p + 1] = Clamp2Byte(((factor * g) >> 8) + bias);
					tmpData[p + 2] = Clamp2Byte(((factor * b) >> 8) + bias);
				}
			}
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
        stbi_write_bmp("write1_neon.bmp",512,512,3,tmpData);
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
    	clock_t start;
	clock_t end;
	start = clock();
    Convolution2D(imgData, imgWidth, imgHeight, imgChannels, edges1filter, 5, 1, 0);
    end = clock();
	printf("runtime with neon: %f s\n",(double)(end-start)/CLOCKS_PER_SEC);
    // printf("fuck");
    stbi_image_free(imgData);
}
