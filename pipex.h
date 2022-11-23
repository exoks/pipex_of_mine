/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:09:44 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/23 19:49:06 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "fcntl.h"
# include <stdio.h>
# define PIPE 1
# define CLOSE 0

typedef struct 		s_cmd
{
	int				id;
	char			*path;
	char			**args;
	struct s_cmd 	*next;
}					t_cmd;

t_cmd	*ft_last_cmd(t_cmd *cmds);
#endif
