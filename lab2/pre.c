#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp = NULL;
	
	fp = fopen("guns.txt","r");
	if (fp == NULL) {
		printf("not found");
		return 0;
	}
	
	int ch;
	

	FILE *fpw = NULL;
	fpw = fopen("newguns.txt","w");

	while(EOF != (ch = fgetc(fp)))
	{
	
		
	
		printf("%c",ch);
		if(ch>='A' && ch<='Z'){
			ch = ch + 32;
		}
		if((ch>='A' && ch<='Z') ||(ch>='a' && ch<='z'));
		else{
			ch = ' ';
		}

		fputc(ch,fpw);
	}	
	//}


	//printf("1: %s\n", buff);

	fclose(fp);


    return 0;
}
