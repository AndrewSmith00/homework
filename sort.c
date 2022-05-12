#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int const n = 9999;

int main()
{
    int arr[n];
    int maxCount = 1, maxIndex = -1, count;
    clock_t start, stop;
    double duration;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
    }
    printf("\nUnsorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    //--------------------------------Find most frequent (stupid version)------------------------------

    start = clock();

    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = i; j < n; j++)
            if (arr[i] == arr[j])
                count++;

        if (maxCount < count)
        {
            maxCount = count;
            maxIndex = i;
        }
    }

    stop = clock();

    duration = (double)(stop - start) / CLOCKS_PER_SEC;

    if (maxIndex > -1)
        printf("Most frequent element is %d\nTime for unsorted array: %2.15f sec\n\n", arr[maxIndex], duration);
    else
        printf("No repeating elements\nTime for unsorted array: %2.15f sec\n\n", duration);

    // ----------------------------------Sorting:------------------------------------------------------

    start = clock();
    
    double factor;
    int step, temp, swapped;

    swapped = 1;
    step = n;
    factor = 1.3;

    while (step > 1 || swapped)
    {
        if (step > 1)
            step = step / factor;
        swapped = 0;

        for (int i = 0; i + step < n; i++)
        {
            if (arr[i] > arr[i + step])
            {
                temp = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = temp;
                swapped = 1;
            }
        }
        for (int i = n - 1; i - step >= 0; i--)
        {
            if (arr[i] < arr[i - step])
            {
                temp = arr[i];
                arr[i] = arr[i - step];
                arr[i - step] = temp;
                swapped = 1;
            }
        }
    }

    //----------------------------------------Find most frequent (cool version)-------------------------------

    int last, save;
    count = 1;
    maxCount = 1;

    last = arr[0];
    save = last;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] == last)
            count++;
        else
        {
            if (maxCount < count)
            {
                maxCount = count;
                save = last;
            }
            last = arr[i];
            count = 1;
        }
    }
    if (maxCount < count)
    {
        maxCount = count;
        save = last;
    }

    stop = clock();

    duration = (double)(stop - start) / CLOCKS_PER_SEC;

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    printf("Most frequent element is %d\nTime for sorted array:   %2.15f sec\n\n", save, duration);

    return 0;
}
