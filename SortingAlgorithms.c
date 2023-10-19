/* Will work with arrays for today. Will try out with linked lists next time, 
though I believe a simple swapping function should be enough.*/

#include <stdio.h>

// Simple sorting to ascending order
void simple_sort(int arr[], int n, char order){
    int temp;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (order == 'a'){
                if (arr[j] < arr[i]){
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }else if(order == 'd'){
                if (arr[j] > arr[i]){
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }else{
                printf("Not a valid operation\n");
                return;
            }
        }
    }
}

int main(){

    int arr[5] = {7, -1, 3, 4, 2};

    for (int i = 0; i < 5; i++){
        printf("%d ", arr[i]);
    }
    
    printf("\n");

    simple_sort(arr, 5, 'd');

    for (int i = 0; i < 5; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}