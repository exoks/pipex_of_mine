/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/23 20:15:11 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	**ft_get_paths(char **env);
char	*ft_get_cmd_path(char *cmd_name, char **env);
t_cmd	*ft_extract_cmds(int ac, char **av, char **env);
int		*ft_manage_pipes(int *pipes, int ac, int flag);

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		*pipes;

	if (ac < 4)
		return (0);
	cmds = ft_extract_cmds(ac, av, env);
	pipes = ft_manage_pipes(pipes, ac, PIPE);
	/*while (cmds->id)
	{
		printf("===================================\n");
		printf("id ===> %d\n", cmds->id);
		printf("path ===> %s\n", cmds->path);
		while (*(cmds->args))
			printf("arg :-> %s\n", *(cmds->args)++);
		cmds++;
	}*/
	return (0);
}

int *ft_manage_pipes(int *pipes, int ac, int flag)
{
	int	i;

	if (flag == PIPE)
		pipes = malloc(sizeof(int) * (2ac - 8));
	if (!pipes)
		return (0);
	i = -1;
	while (++i < 2ac - 8)
	{
		if (flag == PIPE)
			pipe(pipes[i++]);
		if (flag == CLOSE)
			close(pipes[i]);
	}
	return (pipes);
}

char	**ft_get_paths(char **env)
{
	while (*env && !ft_strnstr(*env, "PATH", 4))
		env++;
	if (*env)
		return (ft_split(ft_strchr(*env, '/'), ':'));
	return (0);
}

char	*ft_get_cmd_path(char *cmd_name, char **env)
{
		int		i;
		char	*tmp;
		char	**paths;
		char	*path;

		path = 0;
		paths = ft_get_paths(env);
		if (!paths)
			write(2, "PATH NOT FOUND \n", 16);
		i = -1;
		while (paths[++i])
		{
			tmp = ft_strjoin(paths[i], cmd_name);
			if (!access(tmp, F_OK))
				path = ft_strjoin(paths[i], cmd_name);
			free(tmp);
			free(paths[i]);
		}
		free(cmd_name);
		free(paths);
		return (path);
}

t_cmd	*ft_extract_cmds(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		i;

	cmds = (t_cmd *) malloc(sizeof(t_cmd) * ac - 2);
	if (!cmds)
		return (0);
	i = 1;
	while (++i < ac - 1)
	{
		cmds[i - 2].id = i - 1;
		cmds[i - 2].args = ft_split(av[i], ' ');
		cmds[i - 2].path = ft_get_cmd_path(ft_strjoin("/", (cmds[i - 2].args)[0]), env);
	}
	cmds[i - 2].id = 0;
	return (cmds);
}
