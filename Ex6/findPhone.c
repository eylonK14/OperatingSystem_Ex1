#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <name>\n", argv[0]);
		exit(1);
	}
	name = argv[1];
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
	int awkCmd[] = {"awk", "{print $2}", NULL};
	execvp(awkCmd[0], awkCmd);
	return 0;
}