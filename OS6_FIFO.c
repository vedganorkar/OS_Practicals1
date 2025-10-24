#include <stdio.h>

void fifo(int pages[], int n, int frames) {
  int frameArr[frames];
  int front = 0, pageFaults = 0;
  
  for (int i = 0; i < frames; i++)
    frameArr[i] = -1;
  
  for (int i = 0; i < n; i++) {
    int found = 0;
    for (int j = 0; j < frames; j++) {
      if (frameArr[j] == pages[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      frameArr[front] = pages[i];
      front = (front + 1) % frames;
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
  
  printf("\nFIFO Page Replacement simulation:\n");
  fifo(pages, n, frames);
  
  return 0;
} 
