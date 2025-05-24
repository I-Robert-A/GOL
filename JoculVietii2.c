#include "JoculVietii.h"

int main(int argc, char* argv[])
{
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
FILE* mINT,* mOUT;
char** ma;
stiva* topS=NULL;
list *elem=NULL;
int q=0;
int n,m,k,p; 
FOP(&mINT,argv[1],"rt"); 
fscanf(mINT, "%d %d %d %d", &p,&n, &m, &k);
    ma=(char**)calloc(n,sizeof(char*));
    int i;
    for(i=0;i<n;i++)
    {
        ma[i]=(char*)calloc(m+1,sizeof(char));
    }
    citire(mINT,ma,n,m);
    FOP(&mOUT,argv[2],"wt"); 
    if(p==1)
    {afisare(ma,n,m,mOUT);
    reguli(mINT,ma,n,m,k,mOUT,p,&topS,&q);}
    if(p==2)
    {   task2(mINT,ma,n,m,k,mOUT,p,&topS,&q);
        afisareS(&topS,mOUT,q);
        }
    for(i=0;i<n;i++)
    {
        free(ma[i]);
    }
    free(ma);
fclose(mINT);
fclose(mOUT);
eliberareStivaComplet(topS);
    return 0;
}
