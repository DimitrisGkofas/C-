#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
	int output[n];
    int count[2] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 2]++;
	count[1] += count[0];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 2] - 1] = arr[i];
        count[(arr[i] / exp) % 2]--;
    }
	for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp <<= 1)
        countSort(arr, n, exp);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
}

int main() {
    srand(time(NULL));
    int arr[32];
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++)
        arr[i] = rand()%1024;
    radixSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
	return 0;
}