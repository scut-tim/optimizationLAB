
#include<stdio.h>
#include<malloc.h>
#include <string.h>
#include<math.h>
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
			for (int y = 0; y < height; y++) {
				int y1 = y - halfW + height;
				for (int x = 0; x < width; x++) {
					int x1 = x - halfW + width;
					int r = 0;
					int g = 0;
					int b = 0;
					float32x4_t rgb = vdupq_n_f32(0);
					unsigned int p = (y * width + x) * channels;
					for (unsigned int fx = 0; fx < filterW; fx++) {
						int dx = (x1 + fx) % width;
						int fidx = fx * (filterW);
						for (unsigned int fy = 0; fy < filterW; fy++) {
							int pos = (((y1 + fy) % height) * width + dx) * channels;
							int * pfilter = & filter[fidx + (fy)];
							//r += data[pos] * ( * pfilter);
							//g += data[pos + 1] * ( * pfilter);
							//b += data[pos + 2] * ( * pfilter);
								
							uint8x8_t datax8 = vld1_u8(&data[pos]);
					//		uint8_t data1 = vget_lane_u8(datax8,0);
					//		uint8_t data2 = vget_lane_u8(datax8,1);
					//		uint8_t data3 = vget_lane_u8(datax8,2);
							uint16x8_t datax8Mv = vmovl_u8(datax8);//move
							int32x4_t filterx4 = vdupq_n_s32(filter[fidx+(fy)]);//dup filter
							uint16x4_t datax4 = vget_low_u16(datax8Mv);//get low 3 wanted data
							uint32x4_t datax4_32 = vmovl_u16(datax4);//trans to 32
							
							rgb = vmlaq_f32(rgb,vcvtq_f32_u32(datax4_32),vcvtq_f32_s32(filterx4));
							
							
							
							
					//		uint32x4_t vld1q_u32 (uint32_t const * ptr)
							int a = 1;
							a++;	
						}
					}
					float32x2_t rg = vget_low_f32(rgb);
                                        float32x2_t bb = vget_high_f32(rgb);
					r = (int)vget_lane_f32(rg,0);
					g = (int)vget_lane_f32(rg,1);
					b = (int)vget_lane_f32(bb,0);
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
        stbi_write_bmp("write1WithNeon.bmp",512,512,3,tmpData);
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
    Convolution2D(imgData, imgWidth, imgHeight, imgChannels, edges1filter, 5, 1, 0);
    printf("done.........");
    stbi_image_free(imgData);
}
