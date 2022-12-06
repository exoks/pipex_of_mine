/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/06 20:09:37 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		*pipes;
	int		status;
	int		inout_fd[2];
	int		is_here_doc;

	
	if (ac <= 4)
		return (EXIT_FAILURE);
	status = 0;
	pipes = NULL;
	is_here_doc = (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])));
//	printf("HERE_DOC|==> %s\n", (is_here_doc)? "yes": "no");
	pipes = ft_manage_pipes(pipes, ac - 3, PIPE);
	if (is_here_doc && ac > 5)
		av = ft_here_doc(ac--, av, pipes);
	cmds = ft_extract_cmds(ac, av, env);
//	ft_print_cmds(cmds);
	get_inout_files(cmds, &inout_fd[0], is_here_doc, pipes);
	ft_exec_cmds(cmds, env, pipes, inout_fd, is_here_doc);
	ft_manage_pipes(inout_fd, 2, CLOSE);
	ft_manage_pipes(pipes, cmds->ncmds, CLOSE);
	int	i = -1;
	while (cmds[++i].id)
	{
		if (waitpid(cmds[i].pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
	}
	ft_clear_cmds(cmds);
	free(pipes);
	return (WEXITSTATUS(status));
}

int	get_inout_files(t_cmd *cmds, int *inout_fd, int is_here_doc, int *pipes)
{
	int	flag;

	flag = O_APPEND * (is_here_doc) + O_TRUNC * (!is_here_doc);
	if (is_here_doc)
		inout_fd[0] = dup(pipes[0]);
	else
		inout_fd[0] = open(cmds->infile, O_RDONLY | O_CREAT, 0644);
	inout_fd[1] = open(cmds->outfile, O_CREAT | O_WRONLY | flag, 0644);
	if (inout_fd[1] == -1)
		exit(EXIT_FAILURE);
	return (0);
}

int	ft_print_err_mssg(t_cmd *cmds)
{
	pid_t	pid;
//	char	*tmp;

//	tmp = strerror(errno);
	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		close(1);
		dup2(2, 1);
		if (!cmds->path)
			printf("pipex: %s: command not found\n", cmds->name);
		if (!access(cmds->name, F_OK) && access(cmds->name, X_OK))
			printf("pipex: permission denied: %s\n", cmds->name);
	}
	if (!cmds->path)
		exit(EXIT_ERROR);
	if (!access(cmds->name, F_OK) && access(cmds->name, X_OK))
		return (EXIT_ERROR - 1);
	return (EXIT_ERROR);
}

int	ft_exec_cmds(t_cmd *cmds, char **env, int *pipes, int *inout_fd, int is_here_doc)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (cmds[++i].id)
	{
		if ((pid = fork()) == -1)
			perror("Error creating child process \n");
		if (pid == 0)
		{
			printf("in: %d\nout : %d\n", inout_fd[0], inout_fd[1]);
			if (cmds[i].id == 1)
			{
				if (inout_fd[0] == -1)
					break;
				else if (is_here_doc)
					dup2(pipes[0], 0);
				else
					dup2(inout_fd[0], 0);
			}
			if (cmds[i].id > 1)
			{
				printf("\n=========\nre: %d\n(READ)==> fd[%d]", -1, 2 * i - (2 * (!is_here_doc)));
				/*int re = */dup2(pipes[2 * i - (2 * (!is_here_doc))], 0);
			}
			if (cmds[i].id < cmds[i].ncmds)
			{
				printf("\n=========\nre: %d\n(WRITE)==> fd[%d]", -1, 2 * i + 1 + (2 * is_here_doc));
				/*int re = */dup2(pipes[2 * i + 1 + (2 * is_here_doc)], 1);
			}
			if (cmds[i].id == cmds[i].ncmds)
				dup2(inout_fd[1], 1);
			ft_manage_pipes(pipes, cmds[i].ncmds + is_here_doc, CLOSE);
			ft_manage_pipes(inout_fd, 2, CLOSE);
			if (execve(cmds[i].path, cmds[i].args, env) == -1)
				exit(ft_print_err_mssg(&cmds[i]));
		}
		cmds[i].pid = pid;
	}
	return (0);
}

int *ft_manage_pipes(int *pipes, int ncmds, int flag)
{
	int	i;

	if (flag == PIPE)
		printf("|number of pipes created|=> %d\n", 2 * ncmds - 2);
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
