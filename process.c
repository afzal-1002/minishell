#include "minishell.h"

int	main(void)
{
	printf("Hello Parent Pid %d \n", getpid());
	printf(" First Child: %d Pid %d \n", fork(), getpid());
	printf(" Second Child: %d Pid %d \n", fork(), getpid());
	printf("Hello\n");
	return (0);
}
