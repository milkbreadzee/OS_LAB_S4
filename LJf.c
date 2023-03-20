#include <stdio.h>

typedef struct  {
    int id; // proccess ID
    int arrival_time; // arrival time of the proccess
    int burst_time; // burst time of the proccess
}proccess;
int processCount = 0;
proccess proccesss[100];
void swap( proccess* a,  proccess* b) {
     proccess temp = *a;
    *a = *b;
    *b = temp;
}

void LJF( proccess* proccesss) {
    int i, j;
    // sort proccesss in descending order of burst time
    for (i = 0; i < processCount-1; i++) {
        for (j = 0; j < processCount-i-1; j++) {
            if (proccesss[j].burst_time < proccesss[j+1].burst_time) {
                swap(&proccesss[j], &proccesss[j+1]);
            }
        }
    }
    // print schedule
    printf("LJF schedule:\n");
    int time = 0;
    for (i = 0; i < processCount; i++) {
        printf("proccess %d: start time = %d, end time = %d\n", proccesss[i].id, time, time+proccesss[i].burst_time);
        time += proccesss[i].burst_time;
    }
}


void getProcess(){
    printf("Enter the process count: \n");
    scanf("%d", &processCount);

    if(processCount<6){
        for(int i = 0; i<processCount; i++){
            printf("Process ID: ");
            scanf("%d", &proccesss[i].id);
             printf("Process arrival time: ");
            scanf("%d", &proccesss[i].arrival_time);
             printf("Process burst time: ");
            scanf("%d", &proccesss[i].burst_time);
            printf("\n");
        }
    }
}

int main() {
    getProcess();
// int n = sizeof(proccesss)/sizeof(proccesss[0]);
    LJF(proccesss);
    return 0;
}
