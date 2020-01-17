/* binsearch: binary search */
#include <stdio.h>


int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n-1;

  while (low < high) {
    mid = (low + high) / 2;
    if (x <= v[mid])
      high = mid;
    else
      low = mid + 1;
  }

  return (x == v[low]) ? low : -1;
}

int main()
{
  int v[5] = {1, 2, 3, 4, 5};
  int x = 4;
  printf("%d\n", binsearch(x, v, 5));

  return 0;
}
