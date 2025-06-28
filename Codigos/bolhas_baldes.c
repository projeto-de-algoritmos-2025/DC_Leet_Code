#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strdup, embora não seja usado na solução final

long long *temp_arr; // Global para o merge sort

long long merge_and_count_inversions(int arr[], int left, int mid, int right) {
    long long inversions = 0;
    int i = left;     
    int j = mid + 1;  
    int k = left;     

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp_arr[k++] = arr[i++];
        } else {
            inversions += (mid - i + 1);
            temp_arr[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp_arr[k++] = arr[i++];
    }
    while (j <= right) {
        temp_arr[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp_arr[i];
    }
    return inversions;
}

long long count_inversions_merge_sort(int arr[], int left, int right) {
    long long inversions = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inversions += count_inversions_merge_sort(arr, left, mid);
        inversions += count_inversions_merge_sort(arr, mid + 1, right);
        inversions += merge_and_count_inversions(arr, left, mid, right);
    }
    return inversions;
}

int main() {
    int N;
    int *arr; 

    while (scanf("%d", &N) == 1 && N != 0) {
        arr = (int *)malloc(sizeof(int) * N);
        temp_arr = (long long *)malloc(sizeof(long long) * N);

        if (arr == NULL || temp_arr == NULL) {
            fprintf(stderr, "Erro de alocação de memória!\n");
            return 1;
        }

        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
        }
        
        long long total_inversions = count_inversions_merge_sort(arr, 0, N - 1);

        if (total_inversions % 2 == 0) {
            printf("Carlos\n"); // APENAS esta linha de saída para um caso
        } else {
            printf("Marcelo\n"); 
        }

        free(arr);
        free(temp_arr);
    }
    return 0;
}