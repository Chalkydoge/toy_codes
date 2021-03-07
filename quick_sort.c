#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int MOD = 1e9 + 7;
clock_t  start, finish;

int* generate_data(int amount){
    int* arr = (int*)malloc(sizeof(int) * amount);
    srand((unsigned)time(NULL));
    for(int i = 0; i < amount; ++i){
        int val = rand() % MOD;
        arr[i] = val;
    }
    return arr;
}

void print_data(int* arr, int amount){
    for(int i = 0; i < amount; ++i){
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int left, int right){
    srand((unsigned)time(NULL));
    int idx = rand() % (right - left + 1) + left;
    swap(&arr[left], &arr[idx]);
    int pivot = arr[left];
    int mid = left;
    int step = 8;
    int k;

    for(k = left + 1; k + step <= right; k += step){
        if(arr[k] < pivot){
            swap(&arr[++mid], &arr[k]);
        }
        if(arr[k + 1] < pivot){
            swap(&arr[++mid], &arr[k + 1]);
        }
        if(arr[k + 2] < pivot){
            swap(&arr[++mid], &arr[k + 2]);
        }
        if(arr[k + 3] < pivot){
            swap(&arr[++mid], &arr[k + 3]);
        }
        if(arr[k + 4] < pivot){
            swap(&arr[++mid], &arr[k + 4]);
        }
        if(arr[k + 5] < pivot){
            swap(&arr[++mid], &arr[k + 5]);
        }
        if(arr[k + 6] < pivot){
            swap(&arr[++mid], &arr[k + 6]);
        }
        if(arr[k + 7] < pivot){
            swap(&arr[++mid], &arr[k + 7]);
        }
    }

    for(; k <= right; ++k){
        if(arr[k] < pivot){
            swap(&arr[++mid], &arr[k]);
        }        
    }

    swap(&arr[left], &arr[mid]);
    return mid;
}

void quick_sort(int* arr, int left, int right){
    if(right - left <= 1){
        return;
    }
    // printf("%d\t%d\n", left, right);
    int mid = partition(arr, left, right - 1);
    quick_sort(arr, left, mid);
    quick_sort(arr, mid + 1, right);
}

void small_sample_test(int* ptr){
    ptr = generate_data(30);
    print_data(ptr, 30);
    printf("\n");
    quick_sort(ptr, 0, 30);
    print_data(ptr, 30);
    printf("\n");
}

int main(){
    int* ptr = NULL;
    printf("Quick Sort Test:\n");
    for(int count = 1; count <= 10; ++count){
        int N = count * 10000;
        ptr = generate_data(N);
        start = clock();
        quick_sort(ptr, 0, N);
        finish = clock();
        printf("%f,",
        (double)(1000.0 * (finish - start))/CLOCKS_PER_SEC);
        free(ptr);
    }
    // small_sample_test(ptr);
    return 0;
}