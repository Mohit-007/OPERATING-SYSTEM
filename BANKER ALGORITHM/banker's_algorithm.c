#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void printResult(int test);

void safeSequence(int processes,int resources,int allocation[processes][resources],int max[processes][resources],int need[processes][resources],int available[resources]){
	int finished[processes], ans[processes], ind = 0;
	int i,j,k,test;
	for (k=0;k<processes;k++) { 
		finished[k] = 0;
	} 
	int y = 0; 
	for (k = 0;k<processes;k++) { 
		for (i=0;i<processes;i++) { 
			if (finished[i] == 0) {

				int flag = 0; 
				for (j=0;j<resources;j++) { 
					if (need[i][j]>available[j]){ 
						flag = 1; 
						break; 
					} 
				} 

				if (flag==0) { 
					ans[ind++]=i; 
					for (y=0;y<resources;y++) 
						available[y]+=allocation[i][y]; 
					finished[i]=1; 
				} 
			} 
		} 
	} 

	if(ind!=processes){
		printf("No Safe Sequence");
        printf("Resource Allocation not possible");
	} 
	else{
		printf("Following is the Safe Sequence\n"); 
		for (i=0;i<processes-1;i++) 
			printf(" P%d ->", ans[i]); 
		printf(" P%d", ans[processes - 1]);
        printf("\nResource Allocation is possible\n");
	}
	printf("\n");
}


void resourceRequest(int processes,int resources,int allocation[processes][resources],int max[processes][resources],int need[processes][resources],int available[resources],int process_id){
	int i,j,k;
	int add_req[resources];
	printf("Enter the additional resources: \n");
	for(int i=0;i<resources;i++){
		scanf("%d",&add_req[i]);
	}
	for(i=0;i<resources;i++){
		if(add_req[i]>need[process_id][i]){
			printf("Allocation cannot be made since additional resources required exceed need\n");
			exit(0);
		}
	}
	for(i=0;i<resources;i++){
		if(add_req[i]>available[i]){
			printf("Allocation cannot be made since additional resources required exceed available resources\n");
			exit(0);
		}
	}

	for(i=0;i<resources;i++){
		available[i]-=add_req[i];
		allocation[process_id][i]+=add_req[i];
		need[process_id][i]-=add_req[i];
	}
	safeSequence(processes,resources,allocation,max,need,available);
}

int main(){
	
	int i,j,req;
	int processes,resources;
	printf("Enter the number of processes and resources: \n");
	scanf("%d%d",&processes,&resources);
	int allocation[processes][resources];
	printf("Define the elements for allocation matrix: \n");
	for(i=0;i<processes;i++){
		for(j=0;j<resources;j++){
			scanf("%d",&allocation[i][j]);
		}
	}
	int max[processes][resources];
	printf("Define the elements for max matrix: \n");
	for(i=0;i<processes;i++){
		for(j=0;j<resources;j++){
			scanf("%d",&max[i][j]);
		}
	}
	int available[resources];
	printf("Define number of resources available: \n");
	for(i=0;i<resources;i++){
		scanf("%d",&available[i]);
	}
	int need[processes][resources];
	for(i=0;i<processes;i++){
		for(int j=0;j<resources;j++){
			need[i][j]=max[i][j]-allocation[i][j];
		}
	}
	safeSequence(processes,resources,allocation,max,need,available);
	printf("Do you want to make an additional request for a particular process? (1==Yes || 0==No): \n");
	scanf("%d",&req);
	if(req==0){
		printf("Ok\n");
		exit(0);
	}
	else{
		int process_id;
		printf("Enter process id: ");
		scanf("%d",&process_id);
		resourceRequest(processes,resources,allocation,max,need,available,process_id);
	}
}

