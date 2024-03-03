#include <stdio.h>

int main () {
    int fact_num = 0;
    scanf("%d", &fact_num);

    if (fact_num <  0) printf("-1");
    if (fact_num == 0) printf( "1");

    if (fact_num > 0) {
        int a = 1;
        while (fact_num) {
            a = a * fact_num;
            fact_num = fact_num - 1;
        }

        printf("%d", a);
    }

    return 0;
}