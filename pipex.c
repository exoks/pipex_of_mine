/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/29 16:10:59 by oezzaou          ###   ########.fr       */
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
		return (EXIT_FAILURE);
	cmds = ft_extract_cmds(ac, av, env);
	get_inout_files(cmds, &inout_fd[0]);
	pipes = ft_manage_pipes(pipes, cmds->ncmds, PIPE);
	ft_exec_cmds(cmds, env, pipes, inout_fd);
	ft_print_cmds(cmds);
/*	ft_manage_pipes(inout_fd, 2, CLOSE);
	ft_manage_pipes(pipes, cmds->ncmds, CLOSE);
	int	i = -1;
	while (cmds[++i].id)
	{
		if (waitpid(cmds[i].pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
	}
	ft_clear_cmds(cmds);
	free(pipes);
	return (WEXITSTATUS(status));*/
}

int	get_inout_files(t_cmd *cmds, int *inout_fd)
{
	inout_fd[0] = open(cmds->infile, O_RDONLY | O_CREAT, 0644);
	if (inout_fd[0] == -1)
		perror(0);
	inout_fd[1] = open(cmds->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (inout_fd[1] == -1)
	{
		perror(0);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_print_err_mssg(char *cmd_name)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		close(1);
		dup2(2, 1);
		printf("pipex: %s: command not found\n", cmd_name);
	}
	return (EXIT_ERROR);
}

int	ft_exec_cmds(t_cmd *cmds, char **env, int *pipes, int *inout_fd)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (cmds[++i].id)
	{
		if ((pid = fork()) == -1)
			perror("Error creating child process \n");
		else if (pid == 0)
		{
			if (cmds[i].id == 1)
				dup2(inout_fd[0], 0);
			if (cmds[i].id > 1)
				dup2(pipes[(2 * i) - 2], 0);
			if (cmds[i].id < cmds[i].ncmds)
				dup2(pipes[2 * i + 1], 1);
			if (cmds[i].id == cmds[i].ncmds)
				dup2(inout_fd[1], 1);
			ft_manage_pipes(pipes, cmds[i].ncmds, CLOSE);
			ft_manage_pipes(inout_fd, 2, CLOSE);
			if (execve(cmds[i].path, cmds[i].args, env) == -1)
				exit(ft_print_err_mssg(cmds[i].name));
		}
		cmds[i].pid = pid;
	}
	return (0);
}

int *ft_manage_pipes(int *pipes, int ncmds, int flag)
{
	int	i;

	if (flag == PIPE)
		pipes = (int *) malloc(sizeof(int) * (2 * ncmds - 2));
	if (!pipes)
		return (0);
	i = -1;
	while (++i < 2 * ncmds - 2)
	{
		if (flag == PIPE)
			pipe(&pipes[i++]);
		if (flag == CLOSE)
			close(pipes[i]);
	}
	return (pipes);
}
