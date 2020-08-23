#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define LENGTH 27



typedef int ElemType;

typedef struct HuffmanTreeNode{
    ElemType data;  //哈夫曼树中节点的权值
    struct HuffmanTreeNode* left;
    struct HuffmanTreeNode* right;
}HuffmanTreeNode,*PtrHuffman;
//2038074
int* decode(int *code,int len, PtrHuffman root){
    
    PtrHuffman temp = root;
    int* result = malloc(2038074);
    int r = 0;
    for(int i = 0;i<len;i++){
        if(temp->left == NULL && temp->right == NULL){
            result[r++] = temp->data;
            temp = root;
        }
        if(code[i] == 0) temp = temp->left;
        else                  temp = temp->right;
    }
    return result;

}





PtrHuffman createHuffmanTree(ElemType arr[]){
    PtrHuffman ptrArr[LENGTH];
    PtrHuffman ptr,pRoot=NULL;

    for (int i = 0; i < LENGTH; i++){  
        ptr = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));
        ptr->data = arr[i];
        ptr->left = ptr->right = NULL;
        ptrArr[i] = ptr;
    }

    for(int i = 1; i < LENGTH; i++){  
        int k1 = -1, k2;
        for(int j = 0; j < LENGTH; j++){
            if (ptrArr[j] != NULL && k1 == -1){
                k1 = j;
                continue;
            }
            if (ptrArr[j] != NULL){
                k2 = j;
                break;
            }
        }
        
        for (int j = k2; j < LENGTH; j++){
            if(ptrArr[j] != NULL){
                if(ptrArr[j]->data < ptrArr[k1]->data){
                    k2 = k1;
                    k1 = j;
                }else if(ptrArr[j]->data < ptrArr[k2]->data){
                    k2 = j;
                }
            }
        }
        
        pRoot = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));
        pRoot->data = ptrArr[k1]->data + ptrArr[k2]->data;
        pRoot->left = ptrArr[k1];
        pRoot->right = ptrArr[k2];

        ptrArr[k1] = pRoot; 
        ptrArr[k2] = NULL; 
    }

    return pRoot;
}






int main(){

	ElemType w[27];
    	w[1] = 67962112;
   	w[2] = 24373121;
   	w[3] = 4762938;
    	w[4] = 8982417;
    	w[5] = 10805580;
    	w[6] = 37907119;
    	w[7] = 7486889;
    	w[8] = 5143059;
    	w[9] = 18058207;
    	w[10] = 21820970;
    	w[11] = 474021;
    	w[12] = 1720909;
    	w[13] = 11730498;
    	w[14] = 7391336;
    	w[15] = 21402466;
    	w[16] = 23215532;
    	w[17] = 5719422;
    	w[18] = 297237;
    	w[19] = 17897352;
    	w[20] = 19059775;
    	w[21] = 28691274;
    	w[22] = 8022379;
    	w[23] = 2835696;
    	w[24] = 6505294;
    	w[25] = 562732;
    	w[26] = 5910495;
    	w[0] = 93172;

    	PtrHuffman pRoot = createHuffmanTree(w);  
    	
    	printf("%d\n",pRoot->data);


	int *code = malloc(12007740);
	FILE *fp = fopen("encodeguns.txt","r");
	if(fp == NULL)
	printf("file not found");
	int i = 0,ch;
	
	while(EOF != (ch = fgetc(fp))) code[i++] = ch - 48;
	fclose(fp);
	printf("len: %d\n",i);
	//for(int j = 0;j<100;j++)
	//printf("%d",code[j]);
	
	clock_t start;
	clock_t end;
	start = clock();
	int* result = decode(code,2038074,pRoot);
	end = clock();
	for(int j = 0;j<19;j++)printf("%d ",result[j]);
	double time = (double)(end-start)/CLOCKS_PER_SEC;
	printf("没有消除分支time: %f\n",time);


}
