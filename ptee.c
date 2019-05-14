/* ptee.c - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>

static void usage(void);
static int write_all(int, const char *, size_t);

int
main(int argc, char **argv)
{
	static char buf[4096];

	int child_fds[2];
	int child_pid;
	ssize_t nread;
	int status;

#ifdef __OpenBSD__
	if (pledge("stdio proc exec", NULL) == -1)
		err(1, "pledge");
#endif

	if (getopt(argc, argv, "") != -1)
		usage();

	argc -= optind;
	argv += optind;

	if (!argc)
		usage();

	if (pipe(child_fds) == -1)
		err(1, "pipe");
	if ((child_pid = fork()) == -1)
		err(1, "fork");

	if (!child_pid) {
		if (dup2(child_fds[0], STDIN_FILENO) == -1)
			err(1, "dup2");
		if (close(child_fds[0]) == -1)
			err(1, "close");
		if (close(child_fds[1]) == -1)
			err(1, "close");
		execvp(argv[0], argv);
		err(1, "%s", argv[0]);
	}

	while ((nread = read(STDIN_FILENO, buf, sizeof(buf)))) {
		if (nread == -1)
			err(1, "<stdin>");
		if (write_all(STDOUT_FILENO, buf, nread) == -1)
			err(1, "<stdout>");
		if (write_all(child_fds[1], buf, nread) == -1)
			err(1, "%s", argv[0]);
	}

	if (close(child_fds[1]) == -1)
		err(1, "close");
	if (wait(&status) == -1)
		err(1, "wait");

	return status;
}

static void
usage(void)
{
	fputs("usage: ptee program [argument ...]\n", stderr);
	exit(1);
}

static int
write_all(int fd, const char *buf, size_t num)
{
	ssize_t nwritten;

	while (num) {
		if ((nwritten = write(fd, buf, num)) == -1)
			return -1;
		buf += nwritten;
		num -= nwritten;
	}

	return 0;
}
