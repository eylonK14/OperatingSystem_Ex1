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
	char *cutCmd[] = {"cut", "-d", " ", "-f", "2", NULL};
	int pipefd[2];
	pipe(pipefd);
	if (fork() == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execvp(grepCmd[0], grepCmd);
	} else {
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execvp(cutCmd[0], cutCmd);
	}
	// replace spaces with hashtag
	int pipefd2[2];
	pipe(pipefd2);
	if (fork() == 0) {
		close(pipefd2[0]);
		dup2(pipefd2[1], 1);
		close(pipefd2[1]);
		char *sedCmd[] = {"sed", "s/#/ /", NULL};
		execvp(sedCmd[0], sedCmd);
	} else {
		close(pipefd2[1]);
		dup2(pipefd2[0], 0);
		close(pipefd2[0]);
	}
	// replace comma with space
	int pipefd3[2];
	pipe(pipefd3);
	if (fork() == 0) {
		close(pipefd3[0]);
		dup2(pipefd3[1], 1);
		close(pipefd3[1]);
		char *secondSedCmd[] = {"sed", "s/,/ /", NULL};
		execvp(secondSedCmd[0], secondSedCmd);
	} else {
		close(pipefd3[1]);
		dup2(pipefd3[0], 0);
		close(pipefd3[0]);
	}
	char *awkCmd[] = {"awk", "{print $2}", NULL};
	execvp(awkCmd[0], awkCmd);
	return 0;
}