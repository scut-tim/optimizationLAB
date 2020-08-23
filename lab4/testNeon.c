#include<stdio.h>
#include<arm_neon.h>
#include<stdint.h>

#define pp printf

uint32_t vector_add_of_n(uint32_t* ptr, uint32_t items){
uint32_t result,* i;
uint32x2_t vec64a, vec64b;
uint32x4_t vec128 = vdupq_n_u32(0); // clear accumulators
for (i=ptr; i<(ptr+(items/4));i+=4){
  uint32x4_t temp128 = vld1q_u32(i); // load four 32-bit values
  vec128=vaddq_u32(vec128, temp128); // add 128-bit vectors
}
vec64a = vget_low_u32(vec128); // split 128-bit vector
vec64b = vget_high_u32(vec128); // into two 64-bit vectors
vec64a = vadd_u32 (vec64a, vec64b); // add 64-bit vectors together
result = vget_lane_u32(vec64a, 0); // extract lanes and
result += vget_lane_u32(vec64a, 1); // add together scalars
return result;
}






int main(){





	uint32_t ptrr[8] = {1,2,3,4,5,6,7,8};
	uint32_t *ptr = ptrr;
	int r =	vector_add_of_n(ptr,8);
	uint32_t result,*i;
	uint32x2_t vec64a, vec64b;
	uint32x4_t vec128 = vdupq_n_u32(0);
	uint32_t items = 8;
	for(i = ptr;i<(ptr+items);i+=4){
		uint32x4_t temp128 = vld1q_u32(i);
		vec128 = vaddq_u32(vec128,temp128);
	}
	vec64a = vget_low_u32(vec128);
	vec64b = vget_high_u32(vec128);
	vec64a = vadd_u32(vec64a,vec64b);
	result = vget_lane_u32(vec64a,0);
	result += vget_lane_u32(vec64a,1);
	
	printf("%d\n",result);
        printf("%d\n",r);
	pp("%d\n",result);



}
