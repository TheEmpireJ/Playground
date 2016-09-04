// Playground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// prints an array of ints, of size ArraySize
void PrintIntArry(int* InputArray, int ArraySize)
{
	std::cout << "{ ";
	for (int i = 0; i < ArraySize; i++)
	{
		std::cout << InputArray[i] << ", ";
	}
	std::cout << " }" << std::endl;
}

// returns the pivot position
int Partition(int* InputArray, int ArraySize)
{
	// choosing the last element in the array as a pivot
	int pivot = InputArray[ArraySize - 1];
	
	int lowIndex = -1; // -1 because we pre-increment
	int highIndex = ArraySize - 1; // again, we pre-decrement the highIndex

	/* do
	{ 
		if (InputArray[lowIndex] > pivot)
		{
			if (InputArray[highIndex] < pivot)
			{
				std::swap(InputArray[lowIndex], InputArray[highIndex]);
			}
			else
			{
				highIndex--;
			}
		}
		else 
		{
			lowIndex++;
		}
	} while (lowIndex < highIndex);

	std::swap(InputArray[ArraySize - 1], InputArray[lowIndex]); */

	while(true)
	{
		do { lowIndex++; } while (InputArray[lowIndex] < pivot);
		do { highIndex--; } while (highIndex > 0 && InputArray[highIndex] > pivot);

		if (lowIndex >= highIndex)
		{
			break;
		}
		else
		{
			std::swap(InputArray[lowIndex], InputArray[highIndex]);
		}
	}
	std::swap(InputArray[ArraySize - 1], InputArray[lowIndex]);

	return lowIndex;
}

// sorts an int array
void Quicksort(int* InputArray, int ArraySize)
{
	if (ArraySize <= 1) { return; }

	int PivotIndex = Partition(InputArray, ArraySize);

	Quicksort(InputArray, PivotIndex);
	Quicksort(&InputArray[PivotIndex + 1], ArraySize - PivotIndex - 1);
}

void Mergesort(int* InputArray, int ArraySize)
{
	/// base case
	if (ArraySize <= 1) { return; }

	/// split the array
	int splitIndex = (ArraySize - 1) / 2;

	int* leftArray = InputArray;
	int leftArraySize = splitIndex + 1;

	int* rightArray = &InputArray[splitIndex + 1];
	int	rightArraySize = ArraySize - splitIndex - 1;

	/// mergesort each side
	Mergesort(leftArray, leftArraySize);
	Mergesort(rightArray, rightArraySize);

	int l = 0;
	int r = 0; // left and right array indexes

	/// merge the results
	// TODO extract the merge to a function
	int* temp = new int[ArraySize];
	for (int i = 0; i < ArraySize; i++)
	{
		if (l >= leftArraySize) // nothing left in the left array, so pull from right
		{
			temp[i] = rightArray[r];
			r++;
		} 
		else if (r >= rightArraySize) // nothing left in the right array, so pull from left
		{
			temp[i] = leftArray[l];
			l++;
		}
		else if (leftArray[l] < rightArray[r]) // pull the smallest element from the arrays
		{
			temp[i] = leftArray[l];
			l++;
		}
		else
		{
			temp[i] = rightArray[r];
			r++;
		}
	}

	/// copy the temp array back over the original
	for (int i = 0; i < ArraySize; i++)
	{
		InputArray[i] = temp[i];
	}

	delete temp;
	return;
}



int main()
{
	const int ARRAY_SIZE = 20;

	int Array[ARRAY_SIZE] = { 20, 1, 45, 38, 27, 3, 90, 45, 78, 77, 22, 34, 56, 70, 11, 49, 66, 83, 99, 51 }; // randomness
	//int Array[ARRAY_SIZE] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 }; // already sorted
	//int Array[ARRAY_SIZE] = { 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 }; // reverse sorted
	//int Array[ARRAY_SIZE] = { 1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5 }; // many same elements

	std::cout << "Initial Array:" << std::endl;
	PrintIntArry(Array, ARRAY_SIZE);

	// Quicksort(Array, ARRAY_SIZE);
	Mergesort(Array, ARRAY_SIZE);

	std::cout << std::endl << "Sorted Array:" << std::endl;
	PrintIntArry(Array, ARRAY_SIZE);

	return 0;
}