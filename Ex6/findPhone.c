#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <name>\n", argv[0]);
		exit(1);
	}
	char *name = argv[1];
	char *grepCmd[] = {"grep", name, "phonebook.txt", NULL};
	char *sedCmd[] = {"sed", "s/#/ /", NULL};
	char *secondSedCmd[] = {"sed", "s/,/ /", NULL};
	// we are doing this command: grep name phonebook.txt | sed 's/ /#/g' | sed 's/,/ /' | awk '{ print $2 }'
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	pid_t pid1 = fork();
	if (pid1 == 0) {
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe1[1]);
		execvp(grepCmd[0], grepCmd);
	}
	pid_t pid2 = fork();
	if (pid2 == 0) {
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(sedCmd[0], sedCmd);
	}
	pid_t pid3 = fork();
	if (pid3 == 0) {
		dup2(pipe2[0], 0);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(secondSedCmd[0], secondSedCmd);
	}
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
	char *awkCmd[] = {"awk", "{ print $2 }", NULL};
	pid_t pid4 = fork();
	if (pid4 == 0) {
		dup2(0, 0);
		execvp(awkCmd[0], awkCmd);
	}
	waitpid(pid4, NULL, 0);
	return 0;
}