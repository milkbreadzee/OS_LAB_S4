#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct  {
    int id; 
    int arrival_time; 
    int burst_time; 
}proccess;
int processCount = 0, total = 0;
proccess proccesss[100];

void getProcess(){
    printf("Enter the process count: \n");
    scanf("%d", &processCount);

    if(processCount<100){
        for(int i = 0; i<processCount; i++){
            printf("Process ID: ");
            scanf("%d", &proccesss[i].id);
             printf("Process arrival time: ");
            scanf("%d", &proccesss[i].arrival_time);
             printf("Process burst time: ");
            scanf("%d", &proccesss[i].burst_time);
            total += proccesss[i].burst_time;
            printf("\n");
        }
    }
}

void findAvgtime(proccess temp[]){
    int wt[processCount], tat[processCount], total_wt = 0, total_tat = 0;
    //fing waiting time, fing turn around time
    findWaitingTime(temp, wt);
    findTurnAroundtime(temp, wt, tat);

    printf("Process \t Arrival time \t Burst Time \t Wait Time \t TAT\n");
     for (int i = 0; i < processCount; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d \t\t %d \t\t %d \t\t %d\n", temp[i].id, temp[i].arrival_time, temp[i].burst_time, wt[i], tat[i]);
    }
    float avg_wt = total_wt/processCount;
    float avg_tat = total_tat/processCount;

    printf("average wait time : %d", avg_wt);
    printf("average turn around time : %d", avg_tat);
}

void findWaitingTime(proccess temp[], int wt[]){

    int rt[processCount]; //remaining time = burst time for now
    for(int i = 0; i<processCount; i++){
        rt[i] = temp[i].burst_time;
    }

    int complete = 0, t = 0, minm = INT_MAX; //assign minm to max int possible to compare values later
    int shortest = 0, finish_time;
    bool check = false;


    while(complete!= processCount){

        //looking for the proccess with min remanining time
        for(int j = 0; j<processCount; j++){
            if((temp[j].arrival_time <= t)&&(rt[j]<minm)&&(rt[j]>0)){
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if(check == false){
            t++;
            continue;
        }

        rt[shortest]--; //reducing remaining time of the shortest job by 1 and then update the min value

        minm = rt[shortest];

        if (minm == 0)
            minm = INT_MAX;
        

            //if the current process is complete
          if (rt[shortest] == 0) {
 
            // Increment complete
            complete++;
            check = false;
 
            // Find finish time of current process
            finish_time = t + 1;
 
            // Calculate waiting time
            wt[shortest] = finish_time -temp[shortest].burst_time -temp[shortest].arrival_time;
 
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}


void findTurnAroundtime(proccess temp[], int wt[], int tat[]){
    for(int i = 0; i<processCount; i++){
        tat[i] = temp[i].burst_time+ wt[i];
    }
}

void main(){
    getProcess();
    findAvgtime(proccesss);
}