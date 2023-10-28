#include <stdio.h>
// #include <cstring>

// Struct representing process
struct Process
{
	int arrivalTime;
	int burstTime;
	int remainingTime;
	int pid;
};

// Function to swap structs
void swap(struct Process *a, struct Process *b)
{
	struct Process temp = *a;
	*a = *b;
	*b = temp;
}

// Function to sort processes according to arrival times
// void sortArrivalTimes(struct Process processes[], int n) {
// 	for(int i = 0; i < n-1; i++) {
// 		if(processes[i].arrivalTime > processes[i+1].arrivalTime) {
// 			swap(&processes[i+1], &processes[i]);
// 		}
// 	}
// }

void sortArrivalTimes(struct Process processes[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
			{
				struct Process temp = processes[j];
				processes[j] = processes[j + 1];
				processes[j + 1] = temp;
			}
		}
	}
}

int main()
{
	int n;
	int timeQuantum;

	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("\n");

	printf("Enter the time quantum: ");
	scanf("%d", &timeQuantum);
	printf("\n");

	struct Process processes[n];

	for (int i = 0; i < n; i++)
	{
		processes[i].pid = i + 1;

		printf("Enter the arrival time of process %d: ", i + 1);
		scanf("%d", &processes[i].arrivalTime);

		printf("Enter the burst time of process %d: ", i + 1);
		scanf("%d", &processes[i].burstTime);

		processes[i].remainingTime = processes[i].burstTime;
		printf("\n");
	}

	int currentTime = 0;
	int completedProcesses = 0;

	int completionTime[n];
	int turnaroundTime[n];
	int waitingTime[n];

	// Sort all the processes according to their arrival times
	sortArrivalTimes(processes, n);

	while (completedProcesses < n)
	{

		for (int i = 0; i < n; i++)
		{
			if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime)
			{

				if (processes[i].remainingTime > timeQuantum)
				{
					currentTime += timeQuantum;
					processes[i].remainingTime -= timeQuantum;
				}
				else
				{
					currentTime += processes[i].remainingTime;
					processes[i].remainingTime = 0;
					completedProcesses++;
					completionTime[i] = currentTime;
					turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
					waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
				}
			}
		}
	}
	float TotalTurnaroundTime = 0, TotalWaitingTime=0;	
	printf("\nPr\tA.T.\tB.T.\tC.T.\tT.A.T\tW.T.\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime,
			   completionTime[i], turnaroundTime[i], waitingTime[i]);
			   TotalTurnaroundTime += turnaroundTime[i];
			   TotalWaitingTime += waitingTime[i];

	}

	// Finding the average TurnAround time and waiting time
	float avgTAT = TotalTurnaroundTime / n;
	float avgWT = TotalWaitingTime / n;

	printf("\nAverage Turnaround Time: %f", avgTAT);
	printf("\nAverage Waiting Time: %f", avgWT);
	printf("\n\n\n");
	return 0;
}