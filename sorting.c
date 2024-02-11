#include <stdio.h>
#include <stdlib.h>


void fill_random(int *A, int n){
    for (int i = 0; i < n; i++){
        A[i] = rand();
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

int main(){
    int n = 100;
    int *A=malloc(n * sizeof(int));

    fill_vshaped(A, n);
    print_array(A, n);
    shell_sort(A, n, shell_sort_increment(n, 20), 20);
    print_array(A, n);
    

    printf("\n");
    


    free(A);
    return 0;
}