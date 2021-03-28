#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
typedef struct{
char label[10], mnemonic[10], op1[10], op2[10];
}Instruction;
typedef struct{
int id, length;
char mnemonic[10], type[10], code[10];
}Mnemonic;
typedef struct{
int location;
char code[10],op1[10],op2[10];
}intermediate_code;
typedef struct{
	char literal[10];
	int address,index;
}literal;
typedef struct{
	char symbol[10];
	int length,value,address,index;
}symbol;
typedef struct{
	literal literal[10];
	int start,size;
}literaltable;
typedef struct{
	symbol symbol[10];
	int size;
}symboltable;
bool isadigit(char i){
	if(i=='0'||i=='1'||i=='2'||i=='3'||i=='4'||i=='5'||i=='6'||i=='7'||i=='8'||i=='9'){
		return true;
	}
		return false;
}
bool isInteger(char number[10]){
	bool result = true;
	while(*number!='\0'){
		if(!isadigit(*number)){
			result = false;
			break;
		}
		number++;
		
	}
	return result;
}
int eval(char exp[20],symboltable st, FILE** f){
	int j=-1,flag = 0,i=0;
	while(exp[i]!='\0'){
		if(exp[i] == '+'||*exp == '-'){
			j = i;
		}
		i++;
	}
	char sym[10],num[10];
	if(j!=-1){
		for(i=0;i<j;i++){
			sym[i] = exp[i];
		}
		sym[i] = '\0';
		
		for(i=j+1;exp[i]!='\0';i++){
			num[i-j-1] = exp[i];
		}
		num[i] = '\0';
		
		for(i=0;i<st.size;i++){
			if(!strcmp(st.symbol[i].symbol,sym)){
				if(exp[j] == '+'){
					fprintf(*f,"(S,%02d)+(C,%02d)\n",st.symbol[i].index,atoi(num));	
					return st.symbol[i].address + atoi(num);
				}
			else{
				fprintf(*f,"(S,%02d)-(C,%02d)\n",st.symbol[i].index,atoi(num));
				return st.symbol[i].address - atoi(num);
			}
		}
	}
}else{
	for(i=0;i<st.size;i++){
		if(!strcmp(st.symbol[i].symbol,exp)){
			fprintf(*f,"(S,%02d)\n",st.symbol[i].index);
				return st.symbol[i].address;
			}
		}
	}	
}

Mnemonic search(char mnemonic[10]){
	Mnemonic info, result;
	FILE *mot;
	mot = fopen("mot.txt","r");
	while(!feof(mot)){
		fscanf(mot,"%d\t%s\t%s\t%s\t%d", &info.id, info.mnemonic, info.type, info.code, &info.length);
		if(!strcmp(info.mnemonic, mnemonic)){
			fclose(mot);
			return info;
		}
	}
	result.id = 0;
	strcpy(result.mnemonic,"*");
	strcpy(result.type,"*");
	strcpy(result.code,"00");
	result.length = 0;
	return result;
}
int main(){
	int location_counter=0, location = 0,lc=1,sc=1,i,pool = 1;
	char type1[10],code1[10],lit[10][10],sym[10][10];
	symboltable st;
	literaltable lt;
	lt.size = 0;
	lt.start = 0;
	st.size = 0;
	FILE *src,*ic;
	ic = fopen("ic.txt","w");
	char filename[] = "program.txt";
	printf("Enter the name of the source file: ");
	scanf("%s",filename);
	src = fopen(filename,"r");
	Mnemonic info,op1info;
	Instruction source;
	while(!feof(src)){
		fscanf(src,"%s\t%s\t%s\t%s",source.label,source.mnemonic,source.op1,source.op2);
		info = search(source.mnemonic);
		if(source.op1[strlen(source.op1)-1] == ','){
			source.op1[strlen(source.op1)-1] = '\0';
		}
		if(source.op2[strlen(source.op2)-1] == '\''&& source.op2[0]!='='){
			source.op2[strlen(source.op2)-1] = '\0';
		}
		if(source.op2[0] == '\''){
			for(i=1;i<strlen(source.op2)+1;i++){
				source.op2[i-1] = source.op2[i];
			}
		}
		if(strcmp(source.label,"**") && strcmp(info.type,"AD")){
			int flag = 0;
			for(i=0;i<st.size;i++){
				if(!strcmp(st.symbol[i].symbol,source.label)){
					flag = 1;
					sc = i;
					break;
				}
			}
			if(!flag){
				strcpy(st.symbol[st.size].symbol,source.label);
				st.symbol[st.size].address = location_counter;
				st.symbol[st.size].index = st.size + 1;
				st.size++;
			}else{
				st.symbol[i].address = location_counter;
			}
		}
		if(!strcmp(source.mnemonic, "START")){
			fprintf(ic,"*\t(AD,%s)\t*\t(C,%s)\t\n",info.code,source.op2);
			location_counter = atoi(source.op2);
			continue;
		}else if(!strcmp(source.mnemonic, "ORIGIN")){
			fprintf(ic,"*\t(AD,%s)\t*\t",info.code);
			location_counter = eval(source.op2,st,&ic);
			continue;
		}else if(!strcmp(source.mnemonic, "EQU")){
			fprintf(ic,"*\t(AD,%s)\t*\t",info.code);
			strcpy(st.symbol[st.size].symbol,source.label);
			st.symbol[st.size].index = st.size+1;
			st.symbol[st.size].address = eval(source.op2,st,&ic);
			st.size++;			
			continue;
		}else if(!strcmp(source.mnemonic, "LTORG")||!strcmp(source.mnemonic, "END")){
			FILE* Lit,*PT;
			if(lt.start == 0){
				Lit = fopen("LT.txt","w");
				PT = fopen("PT.txt","w");
			}else{
			Lit = fopen("LT.txt","a");
			PT = fopen("PT.txt","a");
			}
			fprintf(ic,"*\t(AD,%s)\t\t*\n",info.code);
			for(i=0;i<lt.size;i++){
				if(i==0){
					fprintf(PT,"%d #%02d\n",pool,lt.start+1);
					pool++;
				}
				fprintf(ic,"%d\t*\t*\t(L,%02d)\n",location_counter,lt.literal[i].index);
				lt.literal[i].address = location_counter;
				fprintf(Lit,"%d\t%s\t%d\n",lt.start+lt.literal[i].index,lt.literal[i].literal,lt.literal[i].address);
				location_counter++;
			}
			fclose(Lit);
			fclose(PT);
			lt.start = lt.size;
			lt.size = 0;
			continue;
		}
		// location counter manipulation
		if(!strcmp(info.type,"AD")){
			location = -1;
		}
		else if(!strcmp(source.mnemonic,"DS")){
			location = location_counter;
			location_counter += atoi(source.op2);
		}
		else{
			location = location_counter;
			location_counter++;
		}
		fprintf(ic,"%d\t", location);
		//mnemonic
		
		fprintf(ic,"(%s,%s)\t",info.type,info.code);
		//operand 1
		op1info = search(source.op1);
		if(!strcmp(source.op1,"**")){
			fprintf(ic,"**\t");
		}
		else if(op1info.id != 0){
			strcpy(type1,op1info.type);
			strcpy(code1,op1info.code);
			fprintf(ic,"(%s,%s)\t", op1info.type,op1info.code);
		}
		else{
			strcpy(type1,"C");
			strcpy(code1,source.op1);
			fprintf(ic,"(C,%s)\t",source.op1);
			
		}
		//operand 2
		if(isInteger(source.op2)){
			fprintf(ic,"(C,%s)\n",source.op2);
		}
		else if(!strcmp(source.op2,"**")){
			fprintf(ic,"**\n");
		}else if(source.op2[0] == '='){
			int flag=0;
			for(i=0;i<lt.size;i++){
			if(!strcmp(lt.literal[i].literal,source.op2)){
				flag = 1;
				lc = i;
				break;
			}
			}
			if(!flag){
			strcpy(lt.literal[lt.size].literal,source.op2);
			lt.literal[lt.size].index = lt.size+1;
			fprintf(ic,"(L,%02d)\n", lt.size+1);
			lt.size++;
			}else{
				fprintf(ic,"(L,%02d)\n",lc+1);
			}
		}else if(isInteger(source.op2)){
			fprintf(ic,"(C,%s)", source.op2);
		}else{
			if(strcmp(info.type,"AD")){
			int flag = 0;
			for(i=0;i<st.size;i++){
				if(!strcmp(st.symbol[i].symbol,source.op2)){
					flag = 1;
					sc = i;
					break;
				}
			}
			if(!flag){
				strcpy(st.symbol[st.size].symbol,source.op2);
				
				st.symbol[st.size].index = st.size + 1;
				fprintf(ic,"(S,%02d)\n",st.size+1);
				st.size++;
			}else{
			fprintf(ic,"(S,%02d)\n",sc+1);
			}
		}else{
			fprintf(ic,"%d\n",eval(source.op2,st,&ic));
		}
}
}
FILE *SYT;
SYT = fopen("ST.txt","w");
	for(i=0;i<st.size;i++){
		fprintf(SYT,"%d\t%s\t%d\n",st.symbol[i].index,st.symbol[i].symbol, st.symbol[i].address);
	}
	fclose(src);
	fclose(ic);
	return 0;
}