
#include <unistd.h>
#include <strings.h>

int main(int argc, char const *argv[])
{
	char name[] = "/Users/hgrampa/Desktop/minishell/utilbin/args";
	char *_argv[3];

	_argv[0] = strdup("first");
	_argv[1] = strdup("second");
	_argv[2] = NULL;

	execve(name, _argv, NULL);

	return 0;
}
