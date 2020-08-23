#include<stdio.h>
#include<time.h>
int main(){
	printf("wo");
	FILE *fp = NULL;
	

	fp = fopen("newguns.txt","r");
	printf("wow\n");
	char *code[27];
	code[26] = "111";
	code['e'-97] = "010";
	code['t'-97] = "1101";
	code['a'-97] = "1011";
	code['o'-97] = "1001";
	code['i'-97] = "1000";
	code['n'-97] = "0111";
	code['s'-97] = "0011";
	code['h'-97] = "0010";
	code['r'-97] = "0001";
        code['l'-97] = "10101";
        code['d'-97] = "01101";
        code['c'-97] = "00001";
        code['u'-97] = "00000";
        code['f'-97] = "110011";
        code['m'-97] = "110010";
        code['w'-97] = "110001";
        code['y'-97] = "101001";
        code['p'-97] = "101000";
        code['g'-97] = "011001";
        code['b'-97] = "011000";
        code['v'-97] = "1100000";
        code['k'-97] = "11000011";
        code['x'-97] = "110000100";
        code['j'-97] = "1100001011";
        code['q'-97] = "11000010101";
	code['z'-97] = "11000010100";
	
		

	FILE *fpencode = NULL;
	fpencode = fopen("encodeguns.txt","w");	
	
	int ch;
	clock_t start = clock();
	while(EOF != (ch = fgetc(fp))){
		
		if(ch == ' ')
		fputs(code[26],fpencode);
		else
		fputs(code[ch-97],fpencode);
	}
	clock_t end = clock();
	double time =(double) (end - start)/CLOCKS_PER_SEC;
	printf("%f\n",time);

	




}
