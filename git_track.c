#include <stdio.h>

int main(){
    
    printf("Hello World\n");

    int sum = 0;
    for (int i = 1; i <= 10; i++){
        sum += i;
    }
    printf("%d\n", sum);

    return 0;
}