#include <stdio.h>
#include <stdlib.h>

static long long *temp_merge_arr;


static long long count_split_reverse_pairs(int nums[], int left, int mid, int right) {
    long long count = 0;
    int j = mid + 1; // Ponteiro para a metade direita

    // Itera sobre a metade esquerda
    for (int i = left; i <= mid; i++) {
        // Para cada elemento nums[i] da metade esquerda,
        // avança o ponteiro 'j' na metade direita enquanto a condição nums[i] > 2 * nums[j] for verdadeira.
        // Converte para long long para evitar overflow na multiplicação 2 * nums[j],
        while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
            j++;
        }
        // O número de elementos que satisfazem a condição para nums[i] é (j - (mid + 1)).
        // (mid + 1) é o início da metade direita.
        count += (j - (mid + 1));
    }
    return count;
}

/*
 *  nums O array original.
 *  left O índice inicial da primeira sub-lista.
 *  mid O índice do meio.
 * right O índice final da segunda sub-lista.
 */
static void merge_arrays(int nums[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp_merge_arr[k++] = nums[i++];
        } else {
            temp_merge_arr[k++] = nums[j++];
        }
    }

    while (i <= mid) {
        temp_merge_arr[k++] = nums[i++];
    }

    while (j <= right) {
        temp_merge_arr[k++] = nums[j++];
    }

    // Copia os elementos de volta para o array original
    for (i = left; i <= right; i++) {
        nums[i] = temp_merge_arr[i];
    }
}

/* nums O array de inteiros.
 * left O índice inicial da sub-array atual.
 * right O índice final da sub-array atual.
 * retorna O número total de pares inversos na sub-array nums[left...right].
 */
static long long merge_sort_and_count_reverse_pairs_recursive(int nums[], int left, int right) {
    long long reverse_pairs = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        // 1. Conquistar: Contar pares inversos nas sub-listas esquerda e direita
        reverse_pairs += merge_sort_and_count_reverse_pairs_recursive(nums, left, mid);
        reverse_pairs += merge_sort_and_count_reverse_pairs_recursive(nums, mid + 1, right);

        // 2. Contar pares inversos entre as duas sub-listas (left_half e right_half)
     
        reverse_pairs += count_split_reverse_pairs(nums, left, mid, right);

        // 3. Mesclar: Ordenar as duas sub-listas para que a próxima chamada recursiva.
        merge_arrays(nums, left, mid, right);
    }
    return reverse_pairs;
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return 0;
    }

   
    temp_merge_arr = (long long *)malloc(sizeof(long long) * numsSize);
    if (temp_merge_arr == NULL) {
  
        return 0; 
    }

    long long total_reverse_pairs = merge_sort_and_count_reverse_pairs_recursive(nums, 0, numsSize - 1);

    free(temp_merge_arr);
    temp_merge_arr = NULL; 

    return (int)total_reverse_pairs;
}