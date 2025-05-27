#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct list list;

struct list
{
    int l,c;
    list* next;
};
typedef struct stiva stiva;
struct stiva
{
    list* Lista;
    stiva* next;
};
struct N {
 list* lista;
struct N * left ,* right ;
};
typedef struct N Node ;

typedef struct {
    int V, E;
    int **a;
} Graph;

void pushL(stiva **top, list *elemL);
list* copiazaLista(list* original);
void afisareS(stiva **topS, FILE* mOUT, int q);
list* popL(stiva** top);
void addAtBeginning (list ** head , int l, int c );
int pop(list **top, int *a, int *b);
void citire(FILE *fisier, char **ma, int n, int m);
void afisare(char **ma, int n, int m, FILE* fisier);
void FOP(FILE **fisier, const char *nume, const char var[3]);
int verificareVec(FILE *fisier, char **ma, int i, int j, int n, int m);
list *reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p);
void task2(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, stiva** topS, int *q);
void eliberareStivaComplet(stiva *top);
void initTree(Node **root);
void postorder(Node **root);
Node * CreateA(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, int *r, int *r1);
void taskuri(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p);
void elibereazaLista(list *top);
void DFS(Graph *g, int *visited, int i, int k, list **top, list **maxList,int *max, int remaining,int *comp_conex, bool *inComp);
void DFS_scan(Graph *g, int visited[], int i, int **comp_conex, int y, int *ko);
void task4(Node *root, char **ma, int n, int m, FILE* mOUT);
void bonus(stiva **topS, char **ma, int n, int m);