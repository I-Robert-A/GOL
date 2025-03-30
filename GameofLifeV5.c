#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct list list;

struct list
{
    int l,c;
    list* next;
};
struct N {
 list* lista;
struct N * left ,* right ;
};
typedef struct N Node ;

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


void initTree(Node **root)
{
*root = (Node*)malloc(sizeof(Node));
(*root)->left = (*root)->right = NULL;
(*root)->lista=NULL;
}


int isEmpty (Node *root)
{
return (root==NULL); 
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


list *reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p)
{
    int i,j,ko,l,c,r=0;
    char lista[256];
    list* top=NULL;
    //top=(list*)malloc(sizeof(list));
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                //car='0';
                ko=verificareVec(fisier,ma,i,j,n,m);
                if(p!=3)
                {
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
                }
                else
                {
                    if(ma[i][j]=='+' && ko==2)
                    {
                        push(&top,i,j);
                    }
                } 
            }
        }
        return top;   
    }


Node * CreateA(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, int *r, int *r1)
{
int li,co,j;
char c ;
Node * root = ( Node *) malloc ( sizeof ( Node ));
list *top;
char **maT;
afisare(ma,n,m,mOUT);
maT=(char**)calloc(n,sizeof(char*));
    int i;
    //printf("ffff");

    for(i=0;i<n;i++)
    {
        maT[i]=(char*)calloc(m,sizeof(char));
    }
for(i=0;i<n;i++)
{
    for(j=0;j<m;j++)
    {
        maT[i][j]=ma[i][j];
    }
}
if((*r)+(*r1)==k)
{
    
    return root;
}
(*r)++;
printf("a:%d %d ", *r, *r1);

if((*r)<=k)
{
    root->lista=reguli(fisier,maT,n,m,k,mOUT,3);
    top=root->lista;
    //test=root->lista;
    //printf("sd");
    //printf("\n");
    //printf("%d %d\n", root->lista->l, root->lista->c);
    while(top!=NULL)
        {
            li=top->l;
            co=top->c;
            //printf("%d",l);
           if(maT[li][co]=='X')
            {
                maT[li][co]='+';
            }
                else
            {
                maT[li][co]='X';
            }
            top=top->next;
        }
    root -> left = CreateA(fisier,maT,n,m,k,mOUT,p,r,r1);
}
(*r1)++;
(*r)--;
printf("b:%d %d", *r, *r1);
root->lista=reguli(fisier,ma,n,m,k,mOUT,1);
top=root->lista;
while(top!=NULL)
        {
            li=top->l;
            co=top->c;
            //printf("%d",l);
           if(ma[li][co]=='X')
            {
                ma[li][co]='+';
            }
                else
            {
                ma[li][co]='X';
            }
            top=top->next;
        }
root->right= CreateA(fisier,ma,n,m,k,mOUT,p,r,r1);
(*r1)--;
}


void preorder ( Node * root, char** ma, int n, int m, FILE* mOUT) 
{list* top;
    int l,c;
    top=root->lista;
if ( root )
{
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
    }
    afisare(ma,n,m,mOUT);
    preorder ( root -> left,ma,n,m,mOUT);
    preorder ( root -> right,ma,n,m,mOUT);
}
}

void taskuri(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p)
{
    int i,j,ko,l,c,r=0;
    char lista[256];
    list* top=NULL;
    printf("ffff");
    while(k!=0)
    {    
        r++;
        if(p==2)
        {
            sprintf(lista, "%d", r);
            fputs(lista,mOUT);
        }
        top=reguli(fisier,ma,n,m,k,mOUT,p);
        //printf("%d %d\n",top->next->l,top->next->c);
        while(top!=NULL)
        {
            pop(&top,&l,&c);
            //printf("%d",l);
           if(ma[l][c]=='X')
            {
                ma[l][c]='+';
            }
                else
            {
                ma[l][c]='X';
            }
        }
       if(p==1)
        {afisare(ma,n,m,mOUT);}
        else if(p==2)
        {  
            fputs("\n", mOUT);
        }
        k--;
        free(top);
    }
}


int main(int argc, char* argv[])
{
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
FILE* mINT,* mOUT;
char** ma;
int n,m,k,p,r=0,r1=0; 
FOP(&mINT,argv[1],"rt"); 
fscanf(mINT, "%d %d %d %d", &p,&n, &m, &k);
    ma=(char**)calloc(n,sizeof(char*));
    int i;
    //printf("ffff");

    for(i=0;i<n;i++)
    {
        ma[i]=(char*)calloc(m,sizeof(char));
    }
    citire(mINT,ma,n,m);
    //printf("ffff");
    FOP(&mOUT,argv[2],"wt"); 
    //printf("ffff");
    if(p!=3)
    {
        if(p==1)
        {
            //printf("qqqq");
            afisare(ma,n,m,mOUT);
        }
        //printf("dddd");
        taskuri(mINT,ma,n,m,k,mOUT,p);
    }
    else
    {
        Node * root = CreateA(mINT,ma,n,m,k,mOUT,p,&r,&r1);
        //preorder(root,ma,n,m,mOUT);
    }
    for(i=0;i<n;i++)
    {
        free(ma[i]);
    }
    free(ma);
fclose(mINT);
fclose(mOUT);
    return 0;
}
