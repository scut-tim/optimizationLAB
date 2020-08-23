#include<stdio.h>
#include<time.h>


void do_block (int n, double *A, double *B, double *C)
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

 

void dgemm_block (int n, double* A, double* B, double* C)
{
    for ( int sj = 0; sj < n; sj += BLOCKSIZE )
        for ( int si = 0; si < n; si += BLOCKSIZE )
            for ( int sk = 0; sk < n; sk += BLOCKSIZE )
                do_block(n, A+si*n+sk, B+sk*n+sj,  C+si*n+sj);
}



int main(){



}

