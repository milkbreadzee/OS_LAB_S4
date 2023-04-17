#include <stdio.h>

int pno, bno;
int p[100], b[100];
void getProcess(){
    printf("Enter the number of Processes : \n");
    scanf("%d", &pno);
    printf("Enter the Process sizes : \n");
    for(int i = 0; i<pno; i++){
        scanf("%d", &p[i]);
    }
}
void getBlocks(){
    printf("Enter the number of Memory Blocks : \n");
    scanf("%d", &bno);
    printf("Enter the Memory Block sizes : \n");
    for(int i = 0; i<bno; i++){
        scanf("%d", &b[i]);
    }
}

void implimentFirstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    //blocksize = array of memory sizes
    //processsize = array of process sizes
    //blocks = number of mem blocks inputted / available
    //processes = number of proccesses inputted
    int allocation[processes];
    //assigning -1 to indicate no memory block allotted yet
    for(int i = 0; i < processes; i++){
        allocation[i] = -1;
    }

    for (int i=0; i < processes; i++)
    {
        for (int j=0; j < blocks; j++) 
        { 
            if (blockSize[j] >= processSize[i])
            {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    break; 
                }
                
            }
        }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

}

int main(){
    getProcess();
    getBlocks();
    implimentFirstFit(b, bno, p, pno);
}