#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list list;

struct list {
    int l, c;
    list* next;
};

struct N {
    list* lista;
    struct N *left, *right;
};

typedef struct N Node;

void push(list** top, int li, int co) {
    list *elem = (list*)malloc(sizeof(list));
    if (elem == NULL) {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    elem->l = li;
    elem->c = co;
    elem->next = *top;
    *top = elem;
}

int pop(list **top, int *a, int *b) {
    if (*top == NULL) {
        return -1;
    }
    list* elem = *top;
    *a = elem->l;
    *b = elem->c;
    *top = (*top)->next;
    free(elem);
    return 0;
}

/*void initTree(Node **root) {
    *root = (Node*)malloc(sizeof(Node));
    (*root)->left = (*root)->right = NULL;
    (*root)->lista = NULL;
}*/

void citire(FILE *fisier, char **ma, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        getc(fisier);
        for (j = 0; j < m; j++) {
            ma[i][j] = getc(fisier);
        }
    }
}

void afisare(char **ma, int n, int m, FILE* fisier) {
    for (int i = 0; i < n; i++) {
        fputs(ma[i], fisier);
        putc('\n', fisier);
    }
    putc('\n', fisier);
}

void FOP(FILE **fisier, const char *nume, const char var[3]) {
    if ((*fisier = fopen(nume, var)) == NULL) {
        printf("Fisier %s nu a putut fi deschis\n", nume);
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

list *reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p) {
    list* top = NULL;
    char lista[256];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ko = verificareVec(fisier, ma, i, j, n, m);
            if (p != 3) {
                if ((ma[i][j] == 'X' && (ko < 2 || ko > 3)) || (ma[i][j] == '+' && ko == 3)) {
                    push(&top, i, j);
                    if (p == 2) {
                        putc(' ', mOUT);
                        sprintf(lista, "%d", i);
                        fputs(lista, mOUT);
                        putc(' ', mOUT);
                        sprintf(lista, "%d", j);
                        fputs(lista, mOUT);
                    }
                }
            } else {
                if (ma[i][j] == '+' && ko == 2) {
                    push(&top, i, j);
                }
            }
        }
    }
    return top;
}

void elibereazaLista(list *top) {
    list *tmp;
    while (top != NULL) {
        tmp = top;
        top = top->next;
        free(tmp);
    }
}

Node* CreateA(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, int *r, int *r1) {
    Node *root = (Node*)malloc(sizeof(Node));
    root->left = root->right = NULL;
    root->lista = NULL;

    char **maT = (char**)calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++) {
        maT[i] = (char*)malloc(m * sizeof(char));
        memcpy(maT[i], ma[i], m);
    }

    afisare(ma, n, m, mOUT);

    if (*r + *r1 == k) {
        for (int i = 0; i < n; i++) free(maT[i]);
        free(maT);
        return root;
    }

    (*r)++;
    if (*r <= k) {
        root->lista = reguli(fisier, maT, n, m, k, mOUT, 3);
        list *top = root->lista;
        while (top != NULL) {
            int li = top->l;
            int co = top->c;
            if (maT[li][co] == 'X') maT[li][co] = '+';
            else maT[li][co] = 'X';
            list* temp = top;
            top = top->next;
            free(temp);
        }
        root->left = CreateA(fisier, maT, n, m, k, mOUT, p, r, r1);
    }

    (*r1)++;
    (*r)--;

    root->lista = reguli(fisier, ma, n, m, k, mOUT, 1);
    list *top = root->lista;
    while (top != NULL) {
        int li = top->l;
        int co = top->c;
        if (ma[li][co] == 'X') ma[li][co] = '+';
        else ma[li][co] = 'X';
        list* temp = top;
        top = top->next;
        free(temp);
    }

    root->right = CreateA(fisier, ma, n, m, k, mOUT, p, r, r1);
    (*r1)--;

    for (int i = 0; i < n; i++) free(maT[i]);
    free(maT);

    return root;
}

void postorder(Node **root) {
    if (*root) {
        postorder(&((*root)->left));
        postorder(&((*root)->right));
        elibereazaLista((*root)->lista);
        free(*root);
        *root = NULL;
    }
}

void taskuri(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p) {
    int l, c, r = 0;
    char lista[256];
    while (k != 0) {
        r++;
        if (p == 2) {
            sprintf(lista, "%d", r);
            fputs(lista, mOUT);
        }
        list *top = reguli(fisier, ma, n, m, k, mOUT, p);
        while (top != NULL) {
            pop(&top, &l, &c);
            if (ma[l][c] == 'X') ma[l][c] = '+';
            else ma[l][c] = 'X';
        }
        if (p == 1) afisare(ma, n, m, mOUT);
        else if (p == 2) fputs("\n", mOUT);
        k--;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Numar insuficient de argumente!\n");
        return 1;
    }

    FILE *mINT, *mOUT;
    char **ma;
    int n, m, k, p, r = 0, r1 = 0;

    FOP(&mINT, argv[1], "rt");
    fscanf(mINT, "%d %d %d %d", &p, &n, &m, &k);

    ma = (char**)calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++) {
        ma[i] = (char*)calloc(m, sizeof(char));
    }

    citire(mINT, ma, n, m);
    FOP(&mOUT, argv[2], "wt");

    if (p != 3) {
        if (p == 1) afisare(ma, n, m, mOUT);
        taskuri(mINT, ma, n, m, k, mOUT, p);
    } else {
        Node *root = NULL;
        //initTree(&root);
        root = CreateA(mINT, ma, n, m, k, mOUT, p, &r, &r1);
        postorder(&root);
    }

    for (int i = 0; i < n; i++) free(ma[i]);
    free(ma);

    fclose(mINT);
    fclose(mOUT);

    return 0;
}
