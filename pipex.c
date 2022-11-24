/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/24 01:25:04 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int	*pipes;

	pipes = NULL;
	if (ac < 4)
		return (0);
	cmds = ft_extract_cmds(ac, av, env);
	pipes = ft_manage_pipes(pipes, ac, PIPE);
	ft_exec_cmds(cmds, av, ac, env, pipes);
//	while (--ac - 2)
//		wait(0);
	ft_manage_pipes(pipes, ac, CLOSE);
	ft_clear_cmds(cmds);
	free(pipes);
	return (0);
}

int	ft_exec_cmds(t_cmd *cmds, char **av, int ac, char **env, int *pipes)
{
	pid_t	pid;
	int	fd_tmp;
	int	i;

	i = 0;
	while (cmds->id)
	{
		pid = fork();
		if (pid == -1)
			perror("Error creating child process \n");
		if (pid == 0)
		{
			if (cmds->id == 1)
			{
				fd_tmp = open(av[1], O_RDONLY);
				if (fd_tmp == -1)
					return (0);
				dup2(fd_tmp, 0);
				close(fd_tmp);
			}
			/*if (cmds->id == ac - 3)
			{
				fd_tmp = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
				if (fd_tmp == -1)
					return (0);
				dup2(fd_tmp, 1);
				close(fd_tmp);
			}*/
			if (cmds->id > 1)
				dup2(pipes[(2 * i) - 2], 0);
			if (cmds->id < ac - 2)
				dup2(pipes[2 * i + 1], 1);
			ft_manage_pipes(pipes, ac, CLOSE);
			execve(cmds->path, cmds->args, env);
		}
		i++;
		cmds++;
	}
	return (0);
}

int *ft_manage_pipes(int *pipes, int ac, int flag)
{
	int	i;

	if (flag == PIPE)
		pipes = malloc(sizeof(int) * (2 * ac - 8));
	if (!pipes)
		return (0);
	i = -1;
	while (++i < 2 * ac - 8)
	{
		if (flag == PIPE)
			pipe(&pipes[i++]);
		if (flag == CLOSE)
			close(pipes[i]);
	}
	return (pipes);
}
