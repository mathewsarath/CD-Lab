# include <stdio.h>
# include <stdlib.h>
#include<ctype.h>
# include <string.h>
# define BUFF_SIZE 1024
# define LEX_SIZE 20
//key word tokens
enum tok_key{
    AUTO,
    ELSE,
    LONG,
    SWITCH,
    BREAK,
    ENUM,
    REGISTER,
    TYPEDEF,
    CASE,
    EXTERN,
    RETURN,
    UNION,
    CHAR,
    FLOAT,
    SHORT,
    UNSIGNED,
    CONST,
    FOR,
    SIGNED,
    VOID,
    CONTINUE,
    GOTO,
    SIZEOF,
    VOLATILE,
    DEFAULT,
    IF,
    STATIC,
    WHILE,
    DO,
    INT,
    STRUCT,
    PACKED,
    DOUBLE,
    TRUE,
    FALSE,
};

//tokens for comparison operators
enum tok_assign{
    EQ,
    NEQ,
    LT,
    GT,
    LTE,
    GTE
};

//tokens for arithmatic opereations
enum tok_arith{
    ADD,
    SUB,
    MULT,
    DIV,
    MOD
};

//tokens for special symbols
enum tok_special{
    SEMICOLON,
    COLON,
    COMMA,
    L_PAREN,
    R_PAREN,
    L_SQ_BCKT,//left square bracket
    R_SQ,BCKT,
};

//symbol table
// struct sym_data
// {
    
// };
int lex_analyser(char* str);
int get_lexeme(char lex[][10],char* str);
int get_token(char* lexeme);

void main(){
    FILE *infile;
    char buffer[BUFF_SIZE];
    //open file
    if((infile = fopen("input2.c","r"))== NULL){
        printf("Error opening file");

        exit(1);
    }
    while((fgets(buffer,BUFF_SIZE,infile)) != NULL){
        lex_analyser(buffer);
    }
    
    fclose(infile);
}

int lex_analyser(char *str){
    printf("\n--------------------------------------------------------\n%s",str);
    char lexeme[LEX_SIZE][10];
    int count=get_lexeme(lexeme,str);
    printf("\nlexeme count=%d",count+1);
    for(int i=0;i<=count;i++)
        printf("\n%s",lexeme[i]);
    return 0;
}

int get_lexeme(char lex[][10],char* str){
    int beg=0,end=0,lex_count=-1,len=strlen(str);
    //printf("\nlen: %d",len);
    while(beg <=len && end<=len && str[end]!='\n' && str[end]!='\0'){
        //printf("\nbeg: %c , end: %c",str[beg],str[end]);
       
       
       if(str[beg]==' '){
           beg++;
           end=beg;
           continue;
       }
       
        if(str[end]==' '){
           // printf("\n end is whitespace");
            int i=0;
            lex_count++;
            for(i=0;beg+i<=end;i++)
                lex[lex_count][i]=str[beg+i];
            lex[lex_count][i]='\0';
            beg=++end;
            continue;
        }


        //identifier
        if(isalpha(str[beg]) || str[beg]=='_'){
            
            if(isalnum(str[end]) || str[end]=='_')
                {
                    //printf(" --identifier");
                    end++;
                    continue;
                }
            else{
                lex_count++;
                int i=0;
                for(i=0;beg+i<end;i++)
                    lex[lex_count][i]=str[beg+i];
                lex[lex_count][i]='\0';
                //printf("\nlexeme is: %s",lex[lex_count]);
                beg=end;
                 //printf("\nafter identifier beg: %c , end: %c",str[beg],str[end]);
                continue;
            }
        }

        //numeric values

         if(isdigit(str[beg])){
            
            if(isdigit(str[end]) || str[end]=='.')
                {
                    //printf(" --number");
                    end++;
                    continue;
                }
            else{
                lex_count++;
                int i=0;
                for(i=0;beg+i<end;i++)
                    lex[lex_count][i]=str[beg+i];
                lex[lex_count][i]='\0';
                //printf("\nlexeme is: %s",lex[lex_count]);
                beg=end;
                 //printf("\nafter identifier beg: %c , end: %c",str[beg],str[end]);
                continue;
            }
        }

        int counter;
        switch (str[beg]){
            //operators
            case '+': 
                       lex_count++;
                        lex[lex_count][0]=str[beg];
                         if(str[beg+1]==str[beg]){
                             lex[lex_count][1]=str[beg+1];
                             lex[lex_count][2]='\0';
                             beg+=2;
                             end++;
                             break;
                         }
                         beg++;
                        lex[lex_count][1]='\0';
                        break;
            case '-':
                       lex_count++;
                        lex[lex_count][0]=str[beg];
                         if(str[beg+1]==str[beg]){
                             lex[lex_count][1]=str[beg+1];
                             lex[lex_count][2]='\0';
                             beg+=2;
                             end++;
                             break;
                         }
                         beg++;
                        lex[lex_count][1]='\0';
                        break;
            case '*':
            case '/':
                        if(str[beg]=='/' && str[beg+1]=='/'){
                            return lex_count;
                        }
            case '%':

                        lex_count++;
                        lex[lex_count][0]=str[beg];
                         if(str[beg+1]=='='){
                             lex[lex_count][1]=str[beg+1];
                             lex[lex_count][2]='\0';
                             break;
                         }
                        lex[lex_count][1]='\0';
                        beg++;
                        break;

            //comparitive operators

            case '<':
                        if( str[beg+1]=='>'){
                            lex_count++;
                            lex[lex_count][0]=str[beg];
                            lex[lex_count][1]=str[beg+1];
                            lex[lex_count][2]='\0';
                            beg=++end;
                            break;
                        }

            case '>':

            case '!':

            //assignment operator
                        
            case '=':
                        lex_count++;
                        lex[lex_count][0]=str[beg];
                         if(str[beg+1]=='='){
                             lex[lex_count][1]=str[beg+1];
                             lex[lex_count][2]='\0';
                             beg+=2;
                             break;
                         }
                         // printf("\n< here:");
                        beg++;
                        lex[lex_count][1]='\0';
                        break;

            //logical operators

            case '&':

            case '|':
                        lex_count++;
                        lex[lex_count][0]=str[beg];
                         if(str[beg+1]==str[beg]){
                             lex[lex_count][1]=str[beg+1];
                             lex[lex_count][2]='\0';
                             beg+=2;
                             break;
                         }
                         beg++;
                        lex[lex_count][1]='\0';
                        break;


            case '\"':
                            //printf("\nreading string");
                            counter=1;
                            lex_count++;
                            lex[lex_count][0]='\"';
                            while(str[beg+counter]!='\"'){
                                lex[lex_count][counter]=str[beg+counter];
                                counter++;
                            }
                            lex[lex_count][counter++]='\"';
                            lex[lex_count][counter]='\0';
                            beg+=counter;
                            end=beg-1;
                            break;

                        
        default:
            //printf("\n inside default");
            lex_count++;
            lex[lex_count][0]=str[beg];
            lex[lex_count][1]='\0';
            beg=end+1;
            break;
        }
        //printf("\n line readin: beg= %d , end = %d lexeme: %s",beg,end,lex[lex_count]);
        end++;
    }
    //printf("\nat end :%d",end);
    return lex_count;
}
