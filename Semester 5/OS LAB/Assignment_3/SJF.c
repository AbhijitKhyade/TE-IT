#include <stdio.h>

//Stucture of Process
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

//Sorting the arrival time 
void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}


//Finding the shortest burst time for process
int findShortestJob(struct Process p[], int n, int currentTime) {
    int shortestJob = -1;
    int shortestBurst = 9999999;

    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && p[i].remainingTime < shortestBurst) {
            shortestJob = i;
            shortestBurst = p[i].remainingTime;
        }
    }

    return shortestJob;
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    //user Input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    //Sorting by arrival time
    sortByArrivalTime(p, n);

    int currentTime = 0;
    int completedProcesses = 0;
    int shortestJob = -1;
    int completionTime[n];
    int turnaroundTime[n];
    int waitingTime[n];


    while (completedProcesses < n) {
        shortestJob = findShortestJob(p, n, currentTime);

        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        p[shortestJob].remainingTime--;
        currentTime++;

        if (p[shortestJob].remainingTime == 0) {
            completedProcesses++;
            completionTime[shortestJob] = currentTime;
        }
    }

	float TotalTurnaroundTime = 0, TotalWaitingTime=0;	
	

    //Prining the output table wise
    printf("Pr_no\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n");
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - p[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - p[i].burstTime;
        
        TotalTurnaroundTime += turnaroundTime[i];
        TotalWaitingTime += waitingTime[i];
        
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime,completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    //Finding the average TurnAround time and waiting time
	float avgTAT = TotalTurnaroundTime/n;
    float avgWT = TotalWaitingTime/n;

	printf("\nAverage Turnaround Time: %f",avgTAT);
	printf("\nAverage Waiting Time: %f",avgWT);
	printf("\n\n\n");



    return 0;
}

