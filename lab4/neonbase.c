#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<arm_neon.h>
#define BLOCKSIZE 128

float rand_float(float s){
	return 4*s*(1-s);
	
}

void matrix_gen(float *a,float *b,int N,float seed){
	float s = seed;
	for(int i=0;i<N*N;i++){
		s=rand_float(s);
		a[i]=s;
		s=rand_float(s);
		b[i]=s;
	}
}




int main(int argc, char *argv[]){

	float seed;
	int N;
	seed = atof(argv[1]);
	N = atoi(argv[2]);

	printf("seed: %f, N: %d\n",seed,N);
	float *a = (float*)malloc((N*N)*sizeof(float));
	float *b = (float*)malloc((N*N)*sizeof(float)); 
	matrix_gen(a,b,N,seed);
	printf("ok1\n");
	float *mul = (float*)malloc((N*N)*sizeof(float));
	float sum;
	float32x4_t ret = vdupq_n_f32(0.0f);
	

	clock_t start;
	clock_t end;
	start = clock();
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j+=4){
			for(int k = 0;k<N;k++){
				float32x4_t P = vdupq_n_f32(a[k + i*N]);
				float32x4_t M = vld1q_f32(&b[j + k*N]);
			//	vfmaq_f32(ret,vdupq_n_f32(a[k]),vld1q_f32(&b[k*N+4]));
				float32x4_t mul = vmulq_f32(P,M);
				ret = vaddq_f32(ret,mul);
			}
			vst1q_f32(&mul[i*N + j],ret);//写入
			ret = vdupq_n_f32(0.0f);
		}
	}
	end = clock();
	printf("runtime with neon: %f",(double)(end-start)/CLOCKS_PER_SEC);
/*	float32x2_t vec64a, vec64b;
	vec64a = vget_low_f32(ret);
	vec64b = vget_high_f32(ret);	
	
	printf("%f\n",vget_lane_f32(vec64a,0));
	printf("%f\n",vget_lane_f32(vec64a,1));
	printf("%f\n",vget_lane_f32(vec64b,0));
	printf("%f\n",vget_lane_f32(vec64b,1));
*/	
/*
	        for(int i = 0;i<N*N;i++){
                printf("%f ",mul[i]);
                if(i % N == 3) printf("\n");
        }
	
*/
	

}
