#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int BLOCKSIZE;

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



void do_block (int n, float *A, float *B, float *C)
{
    for(int i = 0; i < BLOCKSIZE; i++)
    {
        for(int j = 0; j < BLOCKSIZE; j++)
        {
            double cij = C[i*n+j];
            for(int k = 0; k < BLOCKSIZE; k++ )
                cij +=A[i*n+k] * B[k*n + j];
            C[i*n+j] = cij;
        }
    }
}



void dgemm_block (int n, float* A, float* B, float* C)
{
    for ( int sj = 0; sj < n; sj += BLOCKSIZE )
        for ( int si = 0; si < n; si += BLOCKSIZE )
            for ( int sk = 0; sk < n; sk += BLOCKSIZE )
                do_block(n, A+si*n+sk, B+sk*n+sj,  C+si*n+sj);
}



int main(int argc, char *argv[]){

	float seed;
	int N;
	seed = atof(argv[1]);
	N = atoi(argv[2]);
	BLOCKSIZE = atoi(argv[3]);
	printf("seed: %f, N: %d BLOCKSIZE: %d\n",seed,N,BLOCKSIZE);
	float *a = (float*)malloc((N*N)*sizeof(float));
	float *b = (float*)malloc((N*N)*sizeof(float)); 
	matrix_gen(a,b,N,seed);
	printf("ok1\n");
	float *mul = (float*)malloc((N*N)*sizeof(float));
	float sum;
	
	clock_t start;
	clock_t end;

	start = clock();
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++){
			sum = 0;
			for(int k = 0;k<N;k++){
				sum+=a[i*N+k]*b[k*N+j];
				//printf("%d :: %d\n",i*N+k,k*N+j);
			}
			mul[i*N+j] = sum;
		}
		

	}
	end = clock();
	printf("runtime with no block: %f\n",(double)(end - start)/CLOCKS_PER_SEC);

	float trace = 0;
	for(int i = 0;i<N;i++){
		trace += mul[i*N + i];
	}
	//for(int i = 0;i<N*N;i++){
	//	printf("%f ",mul[i]);
	//	if(i % N == 3) printf("\n");
	//}
	printf("trace: %f\n",trace);

	float *c = (float*)malloc((N*N)*sizeof(float));
	start = clock();
	dgemm_block(N,a,b,c);		
	end = clock();
	printf("runtime with block: %f\n",(double)(end - start)/CLOCKS_PER_SEC);
//	      for(int i = 0;i<N*N;i++){
//              printf("%f ",c[i]);
//              if(i % N == 3) printf("\n");
//  	 }



}
