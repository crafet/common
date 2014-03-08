#include <iostream>


/**
  implementation for quick sort
  choose last element of the array as the pivot
  e.g
  arr = {7, 3, 8, 5, 2, 10, 5*}
  after first round partiton for element 5
  arr = {3, 5, 2, 5*, 8, 10, 7}
*/
void swap(int&, int&);
void print_array(int*, int);

int partition(int* arr, int left, int right)
{
	int key = arr[right];
	
	int curpos = left;//从第一个元素下标开始索引
	for (int i = left + 1; i < right; i++) {
		// we dont need to compare key with arr[right]
		if (arr[i] < key) {
			swap(arr[curpos], arr[i]);
			curpos++;
		}
	}
	swap(arr[curpos], arr[right]);

	print_array(arr, right - left + 1);
	return curpos;
}

void print_array(int* arr, int size)
{
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
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

void swap(int& left, int& right)
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
	std::cout << "original array  is :";
	print_array(arr, 7);
	int q = partition(arr, 0, 6);
	std::cout << "q is " << q << std::endl;
	quick_sort(arr, 0, 6);
	print_array(arr, 7);
	return 0;
}

