/** 哈夫曼树编码 **/
#include<stdio.h>
#include<stdlib.h>
#define LENGTH 27

typedef int ElemType;

typedef struct HuffmanTreeNode{
    ElemType data;  //哈夫曼树中节点的权值
    struct HuffmanTreeNode *child[2];
}HuffmanTreeNode,*PtrHuffman;
//2038074
//int* decode(int *code,int len, PtrHuffman root){
//
//    PtrHuffman temp = root;
//    int* result = malloc(2038074);
//    int r = 0;
//    for(int i = 0;i<len;i++){
//        if(temp->left == NULL && temp->right == NULL){
//            result[r++] = temp->data;
//            temp = root;
//        }
//        if(code[i] == 0) temp = temp->left;
//        else                  temp = temp->right;
//    }
//    return result;
//
//}




/**
 * 创建哈夫曼树
 */
PtrHuffman createHuffmanTree(ElemType arr[]){
    PtrHuffman ptrArr[LENGTH];
    PtrHuffman ptr,pRoot=NULL;

    for (int i = 0; i < LENGTH; i++){  //初始化结构体指针数组,数组中每一个元素为一个结构体指针类型
        ptr = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));
        ptr->data = arr[i];
        ptr->child[0] = ptr->child[1] = NULL;
        ptrArr[i] = ptr;
    }

    for(int i = 1; i < LENGTH; i++){  //进行 n-1 次循环建立哈夫曼树
        //k1表示森林中具有最小权值的树根结点的下标,k2为次最小的下标
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
        //将指针数组中的指针指向的最小值赋值给索引号为k1的,次小值赋值给索引号为k2的
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
        //由最小权值树和次最小权值树建立一棵新树,pRoot指向树根结点
        pRoot = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));
        pRoot->data = ptrArr[k1]->data + ptrArr[k2]->data;
        pRoot->child[0] = ptrArr[k1];
        pRoot->child[1] = ptrArr[k2];

        ptrArr[k1] = pRoot; //将指向新树的指针赋给ptrArr指针数组中k1位置
        ptrArr[k2] = NULL; //k2位置为空
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

    PtrHuffman pRoot = createHuffmanTree(w);  //返回指向哈夫曼树根节点的指针
    //printf("%d\n",pRoot->data);
//    if(pRoot->right->right == NULL && pRoot->right->left == NULL)
//    printf("%d\n",pRoot->right->data);



    return 0;
}
