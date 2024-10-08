#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

void merge(int *arr, int beg, int mid, int end)
{
    int i, j, k;
    int n1 = (mid - beg) + 1;
    int n2 = end - mid;
    int left[n1], right[n2];
    for (int i = 0; i < n1; i++)
        left[i] = arr[beg + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + j + 1];
    i = 0;
    j = 0;
    k = beg;
    while (i < n1 && j < n2)
    {
        count++;
        if (left[i] <= right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
        k++;
    }
    while (i < n1)
    {
        arr[k++] = left[i++];
    }
    while (j < n2)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        mergeSort(arr, beg, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, beg, mid, end);
    }
}

void worst(int arr[], int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        int i, j, k;
        int n1 = (mid - beg) + 1;
        int n2 = end - mid;
        int a[n1], b[n2];
        for (i = 0; i < n1; i++)
            a[i] = arr[(2 * i)];
        for (j = 0; j < n2; j++)
            b[j] = arr[(2 * j) + 1];
        worst(a, beg, mid);
        worst(b, mid + 1, end);
        for (i = 0; i < n1; i++)
            arr[i] = a[i];
        for (j = i; j < n2; j++)
            arr[j + 1] = b[j];
    }
}

void tester()
{
    int *arr, n;
    printf("Enter the number of elements\n");
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("The elments of array before sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    mergeSort(arr, 0, n - 1);
    printf("The elements of the array after sorting :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void plotter()
{
    int *arr, n;
    srand(time(NULL));
    FILE *f1, *f2, *f3, *f4;
    f1 = fopen("Mergebest.txt", "w");
    f2 = fopen("Mergeworst.txt", "w");
    f3 = fopen("Mergeavg.txt", "w");
    f4 = fopen("Worstdata.txt", "w");
    for (n = 2; n <= 1024; n = n * 2)
    {
        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            *(arr + i) = i + 1;
        count = 0;
        mergeSort(arr, 0, n - 1); // best case
        fprintf(f1, "%d\t%d\n", n, count);
        count = 0;
        worst(arr, 0, n - 1);
        for (int i = 0; i < n; i++)
            fprintf(f4, "%d", *(arr + i));
        fprintf(f4, "\n");
        mergeSort(arr, 0, n - 1); // worst case
        fprintf(f2, "%d\t%d\n", n, count);
        for (int i = 0; i < n; i++)
            *(arr + i) = rand() % n;
        count = 0;
        mergeSort(arr, 0, n - 1);
        fprintf(f3, "%d\t%d\n", n, count);
        free(arr);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    printf("Data is entered into file\n");
}

void main()
{
    int ch;
    printf("Enter your choice: \n\n1.Tester\n2.Plotter\n\n");
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
        printf("Invalid choice!!!\n\n");
    }
}

Output:
Enter the number of elements
5
Enter the array elements:
3 1 4 1 5
The elements of array before sorting:
3 1 4 1 5 
The elements of the array after sorting:
1 1 3 4 5 
# Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'merge_sort_plot.png'

# Set title and labels
set title "Merge Sort Performance"
set xlabel "Number of Elements"
set ylabel "Number of Comparisons"
set logscale x 2
set grid

# Plot the data from the files
plot 'Mergebest.txt' using 1:2 with linespoints title 'Best Case', \
     'Mergeworst.txt' using 1:2 with linespoints title 'Worst Case', \
     'Mergeavg.txt' using 1:2 with linespoints title 'Average Case'
In terminal
gnuplot plot.gnu
