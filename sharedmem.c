#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

// Shared Memory:
// 	A segment of heap memory can be accessed by multiple processes:
// 		-- via a key that is known by any process that needs to access it
// 		-- shared memory does not get released when a program exits.
// 	5 shared memory operations:
// 		1. shmget()
// 			* used to create the segment (happens once)
// 			* used to access the segment (happens once per process)
// 		2. shmat()
// 			* attach the segment to a variable (once per process)
// 		3. shmdt()
// 			* detach teh segment from a variable (once per process)
// 		4. shmctl()
// 			* remove the segment (happens once)
// ipcs -m: command line utility that prints current shared memory
// ipcs -M: to see what you can do with shared memory on your pc
#define KEY 24601
#define SEG_SIZE 200


int main(){
	int shmd;
	char *data;

	char input[3];
	shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
	data = shmat(shmd,0 ,0);
	// 2nd argument used for specifying address
	// SHM_RDONLY FLAG as third argument if specified
	if (!(*data)){
		printf("New segment,nothing there\n");
		printf("Add data? (y/n): ");
	}
	else{
		// printf()
		printf("Current content is: %s\n",data);
		printf("Modify data? (y/n): ");
	}
	// printf("More data? (y/n): ");
	fgets(input,3,stdin);
	if (input[0] == 'y'){
		printf("Enter new data: ");
		fgets(data,200,stdin);
		// *strchr(data,'\0');
		// *strchr(data,'\n') = 0;
		printf("Content is now: %s",data);
	}
	printf("Delete Segment? (y/n): ");
	fgets(input,3,stdin);
	if (input[0] == 'y'){
		shmctl(shmd,IPC_RMID,0);
		printf("Segment deleted\n");
	}

	return 0;
}

