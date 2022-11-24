/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/24 23:07:17 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		*pipes;
	int		status;
	int		inout_fd[2];

	status = 0;
	pipes = NULL;
	if (ac <= 4)
		return (1);
	get_inout_files(&inout_fd[0], ac, av);
	cmds = ft_extract_cmds(ac, av, env);
	pipes = ft_manage_pipes(pipes, ac, PIPE);
	pid_t	pid;
	int		i = 0;
	while (cmds[i].id)
	{
		if ((pid = fork()) == -1)
			perror(">>> Error creating child process <<<\n");
		if (pid == 0)
		{
			if (cmds[i].id == 1)
				dup2(inout_fd[0], 0);
			if (cmds[i].id == ac - 3)
				dup2(inout_fd[1], 1);
			if (cmds[i].id > 1)
				dup2(pipes[2 * i - 2], 0);
			if (cmds[i].id < ac - 2)
				dup2(pipes[2 * i + 1], 1);
			ft_manage_pipes(pipes, ac, CLOSE);
			close(inout_fd[0]);
			close(inout_fd[1]);
			execve(cmds[i].path, cmds[i].args, env);
		}
		i++;
	}
	ft_clear_cmds(cmds);
	free(pipes);
	return (status);
}

/*int	ft_exec_cmd(t_cmd *cmd, char **env, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == -1)
		perror("Error creating child process \n");
	if (pid == 0)
	{
		dup2(in_fd, 0);
		dup2(out_fd, 1);
		close(in_fd);
		close(out_fd);
		execve(cmd->path, cmd->args, env);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
*/
int	*get_inout_files(int *fd, int ac, char **av)
{
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		return (0);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == -1)
		return (0);
	return (fd);
}
/*
int	ft_exec_cmds(t_cmd *cmds, char **av, int ac, char **env, int *pipes)
{
	pid_t	pid;
	int		i;
	int		fd_tmp;

	i = 0;
	while (cmds->id)
	{
		if ((pid = fork()) == -1)
			perror("Error creating child process \n");
		else if (pid == 0)
		{
			if (cmds->id == 1)
			{
				fd_tmp = open(av[1], O_RDONLY);
				if (fd_tmp == -1)
					return (0);
				dup2(fd_tmp, 0);
				close(fd_tmp);
			}
			if (cmds->id == ac - 3)
			{
				fd_tmp = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
				if (fd_tmp == -1)
					return (0);
				dup2(fd_tmp, 1);
				close(fd_tmp);
			}
			if (cmds->id > 1)
				dup2(pipes[(2 * i) - 2], 0);
			if (cmds->id < ac - 2)
				dup2(pipes[2 * i + 1], 1);
//			ft_manage_pipes(inout_fd, 5, CLOSE);
			ft_manage_pipes(pipes, ac, CLOSE);
			execve(cmds->path, cmds->args, env);
		}
		cmds++;
		i++;
	}
	return (0);
}
*/

int *ft_manage_pipes(int *pipes, int ac, int flag)
{
	int	i;

	if (flag == PIPE)
		pipes = (int *) malloc(sizeof(int) * (2 * ac - 8));
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
