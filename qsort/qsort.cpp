#include <iostream>


/**
  implementation for quick sort
  choose last element of the array as the pivot
  e.g
  arr = {7, 3, 8, 5, 2, 10, 5*}
  after first round partiton for element 5
  arr = {3, 5, 2, 5*, 8, 10, 7}
*/
void swap(int, int);

int partition(int* arr, int left, int right)
{
	int key = arr[right];
	int i = 0;
	int small = i - 1;
	for (i = 0; i < right; i++) {
		// we dont need to compare key with arr[right]
		if (arr[i] <= key) {
			small++;
			swap(arr[small], arr[i]);
		}
		swap(arr[i + 1], key);
	}

	return i + 1;
}

int quick_sort(int*arr, int left, int right)
{
	if (left < right) {
		int q = partition(arr, left, right);
		quick_sort(arr, left, q - 1);
		quick_sort(arr, q + 1, right);
	}
	return 0;
}

void swap(int left, int right)
{
	int tmp = left;
	left = right;
	right = tmp;
}

/**
  main test
*/

int main(int argc, char** argv)
{
	int arr[] = {7, 3, 8, 5, 2, 10, 5};

	quick_sort(arr, 0, 6);
	return 0;
}
