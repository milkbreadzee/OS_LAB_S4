#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

//assuming priority is from 0 - 9, 0 being max priority and 9 being least priority

typedef struct  {
    int id;
    int priority; 
    int arrival_time; 
    int burst_time; 
    int wait_time;
    int tat;
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
            printf("Process Priority: ");
            scanf("%d", &proccesss[i].priority);
             printf("Process arrival time: ");
            scanf("%d", &proccesss[i].arrival_time);
             printf("Process burst time: ");
            scanf("%d", &proccesss[i].burst_time);
            total += proccesss[i].burst_time;
            printf("\n");
        }
    }
}

void executeProcess(proccess temp[]){
    int rt[processCount];
    float tot_wt, tot_tat;
    for(int i = 0; i<processCount; i++){
        rt[i] = temp[i].burst_time;
    }
    //copying bust time into remaining time bc we use that to reduce time from the processes
    int complete = 0, t = 0, minm = INT_MAX; //assign min to max int possible to compare values later
    int shortest = 0, finish_time, min_pri;
    bool check = false;


    min_pri = processCount-1;
    temp[min_pri].priority = minm;

    for(t = 0; complete!=processCount; t++){
        for(int i = 0; i<processCount; i++){
            if((temp[min_pri].priority>temp[i].priority) && (temp[i].arrival_time<=t) && (temp[i].burst_time>0)){
                min_pri = i; //we find the process with highest priority this way (meaning priority no = 0)
            }
        }

        rt[min_pri] = rt[min_pri] -1;
        printf("%d\n", rt[min_pri]);
        if(rt[min_pri] == 0){
            complete++;
            temp[min_pri].wait_time = t+1 - temp[min_pri].arrival_time - rt[min_pri];
            temp[min_pri].tat = t+1-temp[min_pri].arrival_time;
            tot_tat = tot_tat + temp[min_pri].tat;
            tot_wt = tot_wt + temp[min_pri].wait_time;
        }
    }

    float avg_wt = tot_wt/processCount;
    float avg_tat = tot_tat/processCount;

    printf("ID \t Priority \t AT \t BT \t WT \t TAT\n");
    for(int i = 0; i<processCount; i++){
        printf("%d \t %d \t %d \t %d \t %d \t %d \t", temp[i].id, temp[i].priority, temp[i].arrival_time, temp[i].burst_time, temp[i].wait_time, temp[i].tat);
    }

    printf("Average Waiting time: %d", avg_wt);
    printf("Average Turn Around Time time: %d", avg_tat);
}

void main(){
    getProcess();
    executeProcess(proccesss);
}