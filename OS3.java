import java.util.Scanner;

public class StudentResult {
  
  // Global variables to hold the results
  static int totalMarks = 0;
  static float percentage = 0.0f;
  static String result = "";
  
  // Input data
  static int[] marks;
  static int numSubjects = 0;
  static int totalMaxMarks = 0;
  
  // Thread 1: Calculate Total Marks
  static class CalculateTotalMarks extends Thread {
    public void run() {
      totalMarks = 0;
      for (int i = 0; i < numSubjects; i++) {
        totalMarks += marks[i];
      }
      System.out.println("Total Marks: " + totalMarks + "|" + 100 * numSubjects);
    }
  }
  
  // Thread 2: Calculate Percentage
  static class CalculatePercentage extends Thread {
    public void run() {
      percentage = ((float) totalMarks / totalMaxMarks) * 100;
      System.out.println("Percentage: " + percentage + "%");
    }
  }
  
  // Thread 3: Pass/Fail Decision
  static class PassFailDecision extends Thread {
    public void run() {
      if (percentage >= 40) {
        result = "Pass";
      } else {
        result = "Fail";
      }
      System.out.println("Result: " + result);
    }
  }
  
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    // Input: Number of subjects
    System.out.print("Enter the number of subjects: ");
    numSubjects = sc.nextInt();
    
    // Validate input
    if (numSubjects <= 0) {
      System.out.println("Invalid number of subjects!");
      return;
    }
    
    // Initialize the marks array
    marks = new int[numSubjects];
    totalMaxMarks = numSubjects * 100;  // Total maximum marks for all subjects
    
    // Input: Marks for each subject
    for (int i = 0; i < numSubjects; i++) {
      System.out.print("Subject " + (i + 1) + " Marks(Out of 100): ");
      marks[i] = sc.nextInt();
    }
    
    // Create threads
    Thread thread1 = new CalculateTotalMarks();
    Thread thread2 = new CalculatePercentage();
    Thread thread3 = new PassFailDecision();
    
    // Start the threads
    thread1.start();
    try {
      thread1.join();  // Ensure thread1 finishes before moving to thread2
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    
    thread2.start();
    try {
      thread2.join();  // Ensure thread2 finishes before moving to thread3
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    
    thread3.start();
    try {
      thread3.join();  // Wait for thread3 to finish before exiting
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    
    System.out.println("Student Result Processing Completed.");
  }
}

