#include "JoculVietii.h"
void push(list **top, int li, int co)
{
    list *elem;
    elem = (list *)malloc(sizeof(list));
    if (elem == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    elem->next = (*top);
    (*top) = elem;
    elem->l = li;
    elem->c = co;
}

void pushL(stiva **top, list *elemL)
{
    stiva *elem;
    elem = (stiva *)malloc(sizeof(stiva));
    if (elem == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    elem->next = (*top);
    (*top) = elem;
    elem->Lista = elemL;
}

list *popL(stiva **top)
{
    list *val;
    if ((*top) == NULL)
    {
        return NULL;
    }
    stiva *elem;
    elem = (*top);
    *(top) = (*top)->next;
    val = elem->Lista;
    free(elem);
    return val;
}

void addAtBeginning(list **head, int l, int c)
{
    list *newNode = (list *)malloc(sizeof(list));
    if (!newNode)
    {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    newNode->l = l;
    newNode->c = c;
    newNode->next = *head;
    (*head) = newNode;
}

void eliberareStivaComplet(stiva *top)
{
    stiva *topS;
    while (top != NULL)
    {
        list *elem;
        while (top->Lista != NULL)
        {
            elem = top->Lista;
            top->Lista = top->Lista->next;
            free(elem);
        }
        topS = top;
        top = top->next;
        free(topS);
    }
}

void addAtEnd(list **head, int l, int c)
{
    if (*head == NULL)
    {
        addAtBeginning(head, l, c);
        return;
    }
    else
    {
        list *aux = *head;
        while (aux->next != NULL)
            aux = aux->next;

        list *newNode = (list *)calloc(1, sizeof(list));
        newNode->next=NULL;
        if (!newNode)
        {
            printf("Eroare la alocarea memoriei\n");
            exit(1);
        }
        newNode->l = l;
        newNode->c = c;
        newNode->next = NULL;
        aux->next = newNode;
    }
}

void citire(FILE *fisier, char **ma, int n, int m)
{

    int i, j;
    for (i = 0; i < n; i++)
    {
        getc(fisier);
        for (j = 0; j < m; j++)
        {
            ma[i][j] = getc(fisier);
        }
        ma[i][m] = '\0';
    }
}
void afisare(char **ma, int n, int m, FILE *fisier)
{
    int i;
    for (i = 0; i < n; i++)
    {

        fputs(ma[i], fisier);
        putc('\n', fisier);
    }
    putc('\n', fisier);
}

void FOP(FILE **fisier, const char *nume, const char var[3])
{
    printf("%s%s", nume, var);
    printf("sd");
    puts(nume);
    puts(var);
    if ((*fisier = fopen(nume, var)) == NULL)
    {
        printf("Fisier %s nu a putut fi deschis", nume);
        exit(1);
    }
}

int verificareVec(FILE *fisier, char **ma, int i, int j, int n, int m)
{
    int k = 0;
    if (((i - 1) >= 0) && ((j - 1) >= 0))
    {
        if (ma[i - 1][j - 1] == 'X')
            k++;
    }
    if (i - 1 >= 0)
    {
        if (ma[i - 1][j] == 'X')
            k++;
    }
    if (i - 1 >= 0 && j + 1 < m)
    {
        if (ma[i - 1][j + 1] == 'X')
            k++;
    }
    if (j - 1 >= 0)
    {
        if (ma[i][j - 1] == 'X')
            k++;
    }
    if (j + 1 < m)
    {
        if (ma[i][j + 1] == 'X')
            k++;
    }
    if (i + 1 < n && j - 1 >= 0)
    {
        if (ma[i + 1][j - 1] == 'X')
            k++;
    }
    if (i + 1 < n)
    {
        if (ma[i + 1][j] == 'X')
            k++;
    }
    if (i + 1 < n && j + 1 < m)
    {
        if (ma[i + 1][j + 1] == 'X')
            k++;
    }

    return k;
}

int verificareVec2(FILE *fisier, char **ma, int i, int j, int n, int m,stiva *topS)
{
    int k = 0,bi=0;
    list *elem;
    stiva* aux;
    if (((i - 1) >= 0) && ((j - 1) >= 0))
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i-1 && elem->c==j-1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i - 1][j - 1] == 'X' && bi%2==0) || (ma[i - 1][j - 1] == '+' && bi%2==1))
            k++;
    }
    if (i - 1 >= 0)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i-1 && elem->c==j)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i - 1][j] == 'X' && bi%2==0) || (ma[i-1][j]=='+' && bi%2==1))
            k++;
    }
    if (i - 1 >= 0 && j + 1 < m)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i-1 && elem->c==j+1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i - 1][j + 1] == 'X' && bi%2==0)||(ma[i - 1][j + 1] == '+' && bi%2==1))
            k++;
    }
    if (j - 1 >= 0)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i && elem->c==j-1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i][j - 1] == 'X' && bi%2==0) || (ma[i][j - 1] == '+' && bi%2==1))
            k++;
    }
    if (j + 1 < m)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i && elem->c==j+1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i][j + 1] == 'X' && bi%2==0) || (ma[i][j + 1] == '+' && bi%2==1))
            k++;
    }
    if (i + 1 < n && j - 1 >= 0)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i+1 && elem->c==j-1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i + 1][j - 1] == 'X' && bi%2==0) || (ma[i + 1][j - 1] == '+' && bi%2==1))
            k++;
    }
    if (i + 1 < n)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i+1 && elem->c==j)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i + 1][j] == 'X' && bi%2==0)||((ma[i + 1][j] == '+' && bi%2==1)))
            k++;
    }
    if (i + 1 < n && j + 1 < m)
    {
        aux=topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i+1 && elem->c==j+1)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }
        if ((ma[i + 1][j + 1] == 'X' && bi%2==0) || (ma[i + 1][j + 1] == '+' && bi%2==1))
            k++;
    }

    return k;
}

void reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, stiva **topS, int *q)
{
    int i, j, ko, l, c, r = 0;
    char lista[256];
    list *top = NULL, *elem = NULL;
    while (k != 0)
    { 
        top = NULL;
        r++;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                ko = verificareVec(fisier, ma, i, j, n, m);
                if ((ma[i][j] == 'X' && (ko < 2 || ko > 3)) || (ma[i][j] == '+' && ko == 3))
                {
                    addAtEnd(&top, i, j);
                }
            }
        }
        elem = top;
        (*q)++;
        //pushL(topS, top);
        while (elem != NULL)
        {
            l = elem->l;
            c = elem->c;
            if (ma[l][c] == 'X')
            {
                ma[l][c] = '+';
            }
            else
            {
                ma[l][c] = 'X';
            }
            elem = elem->next;
        }
        if (p == 1)
        {
            afisare(ma, n, m, mOUT);
        }
        k--;
    }
    free(top);
}

void task2(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, stiva **topS, int *q)
{
    int i, j, ko, l, c, r = 0,bi=0;
    char lista[256];
    list *top = NULL, *elem = NULL;
    stiva *aux;
    aux=*topS;
    char stare;
    while (k != 0)
    { 
        top = NULL;
        r++;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                aux=*topS;
                bi=0;
                while(aux!=NULL)
                {
                    elem=aux->Lista;
                    while(elem!=NULL)
                    {
                        if(elem->l==i && elem->c==j)
                        {
                            printf("lin:%d %d\n col:%d %d ",elem->l,i,elem->c,j);
                            bi++;
                        }
                        elem=elem->next;
                    }
                    aux=aux->next;
                }   
                printf("\nbi:%d",bi);
                
                ko = verificareVec2(fisier, ma, i, j, n, m,*topS);
                if(bi%2==0)
                {
                    stare=ma[i][j];
                }
                else
                {
                    if(ma[i][j]=='X')
                    {
                        stare='+';
                    }
                    else{stare='X';}
                }
                if ((stare=='X' && (ko < 2 || ko > 3)) || (stare == '+' && ko == 3))
                {
                    addAtEnd(&top, i, j);
                }
            }
        }
        (*q)++;
        pushL(topS, top);
        k--;
    }
    free(top);

}

void afisareS(stiva **topS, FILE *mOUT, int q)
{
    int i, j;
    char lista[256];
    list *elem, *aux;
    if ((*topS)->next)
    {
        afisareS(&(*topS)->next, mOUT, q - 1);
    }
    if (q > 0)
        fprintf(mOUT, "%d", q);
    elem = popL(topS);
    while (elem != NULL)
    {
        aux = elem;
        fprintf(mOUT, " %d %d", elem->l, elem->c);
        elem = elem->next;
        free(aux);
    }
    if (q > 0)
        fprintf(mOUT, "\n");
}

void bonus(stiva** topS, FILE *mOUT)
{
    
}
