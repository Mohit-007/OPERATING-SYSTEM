#include<stdio.h>
#include<stdlib.h>


struct process
{
	int pid;      // process id
	int at;       // arrival time
	int bt;   	  // burst time
	int io_bt;    // input output time
	int burst_time;
	int cpu_bt;   // cpu time
	int ct;		  // completion time
	int wt;		  // waiting time
	int flag;	  // flag
	int tat;
	
	// flag =  0 => !
	// flag =  1 => ready queue
	// flag =  2 => scheduled in processing
	// flag =  3 => ready for input output 
	// flag =  4 => performing input output
	// flag =  5 => completed successfully
};

// sort for arrival time
void sort(struct process p[],int n);

void wait_time(struct process p[], int n); 

void main()
{
	int n=5,i;
	struct process p[n];
	for(i=0;i<n;i++)
	{
		p[i].pid = i;
		//p[i].at = (int)(rand()%5)*2;
		//p[i].bt = (int)(rand()%5)*2+2;
	}
	p[0].at = 3;
	p[1].at = 3;
	p[2].at = 6;
	p[3].at = 7;
	p[4].at = 9;
	p[0].bt = 12;
	p[1].bt = 10;
	p[2].bt = 4;
	p[3].bt = 10;
	p[4].bt = 2;


	for(i=0;i<n;i++)
	{
		p[i].burst_time = p[i].bt;
	}

	for(i=0;i<n;i++)
	{
		printf("%d %d %d\n",p[i].pid,p[i].at,p[i].bt);
	}
	for(i=0;i<n;i++)
	{
		
		p[i].flag = 0;
		p[i].cpu_bt = (p[i].bt)/2;
		p[i].io_bt = (p[i].bt)/2;
	}
	sort(p,n);
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d %d %d\n",p[i].pid,p[i].at,p[i].bt);
	}
	
	wait_time(p,n);
	printf("\n\n");
	printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

	for(i=0;i<n;i++)
	{
		p[i].wt = p[i].ct - p[i].at - p[i].burst_time + 1;
		p[i].tat = p[i].ct - p[i].at;
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].burst_time,p[i].ct,p[i].wt,p[i].tat);
		
	}
	printf("\n");
	int avg_waiting_time =0;
	for(i=0;i<n;i++)
	{
		avg_waiting_time = avg_waiting_time + p[i].wt ;
	}
	
	float avg_wait;
	avg_wait = (float)avg_waiting_time/n;
	printf("average waiting time = \n\n%f\n\n",avg_wait);
	
	


}	

void sort(struct process p[],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at > p[j+1].at)
			{
				temp = p[j].at;
				p[j].at = p[j+1].at;
				p[j+1].at = temp;

				temp = p[j].pid;
				p[j].pid = p[j+1].pid;
				p[j+1].pid = temp;

				temp = p[j].bt;
				p[j].bt = p[j+1].bt;
				p[j+1].bt = temp;


			}
		}
	}
	

}


void wait_time(struct process p[], int n) 
{ 
  	int i;
	int min = 100000;  
    int count = 0;
    int shortest = 0; 
    int cpu_t = 0;
    int io_t = 0;
    int val ;
    int io_flag = 0;
    int cpu_flag = 0;
    while(1) 
    { 
    
    	printf("%dth sec started\n",io_t);
    	count = 0;
    	for(i=0;i<n;i++)
    	{  
			// flag =  0 => !
			// flag =  1 => ready queue
			// flag =  2 => scheduled in processing
			// flag =  3 => ready for input output 
			// flag =  4 => performing input output
			// flag =  5 => completed successfully
    		
			if(p[i].flag != 5 && p[i].flag != 3 && p[i].flag != 2 && p[i].flag != 4 )
			{
	  			if(cpu_t >= p[i].at)
	  		   	{
	  		   		p[i].flag = 1;
	  		   		printf("process arrived and in ready queue for cpu %d\n",i);
				}
			}
    	} 
		
    	for(i=0;i<n;i++)
    	{
    		if(p[i].flag == 1 || p[i].flag == 2 )
    		{
    			if(p[i].bt < min)
    			{	
    				min = p[i].bt;
    				
					if(cpu_flag == 1 && i!=val)
						cpu_flag = 101; 
					val = i;
				}
    		}
    	}	
    	
		
    	


    	for(i=0;i<n;i++)
    	{
    		// process who was executing and now have signal to get out
			if(p[i].flag == 2 && cpu_flag == 101)
    		{
    			//p[i].cpu_bt--;
    			p[i].flag = 1;
    			cpu_flag = 0;
    			printf("process exit the cpu but not completed  = %d\n",i);

			}
		}

		// new process will have cpu
		if(p[val].flag == 1)
			p[val].flag = 2;
		printf("process scheduled in the cpu  = %d\n",val);
 
    	// p[i] who completes the cpu execution
    	for(i=0;i<n;i++)
    	{
    		// process who is in cpu
    		if(p[i].flag == 2)
    		{  
    			// if execution not completed
    				cpu_flag = 1;
					p[i].bt--;
    				p[i].cpu_bt--;
    				printf("process executing in cpu  = %d\n",i);
    				if(p[i].cpu_bt < 0)
    					p[i].cpu_bt = 0;
					if(p[i].cpu_bt == 0)
					{
						cpu_flag = 0;
						p[i].flag = 3;
						min = 1000;
    					printf("process terminated from cpu and ready for io  = %d\n",i);
					}
    			

    		}
    		
    	
    	}

			
 	
		
    	for(i=0;i<n;i++)
    	{
	
			if(p[i].flag == 4)
			{

				printf("process executing in io %d\n",i);
				p[i].io_bt--;
				p[i].bt--;
				if(p[i].bt == 0 || p[i].io_bt == 0)
				{
					io_flag = 0;
					p[i].ct = io_t + 1;
					p[i].flag = 5;
					printf("process completed io operation= %d\n",i);
				}
		
			}
	

    		if(p[i].flag == 3)
    		{  
    			if(io_flag == 0)
    			{
    				min = 1000;
    				printf("process scheduled for io operation = %d\n",i);
    				io_flag = 1;
    				p[i].flag = 4;
    			}
    		}
			
	
    		
    	}

    	// wait time 

    	for(i=0;i<n;i++)
    	{
    		if(p[i].flag == 5)
    		{
    			printf("process completed totally  = %d\n",i);
    			count++;
    		}
    	}
    	
    	if(count == n-1)
    	{
			p[val].ct = io_t + p[val].io_bt +p[val].cpu_bt + 1;	
    		break;
		}
		printf("%dth sec completed\n\n",cpu_t);
    	
    	cpu_t++;
    	io_t++;
    }

} 
