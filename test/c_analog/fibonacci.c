#include <stdio.h>

int main () {
    int fib_num = 0;
    scanf("%d", &fib_num);

    if (fib_num <  1) printf("-1\n");
    if (fib_num == 1) printf("1\n");
    if (fib_num == 2) printf("1\n");

    if (fib_num > 2) {
        int curr_num = 2;

        int a = 1;
        int b = 1;

        while (fib_num - curr_num) {
            int num = a + b;
            a = b;
            b = num;
            curr_num = curr_num + 1;
        }

        printf("%d\n", b);
    }

    return 0;
}
