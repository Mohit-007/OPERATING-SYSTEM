#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void printResult(int test);

void safeSequence(int process,int resources,int allocation[process][resources],int max[process][resources],int need[process][resources],int available[resources]){
	int finished[process], ans[process], ind = 0;
	int i,j,k,test;
	for (k=0;k<process;k++) { 
		finished[k] = 0;
	} 
	int y = 0; 
	for (k = 0;k<process;k++) { 
		for (i=0;i<process;i++) { 
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

	if(ind!=process){
		printf("no safe sequence");
		int test=0;
	} 
	else{
		int test=1;
		printf("following is the safe sequence\n"); 
		for (i=0;i<process-1;i++) 
			printf(" P%d ->", ans[i]); 
		printf(" P%d", ans[process - 1]);
	}
	printf("\n");
	printResult(test);
}

void printResult(int test){
	if(test){
		printf("resources can successfully be allocated\n");
	}
	else{
		printf("resource allocation will be suspended since there is no safe sequence\n");
	}
	exit(0);
}

void resourceRequest(int process,int resources,int allocation[process][resources],int max[process][resources],int need[process][resources],int available[resources],int process_id){
	int i,j,k;
	int add_req[resources];
	printf("enter the additional resources : \n");
	
	for(i=0;i<resources;i++){
		scanf("%d",&add_req[i]);
	}
	for(i=0;i<resources;i++){
		if(add_req[i]>need[process_id][i]){
			printf("allocation can not be made since additional resources required exceed need\n");
			exit(0);
		}
	}
	for(i=0;i<resources;i++){
		if(add_req[i]>available[i]){
			printf("allocation can not be made since additional resources required exceed available resources\n");
			exit(0);
		}
	}

	for(i=0;i<resources;i++){
		available[i]-=add_req[i];
		allocation[process_id][i]+=add_req[i];
		need[process_id][i]-=add_req[i];
	}
	safeSequence(process,resources,allocation,max,need,available);
}

int main(){
	
	int i,j,req;
	int process,resources;
	printf("enter the number of process and resources: \n");
	scanf("%d%d",&process,&resources);
	int allocation[process][resources];
	printf("define the elements for allocation matrix: \n");
	for(i=0;i<process;i++){
		for(j=0;j<resources;j++){
			scanf("%d",&allocation[i][j]);
		}
	}
	int max[process][resources];
	printf("define the elements for max matrix: \n");
	for(i=0;i<process;i++){
		for(j=0;j<resources;j++){
			scanf("%d",&max[i][j]);
		}
	}
	int available[resources];
	printf("define number of resources available: \n");
	for(i=0;i<resources;i++){
		scanf("%d",&available[i]);
	}
	int need[process][resources];
	for(i=0;i<process;i++){
		for(j=0;j<resources;j++){
			need[i][j]=max[i][j]-allocation[i][j];
		}
	}
	safeSequence(process,resources,allocation,max,need,available);
	printf("do you want to make an additional request for a particular process? (Yes==1 || No==0): \n");
	scanf("%d",&req);
	if(req==0){
		printf("Ok\n");
		exit(0);
	}
	else{
		int process_id;
		printf("Enter the process id: ");
		scanf("%d",&process_id);
		resourceRequest(process,resources,allocation,max,need,available,process_id);
	}
}

