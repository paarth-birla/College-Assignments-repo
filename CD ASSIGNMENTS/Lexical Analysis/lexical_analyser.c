#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

typedef struct Terminal_table
{
    int index;	
    char symbol[10];
    char indicator;		
}terminal_table;

typedef struct	Identifier_table
{
    int index;
    char name[10];
}identifier_table;

typedef struct Literal_table
{	
    int sr_no;
    int name;
    int precision;	
    char base[10];
    char scale[10];		
}literal_table;

typedef struct Uniform_symbol_table
{	
    int sr_no;
    int index;	
    char name[10];
    char symbol_class[10];
}uniform_symbol_table;

void main()
{
	FILE *program_file,*terminal_file,*literal_file,*ust_file,*indentifier_file,*indentifier_temp_file,*literal_temp_file;

	terminal_table terminal;	
    identifier_table identifier,identifier_temp;
	literal_table literal,literal_temp;	
    uniform_symbol_table ust;

	int i=0, flag, flag_identifier, flag_literal, temp;		
    char ch,buffer[10];

	program_file=fopen("program.txt","r");
	ust_file=fopen("uniform_symbol_table.txt","w");
	indentifier_file=fopen("identifier_table.txt","w");
	literal_file=fopen("literal_table.txt","w");

	ust.sr_no=1;	
    identifier.index=1;	
    literal.sr_no=1;

	for(i=0;i<10;i++)
		buffer[i]='\0';
	i=0;
	while(!feof(program_file))
	{
		ch=fgetc(program_file);
		if(isalpha(ch) || isdigit(ch))
			buffer[i++]=ch;
	
		else if(ch!='"')
		{
			flag=0;
			terminal_file=fopen("terminal_table.txt","r");
			while(!feof(terminal_file))
			{
				fscanf(terminal_file,"%d %s %c\n",&terminal.index,&terminal.symbol,&terminal.indicator);
				if(strcmp(terminal.symbol,buffer)==0)
				{
					flag=1;
					strcpy(ust.name,buffer);	
                    ust.index=terminal.index;
					if(terminal.indicator=='Y')
						strcpy(ust.symbol_class,"TRM");
					else	
                        strcpy(ust.symbol_class,"KEY");
					fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,ust.index);
					break;
				}
			}
			fclose(terminal_file);
			if(flag==0)
			{
				if(isalpha(buffer[0]))
				{
					flag_identifier=0;	
                    fclose(indentifier_file);
					indentifier_temp_file=fopen("identifier_table.txt","r");
					while(!feof(indentifier_temp_file))
					{
						fscanf(indentifier_temp_file,"%d %s\n",&identifier_temp.index,identifier_temp.name);
						if(strcmp(identifier_temp.name,buffer)==0)
						{
							flag_identifier=1;	break;
						}
					}
					fclose(indentifier_temp_file);		
                    strcpy(ust.name,buffer);
					ust.index=terminal.index;	
                    strcpy(ust.symbol_class,"IDN");
					if(flag_identifier==1)
						fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,identifier_temp.index);
					if(flag_identifier==0)
					{
						indentifier_file=fopen("identifier_table.txt","a");
						strcpy(identifier.name,buffer);
						fprintf(indentifier_file,"%d \t%s\n",identifier.index++,identifier.name);
						fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,identifier.index-1);
						fclose(indentifier_file);
					}
				}
				else if(isdigit(buffer[0]))
				{
					flag_literal=0;
					fclose(literal_file);
					literal_file=fopen("literal_table.txt","r");
					while(!feof(literal_file))
					{
						fscanf(literal_file,"%d %d %s %s %s\n",&literal_temp.sr_no,&literal_temp.name,&literal_temp.precision,&literal_temp.base,&literal_temp.scale);
						temp = atoi(buffer);
						if(literal_temp.name==temp)
						{
							flag_literal=1;	break;
						}
					}
					fclose(literal_file);
					strcpy(ust.name,buffer);
					ust.index=terminal.index;
					strcpy(ust.symbol_class,"LIT");
					if(flag_literal==1)
						fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,literal_temp.sr_no);
					if(flag_literal==0)
					{
						fclose(literal_file);
						literal_file=fopen("literal_table.txt","a");
						literal.name=atoi(buffer);
						literal.precision=2;	
                        strcpy(literal.base,"DECIMAL");
						strcpy(literal.scale,"FIXED");
						strcpy(ust.name,buffer);
						fprintf(literal_file,"%d \t%d \t%d \t%s \t%s\n",literal.sr_no++,literal.name,literal.precision,literal.base,literal.scale);
						fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,literal.sr_no - 1);
						fclose(literal_file);
					}
				}
			}
			for(i=0;i<10;i++)
				buffer[i]='\0';
			buffer[0]=ch;
			terminal_file=fopen("terminal_table.txt","r");
			while(!feof(terminal_file))
			{
				fscanf(terminal_file,"%d %s %c\n",&terminal.index,&terminal.symbol,&terminal.indicator);
				if(strcmp(terminal.symbol,buffer)==0)
				{
					strcpy(ust.name,buffer);
					ust.index=terminal.index;
					strcpy(ust.symbol_class,"TRM");
					fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,ust.index);
					break;
				}
			}
			for(i=0;i<10;i++)		
                buffer[i]='\0';
			fclose(terminal_file);
			i=0;
		}
		else if(ch=='"')
		{
			buffer[0]=ch;
			terminal_file=fopen("terminal_table.txt","r");
			while(!feof(terminal_file))
			{
				fscanf(terminal_file,"%d %s %c\n",&terminal.index,&terminal.symbol,&terminal.indicator);
				if(strcmp(terminal.symbol,buffer)==0)
				{
					strcpy(ust.name,buffer);
					ust.index=terminal.index;
					if(terminal.indicator=='Y')
						strcpy(ust.symbol_class,"TRM");
					else
						strcpy(ust.symbol_class,"KEY");
					fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,ust.index);
					break;
				}
			}
			fclose(terminal_file);		
            ch=fgetc(program_file);
			while(ch!='"')
			{
				ch=fgetc(program_file);
			}
			strcpy(ust.name,buffer);	
            ust.index=terminal.index;
			if(terminal.indicator=='Y')
				strcpy(ust.symbol_class,"TRM");
			else	
                strcpy(ust.symbol_class,"KEY");
			fprintf(ust_file,"%d  %s  %s  %d \n",ust.sr_no++,ust.name,ust.symbol_class,ust.index);
			ch=fgetc(program_file);
		}
    }
    fclose(program_file);	
    fclose(ust_file);		
    fclose(indentifier_file);		
    fclose(literal_file);
}
	
