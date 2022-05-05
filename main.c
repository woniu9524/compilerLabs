#include <stdio.h>
#include "lexical.h"
void f(int (*arr)[3]){
    printf("%d",arr[1][1]);
}
int main() {
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*p)[3]=a;
    f(p);

}
