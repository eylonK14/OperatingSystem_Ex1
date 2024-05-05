#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(char *cmd[], int input_fd, int output_fd)
{
    if (fork() == 0)
	{
        if (input_fd != STDIN_FILENO)
		{
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO)
		{
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        execvp(cmd[0], cmd);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
	// this program assumes that the input is enclosed in double quotes ,
    // and that the name and phone number are separated by a comma
	if (argc != 2)
	{
		printf("Usage: %s <name>\n", argv[0]);
		exit(1);
	}
	char *name = argv[1];
	int pipe1[2], pipe2[2], pipe3[2];

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1)
	{
        perror("pipe");
        return EXIT_FAILURE;
    }

    // grep name phonebook.txt
    char *grep_args[] = {"grep", name, "phonebook.txt", NULL};
    execute_command(grep_args, STDIN_FILENO, pipe1[1]);
    close(pipe1[1]); // Close write end of the first pipe in the parent

    // sed 's/ /#/g'
    char *sed_args1[] = {"sed", "s/ /#/g", NULL};
    execute_command(sed_args1, pipe1[0], pipe2[1]);
    close(pipe1[0]); // Close read end of the first pipe
    close(pipe2[1]); // Close write end of the second pipe in the parent

    // sed 's/,/ /'
    char *sed_args2[] = {"sed", "s/,/ /", NULL};
    execute_command(sed_args2, pipe2[0], pipe3[1]);
    close(pipe2[0]); // Close read end of the second pipe
    close(pipe3[1]); // Close write end of the third pipe in the parent

    // awk '{ print $2 }'
    char *awk_args[] = {"awk", "{ print $2 }", NULL};
    execute_command(awk_args, pipe3[0], STDOUT_FILENO);
    close(pipe3[0]); // Close read end of the third pipe

    // Wait for all child processes to finish
    while (wait(NULL) > 0) {};

	return 0;
}