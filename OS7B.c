#include <stdio.h>
#include <stdlib.h>

int main()
{
  int count = 0;
  int i, j, n, min, pos;
  
  printf("ENTER THE NUMBER OF DISKS: ");
  scanf("%d", &n);
  
  int a[n];
  int visited[n];
  
  printf("Enter the values: ");
  for(i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    visited[i] = 0;
  }
  
  int head = a[0];
  visited[0] = 1;
  
  for(i = 1; i < n; i++) {
    min = 9999;
    pos = -1;
    
    for(j = 0; j < n; j++) {
      if(!visited[j]) {
        int diff = abs(head - a[j]);
        if(diff < min) {
          min = diff;
          pos = j;
        }
      }
    }
    
    count += min;
    head = a[pos];
    visited[pos] = 1;
  }
  
  printf("The total distance is %d\n", count);
  
  return 0;
}
