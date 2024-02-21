#include <stdio.h>

int main(){
    printf("%d\n", -64 - 7);
    int val = -64;
    printf("%d\n", 7);
    size_t radix = 7;
    int x = -64 - radix;
    int y = val - radix;
    printf("%d %d", x, y);
    return 0;
}