#include <stdio.h> 
#include <stdlib.h>
int first_fit(int size, int memory[] , int memory_size);
int best_fit(int size, int memory[] , int memory_size);
int worst_fit(int size, int memory[] , int memory_size);
void show_memory( int memory[] , int memory_size);
void allocate(int memory[] ,int process_no , int start , int size , int memory_size);


int main(){
int memory_size = 1024;
int memory[memory_size] ; 
 int i;
 for(i=0;i<memory_size;i++)
 {
 	memory[i] = 0;
 }
 
 int upper = 40;
 int lower = 1;
 
 int mem_loc = 0;
 
 int j = 0 ;
for (i = 0; i < 10; i++) { 
    int size  = (rand() % (upper - lower + 1)) + lower;
		
    	for( j = mem_loc ; j < mem_loc + size ; j++){
    		memory[j] = i+1; 
		}
		
		mem_loc = (rand() % (100 - 1 + 1)) + 1 + j;
    } 
    
show_memory( memory , memory_size);

printf("Now we will manually add process: \n");

int start = 0 ; 

int choice = 1;
int process_no = 10;
int ff , bf , wf ;
int x ;
while(choice){
	process_no++ ;
	int size  = (rand() % (upper - lower + 1)) + lower;	
	
	printf("Alocating %dth process to memory with size %d \n" , process_no , size) ;

	printf("/n 1: First Fit /n 2:Best Fit /n 3: Worst Fit ? \n");
	fflush(stdin);
	scanf("%d" , &x);
   	switch (x) { 
        	case 1:
        		printf("\n You chose first fit for process no : %d \n" , process_no);
				ff = first_fit(size , memory , memory_size);
				allocate(memory , process_no , ff , size, memory_size) ;
         	    break; 
        	case 2:
        		printf("\n You chose best fit for process no : %d \n" , process_no);
        		bf = best_fit(size, memory , memory_size);
				allocate(memory , process_no , bf, size , memory_size) ;
                break; 
    		case 3:
    			printf("\n You chose worst fit for process no : %d \n" , process_no);
        		wf = worst_fit(size, memory , memory_size);
				allocate(memory ,process_no , wf, size, memory_size) ;
               break; 
        	default: printf("Choice other than 1, 2 and 3"); 
                break;   
   		} 
	printf("\nDo you want to put more processes ? \n");
	fflush(stdin);
	scanf("%d" , &choice);
	}

}

int first_fit(int size, int memory[] , int memory_size){
	int start  , count = 0 ;
	int i;
	for(i =0 ; i < memory_size ; i++){
		if(memory[i] == 0){
			if(memory[i-1] != 0){
				count = 0;
			}
			count++;
		}
		if(count == size){
			start = i-count+1;
			printf("Found  free block at location : %d\n" , start);
			return(start);
		}
	}
}

int best_fit(int size, int memory[] , int memory_size){
	int start , count , fcount , flag = 0 ;
	int smallest = memory_size;
	int i;
	for(i = 0 ; i < memory_size ; i++){
		if(memory[i] == 0){
			if(memory[i-1] != 0 && i){
				count = 0;
			}
			count++;
			if(memory[i+1] != 0 ){
				fcount = count;
				if (smallest > fcount && fcount >= size){
				smallest = fcount;
				start = i-fcount+1;
				}
			}
		}
		
	}
printf("Found smallest free block of size : %d at location : %d\n" , smallest , start);
return(start) ;
}

int worst_fit(int size, int memory[] , int memory_size){
	int start , count , fcount , flag , largest = 0 ;
	int i;
	for(i = 0 ; i < memory_size ; i++){
		if(memory[i] == 0){
			if(memory[i-1] != 0 && i){
				count = 0;
			}
			count++;
			if(memory[i+1] != 0 ){
				fcount = count;
				if (largest < fcount && fcount >= size){
				largest = fcount;
				start = i-fcount+1;
				}
			}
		}
		
	}
printf("Found largest free block of size : %d at location : %d\n" , largest , start);	
return(start) ;
}

void show_memory( int memory[] , int memory_size){
	printf("The memory looks like : \n");
	prinf("\n");
	int l;
	for(l = 0 ; l < 1024 ; l++){
		printf("%d " , memory[l]);
		if(l%32 == 0 && l){
			printf("\n");
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

void allocate(int memory[] ,int process_no , int start , int size , int memory_size){
	int a;
	for(a = start ; a < size + start; a++){
		memory[a] = process_no; 
	}
	show_memory( memory , memory_size);
}



