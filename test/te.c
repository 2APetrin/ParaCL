#include <stdio.h>

int main() {
    int a = 1000000;

    while (a) {
        printf("%d\n", a);
        a = a - 1;
    }
}