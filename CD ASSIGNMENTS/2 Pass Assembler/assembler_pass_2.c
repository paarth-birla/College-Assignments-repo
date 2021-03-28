#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

typedef struct MOT
{
    char type[10];
    int code;
}mot;

typedef struct Symbol_Table
{
    char symbol[10];
    int address;
    int length;
    int value;
    int index;
}symbol_table;

typedef struct Literal_table
{
    int address;
    int index;
    char literal[10];
}literal_table;

char* getLiteral(int index)
{
	FILE *st;
	static literal_table s;
	st = fopen("LT.txt","r");
	while(!feof(st))
    {
	    fscanf(st,"%d\t%s\t%d\n",&s.index,s.literal,&s.address);
	    if(index == s.index)
        {
		    return s.literal;
	    }
	}
}

void rmb(char *l){
	
	if(l[0]=='('){
		int i = 1;
		while(l[i]!='\0'){
			l[i-1] = l[i];
			i++;
		}
	if(l[strlen(l)-2]==')'){
		l[strlen(l)-2] = '\0';
	}
	}
}

int getAddress(mot t){
	if(!strcmp(t.type,"S"))
    {
		FILE *st;
		symbol_table s;
		st = fopen("ST.txt","r");
		while(!feof(st))
        {
		    fscanf(st,"%d\t%s\t%d\n",&s.index,s.symbol,&s.address);
		    if(t.code == s.index)
            {
			    return s.address;
		    }
	    }
	}

	else if(!strcmp(t.type,"L"))
    {
		FILE *st;
		literal_table s;
		st = fopen("LT.txt","r");
		while(!feof(st))
        {
		fscanf(st,"%d\t%s\t%d\n",&s.index,s.literal,&s.address);
		if(t.code == s.index){
			return s.address;
		}
	    }
	}
    else
    {
		return t.code;
	}
}

mot parsetuple(char *s)
{
	int i=0,j;
	while(s[i]!='\0'){
		if(s[i]==','){
			j = i;
		}
		i++;
	}
	mot tup;
	for(i=0;i<j;i++){
		tup.type[i] = s[i];
	}
	tup.type[j] = '\0';
	
	char num[10];
	i = j;
	while(*s!=','){
		s++;
	}
	s++;
	tup.code = atoi(s);
	
	return tup;
	
}

int main()
{
	FILE *ic,*t;
	mot mn,op1,op2;
	char l1[20],l2[20],l3[20],l4[20];
	ic = fopen("IC.txt","r");
	t = fopen("target.txt","w");
	while(!feof(ic))
    {
		fscanf(ic,"%s\t%s\t%s\t%s\n",l1,l2,l3,l4);
		if(strcmp(l1,"**"))
        {
			rmb(l4);
			rmb(l3);
			rmb(l2);
		//address
		    fprintf(t,"%s\t",l1);
		    if(strcmp(l2,"**"))
            {
			    mn = parsetuple(l2);
			    fprintf(t,"%02d\t",mn.code);
		    }
            else
            {
			    fprintf(t,"**\t");
		    }
		//op1
		    if(strcmp(l3,"**"))
            {
			    op1 = parsetuple(l3);
			    fprintf(t,"%02d\t",op1.code);
		    }
            else
            {
			    fprintf(t,"**\t");
		    }
		//op2
		    if(strcmp(l4,"**"))
            {
			    op2 = parsetuple(l4);
			    fprintf(t,"%02d\t",getAddress(op2));
		    }
		    else
            {
			    fprintf(t,"**\t");
		    }
		
		    fprintf(t,"\n");
		}
	}
	return 0;
}