#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

int linearSearch(int *a, int n, int k)
{
    int i;
    count = 0;
    for (i = 0; i < n; i++)
    {
        count++;
        if (a[i] == k)
        {
            return i;
        }
    }
    return -1;
}

void tester()
{
    int *arr, n, key, ch, ans;
    printf("\nEnter array size: ");
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    printf("\nEnter array elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", (arr + i));
    }
    printf("\nEnter key to be searched : ");
    scanf("%d", &key);
    ans = linearSearch(arr, n, key);
    if (ans == -1)
        printf("\nKey not found! %d\n", ans);
    else
        printf("\nKey found at %d index\n", ans);
}

void plotter()
{
    srand(time(NULL));
    int *arr;
    int n, key, r;
    FILE *f1, *f2, *f3;
    f1 = fopen("linearbest.txt", "w");
    f2 = fopen("linearavg.txt", "w");
    f3 = fopen("linearworst.txt", "w");
    n = 2;
    while (n <= 1024)
    {
        arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            *(arr + i) = 1;
        r = linearSearch(arr, n, 1);
        fprintf(f1, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
            *(arr + i) = rand() % n;
        key = rand() % n;
        r = linearSearch(arr, n, key);
        fprintf(f2, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
            *(arr + i) = 0;
        r = linearSearch(arr, n, 1);
        fprintf(f3, "%d\t%d\n", n, count);
        n = n * 2;
        free(arr);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void main()
{
    int ch;
    printf("Enter your choice:\n\n1.Tester\n2.Plotter\n");
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
        printf("Invalid choice!!!\n");
    }
}

Output:
Enter your choice:

1.Tester
2.Plotter
1

Enter array size: 5

Enter array elements: 3 7 2 9 5

Enter key to be searched : 9
Key found at 3 index
Enter your choice:

1.Tester
2.Plotter
2
# plot_linear_search.gnuplot

set terminal png size 800,600
set output 'linear_search_plot.png'
set title "Linear Search Performance"
set xlabel "Array Size (n)"
set ylabel "Number of Comparisons"
set logscale x 2
set key outside

# Plotting Linear Search Best, Average, and Worst Cases
plot "linearbest.txt" using 1:2 with lines title 'Best Case', \
     "linearavg.txt" using 1:2 with lines title 'Average Case', \
     "linearworst.txt" using 1:2 with lines title 'Worst Case'
In terminal
    gnuplot plot_linear_search.gnuplot
