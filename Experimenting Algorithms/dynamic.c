#include <stdio.h>
#include <stdlib.h>


long long int fib(int n, long long int* f){

    if (n == 0) return 0;
    if (n == 1) return 1;
    if (f[n-1] == -1) {
        f[n-1] = fib(n-1, f);
    }
    if (f[n-2] == -1) {
        f[n-2] = fib(n-2, f);
    }
    f[n] = f[n-1] + f[n-2];
    return f[n];
    
}

long long bottom_up_fib(int n){

    long long int* arr = (long long int *)malloc(sizeof(long long)*(n+1));
    arr[0] = 0;
    arr[1] = 1;
    for (int i = 2; i <= n; i++)
        arr[i] = arr[i-1] + arr[i-2];
    return arr[n];
}

long long int badfib(int n){

    if (n == 0) return 0;
    if (n == 1) return 1;
    return badfib(n-1) + badfib(n-2);
    
}


int main(){

    long long int n = 45;
    long long int* m = (long long int *)malloc(sizeof(long long int)*(n+1));
    for (int i = 0; i < n; i++){
        m[i] = -1;
    }
    printf("%lld\n", fib(n, m));
    printf("%lld\n", bottom_up_fib(n));
    printf("%lld", badfib(n));
    return 0;
}// 0, 1, 1, 2, 3, 5, 8, 13