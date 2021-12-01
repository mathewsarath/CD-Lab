%{
int count=0;
int line_count=0;
int id=0;
%}

%%
int|void|include|double|return|case|break|switch|continue|long|class|struct|enum|union|float|while|for|do|if|else {fprintf(yyout, "keyword\t\t|\t%s\n", yytext);count++;printf("keyword\t\t\t|\t%s\n", yytext);}


[a-zA-Z_][a-zA-Z0-9_$]* {fprintf(yyout, "identifier\t\t|\t%s>\n", yytext);count++;printf("identifier\t\t|\t%s\n",yytext);}

^[#][ ]?include|^[#][ ]?define {fprintf(yyout, "preprocessor directive\t|\t%s>\n", yytext);count++;printf("preprocessor directive\t|\t%s\n", yytext);}
[-+*/=%&\|] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[/][/].* {}
[+][+] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[-][-] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[+][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[*][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[-][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[/][=] {fprintf(yyout, "<operator,%s>\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}

[<>=!]={0,1} {fprintf(yyout, "operator\t\t|\t%s\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[&][&] {fprintf(yyout, "operator\t\t|\t%s\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}
[\|][\|] {fprintf(yyout, "operator\t\t|\t%s\n", yytext);count++;printf("operator\t\t|\t%s\n", yytext);}

["][0-9a-zA-Z]*.[a-zA-Z]*["]|["][0-9a-zA-Z% ]*["] {fprintf(yyout, "string\t\t|\t%s\n", yytext);count++;printf("string \t\t|\t%s\n", yytext);}

[^a-zA-Z_][^a-zA-Z0-9_]*[*] {fprintf(yyout, "<pointer,%s>\n", yytext);count++;printf("pointer\t\t|\t%s\n", yytext);}

[\t]+ {}
[\n]+ { line_count++;}
[0-9][0-9]*\.[0-9]+[1-9]+ {fprintf(yyout, "constant\t\t|\t%s\n", yytext);count++;printf("floating point : %s\n",yytext);}

[1-9][0-9]* {fprintf(yyout, "constant\t\t|\t%s\n", yytext);count++;printf( "constant\t\t|\t%s>\n",yytext);}



[(){}|,:<>;] {fprintf(yyout, "special symbol\t\t|\t%s\n", yytext);count++;printf("special symbol\t\t|\t%s\n",yytext);}

%%
int yywrap(){}
int main()
{
FILE *f1,*f2;
f1 = fopen("input.c","r");
f2 = fopen("output.txt","w+");
yyin = f1;
yyout=f2;
fprintf(f2,"token\t\t\t|\tlexeme\n");
printf("token\t\t\t|\tlexeme\n");
printf("---------------------------------------------------------------\n");
yylex();
printf("total no. of tokens = %d\n",count);
}

