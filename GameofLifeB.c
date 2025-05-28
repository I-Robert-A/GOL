#include "JoculVietii.h"


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
    while (top != NULL)
    {
        while (top->Lista != NULL)
        {
            list *elem;
            elem = top->Lista;
            top->Lista = top->Lista->next;
            free(elem);
        }
        stiva *topS;
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
        //newNode->next = NULL;
        if (newNode==NULL)
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

list *copyL(list *head)
{
    list *newHead = NULL;

    while (head != NULL)
    {
        addAtEnd(&newHead, head->l, head->c);
        head = head->next;
    }

    return newHead;
}


void Stergere(list **head)
{
    list *temp;
    if (*head == NULL)
    {
        return;
    }
    temp = *head;
    if ((*head)->next == NULL)
    {
        free(temp);
        *head = NULL;
        return;
    }
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void DFS_scan(Graph *g, int visited[], int i, int **comp_conex, int y, int *ko)
{
    int j;
    visited[i] = 1;
    comp_conex[y][(*ko)] = i;
    (*ko)++;
    printf("Nodul %d -> ", i);
    for (j = 0; j < g->V; j++)
        if (g->a[i][j] == 1 && visited[j] == 0)
            DFS_scan(g, visited, j, comp_conex, y, ko);
}

void buildInCompVector(const int *comp_conex, bool *inComp, int totalNodes)
{

    for (int i = 0; i < totalNodes; i++)
    {
        inComp[i] = false;
    }

    int size = comp_conex[0];
    for (int i = 1; i <= size; i++)
    {
        inComp[comp_conex[i]] = true;
    }
}

void DFS(Graph *g, int visited[], int i, int k, list **top, list **maxList,int *max, int remaining, int *comp_conex, bool *inComp)
{
    int jj;
    if (!inComp[i])
        return;
    visited[i] = 1;
    addAtEnd(top, i, 2);

    if (k > *max)
    {
        *max = k;
        if (*maxList != NULL)
            elibereazaLista(*maxList);
        *maxList = copyL(*top);
    }

    int unvisitedInComp = 0;
    for (jj = 1; jj <= comp_conex[0]; jj++)
    {
        if (visited[comp_conex[jj]]==0)
        {
            unvisitedInComp++;
        }
    }
    if (k + unvisitedInComp <= *max)
    {
        visited[i] = 0;
        if (*top != NULL)
            Stergere(top);
        return;
    }

    int *neighbors = (int *)malloc(g->V * sizeof(int));
    int neighborCount = 0;

    for (jj = 0; jj < g->V; jj++)
    {
        if (g->a[i][jj] == 1 && visited[jj] == 0 && inComp[jj])
        {
            neighbors[neighborCount++] = jj;
        }
    }

    for (jj = 0; jj < neighborCount; jj++)
    {
        DFS(g, visited, neighbors[jj], k + 1, top, maxList, max, remaining - 1, comp_conex, inComp);
    }

    free(neighbors);
    visited[i] = 0;
    if (*top != NULL)
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
    while (top != NULL)
    {
        list *tmp;
        tmp = top;
        top = top->next;
        free(tmp);
    }
}

int verificareVec2(FILE *fisier, char **ma, int i, int j, int n, int m, stiva *topS)
{
    int k = 0, bi;
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
    //char lista[256];
    list *top = NULL;
    // top=(list*)malloc(sizeof(list));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
      
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
    int i, j, ko, r = 0,bi;
    list *top = NULL, *elem = NULL;
    stiva *aux;
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
    //free(top);

}

void afisareS(stiva **topS, FILE *mOUT, int q)
{
    list *elem;
    if ((*topS)->next)
    {
        afisareS(&(*topS)->next, mOUT, q - 1);
    }
    if (q > 0)
        fprintf(mOUT, "%d", q);
    elem = popL(topS);
    while (elem != NULL)
    {
        list* aux;
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
    int i, j, bi;
    stiva *aux;
    list *elem;
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
                    ma[i][j] = '+';
                else if (ma[i][j] == '+')
                    ma[i][j] = 'X';
            }
        }
    }
}
Node *CreateA(FILE *fisier, char **ma, int n, int m, int k, FILE *mOUT, int p, int *r, int *r1)
{
    int i, li, co, j;
    list *top2, *temp2;
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
        // printf("%d ",p);
        afisare(ma, n, m, mOUT);
    }
    printf("%d ", p);

    if (p == 4)
    {
        int *visited, noduri = 0, ko, sum = 0, ko2;
        int **comp_conex;
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
        comp_conex = (int **)calloc(noduri, sizeof(int *));
        for (i = 0; i < noduri; i++)
        {
            comp_conex[i] = (int *)calloc(noduri + 1, sizeof(int));
        }
        g->a = (int **)calloc(noduri, sizeof(int *));
        for (i = 0; i < noduri; i++)
        {
            g->a[i] = (int *)calloc(noduri, sizeof(int));
        }
        vec = (int **)calloc(n, sizeof(int *));
        for (i = 0; i < n; i++)
        {
            vec[i] = (int *)calloc(m, sizeof(int));
        }
        g->V = noduri;
        visited = (int *)calloc(noduri, sizeof(int));
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                // printf("%c ",maT[i][j]);
            }
            // printf("\n");
        }
        sum = 0;
        nodes = NULL;

        sum = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (ma[i][j] == 'X')
                {
                    vec[i][j] = sum;
                    addAtEnd(&nodes, i, j);
                    sum++;
                }
                else
                {
                    vec[i][j] = -1;
                }
            }
        }

        for (i = 0; i < noduri; i++)
        {
            for (j = 0; j < noduri; j++)
            {
                g->a[i][j] = 0;
            }
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (ma[i][j] == 'X')
                {
                    int u = vec[i][j];

                    if (j + 1 < m && ma[i][j + 1] == 'X')
                    {
                        int v = vec[i][j + 1];
                        g->a[u][v] = g->a[v][u] = 1;
                    }

                    if (i + 1 < n && ma[i + 1][j] == 'X')
                    {
                        int v = vec[i + 1][j];
                        g->a[u][v] = g->a[v][u] = 1;
                    }

                    if (i + 1 < n && j + 1 < m && ma[i + 1][j + 1] == 'X')
                    {
                        int v = vec[i + 1][j + 1];
                        g->a[u][v] = g->a[v][u] = 1;
                    }

                    if (i + 1 < n && j - 1 >= 0 && ma[i + 1][j - 1] == 'X')
                    {
                        int v = vec[i + 1][j - 1];
                        g->a[u][v] = g->a[v][u] = 1;
                    }
                }
            }
        }

        //printf("Matricea de adiacență:\n");
        for (i = 0; i < noduri; i++)
        {
            //printf("Nod %d: ", i);
            for (j = 0; j < noduri; j++)
            {
                if (g->a[i][j] == 1)
                {
                    printf("%d ", j);
                }
            }
            printf("\n");
        }

        //printf("Maparea nodurilor:\n");
        list *tempNode = nodes;
        int nodeIdx = 0;
        while (tempNode != NULL)
        {
           // printf("Nod %d -> (%d,%d)\n", nodeIdx, tempNode->l, tempNode->c);
            tempNode = tempNode->next;
            nodeIdx++;
        }
        int max = 0;
        list *maxList = NULL;
        list *top = NULL;
        int remaining;
        sum = 0;

        for (i = 0; i < noduri; i++)
            visited[i] = 0;

        for (i = 0; i < noduri; i++)
        {
            if (visited[i] == 0)
            {
                ko = 1;
                DFS_scan(g, visited, i, comp_conex, sum, &ko);
                if (ko > 1)
                {
                    comp_conex[sum][0] = ko - 1;
                    sum++;
                }
            }
        }

        for (i = 0; i < sum - 1; i++)
        {
            for (j = i + 1; j < sum; j++)
            {
                if (comp_conex[i][0] < comp_conex[j][0])
                {

                    int *temp = comp_conex[i];
                    comp_conex[i] = comp_conex[j];
                    comp_conex[j] = temp;
                }
            }
        }

        /*for (i = 0; i < sum; i++)
        {
            for (j = 0; j <= comp_conex[i][0]; j++)
            {
                printf("sss%d ", comp_conex[i][j]);
            }
            printf("\n");
        }*/

        bool *inComp = (bool *)calloc(g->V, sizeof(bool));

        for (i = 0; i < sum; i++)
        {

            if (comp_conex[i][0] <= max)
            {
                break;
            }

            buildInCompVector(comp_conex[i], inComp, g->V);
            //remaining = comp_conex[i][0] - 1;

            for (ko2 = 0; ko2 < g->V; ko2++)
                visited[ko2] = 0;

            int *sortedNodes = (int *)malloc(comp_conex[i][0] * sizeof(int));
            for (j = 0; j < comp_conex[i][0]; j++)
            {
                sortedNodes[j] = comp_conex[i][j + 1];
            }

            for (int x = 0; x < comp_conex[i][0] - 1; x++)
            {
                for (int y = x + 1; y < comp_conex[i][0]; y++)
                {

                    list *temp1 = nodes;
                    list *temp11 = nodes;
                    int idx1 = 0, idx2 = 0;

                    while (temp1 != NULL && idx1 < sortedNodes[x])
                    {
                        temp1 = temp1->next;
                        idx1++;
                    }

                    while (temp11 != NULL && idx2 < sortedNodes[y])
                    {
                        temp11 = temp11->next;
                        idx2++;
                    }

                    if (temp1 != NULL && temp11 != NULL)
                    {

                        if (temp1->l > temp11->l || (temp1->l == temp11->l && temp1->c > temp11->c))
                        {
                            int temp = sortedNodes[x];
                            sortedNodes[x] = sortedNodes[y];
                            sortedNodes[y] = temp;
                        }
                    }
                }
            }

            for (j = 0; j < comp_conex[i][0]; j++)
            {

                for (ko2 = 0; ko2 < g->V; ko2++)
                    visited[ko2] = 0;

                top = NULL;
                remaining = comp_conex[i][0] - 1;
                DFS(g, visited, sortedNodes[j], 1, &top, &maxList, &max, remaining, comp_conex[i], inComp);
                elibereazaLista(top);
            }

            free(sortedNodes);

            if (i + 1 < sum && max >= comp_conex[i + 1][0])
            {
                break;
            }
        }

        free(inComp);

        fprintf(mOUT, "%d\n", max - 1);
        printf("Lanț maxim găsit: lungime %d\n", max - 1);
        if (maxList != NULL)
        {
            list *temp = maxList;
            printf("Nodurile din lanț: ");
            int ks = 0;
            while (temp != NULL)
            {
                list *tmp = nodes;
                int idx = 0;
                while (tmp != NULL && idx < temp->l)
                {
                    tmp = tmp->next;
                    idx++;
                }
                if (tmp)
                {
                    if (ks != 0)
                    {
                        fprintf(mOUT, " ");
                    }
                    ks++;
                    fprintf(mOUT, "(%d,%d)", tmp->l, tmp->c);
                    printf("(%d,%d) ", tmp->l, tmp->c);
                }
                temp = temp->next;
            }
            printf("\n");
        }
        fprintf(mOUT, "\n");

        for (i = 0; i < noduri; i++)
        {
            free(comp_conex[i]);
            free(g->a[i]);
        }
        free(comp_conex);
        free(g->a);
        free(g);
        for (i = 0; i < n; i++)
        {
            free(vec[i]);
        }
        free(vec);
        free(visited);
        elibereazaLista(nodes);
        elibereazaLista(maxList);
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

        list *lista_left = reguli(fisier, maT, n, m, k, mOUT, 3);
        top2 = lista_left;
        while (top2 != NULL)
        {
            li = top2->l;
            co = top2->c;
            temp2 = top2;
            if (maT[li][co] == 'X')
                maT[li][co] = '+';
            else
                maT[li][co] = 'X';
            top2 = top2->next;
            free(temp2);
        }
        root->left = CreateA(fisier, maT, n, m, k, mOUT, p, r, r1);
    }

    (*r1)++;
    (*r)--;

    root->lista = reguli(fisier, ma, n, m, k, mOUT, 1);
    top2 = root->lista;
    while (top2 != NULL)
    {
        li = top2->l;
        co = top2->c;
        temp2 = top2;
        if (ma[li][co] == 'X')
            ma[li][co] = '+';
        else
            ma[li][co] = 'X';
        top2 = top2->next;
        free(temp2);
    }

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
