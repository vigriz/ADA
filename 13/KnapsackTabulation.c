#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int t[MAX][MAX], v[MAX], w[MAX], n, m, i, j, count = 0;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int Knap()
{
    for (i = 0; i < n + 1; i++)
    {
        for (j = 0; j < m + 1; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else
            {
                count++;
                if (j < w[i-1])
                    t[i][j] = t[i - 1][j];
                else
                    t[i][j] = max(t[i - 1][j], v[i-1] + t[i - 1][j - w[i-1]]);
            }
        }
    }
    return t[n][m];
}

void tester()
{
    printf("Number of items: ");
    scanf("%d", &n);
    printf("Sack capacity; ");
    scanf("%d", &m);
    printf("Weight\tValue\n");
    for (int i = 0; i < n; i++)
        scanf("%d%d", &w[i], &v[i]);
    printf("Max value %d\n", Knap());
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }
    printf("Composition:\n");
    for (int i = n; i > 0; i--)
    {
        if (t[i][m] != t[i - 1][m])
        {
            printf("%d\t", i);
            m = m - w[i-1];
        }
    }
    printf("\n");
}

void plotter()
{
    FILE *f1 = fopen("Knap.txt", "w");
    for (int iter = 1; iter <= 10; iter++)
    {
        count = 0;
        n = iter * 2;
        m = iter * 5;
        for (int i = 1; i <= n; i++)
        {
            w[i] = rand() % m + 1;
            v[i] = rand() % 50 + 1;
        }
        Knap();
        fprintf(f1, "%d\t%d\n", n, count);
    }
    fclose(f1);
}

int main()
{
    int ch;
    printf("Enter your choice:\n1.Tetser\n2.Plotter\n");
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
        printf("Invalid input\n");
    }
    return 0;
}

Output
Number of items: 3
Sack capacity: 5
Weight    Value
1         2
2         3
3         4

Max value 6
0 0 0 0 0 0 
0 2 2 2 2 2 
0 2 3 5 5 5 
0 2 3 5 5 6 
Composition:
3	1	

  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'knap_plot.png'

# Set title and labels
set title "Knapsack Problem Operation Count"
set xlabel "Number of Items"
set ylabel "Operation Count"
set grid

# Set the key (legend) to be displayed outside the plot
set key outside

# Plot the data from the file
plot 'Knap.txt' using 1:2 with linespoints title 'Operation Count' lc rgb "blue"

  In terminal
gnuplot plot_knap.gnu
