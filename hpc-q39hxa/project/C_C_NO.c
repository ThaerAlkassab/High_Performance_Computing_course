#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int w[100], p[100], v[100][100], n, i, j, cap, x[100] = {0};

int max(int i, int j) {
    return ((i > j) ? i : j);
}

int knap(int i, int j) {
    int value;
    if (v[i][j] < 0) {
        printf("\n I");
        if (j < w[i])
        {
            value = knap(i - 1, j);
            printf("\nV%d", value);
        }
        else
        {    
            value = max(knap(i - 1, j), p[i] + knap(i - 1, j - w[i]));
            printf("\nelseV%d", value);
        }    
        v[i][j] = value;
    }
    return (v[i][j]);
}

int main() {
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;
    int profit = 0, count = 0;

    printf("\nThe number of elements\n");
//    n = 100;
    scanf("%d", &n);

    printf("The profit and weights of the elements\n");
    for (i = 0; i < n; i++) {
        printf("For item no %d\n", i + 1);

        p[i] = rand() % 100 + 1; // Adjust the range as needed
        w[i] = rand() % 50 + 1; // Adjust the range as needed

        printf("%d\t%d\n", p[i], w[i]); // Use %d without the ampersand
    }

//    cap = 300;
    printf("\nThe capacity %d \n", cap);
    scanf("%d", &cap);
    
    start = clock();

    for (i = 0; i <= n; i++)
        for (j = 0; j <= cap; j++)
            if ((i == 0) || (j == 0))
                v[i][j] = 0;
            else
                v[i][j] = -1;

    profit = knap(n - 1, cap); // Adjust index to start from 0
    i = n - 1;
    j = cap;

    while (j != 0 && i != 0) {
        if (v[i][j] != v[i - 1][j]) {
            x[i] = 1;
            j = j - w[i];
            i--;
        } else
            i--;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Items included are\n");
    printf("Sl.no\tweight\tprofit\n");
    for (i = 0; i < n; i++) // Adjust index to start from 0
        if (x[i])
            printf("%d\t%d\t%d\n", ++count, w[i], p[i]);

    printf("Total profit = %d\n", profit);
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
