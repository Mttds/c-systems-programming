/* SJF - Shortest Job First */
#include <stdio.h>

int n;
int execution_time[100];
int waiting_time[100];
int turnaround_time[100];
int process_id[100];
float total_waiting_time = 0;
float total_turnaround_time = 0;

int main() {
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  for(int i = 0; i < n; i++) {
    printf("Enter execution time for process %d: ", i+1);
    scanf("%d", &execution_time[i]);
    process_id[i] = i+1;
  }

  // sorting using bubble sort
  for(int i = 0; i < n-1; i++) {
    for(int j = 0; j < n-i-1; j++) {
      if(execution_time[j] > execution_time[j+1]) {
        // Swap execution times
        int temp = execution_time[j];
        execution_time[j] = execution_time[j+1];
        execution_time[j+1] = temp;

        // Swap process IDs to keep them in sync with execution times
        int temp_id = process_id[j];
        process_id[j] = process_id[j+1];
        process_id[j+1] = temp_id;
      }
    }
  }

  waiting_time[0] = 0;
  turnaround_time[0] = execution_time[0];
  for(int i = 1; i < n; i++) {
    waiting_time[i] = execution_time[i-1] + waiting_time[i-1];
    turnaround_time[i] = execution_time[i] + waiting_time[i];
  }

  for(int i = 0; i < n; i++) {
    total_waiting_time += waiting_time[i];
    total_turnaround_time += turnaround_time[i];
  }

  printf("Process\tExecution Time\tWaiting Time\tTurnaround Time\n");
  for(int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", process_id[i], execution_time[i], waiting_time[i], turnaround_time[i]);
  }

  printf("\nAverage Waiting Time: %.2f\n", total_waiting_time/n);
  printf("Average Turnaround Time: %.2f\n", total_turnaround_time/n);

  return 0;
}
