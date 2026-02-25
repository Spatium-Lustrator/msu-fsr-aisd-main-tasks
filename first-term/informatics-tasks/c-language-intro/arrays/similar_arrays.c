#include <stdio.h>

int removeDup(int *arr, int n) {
    if (n == 0) return 0;
  
    int j = 0;
    for (int i = 1; i < n; i++) {

        if (arr[i] != arr[j])
            arr[++j] = arr[i];
    }
  
    return j + 1;
}

void printarr(int *arr, int n) {

    int *a = arr;
    for (int i = 0; i<n; i++) {
        printf("%d ", a[i]);
    }
}

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

    int i=0, j=0, k=0, n1, n2, arr1[100000], arr2[100000], flag=0;
    int new_n1, new_n2;

    scanf("%d", &n1);
    for (i; i<n1; i++) {scanf("%d", &arr1[i]);}
    
    scanf("%d", &n2);
    for (j; j<n2; j++) {scanf("%d", &arr2[j]);}

    mergeSort(arr1, 0, n1-1);
    mergeSort(arr2, 0, n2-1);

    new_n1 = removeDup(arr1, n1);
    new_n2 = removeDup(arr2, n2);

    if (new_n1 == new_n2) {
        for (k; k<new_n1; k++) {
            if (arr1[k]!=arr2[k]) {
                flag = 1;
            }
        }

        if (flag) {
            printf("NO");
        } else {
            printf("YES");
        }
    } else {
        printf("NO");
    }




    return 0;
}