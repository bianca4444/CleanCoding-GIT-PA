/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

 /// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
 /// ex: 1 - restaurantul 1 si tot asa    

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} STK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = g->adjacency_lists[src];
    g->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = g->adjacency_lists[dest];
    g->adjacency_lists[dest] = new_node;
}

GPH *create_graph(int vertices)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

STK *create_stack(int capacity)
{
    STK *stack = malloc(sizeof(STK));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = malloc(capacity * sizeof(int));
    return stack;
}

void push(STK *stack, int data)
{
    stack->array[++stack->top] = data;
}

int pop(STK *stack)
{
    return stack->array[stack->top--];
}

void DFS(GPH *g, STK *s, int vertex_nr)
{
    NODE *adj_list = g->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    g->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);
    push(s, vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (g->visited[connected_vertex] == 0)
            DFS(g, s, connected_vertex);

        temp = temp->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest;
    printf("Adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (int i = 0; i < edg_nr; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void clear_visited(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->visited[i] = 0;
    }
}

void can_reach(GPH *g, int nrv, STK *s1, STK *s2)
{
    int ans = 0;
    for (int i = 0; i < nrv && !ans; i++)
    {
        DFS(g, s1, i);
        clear_visited(g, nrv);
        DFS(g, s2, i);

        for (int j = 0; j < nrv && !ans; j++)
        {
            if ((s1->array[i] != j) && (s2->array[j] == i))
                ans = 1;
        }
    }

    if (ans == 1)
        printf("\nExista drum direct intre doua restaurante.\n");
    else
        printf("\nNu exista drum direct intre doua restaurante. \n");
}

int main()
{
    int nrv, edg_nr;
    printf("Cate noduri are reteaua? ");
    scanf("%d", &nrv);

    printf("Cate muchii are reteaua? ");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nrv);
    STK *s1 = create_stack(2 * nrv);
    STK *s2 = create_stack(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    can_reach(g, nrv, s1, s2);

    return 0;
}
