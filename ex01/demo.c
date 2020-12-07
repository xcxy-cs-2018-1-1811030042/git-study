#include<stdio.h>
int add(int a, int b)
  {
    return a + b;
  }
  int main()
  {
    int sum[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    int array1[10] ={11, 22, 33, 44, 55, 66, 77, 88, 99, 00};
    int array2[10] ={1, 2, 3, 4, 5, 4, 3, 2, 1, 0};
    for (i = 0; i < 10; i++)
      {
        sum[i] = add(array1[i], array2[i]);
      }
 }