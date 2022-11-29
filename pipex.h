/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:09:44 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/27 19:10:40 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# define PIPE 1
# define CLOSE 0
# define EXIT_ERROR 127

typedef struct s_cmd
{
	int		id;
	char	*name;
	char	*path;
	char	**args;
	int		ncmds;
	char	*infile;
	char	*outfile;
	pid_t	pid;
}t_cmd;

t_cmd	*ft_extract_cmds(int ac, char **av, char **env);
int		*ft_manage_pipes(int *pipes, int ncmds, int flag);
int		ft_exec_cmds(t_cmd *cmds, char **env, int *pipes, int *inout_fd);
void	ft_clear_cmds(t_cmd *cmds);
int		get_inout_files(t_cmd *cmds, int *inout_fd);
void	ft_print_cmds(t_cmd *cmds);
#endif
