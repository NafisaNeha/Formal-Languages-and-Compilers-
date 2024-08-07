#include<stdio.h>

int main()
{
    FILE *p1,*p2;
    char c;
    p1=fopen("Input.c","r");
    p2=fopen("output.txt","w");

    if(p1==NULL)
    {
        printf("File Can't be opened\n");
    }

    int Level=0;
    int space=0;


    while((c=fgetc(p1))!=EOF)
    {

    Level:
        if(c=='\n')
        {

            while((c=fgetc(p1))==' ');
            goto Level;
        }

        else if(c=='{')
        {

            fputc(c,p2);


            while((c=fgetc(p1))==' ');
            goto Level;
        }

        else if(c==' ')
        {
            space++;
            if(space>1)
            {
                continue;
            }
            else
            {
                fputc(c,p2);
            }
        }

        else if(c=='/')
        {
            c=fgetc(p1);

            if(c=='/')
            {

                while(c=fgetc(p1)!='\n');
            }

            else if(c=='*')
            {

                while(c=fgetc(p1)!='/');
            }
        }

        else
        {

            space=0;

            fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);
    p2=fopen("output.txt","r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(p2);
    return 0;
}

