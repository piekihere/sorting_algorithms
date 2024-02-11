#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fill_random(int *A, int n){
    srand(time(0));
    for (int i = 0; i < n; i++){
        A[i] = (rand() % (n + 1));

    }

}

void fill_increasing(int *A, int n){
    for (int i = 0; i < n; i++){
        A[i] = i;
    }
}

void fill_decreasing(int *A, int n){
    for (int i = 0; i < n; i++){
        A[i] = n-i-1;
    }
}

void fill_vshaped(int *A, int n){
    for (int i = 0; i < n/2; i++)
    {
        A[i]=n-i-1;
        A[n-i-1]=n-i-1;
    }
}

void print_array(int *A, int n){
    for (int i = 0; i < n; i++){
        printf("%d, ", A[i]);
    }
    printf("\n");
}

int arg_min(int *A, int begin, int end){
    int argmin = begin;
    for (int i = begin; i < end; i++){
        if (A[i]<A[argmin]){
            argmin = i;
        }
    }
    return argmin;
}

void swap(int *A, int i, int j){
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void selection_sort(int *A, int n){
    int j;
    for (int i = 0; i < n; i++)
    {
        j = arg_min(A, i, n);
        swap(A,i,j);
    }
    
}

void bubble_sort(int *A, int n){
    for (int i = 0; i < n; i++){
        for (int j = n-1; j > i; j--){
            if (A[j]<A[j-1]){
                swap(A, j, j-1);
            }
        }
    }
    
}

void shell_sort(int *A, int n, int *H, int t){
    int h;
    int key;
    int i;
    for (int s = t-1; s >= 0; s--){
        h = H[s];
        for (int j = h; j < n; j++){
            key = A[j];
            i = j - h;
            while (i>=0 && A[i]>key){
                A[i+h]<A[i];
                i = i -h;
            }
            A[i+h] = key;
        }
    }
}

int *shell_sort_increment(int n, int t){
    int *tmp = malloc(t * sizeof(int));
    int h = 1;
    int i = 0;
    while (h < n){
        tmp[i] = h;
        h = 3*h+1;
        i++;
    }
    int *H = malloc(i *sizeof(int));
    for (int t = 0; t < i; t++)
    {
        H[t] = tmp[i-t-1];
    }
    free(tmp);
    return H;
}

int partition(int *A, int p, int r){
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r; j++){
        if (A[j] < x){
            i++;
            swap(A, i, j);
        }
    }
    i++;
    swap(A, i, r);
    return i;
}

void quicksort(int *A, int p, int r){
    int q;
    if (p < r){
        q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

int randomized_partition(int *A, int p, int r){
    srand(time(0));
    int i = (rand() % (r - p + 1)) + p;
    swap(A, i, r);
    return partition(A, p, r);
}

void randomized_quicksort(int *A, int p, int r){
    int q;
    if(p < r){
        q = randomized_partition(A, p ,r);
        randomized_quicksort(A, p, q-1);
        randomized_quicksort(A, q+1, r);
    }
}

int left(int i){
    return 2*i+1;
}

int right(int i){
    return 2*i+2;
}

void max_heapify(int *A, int i, int n){
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < n && A[l]>A[largest]){
        largest = l;
    }
    
    if (r < n && A[r]>A[largest]){
        largest = r;
    }

    if (largest != i){
        swap(A, i, largest);
        max_heapify(A, largest, n);
    }
}

void build_max_heap(int *A, int n){
    for(int i = n/2; i >= 0; i--){
        max_heapify(A, i, n);
    }
}

void heapsort(int *A, int n){
    build_max_heap(A, n);
    for (int i = n-1; i > 0; i--){
        swap(A, 0, i);
        max_heapify(A, 0, i);
    }
}

void merge(int *A, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = malloc((n1)* sizeof(int));
    int *R = malloc((n2)* sizeof(int));

    for (int i = 0; i < n1; i++){
        L[i] = A[p+i];
    }
    for (int i = 0; i < n2; i++){
        R[i] = A[q+1+i];
    }
    
    int i = 0;
    int j = 0;
    int k = p;

    while (i<n1 && j < n2){
        if(L[i]<=R[j]){
            A[k] = L[i];
            i++;
        }else{
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int *A, int p, int r){
    int q;
    if (p < r){
        q = (p+r)/2;
        mergesort(A, p, q);
        mergesort(A, q+1, r);
        merge(A, p, q, r);
    }
    
}

void countingsort(int *A, int *B, int k, int n){
    int *C = calloc(k, sizeof(int));
    for (int j = 0; j < n; j++){
        C[A[j]] = C[A[j]] +1;
    }
    for (int i = 1; i <= k; i++){
        C[i] = C[i] + C[i-1];
    }
    for(int j = n-1; j>=0; j--){
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] -1;
    }  
}


int main(){
    int n = 100;
    int *A=malloc(n * sizeof(int));

    fill_random(A, n);
    print_array(A, n);
    //shell_sort(A, n, shell_sort_increment(n, 20), 20);
    //quicksort(A, 0, n-1);
    //randomized_quicksort(A, 0, n-1);
    //heapsort(A, n);
    //mergesort(A, 0, n-1);
    //print_array(A, n);

    int *B=malloc(n * sizeof(int));
    countingsort(A, B, 99, n);
    print_array(B, n);
    

    printf("\n");
    

    free(B);
    free(A);
    return 0;
}