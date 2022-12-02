#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int ac, char **av, char **env)
{
//	int	fd = open("test.txt", O_RDONLY);
//	printf("[fd]:-=> %d\n", fd);
//	dup2(fd, 0);
//	printf("return :=> %d\n", execve("/bin/cat", &av[1], env));
	execve("./hello world.sh", &av[1], env);
	perror(0);
	return (0);
}
