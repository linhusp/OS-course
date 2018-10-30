#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int pnum, count, pid, child_no;
	pnum = atoi(argv[1]);
	
	if (pnum <= 0)
	{
		printf("process = 0");
		return 1;
	}
	else
	{
		pid = 1;
		
		for (count = 0; count < pnum; count++)
		{
			if (pid != 0) pid = fork();
			else break;
		}

		if (pid == 0)
		{
			child_no = count;
			printf("process %d, pid: %d\n", child_no, getpid());
		}
		else
		{
			for (count = 0; count < pnum; count++)
				wait(NULL);
			
			printf("parent id: %d\n", getpid());
		}
	}

	return 0;				
}
