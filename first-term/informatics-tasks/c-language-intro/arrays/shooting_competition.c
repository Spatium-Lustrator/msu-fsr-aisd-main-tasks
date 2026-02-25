#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
    
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {

    int n=0, i=0, max_index=0, tmp=0, place=0;
    int arr[100000];

    scanf("%d", &n);
    for (i; i<n; i++) scanf("%d", &arr[i]);

    for (i=1; i<n-1; i++) {
        if (arr[max_index] < arr[i]) {
            max_index = i;
            tmp = 0;
        } else if ( (arr[i]%10 == 5) && (arr[i]>arr[i+1]) && (arr[i]>tmp)) {
            tmp = arr[i];
        }
    }

    mergeSort(arr, 0, n-1);
    i = n -1;
    while ((arr[i] != tmp) && (i>-1)) {i--;}

    if (i == -1) {
        printf("0");
    } else {
        printf("%d", n-i);
    }





    return 0;
}