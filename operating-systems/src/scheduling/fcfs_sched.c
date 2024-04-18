/* FIFO - FCFS (First Come, First Served) */
#include <stdio.h>

int n;
int duration[100];
int waiting_time[100];
int turnaround_time[100];
float total_waiting_time = 0;
float total_turnaround_time = 0;

int main() {
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  for(int i = 0; i < n; i++) {
    printf("Enter duration for process %d: ", i+1);
    scanf("%d", &duration[i]);
  }  

  waiting_time[0] = 0;
  //turnaround_time[0] = duration[0];

  for(int i = 1; i < n; i++) {
    waiting_time[i] = duration[i-1] + waiting_time[i-1];
    turnaround_time[i] = duration[i] + waiting_time[i];
  }

  for(int i = 0; i < n; i++) {
    total_waiting_time += waiting_time[i];
    total_turnaround_time += turnaround_time[i];
  }

  printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
  for(int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", i+1,
           duration[i], waiting_time[i], turnaround_time[i]);
  }

  printf("Average Waiting Time: %.2f\n", (double)total_waiting_time / n);
  printf("Average Turnaround Time: %.2f\n", (double)total_turnaround_time / n);
  return 0;
}
