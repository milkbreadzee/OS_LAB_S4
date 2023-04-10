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

void implimentBestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];
    //assigning -1 to indicate no block allotted
    for(int i = 0; i < processes; i++){
        allocation[i] = -1;
    }

    for (int i=0; i < processes; i++)
    {
        
        int indexPlaced = -1;
        for (int j=0; j < blocks; j++) 
        { 
            if (blockSize[j] >= processSize[i])
            {
                if (indexPlaced == -1)
                    indexPlaced = j;
                    
                // check rest of the boxes to see if it fits better
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }
 
        if (indexPlaced != -1)
        {
            allocation[i] = indexPlaced;
            blockSize[indexPlaced] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

}




int main(){
    getProcess();
    getBlocks();
    implimentBestFit(b, bno, p, pno);
}