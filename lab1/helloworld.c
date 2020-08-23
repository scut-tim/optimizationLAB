#include<stdio.h>
#include<time.h>
int main(){
	clock_t start = clock();
	printf("hello world\n");
	clock_t end = clock();
	double time = (end - start)/CLOCKS_PER_SEC;
	printf("%f \n",time);


}
