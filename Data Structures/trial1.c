#include <stdio.h>

int main(){

    return 0;
}

int conversion(int num, int radix){
    
    while (num != 0){
        int mod = num % radix;
        num = num / radix;
        char mod_c;
        if (mod < 10){
            mod_c = mod+48;
        }else{
            mod_c = mod+55 ;
        }
    }
}