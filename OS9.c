#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

int memory[MAX_BLOCKS];

// Function to initialize memory blocks
void initialize() {
  for (int i = 0; i < MAX_BLOCKS; i++)
    memory[i] = 0;
}

// Sequential File Allocation
void sequential_allocation() {
  int start = 5;
  int length = 4;
  
  printf("\n--- Sequential File Allocation ---\n");
  printf("File start block = %d, length = %d\n", start, length);
  
  if (start + length > MAX_BLOCKS) {
    printf("Error: File exceeds memory limit.\n");
    return;
  }
  
  // Check if blocks are free
  for (int i = start; i < start + length; i++) {
    if (memory[i] == 1) {
      printf("Error: Block %d already allocated.\n", i);
      return;
    }
  }
  
  // Allocate blocks
  for (int i = start; i < start + length; i++)
    memory[i] = 1;
  
  printf("File successfully allocated from block %d to %d.\n", start, start + length - 1);
}

// Indexed File Allocation
void indexed_allocation() {
  int indexBlock = 12;
  int blocks[] = {20, 21, 22};
  int n = sizeof(blocks) / sizeof(blocks[0]);
  
  printf("\n--- Indexed File Allocation ---\n");
  printf("Index block = %d\n", indexBlock);
  
  if (memory[indexBlock] == 1) {
    printf("Error: Index block already allocated.\n");
    return;
  }
  
  // Allocate index block
  memory[indexBlock] = 1;
  
  // Allocate file blocks
  for (int i = 0; i < n; i++) {
    if (memory[blocks[i]] == 0)
      memory[blocks[i]] = 1;
    else
      printf("Warning: Block %d already allocated.\n", blocks[i]);
  }
  
  printf("File indexed at block %d allocated to blocks: ", indexBlock);
  for (int i = 0; i < n; i++)
    printf("%d ", blocks[i]);
  printf("\n");
}

// Linked File Allocation
void linked_allocation() {
  int blocks[] = {30, 31, 32};
  int n = sizeof(blocks) / sizeof(blocks[0]);
  
  printf("\n--- Linked File Allocation ---\n");
  printf("File blocks: ");
  for (int i = 0; i < n; i++)
    printf("%d ", blocks[i]);
  printf("\n");
  
  // Allocate blocks
  for (int i = 0; i < n; i++) {
    if (memory[blocks[i]] == 0)
      memory[blocks[i]] = 1;
    else {
      printf("Error: Block %d already allocated.\n", blocks[i]);
      return;
    }
  }
  
  // Display linking
  for (int i = 0; i < n - 1; i++)
    printf("Block %d → %d allocated.\n", blocks[i], blocks[i + 1]);
  
  printf("File stored successfully using linked allocation.\n");
}

// Main Function
int main() {
  initialize();
  
  printf("===== FILE ALLOCATION STRATEGIES SIMULATION =====\n");
  
  sequential_allocation();
  indexed_allocation();
  linked_allocation();
  
  printf("\nAll allocations completed successfully.\n");
  return 0;
}
