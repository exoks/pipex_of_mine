/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:09:44 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/24 21:44:34 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# define PIPE 1
# define CLOSE 0

typedef struct s_cmd
{
	int		id;
	char	*path;
	char	**args;
	int		ncmds;
}t_cmd;

t_cmd	*ft_extract_cmds(int ac, char **av, char **env);
int		*ft_manage_pipes(int *pipes, int ac, int flag);
int		ft_exec_cmds(t_cmd *cmds, char **av, int ac, char **env, int *pipes);
void	ft_clear_cmds(t_cmd *cmds);
int		*get_inout_files(int *fd, int ac, char **av);
#endif
