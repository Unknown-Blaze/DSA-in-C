#include <stdio.h>
#include <stdlib.h>

int facto(int n, int* m){
    if (n == 0) return 1;
    if (n == 1) return 1;
    
    if (m[n-1] == -1) m[n-1] = facto(n-1, m);
    m[n] = n * m[n-1];
    return m[n];
}

int main(){
    int n = 10;
    int* m = (int *)malloc(sizeof(int)*(n+1));
    for (int i = 0; i <= n; i++){
        m[i] = -1;
    }
    printf("%d", facto(n, m));
    return 0;
}