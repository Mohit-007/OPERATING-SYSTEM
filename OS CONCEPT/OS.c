#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

main(int argc, char *argv[6])
{	   int fib[5];
		int i;
		int pid;
		fib[0] = 0;
		fib[1] = 1;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error occurred\n");
		}
	else

	if (pid == 0) {
		for(i = 1; i < 6; i++)
				fib[i] = fib[i-1] + fib[i-2];

		for (i = 1; i < argc; i++)
				printf("%3d   %6d\n", argv[i], i < argc - 1 ? " " : "");
	wait (5);
		   printf("Parent waiting for child\n");
	exit(1);
	}
	else
	return 0;
}

