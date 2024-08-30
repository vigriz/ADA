#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count1 = 0, count2;

void heapify(int *arr, int i, int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int maxIdx = i;

    if (left < size && ++count1 && arr[left] > arr[maxIdx])
    {
        maxIdx = left;
    }

    if (right < size && ++count1 && arr[right] > arr[maxIdx])
    {
        maxIdx = right;
    }

    if (maxIdx != i)
    {
        int temp = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx] = temp;

        heapify(arr, maxIdx, size);
    }
}

void heapSort(int *arr, int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(arr, i, n);
    }

    count2 = count1;
    count1 = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, 0, i);
    }
}

void tester()
{
    int n;
    printf("Enter array size : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements :\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    heapSort(&arr[0], n);
    printf("Sorted array :\n");
    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);
}

void plotter()
{
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("heapBest.txt", "w");
    f2 = fopen("heapWorst.txt", "w");
    f3 = fopen("heapAvg.txt", "w");

    int n = 100;

    while (n <= 1000)
    {
        int arr[n];

        for (int i = 0; i < n; i++)
            arr[i] = n - i + 1;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f1, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f2, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count1 = 0;
        heapSort(arr, n);
        fprintf(f3, "%d\t%d\n", n, count1 > count2 ? count1 : count2);

        n += 100;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
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
        printf("Invalid choice!");
    }
}

Output:
Enter array size : 
5
Enter 5 elements :
3 1 4 1 5
Sorted array :
1	1	3	4	5	

# Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'heap_combined_plot.png'

# Set title and labels
set title "Heap Sort Performance"
set xlabel "Array Size"
set ylabel "Operation Count"
set grid

# Set the key (legend) to be displayed outside the plot
set key outside

# Plot the data from the files
plot 'heapBest.txt' using 1:2 with linespoints title 'Best Case' lc rgb "blue", \
     'heapWorst.txt' using 1:2 with linespoints title 'Worst Case' lc rgb "red", \
     'heapAvg.txt' using 1:2 with linespoints title 'Average Case' lc rgb "green"
In terminal
  gnuplot plot_heap_combined.gnu

  
Aliter:
  //Cretaing 3 files here
  gedit plot_heap_best.gnu
  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'heap_best_plot.png'

# Set title and labels
set title "Heap Sort - Best Case Performance"
set xlabel "Array Size"
set ylabel "Operation Count"
set grid

# Plot the data from the file
plot 'heapBest.txt' using 1:2 with linespoints title 'Operation Count'

  gedit plot_heap_worst.gnu
  # Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'heap_worst_plot.png'

# Set title and labels
set title "Heap Sort - Worst Case Performance"
set xlabel "Array Size"
set ylabel "Operation Count"
set grid

# Plot the data from the file
plot 'heapWorst.txt' using 1:2 with linespoints title 'Operation Count'

  gedit plot_heap_avg.gnu
# Set the terminal to PNG with specific size
set terminal pngcairo size 800,600
set output 'heap_avg_plot.png'

# Set title and labels
set title "Heap Sort - Average Case Performance"
set xlabel "Array Size"
set ylabel "Operation Count"
set grid

# Plot the data from the file
plot 'heapAvg.txt' using 1:2 with linespoints title 'Operation Count'

  gnuplot plot_heap_best.gnu
gnuplot plot_heap_worst.gnu
gnuplot plot_heap_avg.gnu

