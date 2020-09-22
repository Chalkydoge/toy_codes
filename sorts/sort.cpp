#include <iostream>
#include <ctime>
#include <random>
#include <vector>
using std::default_random_engine;
using std::max;
using std::min;
using std::uniform_int_distribution;
using std::vector;

int test[100000];
int aud[100000];

int SW[12] = {1,5,19,41,109,209,505,929,2161,3905,8929,16001}; // Sedgewick sequence
int S[7] = {1,4,13,40,121,364,1093};
//9*4^k-9*2^k+1 or 4^k-3*2^k+1

// 0. 冒泡排序 [lo, hi]
template <typename T>
void bubble_sort(T* arr, const unsigned& left, const unsigned& right){
    using std::swap;
    for (unsigned i = left; i <= right; ++i){
        for (auto j = i; j <= right; ++j){
            if(arr[i] > arr[j]){
                swap(arr[i], arr[j]);
            }
        }
    }
}

// 1. 选择排序 [lo, hi]
template <typename T>
void selection_sort(T* arr, unsigned size){
    for (unsigned i = 0; i < size; ++i){
        unsigned min = i;
        for (unsigned j = i + 1; j < size; ++j){
            if(*(arr+j) < *(arr+min)){
                min = j;
            }
        }
        using std::swap;
        swap(*(arr + i), *(arr + min));
    }
}

// 2. 插入排序 [lo, hi]
template <typename T>
void insertion_sort(T* arr, unsigned size){
    for (unsigned i = 0; i < size; ++i){
        for (unsigned j = i; j > 0 && *(arr + j) < *(arr + j - 1); --j){
            using std::swap;
            swap(*(arr + j), *(arr + j - 1));
        }
    }
}

void generate_random_nums(int* arr, uint64_t num){
    static default_random_engine e1;
    static std::uniform_int_distribution<unsigned> u(0,1024);
    for (uint64_t i = 0; i < num; ++i){
        *(arr+i) = (u(e1));
    }
}

void generate_random_nums_for_heap(int* arr, uint64_t num){
    static default_random_engine e1;
    static std::uniform_int_distribution<unsigned> u(0,1024);
    *arr = 0;
    for (uint64_t i = 1; i <= num; ++i){
        *(arr+i) = (u(e1));
    }
}

// 3. 快速排序 [lo, hi)
	// pivot-x-x-x-x-x-x-x- x -x-x-x-x-x-x-x-
	//       -------L-------x-------G--------
	//	lo  mi'             mi              hi
	//       1 2 3 4 5 6 7  mi 1 2 3 4 5 6 7
	//       k->->->->->k->k->->...
	// if elem in L>pivot? swap it !
	// not? then it is part of L, leave it!

template<typename T>
unsigned partition(T* arr, unsigned left, unsigned right){
    using std::swap;
    swap(arr[left], arr[left + rand() % (right - left + 1)]);
    int pivot = arr[left];
    int mid = left;
    for(unsigned k = left + 1; k <= right; ++k){
        if(arr[k] < pivot){
            swap(arr[++mid], arr[k]);
        }
    }
    swap(arr[left], arr[mid]);
    return mid;
}

template<typename T>
unsigned partition(vector<T>& arr, unsigned left, unsigned right){
    using std::swap;
    swap(arr[left], arr[left + rand() % (right - left + 1)]);
    int pivot = arr[left];
    int mid = left;
    for(unsigned k = left + 1; k <= right; ++k){
        if(arr[k] < pivot){
            swap(arr[++mid], arr[k]);
        }
    }
    swap(arr[left], arr[mid]);
    return mid;
}

template<typename T>
void quick_sort(T* arr, unsigned left, unsigned right){
    if(right - left < 2)
        return;
    unsigned mid = partition<T>(arr, left, right - 1);
    quick_sort(arr, left, mid);
    quick_sort(arr, mid + 1, right);
}

template<typename T>
void quick_sort(vector<T>& arr, unsigned left, unsigned right){
    if(right - left < 2)
        return;
    unsigned mid = partition<T>(arr, left, right - 1);
    quick_sort(arr, left, mid);
    quick_sort(arr, mid + 1, right);
}

// 4. 归并排序 [lo, hi]
template<typename T>
void merge(T* arr, const unsigned& left, const unsigned& right){
    unsigned mid = (left + right) / 2;
    unsigned i = left, j = mid + 1;
    for (unsigned k = left; k <= right; ++k){
        aud[k] = arr[k]; // copy first
    }

    for (unsigned k = left; k <= right; ++k){
        if(i > mid){
            arr[k] = aud[j++];
        }
        else if(j > right){
            arr[k] = aud[i++];
        }
        else if(aud[i] < aud[j]){
            arr[k] = aud[i++];
        }
        else{
            arr[k] = aud[j++];
        }
    }
}

template<typename T>
void merge_sort(T* arr, const unsigned& left, const unsigned& right){
    if(left >= right)
        return;
    unsigned mid = (left + right) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, right);
}

// 5. Shell sort [lo, hi]
template<typename T>
void shell_sort(T* arr, const unsigned& left, const unsigned& right){
    unsigned len = 12;
    unsigned n = right - left + 1;

    for(int i = len - 1; i >= 0; --i){
        for(int j = SW[i]; j < static_cast<int>(n); ++j){
            //do the insertion a[i-h]->a[i-2h]...
			for(int k = j; (k >= SW[i]) && (arr[k] < arr[k - SW[i]]); k -= SW[i]){
                using std::swap;
                swap(arr[k],arr[k - SW[i]]);
			}
        }
	}
}

// 6. 桶排序
template<typename T>
void bucket_sort(T* arr, const unsigned& size){
    T l = 0;
    T r = 0;
    for (unsigned i = 0; i < size; ++i){
		if(l > arr[i]){
            l = arr[i];
        }
        if(arr[i] > r){
            r = arr[i];
        }
	}

	T delta = r - l;
	unsigned long long sz = static_cast<unsigned long long>((delta / size) + 1);
	vector<vector<T>> bucket(sz, vector<T>());

	for (unsigned i = 0; i < size; ++i){
		unsigned pos = (arr[i] - l)/ size;
		bucket[pos].push_back(arr[i]);
	}

	for (unsigned i = 0; i < sz; ++i){
		unsigned h = static_cast<unsigned>(bucket[i].size());
        quick_sort(bucket[i], 0, h);
    }

	unsigned index = 0;
	for(unsigned long long i = 0; i < sz; ++i){
        unsigned long long idx = bucket[i].size();
        for(unsigned long long j = 0; j < idx; ++j){
			arr[index++] = bucket[i][j];
		}
	}
}

// 7. 堆排序 Notice: indexes + 1
template<typename T>
void sink(T* arr, unsigned k, unsigned N){
    /* FIND THE RIGHT POSITION FOR arr[k] */
    while(2*k <= N){
        using std::swap;
        auto j = 2 * k;
        if(j < N && arr[j] < arr[j + 1]){
            j++;
        }
        if(arr[k] >= arr[j]){
            break;
        }
        swap(arr[k], arr[j]);
        k = j;
    }
}

template<typename T>
void heap_sort(T* arr, unsigned N){
    /* Heapify */
    for (auto k = N / 2; k >= 1; --k){
        sink(arr, k, N);
    }
    /* 1 2 3 ... N-1 N
    *    HEAP     ^ | SORTED
    *  1 2 3 ... N-1 N
    *    HEAP  ^ | SORTED
    *  ...
    *  TILL HEAP_SIZE == 1!
    */

    /* FIND MAX & EXCHANGE */
    while(N > 1){
        using std::swap;
        swap(arr[1], arr[N--]);
        sink(arr, 1, N);
    }
}


int main(){
    generate_random_nums(test, 100);
    // heap_sort<int>(test, 100);
    // bucket_sort(test, 100);
    // quick_sort(test, 0, 100);
    // merge_sort(test, 0, 99);
    // bubble_sort(test, 0, 99);
    // selection_sort(test, 100);
    // insertion_sort(test, 100);
    shell_sort(test, 0, 99);
    for (int i = 0; i < 99; ++i){
        std::cout << test[i] << ' ';
        if(i && i % 9 == 0)
            std::cout << '\n';
    }
    return 0;
}
