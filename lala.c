#include <signal.h>
#include <stdio.h>

void test(int signum)
{
	printf("LALA = %d\n", signum);
}

int		main()
{
	struct sigaction psa;

	psa.sa_handler = test;
	sigaction(SIGTSTP, &psa, NULL);
	while(1);
	return (0);
}
