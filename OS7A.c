#include <stdio.h>
#include <stdlib.h>

int main()
{
  int sum = 0;
  int count = 0;
  int i;
  int n;
  
  printf("ENTER THE NUMBER OF DISKS: ");
  scanf("%d", &n);
  
  int a[n];
  
  printf("Enter the values: ");
  for(i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  
  for(i = 0; i < n - 1; i++) {
    count += abs(a[i + 1] - a[i]);
  }
  
  printf("The total distance is %d\n", count);
  
  return 0;
}
