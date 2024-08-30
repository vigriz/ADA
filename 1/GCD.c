#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count = 0;

int gcdEuclid(int m, int n)
{
    count = 0;
    while (n != 0)
    {
        int temp = m % n;
        m = n;
        n = temp;
        count++;
    }

    return m;
}

int gcdConsecutiveIntegerCheck(int m, int n)
{
    count = 0;
    int t = m > n ? n : m;
    for (int i = t; i > 0; i--)
    {
        count++;
        if (m % i == 0)
        {
            count++;
            if (n % i == 0)
                return i;
        }
    }

    return m > n ? m : n;
}

int modifiedEuclids(int m, int n)
{
    if (n == 0 || m == 0)
        return m > n ? m : n;

    count = 0;

    while (++count && m != n)
    {
        if (m > n)
            m -= n;
        else
            n -= m;
    }

    return n;
}

void tester()
{
    int m, n;
    printf("Enter 2 numbers : ");
    scanf("%d%d", &m, &n);

    if (m < 0 && n < 0)
    {
        printf("Cannot find gcd...Invalid inputs...");
    }

    printf("gcd through euclid algorithm :%d\n", gcdEuclid(m, n));
    printf("gcd through consecutive checking method :%d\n", gcdConsecutiveIntegerCheck(m, n));
    printf("gcd through repeated subtraction method :%d\n", modifiedEuclids(m, n));
}

void plotter()
{
    FILE *f1 = fopen("euclidBest.txt", "w");
    FILE *f2 = fopen("euclidWorst.txt", "w");
    FILE *f3 = fopen("consecBest.txt", "w");
    FILE *f4 = fopen("consecWorst.txt", "w");
    FILE *f5 = fopen("modifiedBest.txt", "w");
    FILE *f6 = fopen("modifiedWorst.txt", "w");

    for (int i = 10; i <= 100; i += 10)
    {
        int min = INT_MAX, max = INT_MIN;
        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                gcdEuclid(j, k);
                if (count < min)
                    min = count;
                if (count > max)
                    max = count;
            }
        }
        fprintf(f1, "%d\t%d\n", i, min);
        fprintf(f2, "%d\t%d\n", i, max);
    }

    for (int i = 10; i <= 100; i += 10)
    {
        int min = INT_MAX, max = INT_MIN;
        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                gcdConsecutiveIntegerCheck(j, k);
                if (count < min)
                    min = count;
                if (count > max)
                    max = count;
            }
        }
        fprintf(f3, "%d\t%d\n", i, min);
        fprintf(f4, "%d\t%d\n", i, max);
    }

    for (int i = 10; i <= 100; i += 10)
    {
        int min = INT_MAX, max = INT_MIN;
        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                modifiedEuclids(j, k);
                if (count < min)
                    min = count;
                if (count > max)
                    max = count;
            }
        }
        fprintf(f5, "%d\t%d\n", i, min);
        fprintf(f6, "%d\t%d\n", i, max);
    }
}

void main()
{
    int ch;
    printf("\nEnter:\n1.Tester\n2.Plotter\n");
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
        printf("Invalid Choice!!");
    }
}

Output:
Enter:
1.Tester
2.Plotter
1
Enter 2 numbers : 36 24
gcd through euclid algorithm :12
gcd through consecutive checking method :12
gcd through repeated subtraction method :12


Enter:
1.Tester
2.Plotter
2
# plot_gcd.gnuplot

set terminal png size 800,600
set output 'gcd_plot.png'
set title "GCD Algorithm Comparisons"
set xlabel "Input Range"
set ylabel "Number of Steps"
set key outside

# Plotting the Euclid's algorithm
plot "euclidBest.txt" using 1:2 with lines title 'Euclid Best Case', \
     "euclidWorst.txt" using 1:2 with lines title 'Euclid Worst Case', \
     "consecBest.txt" using 1:2 with lines title 'Consecutive Best Case', \
     "consecWorst.txt" using 1:2 with lines title 'Consecutive Worst Case', \
     "modifiedBest.txt" using 1:2 with lines title 'Modified Best Case', \
     "modifiedWorst.txt" using 1:2 with lines title 'Modified Worst Case'

  Aliter:
  set title "GCD"
set xrange[0:11]
set yrange[0:100]
set xlabel "Particular pair of numbers"
set ylabel "Count"
set style data linespoints
plot 'gcd.dat' u 1:2 w lp,'gcd.dat' u 1:3 w lp,'gcd.dat' u 1:4 w lp

In terminal
gnuplot plot_gcd.gnuplot
