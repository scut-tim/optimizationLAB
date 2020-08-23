#include<stdio.h>
#include<stdlib.h>

int cmp ( const void *a , const void *b){
        return *(int *)b - *(int *)a;
}

int main(){

	FILE *fp = NULL;
	int blank = 0;	
	int letter[27] = {0};
	fp = fopen("newguns.txt","r");

	int ch;
	
	while(EOF != (ch = fgetc(fp))){
		
	if(ch == ' '){ blank++; continue;}
	if(ch == 'a'){letter['a'-97]++; continue;}
	if(ch == 'b'){letter['b'-97]++; continue;}
	if(ch == 'c'){letter['c'-97]++; continue;}
	if(ch == 'd'){letter['d'-97]++; continue;}
	if(ch == 'e'){letter['e'-97]++; continue;}
	if(ch == 'f'){letter['f'-97]++; continue;}
	if(ch == 'g'){letter['g'-97]++; continue;}
	if(ch == 'h'){letter['h'-97]++; continue;}
	if(ch == 'i'){letter['i'-97]++; continue;}
	if(ch == 'j'){letter['j'-97]++; continue;}
	if(ch == 'k'){letter['k'-97]++; continue;}
	if(ch == 'l'){letter['l'-97]++; continue;}
	if(ch == 'm'){letter['m'-97]++; continue;}
	if(ch == 'n'){letter['n'-97]++; continue;}
	if(ch == 'o'){letter['o'-97]++; continue;}
	if(ch == 'p'){letter['p'-97]++; continue;}
	if(ch == 'q'){letter['q'-97]++; continue;}
	if(ch == 'r'){letter['r'-97]++; continue;}
	if(ch == 's'){letter['s'-97]++; continue;}
	if(ch == 't'){letter['t'-97]++; continue;}
	if(ch == 'u'){letter['u'-97]++; continue;}
	if(ch == 'v'){letter['v'-97]++; continue;}
	if(ch == 'w'){letter['w'-97]++; continue;}
	if(ch == 'x'){letter['x'-97]++; continue;}
	if(ch == 'y'){letter['y'-97]++; continue;}
	if(ch == 'z'){letter['z'-97]++; continue;}	
	}

	printf("blank: %d\n",blank);
	for(int i = 0;i<26;i++){
		printf("%d\n",letter[i]);
	}

	letter[26] = blank;
	int tmp[27];
	for(int i = 0;i<26;i++){
		tmp[i] = letter[i];
	}
		
	qsort(letter,27,sizeof(int),cmp);

	char c = ' ';
	for(int i = 0;i<27;i++){
		for(int j = 0;j<27;j++){
			if(tmp[j] == letter[i]){
				c = 'a' + j;
			}
		}
                printf("%c: %d",c,letter[i]);
		if(i % 4 == 0)printf("\n");
        }

	
}
