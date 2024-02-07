#include <iostream>
#define MAX_SIZE 10000
using namespace std;

void heapify(int arr[], int size, int i)
{
	int largest = i;
	int left = largest * 2 + 1;
	int right = largest * 2 + 2;

	if (left < size && arr[left] > arr[largest])
		largest = left;

	if (right < size && arr[right] > arr[largest])
		largest = right;

	if (largest != i)
	{
		swap(arr[largest], arr[i]);
		heapify(arr, size, largest);
	}
}
void heap(int arr[], int size)
{
	for (int i = (size - 1) / 2; i >= 0; i--)
	{
		heapify(arr, size, i);
	}

	for (int i = size - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void insert(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = key;
	}
}

void merge(int arr[], int left, int mid, int right)
{
	int tempA[MAX_SIZE];
	int left1 = left;	int right1 = mid;
	int left2 = mid + 1;	int right2 = right;
	int index = left1;
	while (left1 <= right1 && left2 <= right2)
	{
		if (arr[left1] < arr[left2]) {
			tempA[index] = arr[left1];
			left1++;
		}
		else
		{
			tempA[index] = arr[left2];
			left2++;
		}
		++index;
	}

	if (left2 > right2 && left1 <= right1)
	{
		for (; left1 <= right1; left1++, index++)
		{
			tempA[index] = arr[left1];
		}
	}
	
	if (left1 > right1 && left2 <= right2);
	{
		for (; left2 <= right2; left2++, index++)
		{
			tempA[index] = arr[left2];
		}
	}
	for (int i = left; i <= right; i++)
		arr[i] = tempA[i];
}

void mergeSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int loc_pivot(int arr[], int left, int right)
{
	int pivot = right;
	int swap_pos = -1;

	for (int j = 0; j <= right; j++)
	{
		if (arr[j] <= arr[pivot])
		{
			swap_pos++;
			if (swap_pos < pivot)	swap(arr[j], arr[swap_pos]);
		}
	}
	return swap_pos;
}

void quicksort(int arr[], int left, int right)
{
	int pivot;
	if (left < right)
	{
		pivot = loc_pivot(arr, left, right);
		if (left < pivot)	quicksort(arr, left, pivot - 1);
		if (right > pivot)	quicksort(arr, pivot + 1, right);
	}
}

int main()
{
	int arr[] = { 1,3,5,7,9,11,0,2,4,6,8,100};
	int N = sizeof(arr) / sizeof(arr[0]);

	quicksort(arr, 0, N-1);
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}