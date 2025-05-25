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
        newNode->next = NULL;
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

list* copyL(list *head) {
    list *newHead = NULL;

    while (head != NULL) {
        addAtEnd(&newHead, head->l, head->c);
        head = head->next;
    }

    return newHead;
}

void Stergere(list** head)
{
    list *temp;
    if(*head==NULL)
    {
        return;
    }
    temp=*head;
    if((*head)->next==NULL)
    {
        free(temp);
        *head=NULL;
        return;
    }
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    free(temp->next);
    temp->next=NULL;

}

void DFS_scan(Graph *g, int visited[], int i, int k, list **top,list **maxList, int *max)
{
    int j;
    list* aux;
    visited[i] = 1;
    //printf("Nodul %d -> ", i);
    addAtEnd(top,i,2);
    if(k>*max)
                {
                    (*max)=k;
                    *maxList=copyL(*top);
                }
    for (j = 0; j < g->V; j++)
    {
        if (g->a[i][j] == 1 && visited[j] == 0)
            {
                DFS_scan(g, visited, j, k+1, top,maxList,max);
            }
    }
    //visited[i]=0;
    Stergere(top);
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

void elibereazaLista(list *top)
{
    list *tmp;
    while (top != NULL)
    {
        tmp = top;
        top = top->next;
        free(tmp);
    }
}

int verificareVec2(FILE *fisier, char **ma, int i, int j, int n, int m, stiva *topS)
{
    int k = 0, bi = 0;
    list *elem;
    stiva *aux;
    if (((i - 1) >= 0) && ((j - 1) >= 0))
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i - 1 && elem->c == j - 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i - 1][j - 1] == 'X' && bi % 2 == 0) || (ma[i - 1][j - 1] == '+' && bi % 2 == 1))
            k++;
    }
    if (i - 1 >= 0)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i - 1 && elem->c == j)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i - 1][j] == 'X' && bi % 2 == 0) || (ma[i - 1][j] == '+' && bi % 2 == 1))
            k++;
    }
    if (i - 1 >= 0 && j + 1 < m)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i - 1 && elem->c == j + 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i - 1][j + 1] == 'X' && bi % 2 == 0) || (ma[i - 1][j + 1] == '+' && bi % 2 == 1))
            k++;
    }
    if (j - 1 >= 0)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i && elem->c == j - 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i][j - 1] == 'X' && bi % 2 == 0) || (ma[i][j - 1] == '+' && bi % 2 == 1))
            k++;
    }
    if (j + 1 < m)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i && elem->c == j + 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i][j + 1] == 'X' && bi % 2 == 0) || (ma[i][j + 1] == '+' && bi % 2 == 1))
            k++;
    }
    if (i + 1 < n && j - 1 >= 0)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i + 1 && elem->c == j - 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i + 1][j - 1] == 'X' && bi % 2 == 0) || (ma[i + 1][j - 1] == '+' && bi % 2 == 1))
            k++;
    }
    if (i + 1 < n)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i + 1 && elem->c == j)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i + 1][j] == 'X' && bi % 2 == 0) || ((ma[i + 1][j] == '+' && bi % 2 == 1)))
            k++;
    }
    if (i + 1 < n && j + 1 < m)
    {
        aux = topS;
        bi = 0;
        while (aux != NULL)
        {
            elem = aux->Lista;
            while (elem != NULL)
            {
                if (elem->l == i + 1 && elem->c == j + 1)
                {
                    printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                    bi++;
                }
                elem = elem->next;
            }
            aux = aux->next;
        }
        if ((ma[i + 1][j + 1] == 'X' && bi % 2 == 0) || (ma[i + 1][j + 1] == '+' && bi % 2 == 1))
            k++;
    }

    return k;
}

list *reguli(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p)
{
    int i, j, ko;
    char lista[256];
    list *top = NULL;
    // top=(list*)malloc(sizeof(list));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            // car='0';
            ko = verificareVec(fisier, ma, i, j, n, m);
            if (p != 3)
            {
                if ((ma[i][j] == 'X' && (ko < 2 || ko > 3)) || (ma[i][j] == '+' && ko == 3))
                {
                    addAtEnd(&top, i, j);
                }
            }
            else
            {
                if (ma[i][j] == '+' && ko == 2)
                {
                    addAtEnd(&top, i, j);
                }
            }
        }
    }
    return top;
}
void taskuri(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p)
{
    int l, c, r = 0;
    char lista[256];
    list *top = NULL;
    list *elem = NULL;
    printf("ffff");
    while (k != 0)
    {
        r++;
        top = reguli(fisier, ma, n, m, k, mOUT, p);
        // printf("%d %d\n",top->next->l,top->next->c);
        while (top != NULL)
        {
            elem = top;
            top = top->next;
            l = elem->l;
            c = elem->c;
            free(elem);
            // printf("%d",l);
            if (ma[l][c] == 'X')
            {
                ma[l][c] = '+';
            }
            else
            {
                ma[l][c] = 'X';
            }
        }
        if (p == 1)
        {
            afisare(ma, n, m, mOUT);
        }
        k--;
        free(top);
    }
}

void task2(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, stiva **topS, int *q)
{
    int i, j, ko, l, c, r = 0, bi = 0;
    char lista[256];
    list *top = NULL, *elem = NULL;
    stiva *aux;
    aux = *topS;
    char stare;
    while (k != 0)
    {
        top = NULL;
        r++;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                aux = *topS;
                bi = 0;
                while (aux != NULL)
                {
                    elem = aux->Lista;
                    while (elem != NULL)
                    {
                        if (elem->l == i && elem->c == j)
                        {
                            printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                            bi++;
                        }
                        elem = elem->next;
                    }
                    aux = aux->next;
                }
                printf("\nbi:%d", bi);

                ko = verificareVec2(fisier, ma, i, j, n, m, *topS);
                if (bi % 2 == 0)
                {
                    stare = ma[i][j];
                }
                else
                {
                    if (ma[i][j] == 'X')
                    {
                        stare = '+';
                    }
                    else
                    {
                        stare = 'X';
                    }
                }
                if ((stare == 'X' && (ko < 2 || ko > 3)) || (stare == '+' && ko == 3))
                {
                    addAtEnd(&top, i, j);
                }
            }
        }
        (*q)++; // sterge q!!!
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

void bonus(stiva **topS, char **ma, int n, int m)
{
    int i, j, bi = 0;
    stiva *aux;
    list *elem;
    char stare;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            aux = *topS;
            bi = 0;
            while (aux != NULL)
            {
                elem = aux->Lista;
                while (elem != NULL)
                {
                    if (elem->l == i && elem->c == j)
                    {
                        printf("lin:%d %d\n col:%d %d ", elem->l, i, elem->c, j);
                        bi++;
                    }
                    elem = elem->next;
                }
                aux = aux->next;
            }
            printf("\nbi:%d", bi);

            if (bi % 2 == 1)
            {
                if (ma[i][j] == 'X')
                {
                    stare = '+';
                }
                else
                {
                    stare = 'X';
                }
            }
        }
    }
}
Node *CreateA(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, int *r, int *r1)
{
    int i, li, co, j;
    list *top, *temp;
    Node *root = (Node *)malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    root->lista = NULL;
    
    char **maT = (char **)calloc(n, sizeof(char *));
    for (i = 0; i < n; i++)
    {
        maT[i] = (char *)malloc(m * sizeof(char));
        for (j = 0; j < m; j++)
            maT[i][j] = ma[i][j];
    }
    
    if (p == 3)
        {
            //printf("%d ",p);
        afisare(ma, n, m, mOUT);
        }
    printf("%d ",p);

    if(p==4)
    {
        int *visited, noduri = 0, ko = 0, sum = 0,kl=0,ko2=0;
        int **vec;
    Graph *g;
    list *nodes;
    g = (Graph *)malloc(sizeof(Graph));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (ma[i][j] == 'X')
            {
                noduri++;
            }
        }
    }
    g->a = (int **)calloc(noduri, sizeof(int *));
    for (i = 0; i < noduri; i++)
    {
        g->a[i] = (int *)calloc(noduri,sizeof(int));
    }
    vec = (int **)calloc(n, sizeof(int *));
    for (i = 0; i < n; i++)
    {
        vec[i] = (int *)calloc(m,sizeof(int));
    }
    g->V=noduri;
    visited = (int *)calloc(noduri, sizeof(int));
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            //printf("%c ",maT[i][j]);
        }
        //printf("\n");
    }
    sum=0;
    nodes = NULL;

    // Construim vec și lista de noduri doar pentru 'X'
    sum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (ma[i][j] == 'X') {
                vec[i][j] = sum;
                addAtEnd(&nodes, i, j);
                sum++;
            } else {
                vec[i][j] = -1; // invalid
            }
        }
    }

    // Construim graful
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (ma[i][j] == 'X') {
                int u = vec[i][j];

                if (j + 1 < m && ma[i][j + 1] == 'X') {
                    int v = vec[i][j + 1];
                    g->a[u][v] = g->a[v][u] = 1;
                }
                if (i + 1 < n && j - 1 >= 0 && ma[i + 1][j - 1] == 'X') {
                    int v = vec[i + 1][j - 1];
                    g->a[u][v] = g->a[v][u] = 1;
                }
                if (i + 1 < n && ma[i + 1][j] == 'X') {
                    int v = vec[i + 1][j];
                    g->a[u][v] = g->a[v][u] = 1;
                }
                if (i + 1 < n && j + 1 < m && ma[i + 1][j + 1] == 'X') {
                    int v = vec[i + 1][j + 1];
                    g->a[u][v] = g->a[v][u] = 1;
                }
            }
        }
    }
    for(i=0;i<noduri;i++)
    {
        for(j=0;j<noduri;j++)
        {
            printf("%d ", g->a[i][j]);
        }
        printf("\n");
    }
    int max=-1;
    list* maxList;
    for (i = 0; i < noduri; i++)
    {
        top=NULL;
        DFS_scan(g, visited, i, ko,&top,&maxList,&max);
        elibereazaLista(top);
    }
    int nrNod=0;
    fprintf(mOUT,"%d\n",max);
list* temp = maxList;
while (temp != NULL)
{
    list* tmp = nodes;
    int idx = 0;
    while (tmp != NULL && idx < temp->l)
    {
        tmp = tmp->next;
        idx++;
    }
    if (tmp && (tmp->l!=0 || tmp->c!=0))
    
        fprintf(mOUT, "(%d,%d) ", tmp->l, tmp->c);

    temp = temp->next;
}
fprintf(mOUT, "\n");
    }

    if (*r + *r1 == k)
    {
        for (i = 0; i < n; i++)
            free(maT[i]);
        free(maT);
        return root;
    }
    
    (*r)++;
    if (*r <= k)
    {
        // Pentru ramura stângă
        list *lista_left = reguli(fisier, maT, n, m, k, mOUT, 3);
        top = lista_left;
        while (top != NULL)
        {
            li = top->l;
            co = top->c;
            temp = top;
            if (maT[li][co] == 'X')
                maT[li][co] = '+';
            else
                maT[li][co] = 'X';
            top = top->next;
            free(temp);
        }
        root->left = CreateA(fisier, maT, n, m, k, mOUT, p, r, r1);
    }
    
    (*r1)++;
    (*r)--;
    
    // Pentru ramura dreaptă - aceasta va fi lista finală a nodului
    root->lista = reguli(fisier, ma, n, m, k, mOUT, 1);
    top = root->lista;
    while (top != NULL)
    {
        li = top->l;
        co = top->c;
        temp = top;
        if (ma[li][co] == 'X')
            ma[li][co] = '+';
        else
            ma[li][co] = 'X';
        top = top->next;
        free(temp);
    }
    
    // PROBLEMA: Aici setezi root->lista = NULL pentru că ai eliberat lista
    root->lista = NULL;
    
    root->right = CreateA(fisier, ma, n, m, k, mOUT, p, r, r1);
    (*r1)--;
    
    for (i = 0; i < n; i++)
        free(maT[i]);
    free(maT);
    return root;
}


void postorder(Node **root)
{
    if (*root)
    {
        postorder(&((*root)->left));
        postorder(&((*root)->right));
        elibereazaLista((*root)->lista);
        free(*root);
        *root = NULL;
    }
}

void task4(Node *root, char **ma, int n, int m, FILE* mOUT)
{
    printf("xxxxxxxxxx");
    if (!root)
        return;

    int i, j, li, co, *visited, noduri = 0, k = 0, sum = 0;
    Graph *g;
    list *nodes;
    g = (Graph *)malloc(sizeof(Graph));

    // Alocăm o copie a matricei ma
    char **maT = (char **)calloc(n, sizeof(char *));
    for (i = 0; i < n; i++)
    {
        maT[i] = (char *)malloc(m * sizeof(char));
        for (j = 0; j < m; j++)
        {
            maT[i][j] = ma[i][j];
        }
    }

    // Aplicăm modificările din lista nodului curent în maT
    list *top = root->lista;
    while (top != NULL)
    {
        li = top->l;
        co = top->c;
        if (maT[li][co] == 'X')
        {
            maT[li][co] = '+';
        }
        else
        {
            maT[li][co] = 'X';
        }
        top = top->next;
    }

    // Afișăm matricea pentru acest nod (generație)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (ma[i][j] == 'X')
            {
                noduri++;
            }
        }
    }
    g->a = (int **)calloc(noduri, sizeof(int *));
    for (i = 0; i < noduri; i++)
    {
        g->a[i] = (int *)calloc(noduri,sizeof(int));
    }
    g->V=noduri;
    visited = (int *)calloc(noduri, sizeof(int));
    nodes=(list*)malloc(sizeof(list));
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%c ",maT[i][j]);
        }
        printf("\n");
    }
   sum=0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            //printf("345674");
            if (ma[i][j] == 'X')
            {
                //printf("345674");
                addAtEnd(&nodes,i,j);
                k = 0;
                if (j + 1 < m)
                {
                    if (ma[i][j + 1] == 'X')
                    {
                        k++;
                        g->a[sum][sum + k] = 1;
                        g->a[sum + k][sum] = 1;
                    }
                }
                if (i + 1 < n && j - 1 > 0)
                {
                    if (ma[i + 1][j - 1] == 'X')
                    {
                        k++;
                        g->a[sum][sum + k] = 1;
                        g->a[sum + k][sum] = 1;
                    }
                }
                if (i + 1 < n)
                {
                    if (ma[i + 1][j] == 'X')
                    {
                        k++;
                        g->a[sum][sum + k] = 1;
                        g->a[sum + k][sum] = 1;
                    }
                }
                if (i + 1 < n && j + 1 < m)
                {
                    if (ma[i + 1][j + 1] == 'X')
                    {
                        k++;
                        g->a[sum][sum + k] = 1;
                        g->a[sum + k][sum] = 1;
                    }
                }
                sum++;
            }
        }
    }
    for(i=0;i<noduri;i++)
    {
        for(j=0;j<noduri;j++)
        {
            printf("%d ", g->a[i][j]);
        }
        printf("\n");
    }
    k=0;
    int max=-1;
    list* maxList;
    for (i = 0; i < noduri; i++)
    {
        top=NULL;
        DFS_scan(g, visited, i, k,&top,&maxList,&max);
        elibereazaLista(top);
    }
    int nrNod=0;
    fprintf(mOUT,"%d\n",max);
list* temp = maxList;
while (temp != NULL)
{
    list* tmp = nodes;
    int idx = 0;
    while (tmp != NULL && idx < temp->l)
    {
        tmp = tmp->next;
        idx++;
    }
    if (tmp && (tmp->l!=0 || tmp->c!=0))
    
        fprintf(mOUT, "(%d,%d) ", tmp->l, tmp->c);

    temp = temp->next;
}
fprintf(mOUT, "\n");
    // Recursiv în stânga și dreapta
    task4(root->left, maT, n, m,mOUT);
    task4(root->right, ma, n, m,mOUT);

    // Eliberăm memoria matricei maT
    for (i = 0; i < n; i++)
        free(maT[i]);
    free(maT);
}