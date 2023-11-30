#include <stdio.h>

int main(){
    
    printf("Hello World\n");

    int sum = 0;
    for (int i = 1; i <= 10; i++){
        sum += i;
    }
    printf("%d\n", sum);

    int sum2 = 0;
    for (int i = 10; i > 0; i--) sum2 += i;
    printf("%d", sum2);

    return 0;
}