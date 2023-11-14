#include <iostream>
#include <vector>
#include <algorithm>

int partition(int low, int high, std::vector<int>& arr) {
	int pivot = arr[low];
	int i = low + 1;
	int j = high;
	while (true) {
		while (i <= j && arr[i] <= pivot) {
			i++;
		}
		while (i <= j && arr[j] > pivot) {
			j--;
		}
		if (i >= j) {
			break;
		}
		std::swap(arr[i], arr[j]);
	}
	std::swap(arr[low], arr[j]);
	return j;
}

void quickSort(std::vector<int>& arr, int low, int high) {
	if (low < high) {
		int p = partition(low, high, arr);
		quickSort(arr, low, p - 1);
		quickSort(arr, p + 1, high);
	}
}

int main() {
	std::vector<int> arr = { 6,5,8,9,3,10,15,12,16 };
	int high = arr.size() - 1;

	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << "\n";
	}

	std::cout << "Now for the sorted half \n";
	quickSort(arr, 0, high);
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << "\n";
	}

	return 0;
}