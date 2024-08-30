#include <stdio.h>
#include <stdlib.h>

int n, indeg[20], opcount = 0, queue[20], front = -1, rear = -1;

int bfs(int mat[n][n])
{
    int count = 0;
    front = rear = -1;

    for (int i = 0; i < n; i++)
    {
        if (indeg[i] == 0)
        {
            queue[++rear] = i;
        }
    }

    while (front != rear)
    {
        int curr = queue[++front];
        count++;

        for (int i = 0; i < n; i++)
        {
            opcount++;
            if (mat[curr][i])
            {
                indeg[i]--;
                if (!indeg[i])
                    queue[++rear] = i;
            }
        }
    }

    return count != n;
}

void tester()
{
    printf("Enter number of vertices :\n");
    scanf("%d", &n);
    int adjMat[n][n];

    for (int i = 0; i < n; i++)
        indeg[i] = 0;

    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
            if (adjMat[i][j])
                indeg[j]++;
        }
    }

    if (bfs(adjMat))
    {
        printf("Cycle exists..Cannot perform topological sorting!!!");
        exit(0);
    }
    else
    {
        printf("Topological sorting order : \n");

        for (int i = 0; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
    }
}

void plotter()
{
    FILE *f1 = fopen("srcrmMatTopSort.txt", "w");

    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];

        for (int i = 0; i < n; i++)
            indeg[i] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                adjMat[i][j] = 1;
                indeg[j]++;
            }
        }

        opcount = 0;
        bfs(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }

    fclose(f1);
}

void main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
}

Output:
Enter number of vertices :
4
Enter the adjacency matrix :
0 1 0 0
0 0 1 0
0 0 0 1
0 0 0 0
Topological sorting order :
0 1 2 3

  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'topo_sort_bfs_plot.png'

# Set title and labels
set title "BFS Operation Count vs Number of Vertices for Topological Sorting"
set xlabel "Number of Vertices"
set ylabel "Operation Count"
set grid

# Plot the data from the file
plot 'srcrmMatTopSort.txt' using 1:2 with linespoints title 'Operation Count'

  In terminal
gnuplot plot_topo_sort_bfs.gnu
