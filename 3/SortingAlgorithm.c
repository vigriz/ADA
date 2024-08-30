#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;
int bubblesort(int *a, int n)
{
    count = 0;
    int i, j, t, flag = 0;
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            count++;
            if (a[j] > a[j + 1])
            {
                t = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = t;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    return count;
}

void insertionSort(int *arr, int n)
{
    count = 0;
    for (int i = 1; i < n; i++)
    {
        int val = arr[i];
        int j = i - 1;
        while (++count && arr[j] > val)
        {
            arr[j + 1] = arr[j];
            j--;
            if (j < 0)
                break;
        }
        arr[j + 1] = val;
    }
}

void selectionSort(int *arr, int n)
{
    count = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int pos = i;
        for (int j = pos + 1; j < n; j++)
        {
            count++;
            if (arr[pos] > arr[j])
                pos = j;
        }
        if (pos != i)
        {
            int temp = arr[pos];
            arr[pos] = arr[i];
            arr[i] = temp;
        }
    }
}

void plotter1()
{
    int *arr, n;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("Bubblebest.txt", "w");
    f2 = fopen("Bubbleworst.txt", "w");
    f3 = fopen("Bubbleavg.txt", "w");
    n = 10;
    while (n <= 30000)
    {
        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = n - i;
        }
        bubblesort(arr, n); // worst case
        fprintf(f2, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = i + 1;
        }
        bubblesort(arr, n); // best case
        fprintf(f1, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = rand() % n;
        }
        bubblesort(arr, n); // average case
        fprintf(f3, "%d\t%d\n", n, count);
        if (n < 10000)
            n *= 10;
        else
            n += 10000;
        free(arr);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void plotter2()
{
    int *arr, n;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("Insertionbest.txt", "w");
    f2 = fopen("Insertionworst.txt", "w");
    f3 = fopen("Insertionavg.txt", "w");
    n = 10;
    while (n <= 30000)
    {
        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = n - i;
        }
        insertionSort(arr, n); // worst case
        fprintf(f2, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = i + 1;
        }
        insertionSort(arr, n); // best case
        fprintf(f1, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = rand() % n;
        }
        insertionSort(arr, n); // average case
        fprintf(f3, "%d\t%d\n", n, count);
        if (n < 10000)
            n *= 10;
        else
            n += 10000;
        free(arr);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void plotter3()
{
    FILE *f;
    f = fopen("selectionsort.txt", "w");
    int j;
    int n = 10;
    while (n <= 30000)
    {
        int *a = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            *(a + i) = i;
        count = 0;
        selectionSort(a, n);
        fprintf(f, "%d\t%d\n", n, count);
        if (n < 10000)
            n *= 10;
        else
            n += 10000;
        free(a);
    }
}

void main()
{
    int *arr, n, ch, f;
    printf("Enter \n1.Tester\n2.Plotter\n");
    scanf("%d", &f);
    if (f == 1)
    {
        printf("\nEnter array size: ");
        scanf("%d", &n);
        arr = (int *)malloc(n * sizeof(int));
        printf("Enter the array elements: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", (arr + i));
        }
        printf("\nEnter \n1. Bubble sort\n2. Insertion Sort.\n3. Selection Sort\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            bubblesort(arr, n);
            printf("\nArray after bubble sort:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", *(arr + i));
            }
            break;
        case 2:
            insertionSort(arr, n);
            printf("\nArray after insertion sort:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", *(arr + i));
            }
            break;
        case 3:
            selectionSort(arr, n);
            printf("\nArray after selection sort:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", *(arr + i));
            }
            break;
        default:
            printf("Invaid choice! ");
        }
        printf("\n");
        free(arr);
    }
    else if (f == 2)
    {
        printf("\nEnter \n1. Bubble sort\n2. Insertion Sort.\n3. Selection Sort\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            plotter1();
            break;
        case 2:
            plotter2();
            break;
        case 3:
            plotter3();
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

Output:
Enter 
1.Tester
2.Plotter
1

Enter array size: 5
Enter the array elements: 4 3 2 5 1

Enter 
1. Bubble sort
2. Insertion Sort.
3. Selection Sort
Enter your choice: 1
Array after bubble sort:
1 2 3 4 5 
Enter 
1.Tester
2.Plotter
2

Enter 
1. Bubble sort
2. Insertion Sort.
3. Selection Sort
Enter your choice: 1

  # plot_sorting_algorithms.gnuplot

set terminal png size 800,600
set output 'sorting_algorithms_plot.png'
set title "Sorting Algorithms Performance"
set xlabel "Array Size (n)"
set ylabel "Number of Comparisons"
set logscale x 2
set key outside

# Plotting Bubble Sort
set style data lines
set style line 1 lc rgb 'blue' lw 2
set style line 2 lc rgb 'red' lw 2
set style line 3 lc rgb 'green' lw 2

# Bubble Sort
plot "Bubblebest.txt" using 1:2 with lines title 'Bubble Sort Best Case' ls 1, \
     "Bubbleavg.txt" using 1:2 with lines title 'Bubble Sort Average Case' ls 2, \
     "Bubbleworst.txt" using 1:2 with lines title 'Bubble Sort Worst Case' ls 3

# Insertion Sort
set output 'insertion_sort_plot.png'
set title "Insertion Sort Performance"
plot "Insertionbest.txt" using 1:2 with lines title 'Insertion Sort Best Case' ls 1, \
     "Insertionavg.txt" using 1:2 with lines title 'Insertion Sort Average Case' ls 2, \
     "Insertionworst.txt" using 1:2 with lines title 'Insertion Sort Worst Case' ls 3

# Selection Sort
set output 'selection_sort_plot.png'
set title "Selection Sort Performance"
plot "selectionsort.txt" using 1:2 with lines title 'Selection Sort' ls 1

gnuplot plot_sorting_algorithms.gnuplot
