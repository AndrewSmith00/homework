#include <stdio.h>
#include <stdlib.h>

int const n = 999;

int main()
{
	int arr[n];
	int maxCount = 1, maxIndex = -1, count;

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
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

	if (maxIndex > -1)
		printf("Most frequent element is %d\n", arr[maxIndex]);
	else
		printf("No repeating elements\n");

	// sorting:
	double factor;
	int step, temp, left, right, control, swapped;

	swapped = 1;
	step = n;
	left = 0;
	right = n - 1;
	factor = 1.3;

	while (step > 1 || swapped)
	{
		if (step > 1)
			step = step / factor;
		swapped = 0;


		for (int i = left; i + step <= right; i++)
		{
			control = right;
			if (arr[i] > arr[i + step])
			{
				temp = arr[i];
				arr[i] = arr[i + step];
				arr[i + step] = temp;
				swapped = 1;
				control = i;
			}
		}
		control = right;

		for (int i = right; i - step >= left; i--)
		{
			control = left;
			if (arr[i] < arr[i - step])
			{
				temp = arr[i];
				arr[i] = arr[i - step];
				arr[i - step] = temp;
				swapped = 1;
				control = i;
			}
		}
		left = control;
	}

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}
