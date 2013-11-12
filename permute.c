#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int permute_inner(int *array, int *flags, int *result, int size, int index);
int permute(int *array, int arraySize);


int permute(int *array, int arraySize)
{
	const int bufferSize = sizeof(int) * arraySize;
	int *pResults = (int*)malloc(bufferSize);
	int *pFlags = (int*)malloc(bufferSize);
	int sum = 0;

	if (arraySize <= 0)
		return 0;

	memset((void*)pResults, 0, bufferSize);
	memset((void*)pFlags, 0, bufferSize);

	sum = permute_inner(array, pFlags, pResults, arraySize, arraySize - 1);

	free(pResults);
	free(pFlags);

	return sum;
}

int permute_inner(int *array, int *flags, int *result, int size, int index)
{
	int i = 0, sum = 0;
	if (index == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (0 == flags[i])
			{
				result[0] = array[i];
				break;
			}
		}

		for (i = 0; i < size; i++)
			printf("%8d", result[i]);

		printf("\n");
		return 1;
	}
	for (i = 0; i < size; i++)
	{
		if (flags[i])
			continue;

		result[index] = array[i];
		flags[i] = 1;
		sum += permute_inner(array, flags, result, size, index - 1);
		flags[i] = 0;
	}
	return sum;
}

int main()
{
	int array[] = {1, 2, 3, 4};
	int sum = 0;
	printf("permutation of array is:\n");
	sum = permute(array, sizeof(array) / sizeof(array[0]));
	printf("permutation count is: %d\n", sum);
	return 0;
}
