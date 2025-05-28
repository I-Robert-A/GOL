#include "JoculVietii.h"

int main(int argc, char* argv[])
{
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
FILE* mINT,* mOUT;
char** ma;
stiva* topS=NULL;
//const list *elem;
int q=0;
int n,m,k,p,r=0,r1=0; 
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
        {
            //printf("qqqq");
            afisare(ma,n,m,mOUT);
            taskuri(mINT,ma,n,m,k,mOUT,p);
        }
        //printf("dddd");
        if(p==3 || p==4)
        {Node *root = NULL;
            printf("cv");
        // initTree(&root);
        root = CreateA(mINT, ma, n, m, k, mOUT, p, &r, &r1);
        if(p==4)
        {
            //task4(root,ma,n,m,mOUT);
        }
        postorder(&root);
    }
    if(p==2)
    {   task2(mINT,ma,n,m,k,mOUT,p,&topS,&q);
        //merge dar dureaza mult!!
        afisareS(&topS, mOUT, q);
    eliberareStivaComplet(topS);
        }
        if(p==10)
        {
            bonus(&topS,ma,n,m);
        }
    for(i=0;i<n;i++)
    {
        free(ma[i]);
    }
    free(ma);
fclose(mINT);
fclose(mOUT);
//eliberareStivaComplet(topS);
    return 0;
}
