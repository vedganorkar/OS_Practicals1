#include <stdio.h>

void lru(int pages[], int n, int frames) {
  int frameArr[frames];
  int counter[frames];  // To track recent usage
  int time = 0, pageFaults = 0;
  
  for (int i = 0; i < frames; i++) {
    frameArr[i] = -1;
    counter[i] = 0;
  }
  
  for (int i = 0; i < n; i++) {
    int found = -1;
    
    // Check if page already present
    for (int j = 0; j < frames; j++) {
      if (frameArr[j] == pages[i]) {
        found = j;
        break;
      }
    }
    
    if (found != -1) {
      time++;
      counter[found] = time; // Update usage time
    } else {
      int lru_index = 0;
      int min_time = counter[0];
      
      // Find least recently used frame
      for (int j = 1; j < frames; j++) {
        if (counter[j] < min_time) {
          min_time = counter[j];
          lru_index = j;
        }
      }
      
      frameArr[lru_index] = pages[i];
      time++;
      counter[lru_index] = time;
      pageFaults++;
    }
    
    // Print current frames
    printf("Frames: ");
    for (int k = 0; k < frames; k++) {
      if (frameArr[k] != -1)
        printf("%d ", frameArr[k]);
      else
        printf("- ");
    }
    printf("\n");
  }
  
  printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
  int n, frames;
  
  printf("Enter number of pages: ");
  scanf("%d", &n);
  
  int pages[n];
  printf("Enter page reference string: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &pages[i]);
  
  printf("Enter number of frames: ");
  scanf("%d", &frames);
  
  printf("\nLRU Page Replacement simulation:\n");
  lru(pages, n, frames);
  
  return 0;
}
