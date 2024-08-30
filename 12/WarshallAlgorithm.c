#include <stdio.h>
#include <stdlib.h>

int n, opcount, paths[100][100];

int warshall(int adjMat[n][n], int n)
{
    opcount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            paths[i][j] = adjMat[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (paths[i][k])
            {
                for (int j = 0; j < n; j++)
                {
                    opcount++;
                    paths[i][j] = paths[i][j] || (paths[i][k] && paths[k][j]);
                }
            }
}

void tester()
{
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    int adjMat[n][n];
    printf("Enter the adjacency matrix: \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);
    warshall(adjMat, n);
    printf("Transitive closure matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", paths[i][j]);
        printf("\n");
    }
}

void plotter()
{
    FILE *f1 = fopen("warshallbest.txt", "w");
    FILE *f2 = fopen("warshallworst.txt", "w");
    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                if (i != j)
                    adjMat[i][j] = 1;
                else
                    adjMat[i][j] = 0;
        warshall(adjMat, n);
        fprintf(f2, "%d\t%d\n", n, opcount);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;
        for (int i = 0; i < n - 1; i++)
            adjMat[i][i + 1] = 1;
        adjMat[n - 1][0] = 1;
        warshall(adjMat, n);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }
    fclose(f1);
    fclose(f2);
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
Enter the adjacency matrix:
0 1 0
0 0 1
1 0 0

  Transitive closure matrix:
1	1	1	
1	1	1	
1	1	1	

  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'warshall_combined_plot.png'

# Set title and labels
set title "Warshall's Algorithm Performance"
set xlabel "Number of Nodes"
set ylabel "Operation Count"
set grid

# Set the key (legend) to be displayed outside the plot
set key outside

# Plot the data from the files
plot 'warshallbest.txt' using 1:2 with linespoints title 'Best Case' lc rgb "blue", \
     'warshallworst.txt' using 1:2 with linespoints title 'Worst Case' lc rgb "red"
In terminal
gnuplot plot_warshall.gnu
