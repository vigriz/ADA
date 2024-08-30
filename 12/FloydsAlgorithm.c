#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int n, opcount, dist[100][100];

int floyds(int adjMat[n][n], int n)
{
    opcount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMat[i][j] == -1)
                dist[i][j] = INT_MAX;
            else
                dist[i][j] = adjMat[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
        {
            int tempDist = dist[i][k];
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] > tempDist)
                {
                    opcount++;
                    if (dist[k][j] != INT_MAX && dist[i][j] > tempDist + dist[k][j])
                    {
                        dist[i][j] = tempDist + dist[k][j];
                    }
                }
            }
        }
}

void tester()
{
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    int adjMat[n][n];
    printf("Enter adjacency matrix: \n");
    printf("[Note: Enter -1 to indicate infinity]\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);
    floyds(adjMat, n);
    printf("Shortest distance between all pair of nodes:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", dist[i][j]);
        printf("\n");
    }
}

void plotter()
{
    srand(time(NULL));
    FILE *fp = fopen("floydes.txt", "w");
    for (int k = 2; k < 12; k++)
    {
        n = k;
        int adjMat[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    adjMat[i][j] = rand();
                else
                    adjMat[i][j] = 0;
        floyds(adjMat, n);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }
    fclose(fp);
}

void main()
{
    int ch;
    printf("Enter\n1.Tester\n2.Plotter\n");
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
        printf("Invalid choice!! ");
    }
}

Output:
Enter the number of nodes: 3
Enter adjacency matrix: 
[Note: Enter -1 to indicate infinity]
0 3 -1
-1 0 1
-1 -1 0
Shortest distance between all pair of nodes:
0    3    4    
INF    0    1    
INF    INF    0    

  Here, INF represents an unreachable path.

# Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'floyds_plot.png'

# Set title and labels
set title "Floyd-Warshall Algorithm Performance"
set xlabel "Number of Nodes"
set ylabel "Operation Count"
set grid

# Set the key (legend) to be displayed outside the plot
set key outside

# Plot the data from the file
plot 'floydes.txt' using 1:2 with linespoints title 'Operation Count' lc rgb "blue"

  In terminal
gnuplot plot_floyds.gnu
