#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {

    int a[SIZE], i;
    long sum = 0;
    long sum2 = 0;
    double t1, t2;

    #pragma omp parallel shared(a) private(i)
    {
        #pragma omp for
        for (i = 0; i < SIZE; i++) {
            a[i] = i;
        }
    }

    t1 = omp_get_wtime();
    #pragma omp parallel shared(sum, a) private(i)
    {
        #pragma omp for
        for (i = 0; i < SIZE; i++) {
            
            #pragma omp critical 
            {
                sum += a[i];
            }
        }
    }
    
    t2 = omp_get_wtime();
    printf("1) Total sum = %ld, Total execution time = %lf\n", sum, (t2 - t1));

    sum = 0;

    t1 = omp_get_wtime();
    #pragma omp parallel reduction(+:sum) shared(a) private(i)
    {
        #pragma omp for
        for (i = 0; i < SIZE; i++) {
            sum += a[i];
        }
    }
    t2 = omp_get_wtime();

    printf("2)Total sum = %ld, Total execution time = %lf\n", sum, (t2 - t1));

    return 0;
}