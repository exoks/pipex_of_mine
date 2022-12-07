/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/07 20:10:20 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_wait_child_ps(t_cmd *cmds, int *status);

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		*pipes;
	int		status;
	int		inout_fd[2];
	int		is_here_doc;

	if (ac <= 4)
		return (EXIT_FAILURE);
	pipes = NULL;
	is_here_doc = (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])));
//	printf("HERE_DOC|==> %s\n", (is_here_doc)? "yes": "no");
	pipes = ft_manage_pipes(pipes, ac - 3, PIPE);
	if (is_here_doc)
		av = ft_here_doc(ac--, av, pipes);
	cmds = ft_extract_cmds(ac, av, env);
//	ft_print_cmds(cmds);
	get_inout_files(cmds, &inout_fd[0], is_here_doc);
	ft_exec_cmds(cmds, env, pipes, inout_fd, is_here_doc);
	ft_manage_pipes(inout_fd, 2, CLOSE);
	ft_manage_pipes(pipes, cmds->ncmds + is_here_doc, CLOSE);
	ft_wait_child_ps(cmds, &status);
	ft_clear(cmds, pipes);
	return (WEXITSTATUS(status));
}

void	ft_wait_child_ps(t_cmd *cmds, int *status)
{
	while (cmds->id)
		if (waitpid((*cmds++).pid, status, 0) == -1)
			exit(EXIT_FAILURE);
}

int	get_inout_files(t_cmd *cmds, int *inout_fd, int is_here_doc)
{
	int	flag;

	flag = O_APPEND * (is_here_doc) + O_TRUNC * (!is_here_doc);
	inout_fd[1] = open(cmds->outfile, O_CREAT | O_WRONLY | flag, 0644);
	if (inout_fd[1] == -1)
		exit(EXIT_FAILURE);
	if (!is_here_doc)
		inout_fd[0] = open(cmds->infile, O_CREAT | O_RDONLY, 0644);
	return (0);
}

int	ft_print_err_mssg(t_cmd *cmds)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		perror(0);
	if (pid == 0)
	{
		dup2(2, 1);
		if (!cmds->path)
			ft_printf("pipex: %s: command not found\n", cmds->name);
		if (!access(cmds->name, F_OK) && access(cmds->name, X_OK))
			ft_printf("pipex: permission denied: %s\n", cmds->name);
	}
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
			if (cmds[i].id == 1 && inout_fd[0] == -1)
				break;
			if (cmds[i].id == 1 && inout_fd[0] != -1)
				dup2(inout_fd[0] * !is_here_doc + (pipes[0] * is_here_doc), 0);
			if (cmds[i].id > 1)
				dup2(pipes[2 * i - (2 * (!is_here_doc))], 0);
			if (cmds[i].id < cmds[i].ncmds)
				dup2(pipes[2 * i + 1 + (2 * is_here_doc)], 1);
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

int	*ft_manage_pipes(int *pipes, int ncmds, int flag)
{
	int	i;

	if (flag == PIPE && !(pipes = malloc(sizeof(int) * (2 * ncmds - 2))))
		exit(EXIT_FAILURE);
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
