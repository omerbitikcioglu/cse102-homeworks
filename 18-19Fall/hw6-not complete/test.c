#include <stdio.h>
#include <string.h>
int main(void)
{
    func(5,0);
}

void func(int i , int j)
{
    j=i;

    printf("%d",j);
}
