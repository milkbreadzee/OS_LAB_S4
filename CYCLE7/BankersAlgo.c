#include<stdio.h>
void main() {
	int k=0,output[10],d=0,t=0,instance[5],i,available[5],allocated[10][5],need[10][5],MAX[10][5],pno,P[10],j,rz, count=0;
	printf("\n Enter the number of resources : ");
	scanf("%d", &rz);
    
	printf("\n enter the max instancetances of each resources\n");
	for (i=0;i<rz;i++) {
		available[i]=0;
		printf("%c= ",(i+97));
		scanf("%d",&instance[i]);
	}
	printf("\n Enter the number of processes : ");
	scanf("%d", &pno);
	printf("\n Enter the allocation matrix \n     ");
	for (i=0;i<rz;i++)
	printf(" %c",(i+97));
	printf("\n");
	for (i=0;i <pno;i++) {
		P[i]=i;
		printf("P[%d]  ",P[i]);
		for (j=0;j<rz;j++) {
			scanf("%d",&allocated[i][j]);
			available[j]+=allocated[i][j];
		}
	}
	printf("\nEnter the MAX matrix \n     ");
      for (i=0;i<rz;i++) {
		printf(" %c",(i+97));
		available[i]=instance[i]-available[i];
	}
	printf("\n");
	for (i=0;i <pno;i++) {
		printf("P[%d]  ",i);
		for (j=0;j<rz;j++)
		 scanf("%d", &MAX[i][j]);
	}
	printf("\n");
    int goto_count = 0;
	A: d=-1;
    printf("\ngoto count = %d", goto_count);
	for (i=0;i <pno;i++) {
		count=0;
		t=P[i];
		for (j=0;j<rz;j++) {
			need[t][j] = MAX[t][j]-allocated[t][j];
			if(need[t][j]<=available[j])
			 count++;
		}
		if(count==rz) {
			output[k++]=P[i];
            printf("\noutput at k++ {%d} = P[i] {%d}\n", P[i], P[i]);
			for (j=0;j<rz;j++)
			available[j]+=allocated[t][j];
		} else{
             P[++d]=P[i];
             printf("\nP[++d] = P[i] at %d = %d\n", P[i], P[i]);
        }
		
	}
	if(d!=-1) {
		pno=d+1;
        goto_count++;
		goto A;
	}

	printf("\t <");
	for (i=0;i<k;i++)
	printf(" P[%d] ",output[i]);
	printf(">");
    printf("\n");
}