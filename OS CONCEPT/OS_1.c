#include<stdio.h>
#include<stdlib.h>


struct process
{
	int pid;     
	int at;      
	int bt;   	 
	int io_bt;   
	int burst_time;
	int cpu_bt;  
	int ct;		 
	int wt;		 
	int flag;	 
	
};


void wait(struct process p[], int n); 

void main()
{
	int n=5,i;
	struct process p[n];
	for(i=0;i<n;i++)
	{
		p[i].pid = i;
		p[i].at = (int)(rand()%5)*2;
		p[i].bt = (int)(rand()%5)*2+2;

	}

	for(i=0;i<n;i++)
	{
		p[i].burst_time = p[i].bt;
	}
	for(i=0;i<n;i++)
	{
		
		p[i].flag = 0;
		p[i].cpu_bt = (p[i].bt)/2;
		p[i].io_bt = (p[i].bt)/2;
	}
	wait(p,n);
	printf("\n\n");

	for(i=0;i<n;i++)
	{
		p[i].wt = p[i].ct - p[i].at - p[i].burst_time + 1;
		
		printf("%d %d %d\n",p[i].pid,p[i].at,p[i].wt);
		
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


void wait(struct process p[], int n) 
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
    
    	count = 0;
    	for(i=0;i<n;i++)
    	{  
    		
			if(p[i].flag != 5 && p[i].flag != 3 && p[i].flag != 2 && p[i].flag != 4 )
			{
	  			if(cpu_t >= p[i].at)
	  		   	{
	  		   		p[i].flag = 1;
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
			if(p[i].flag == 2 && cpu_flag == 101)
    		{
    			p[i].flag = 1;
    			cpu_flag = 0;

			}
		}
		if(p[val].flag == 1)
			p[val].flag = 2;
    	for(i=0;i<n;i++)
    	{
    		if(p[i].flag == 2)
    		{  
    				cpu_flag = 1;
					p[i].bt--;
    				p[i].cpu_bt--;
    				if(p[i].cpu_bt < 0)
    					p[i].cpu_bt = 0;
					if(p[i].cpu_bt == 0)
					{
						cpu_flag = 0;
						p[i].flag = 3;
						min = 1000;
					}
    			

    		}
    		
      	}

			
 	
		
    	for(i=0;i<n;i++)
    	{
	
			if(p[i].flag == 4)
			{

				p[i].io_bt--;
				p[i].bt--;
				if(p[i].bt == 0 || p[i].io_bt == 0)
				{
					io_flag = 0;
					p[i].ct = io_t + 1;
					p[i].flag = 5;
				}
		
			}
	

    		if(p[i].flag == 3)
    		{  
    			if(io_flag == 0)
    			{
    				min = 1000;
    				io_flag = 1;
    				p[i].flag = 4;
    			}
    		}
			
	
    		
    	}


    	for(i=0;i<n;i++)
    	{
    		if(p[i].flag == 5)
    		{
    			count++;
    		}
    	}
    	
    	if(count == n-1)
    	{
			p[val].ct = io_t + p[val].io_bt +p[val].cpu_bt + 1;	
    		break;
		}
    	
    	cpu_t++;
    	io_t++;
    }

} 
