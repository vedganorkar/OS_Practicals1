#include <stdio.h>
#include <stdbool.h>

int main() {
  int n, m;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter number of resources: ");
  scanf("%d", &m);
  
  int allocation[10][10], request[10][10], available[10];
  int work[10];
  bool finish[10];
  
  printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &allocation[i][j]);
  
  printf("\nEnter Request (Need) Matrix (%d x %d):\n", n, m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &request[i][j]);
  
  printf("\nEnter Available Resources (%d values):\n", m);
  for (int j = 0; j < m; j++)
    scanf("%d", &available[j]);
  
  // Initialize work and finish
  for (int j = 0; j < m; j++)
    work[j] = available[j];
  for (int i = 0; i < n; i++)
    finish[i] = false;
  
  int count = 0;
  bool found;
  
  // Deadlock Detection Algorithm
  while (1) {
    found = false;
    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
        bool can_finish = true;
        for (int j = 0; j < m; j++) {
          if (request[i][j] > work[j]) {
            can_finish = false;
            break;
          }
        }
        if (can_finish) {
          for (int j = 0; j < m; j++)
            work[j] += allocation[i][j];
            finish[i] = true;
            found = true;
            count++;
            printf("\nProcess P%d can finish. Updated Available: ", i);
            for (int j = 0; j < m; j++)
              printf("%d ", work[j]);
            printf("\n");
        }
      }
    }
    if (!found)
      break;
  }
  
  // Result
  printf("\n--- Final Result ---\n");
  bool deadlock = false;
  for (int i = 0; i < n; i++) {
    if (!finish[i]) {
      printf("Process P%d is deadlocked\n", i);
      deadlock = true;
    } else {
      printf("Process P%d completed\n", i);
    }
  }
  
  if (deadlock)
    printf("\nDeadlock detected in the system.\n");
  else
    printf("\nNo Deadlock detected. System is safe.\n");
  
  return 0;
}
