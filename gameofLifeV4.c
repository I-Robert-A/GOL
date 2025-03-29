#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct list list;

struct list
{
    int l,c;
    list* next;
};

void push(list** top, int li, int co)
{
    list *elem;
    elem=(list*)malloc(sizeof(list));
    if (elem == NULL) {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    elem->next=(*top);
    (*top)=elem;
    elem->l=li;
    elem->c=co;
}

int pop(list **top, int *a, int *b)
{
    if((*top)==NULL)
    {
        return -1;
    }
    list* elem;
    elem=(*top);
    *(top)=(*top)->next;
    (*a)=elem->l;
    (*b)=elem->c;
    free(elem);
    return 0;
}
/*
void eliberare(list **top)
{
    list* elem;
    while((*top)!=NULL)
    {
        elem=(*top);
        (*top)=(*top)->next;
        free(elem);
    }
}
*/
void citire(FILE *fisier, char **ma, int n, int m)
{

    int i,j;
    for(i=0;i<n;i++)
        {
            getc(fisier);
            for(j=0;j<m;j++)
            {
            ma[i][j]=getc(fisier);
            }
            
        }
}
void afisare(char **ma, int n, int m, FILE* fisier)
{
    int i;
    for(i=0;i<n;i++)
    {
        
        fputs(ma[i],fisier);
        putc('\n',fisier);
    }
    putc('\n',fisier);

}

void FOP(FILE **fisier, const char *nume, const char var[3])
{
    printf("%s%s", nume, var);
    printf("sd");
    puts(nume);
    puts(var);
        if ((*fisier=fopen(nume, var))==NULL)
        {
            printf("Fisier %s nu a putut fi deschis", nume);
            exit(1);
        }
}

int verificareVec(FILE *fisier, char **ma, int i, int j, int n, int m)
{
    int k=0;
    if(((i-1)>=0) && ((j-1)>=0))
    {
        if(ma[i-1][j-1]=='X')
        k++;
    }
     if(i-1>=0)
    {
        if(ma[i-1][j]=='X')
        k++;
    }
    if(i-1>=0 && j+1<m)
    {
        if(ma[i-1][j+1]=='X')
        k++;
    }
    if(j-1>=0)
    {
        if(ma[i][j-1]=='X')
        k++;
    }
    if(j+1<m)
    {
        if(ma[i][j+1]=='X')
        k++;
    }
    if(i+1<n && j-1>=0)
    {
        if(ma[i+1][j-1]=='X')
        k++;
    }
    if(i+1<n)
    {
        if(ma[i+1][j]=='X')
        k++;
    }
    if(i+1<n && j+1<m)
    {
        if(ma[i+1][j+1]=='X')
        k++;
    }
    
            return k;
}
void reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p)
{
    int i,j,ko,l,c,r=0;
    char lista[256];
    list* top=NULL;
    //FILE *test;
    //FOP(&test,"mOUT","wt");
    while(k!=0)
    {    
        r++;
        //kk=0;
        if(p==2)
        {
            sprintf(lista, "%d", r);
            fputs(lista,mOUT);
            //putc(' ',mOUT);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                //car='0';
                ko=verificareVec(fisier,ma,i,j,n,m);
                if((ma[i][j]=='X' && (ko<2 || ko>3)) || (ma[i][j]=='+' && ko==3))
                {
                    push(&top,i,j);
                    if(p==2)
                    {
                    putc(' ',mOUT);
                    sprintf(lista, "%d", i);
                    fputs(lista,mOUT);
                    putc(' ',mOUT);
                    sprintf(lista, "%d", j);
                    fputs(lista,mOUT);
                    }
                } 
                //car=car+ko;
                //putc(car,test);
            }
        }
        while(top!=NULL)
        {
            pop(&top,&l,&c);
           if(ma[l][c]=='X')
            {
                ma[l][c]='+';
            }
                else
            {
                ma[l][c]='X';
            }
            /*if(p==2)
            {   
                for(i=kk-1;i>=0;i--)
                {
                    v[i+1]=v[i];
                }
                v[0]=c;
                kk++;
                for(i=kk-1;i>=0;i--)
                {
                    v[i+1]=v[i];
                }
                v[0]=l;
                kk++;
            }*/
        }
       // putc('\n',test);
       if(p==1)
        {afisare(ma,n,m,mOUT);}
        else if(p==2)
        {   /*for(i=0;i<kk;i++)
            {sprintf(lista, "%d", v[i]);
            fputs(lista,mOUT);
            putc(' ',mOUT);
            }*/
            fputs("\n", mOUT);
            //strcpy(lista,"");
        }
        k--;
    }
}


int main(int argc, char* argv[])
{
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
FILE* mINT,* mOUT;
char** ma;

int n,m,k,p; 
FOP(&mINT,argv[1],"rt"); 
fscanf(mINT, "%d %d %d %d", &p,&n, &m, &k);
    ma=(char**)calloc(n,sizeof(char*));
    int i;
    for(i=0;i<n;i++)
    {
        ma[i]=(char*)calloc(m,sizeof(char));
    }
    citire(mINT,ma,n,m);
    FOP(&mOUT,argv[2],"wt"); 
    if(p==1)
    {afisare(ma,n,m,mOUT);}
    reguli(mINT,ma,n,m,k,mOUT,p);
    for(i=0;i<n;i++)
    {
        free(ma[i]);
    }
    free(ma);
fclose(mINT);
fclose(mOUT);
    return 0;
}
