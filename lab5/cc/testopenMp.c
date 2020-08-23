#include <stdio.h>
#include "omp.h"

int main(int argc, char **argv) {
	//设置线程数，一般设置的线程数不超过CPU核心数，这里开4个线程执行并行代码段

	int sum = 0;
	omp_set_num_threads(4);
#pragma omp parallel
{
    #pragma omp for reduction(+:sum)
    for(int i = 0;i<100000;i++){
        sum+=1;
    }

}

printf("%d ",sum);
}

