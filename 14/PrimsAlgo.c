#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int heapCount = 0, graphCount = 0, n;

typedef struct pair
{
    int node;
    int val;
    int parent;
} *Pair;

Pair createPair(int n, int val, int parent)
{
    Pair p = (Pair)malloc(sizeof(struct pair));
    p->val = val;
    p->node = n;
    p->parent = parent;
    return p;
}

typedef struct PriorityQ
{
    Pair *arr;
    int currSize;
} *PriorityQueue;

PriorityQueue init(int edges)
{
    PriorityQueue pq = (PriorityQueue)malloc(sizeof(struct PriorityQ));
    pq->arr = (Pair *)malloc(edges * sizeof(struct pair));
    pq->currSize = 0;

    return pq;
}

void add(PriorityQueue pq, Pair p)
{
    pq->arr[pq->currSize] = p;
    pq->currSize += 1;

    int x = pq->currSize - 1;
    int parIdx = (x - 1) / 2;

    while (pq->arr[x]->val < pq->arr[parIdx]->val)
    {
        Pair temp = pq->arr[x];
        pq->arr[x] = pq->arr[parIdx];
        pq->arr[parIdx] = temp;

        x = parIdx;
        parIdx = (x - 1) / 2;
    }
}

void heapify(PriorityQueue pq, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int minIdx = i;
    heapCount++;

    if (left < pq->currSize && pq->arr[minIdx]->val > pq->arr[left]->val)
    {
        minIdx = left;
    }

    if (right < pq->currSize && pq->arr[minIdx]->val > pq->arr[right]->val)
    {
        minIdx = right;
    }

    if (minIdx != i)
    {
        Pair temp = pq->arr[i];
        pq->arr[i] = pq->arr[minIdx];
        pq->arr[minIdx] = temp;

        heapify(pq, minIdx);
    }
}

Pair delete(PriorityQueue pq)
{
    Pair p = pq->arr[0];

    Pair temp = p;
    pq->arr[0] = pq->arr[pq->currSize - 1];
    pq->arr[pq->currSize - 1] = temp;

    pq->currSize -= 1;

    heapify(pq, 0);
    return p;
}

int prims(int n, int adjMat[n][n])
{
    int vis[n], finalCost = 0, MSTEdge[n][2], k = 0;
    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
    }
    int edges = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && adjMat[i][j] != INT_MAX)
                edges++;
        }
    }

    PriorityQueue pq = init(edges);
    add(pq, createPair(0, 0, -1));

    while (pq->currSize != 0)
    {
        Pair curr = delete (pq);
        if (!vis[curr->node])
        {
            vis[curr->node] = 1;
            MSTEdge[k][0] = curr->parent;
            MSTEdge[k++][1] = curr->node;
            finalCost += curr->val;

            graphCount++;

            for (int i = 0; i < n; i++)
            {
                if (curr->node != i && adjMat[curr->node][i] != INT_MAX)
                {
                    graphCount++;
                    add(pq, createPair(i, adjMat[curr->node][i], curr->node));
                }
            }
        }
    }

    printf("MST edges are :\n");
    for (int i = 1; i < n; i++)
    {
        printf("%d -- %d\n", MSTEdge[i][0], MSTEdge[i][1]);
    }

    return finalCost;
}

void tester()
{
    int source;
    printf("Enter the number of nodes : ");
    scanf("%d", &n);
    printf("Enter adjacency matrix :\n");
    int adjMat[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMat[i][j] == -1)
                adjMat[i][j] = INT_MAX;

    printf("\nMinimum cost of MST : %d\n", prims(n, adjMat));
    printf("\nheapCount : %d\tGraphCount: %d\n", heapCount, graphCount);
}

void plotter()
{
    FILE *f = fopen("prims.txt", "w");
    for (int i = 0; i < 5; i++)
    {
        heapCount = 0;
        graphCount = 0;
        tester();
        fprintf(f, "%d\t%d\n", n, graphCount > heapCount ? graphCount : heapCount);
    }

    fclose(f);
}

void main()
{
    int ch;
    printf("\n\nEnter\n1.Tester\n2.Plotter\n");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid Input!");
    }
}

Output:
Enter the number of nodes : 4
Enter adjacency matrix :
0 2 3 1
2 0 4 2
3 4 0 5
1 2 5 0

  Minimum cost of MST : 6

MST edges are :
0 -- 3
0 -- 1
1 -- 2

heapCount : 12    GraphCount: 12

  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'prims_plot.png'

# Set title and labels
set title "Prim's Algorithm Performance"
set xlabel "Number of Nodes"
set ylabel "Operation Count"
set grid

# Set the key (legend) to be displayed outside the plot
set key outside

# Plot the data from the file
plot 'prims.txt' using 1:2 with linespoints title 'Operation Count' lc rgb "blue"

  In terminal
gnuplot plot_prims.gnu
