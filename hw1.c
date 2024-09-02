#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MINPID 0
#define MAXPID 128

unsigned int bitmap[4];

int testBit(int k)
{
	int tmp;
	tmp = bitmap[(k/32)]&(1<<(k%32)); 
	
	return tmp;
}

int allocate_map(){
	int i;
	for(i=0; i<4; i++){
		bitmap[i] = 0;
	}
	
	if(i!=0)	return 1;
	else		return -1;
}

int allocate_pid(){
	int i;
	
	for(i=0; i<MAXPID; i++){
		if(!testBit(i)){	// if 0 -> not set		
			bitmap[(i/32)] = bitmap[(i/32)]|(1<<(i%32));
			return i;
		}
	}
	return -1;
}

void release_pid(int k){
	bitmap[(k/32)] = bitmap[(k/32)]&~(1<<(k%32)); 	
}

void show(){
	int i;
	for(i=0; i<4; i++){
		printf("bitmap[%d] = %u\n",i,bitmap[i]);
	}
}

int main(){
	int map = 0, choose = 0, del = 0, pid = 0;;
	
	while(map!=1){
		map = allocate_map();
	}
	
	printf("-------------Allocating bitmap-------------\n");
	show();
	
	while(choose != 3){
		printf("-------------------------------------------\n");
		printf("(1)create a process (2)delete a process (3)exit\nPlease enter your choise : ");
		scanf("%d",&choose);

		
		if(choose == 1){
			pid = allocate_pid();
			
			if(pid >= 0)
				printf("Sucessful to allocate PID. The PID of new process : %d\n",pid);
			else{
				printf("Failed to allocate.\n");
				continue;	
			}
				
		}	
		if(choose == 2){
			printf("PLease enter the PID you want to delete : ");
			scanf("%d", &del);
			//printf("pid:%d,del:%d\n",pid,del);
			if(!testBit(del)){
				
				printf("\n\nThis Pid is not allocated\n");
				continue;
			}
			else{
				release_pid(del);
			}
				
		}
		if (choose == 3){
			printf("Exit this Process !\n");
			break;
		}	
		show();
	}
	
	
	
	return 0;
} 
