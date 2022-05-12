#include <stdio.h>
#include <stdlib.h>

int const n = 999;

int main()
{
    int arr[n];
    int maxCount = 1, maxIndex = -1, count;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand()%100;
    }

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

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

    if(maxIndex > -1)
        printf("Most frequent element is %d\n", arr[maxIndex]);
    else
        printf("No repeating elements");
    // sorting:
    double factor = 1.3;
    int step, temp, countOp;
    //int left, right;

    step = n / factor;
    countOp = 0;
    
/*
    while (step >= 1)
    {
        left = 0;
        right = n - 1;
        while (left < right)
        {
            for (int i = left; i + step < right; i++)
            {   
                if (arr[i] > arr[i + step])
                {
                    temp = arr[i];
                    arr[i] = arr[i + step];
                    arr[i + step] = temp;
                    countOp++;
                }
            }
            right--;
            for (int i = right; i - step > left; i--)
            {
                if (arr[i] < arr[i - step])
                {
                    temp = arr[i];
                    arr[i] = arr[i + step];
                    arr[i + step] = temp;
                    countOp++;
                }
            }
            left++;
        }
        
        step /= factor;
    }
    */
    
    while(step >= 1)
    {
        for (int i = 0; i + step < n; i++)
            {
                if (arr[i] > arr[i + step])
                {   temp = arr[i];
                    arr[i] = arr[i + step];
                    arr[i + step] = temp;
                    countOp++;
                }
            }
        step /= factor;
    }
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nAmount of operations: %d\n", countOp);

    return 0;
}