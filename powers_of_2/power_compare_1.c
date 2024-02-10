#include<stdio.h>
#include<math.h>

int main() {
    unsigned int x;
    for (int i=0; i<10000000; i++) {
        for (int j=0; j<31; j++) {
            x = 1 << j;
            // printf("%i\n", x);
        }
    }
}