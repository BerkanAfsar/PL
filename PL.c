#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *keywords[]={"int","add","sub","to","from","move","out","loop","times"};
char paranthesis[]={'(',')','{','}','[',']'};
char delemeters[]={',','.'};
int isParanthes(char x);
int isKeyword(char *x);


int main()
{
    FILE *codetext;
    int gecici,t;
    char *filename;
    filename=malloc(filename);
    printf("Enter file name\n");
    scanf("%s",filename);
    char asilfile[40];

    for(t=0;t<strlen(filename);t++)
    {
        asilfile[t]=filename[t];
    }
    t=strlen(filename);
    asilfile[t]='.';
    asilfile[t+1]='b';
    asilfile[t+2]='a';
    asilfile[t+3]='\0';


    filename=asilfile;

    char alinankarakter;
    char *str;
    char literals[100][100],constants[100][10],word[100][100];
    int i=0,j=0,k=0,l=0,a=0,b=0,literalcount=0,constantcount=0,delemetercount=0,paranthescount=0,keywordcount=0,identifiercount=0,noktasayisi=1;
        if((codetext=fopen(filename,"r"))==NULL)
    {
        printf("file not found\n");
    }
    else{
        do{
            alinankarakter=fgetc(codetext);

            if(alinankarakter=='"')
            {
                j=0;
                do
                {
                 alinankarakter=fgetc(codetext);
                 if(alinankarakter!='"')
                 {
                     literals[i][j]=alinankarakter;
                    printf("%c",alinankarakter);
                    j++;
                 }
                }while(alinankarakter!='"');
                printf("<- is literal\n");
                literals[i][j]='/0';

                i++;
                literalcount++;
            }
            else{
                if(isdigit(alinankarakter)||alinankarakter=='+'||alinankarakter=='-')
                {
                    l=0;
                    do
                    {
                        constants[k][l]=alinankarakter;
                        printf("%c",alinankarakter);
                        alinankarakter=fgetc(codetext);
                        if(l>100)
                        {
                            printf("     int can not be over 100 digits:%d .line\n",noktasayisi);
                            break;
                        }
                        l++;
                    }while(isdigit(alinankarakter));
                    printf(" <- is constant\n");
                    constantcount++;
                    k++;

                    if(alinankarakter=='+'||alinankarakter=='-')
                    {
                        printf("     faulty char:%c %d. line\n",alinankarakter,noktasayisi);
                        break;
                    }
                }
                else
                {
                   if(alinankarakter==','||alinankarakter=='.')
                   {
                       delemetercount++;
                       printf("%c <- delemeter\n",alinankarakter);
                   }
                   else
                   {
                       if(isParanthes(alinankarakter))
                       {
                           printf("%c <- is paranthes\n",alinankarakter);
                           paranthescount++;
                       }
                       else
                       {
                           if(isalpha(alinankarakter))
                           {
                                b=0;
                               do
                               {
                                 word[a][b]=alinankarakter;
                                 b++;
                                 printf("%c",alinankarakter);
                                 alinankarakter=fgetc(codetext);
                                 if(b>20)
                                 {
                                     printf("      variable can not be over 20 char:%d. line\n",noktasayisi);
                                     return 0;
                                 }
                               }while(isalpha(alinankarakter)||isdigit(alinankarakter));
                                str=(char *)malloc(40);
                                word[a][b]='\0';
                               str=&word[a];

                               a++;


                               if(isKeyword(str))
                               {
                                   printf(" <- is keyword \n");
                                   keywordcount++;
                               }
                               else
                               {
                                   printf(" <- is identifier \n");
                                   identifiercount++;
                               }
                               free(str);
                               if(alinankarakter==','||alinankarakter=='.')
                                {
                                    delemetercount++;
                                    if(alinankarakter=='.')
                                    {
                                        noktasayisi++;
                                    }
                                    printf("%c <- delemeter\n",alinankarakter);
                                }
                                if(alinankarakter=='"')
                                {
                                    j=0;
                                    do
                                    {
                                     alinankarakter=fgetc(codetext);
                                     literals[i][j]=alinankarakter;
                                     printf("%c",alinankarakter);
                                     j++;
                                    }while(alinankarakter=='"');
                                    printf("<- is literal\n");
                                    literals[i][j]='/0';

                                    i++;
                                    literalcount++;
                                }
                                if(isParanthes(alinankarakter))
                                    {
                                        printf("%c <- is paranthes\n",alinankarakter);
                                        paranthescount++;
                                    }

                           }
                           else
                           {
                               if(alinankarakter==' '||alinankarakter=='\0'||alinankarakter=='\n')
                               {

                               }

                               else{
                                    if(!feof(codetext)){
                                printf("    unknown char: %d.line\n",noktasayisi);
                                break;
                                    }
                                    else
                                    {

                                    }
                               }

                           }

                       }
                   }
                }
            }
        }while(!feof(codetext));
        printf("literal count:%d\n",literalcount);
        printf("constant count:%d\n",constantcount);
        printf("delemeter count:%d\n",delemetercount);
        printf("paranthes count:%d\n",paranthescount);
        printf("keyword count:%d\n",keywordcount);
        printf("identifier count:%d\n",identifiercount);

    }
    fclose(codetext);
    return 0;
}

int isParanthes(char x)
{
    int o;
    for(o=0;o<6;o++)
    {
        if(paranthesis[o]==x)
        {return 1;}
    }
    return 0;
}

int isKeyword(char *x)
{

    int o=0;
    for(o=0;o<9;o++)
    {
     if(strcmp(keywords[o],x)==0)
     {

         return 1;
     }

    }
    return 0;

}

