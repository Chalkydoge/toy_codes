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

void bubble_sort(int* arr, int amount){
    start = clock();
    for(int i = 0; i < amount; ++i){
        for(int j = i + 1; j < amount; ++j){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    finish = clock();
    printf("%f,", (double)(1000.0 * (finish - start))/CLOCKS_PER_SEC);
}

int main(){
    int* ptr = NULL;
    printf("Bubble Sort Test:\n");
    for(int count = 1; count <= 10; ++count){
        int N = count * 10000;
        ptr = generate_data(N);
        bubble_sort(ptr, N);
        free(ptr);
    }
    return 0;
}