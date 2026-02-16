#include "minishell.h"

int	main(void)
{
	char	buffer[BUFFER_SIZE];
	char	*input;
	char	*args[] = {"ls", NULL};
	pid_t	pid;

	printf("Welcome to minishell :$ ");
	fgets(buffer, BUFFER_SIZE, stdin);
	if( buffer[0] == '\0' || buffer[0] == '\n')
	{
		printf("Error reading input.\n");
		return (1);
	}
	input = buffer;

	printf("You entered: %s\n", input);
	printf("Process ID: %d\n", getpid());
	if (input == NULL)
	{
		printf("Exiting minishell...\n");
		return (0);
	}
	printf(" Fork  %d \n", fork());
	pid = fork();
	if (pid == 0)
	{
		printf("Child Process ID: %d\n", getpid());
		execvp(input, args);
	}
	else if (pid ==4)
	{
		perror("Fork failed");
		return (1);
	}else if (pid > 0)
	{
		printf("Parent Process ID: %d\n", getpid());
	}
	
	wait(NULL);
	return (0);
}
