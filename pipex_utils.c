/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:40:18 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/23 17:42:05 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_cmd	*ft_last_cmd(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->next == 0)
			return (cmds);
		cmds = cmds->next;
	}
	return (0);
}
