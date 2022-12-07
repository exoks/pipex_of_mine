/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:25:27 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/07 15:57:00 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*get_next_line(fd)
{
	char	c;
	char	*buff;
	char	*tmp;

	buff = ft_strdup("");
	while (read(fd, &c, 1) > 0 && c != '\n')
	{
		tmp = ft_strjoin(buff, &c);
		free(buff);
		buff = tmp;
	}
	if (c == '\n')
	{
		tmp = ft_strjoin(buff, "\n");
		free(buff);
		buff = tmp;
	}
	return (buff);
}

char  **ft_here_doc(int ac, char **av, int *pipes)
{
	char    **tab;
	int     i;
	char	*s;

	if (ac <= 5)
		exit(EXIT_FAILURE);	
	tab = (char **) malloc(sizeof(char *) * (ac - 1));
	if (!tab)
		return (0);
	tab[0] = av[0];
	tab[1] = "";
	i = -1;
	while (av[++i + 3])
		tab[i + 2] = av[i + 3];
	tab[i + 2] = NULL;
	s = get_next_line(0);
	 while (ft_strncmp(s, av[2], ((ft_strlen(s) - 1) * (ft_strlen(s) - 1 >= ft_strlen(av[2])) + 
					 (ft_strlen(av[2]) * (ft_strlen(s) - 1 < ft_strlen(av[2]))))))
	 {
		 write(pipes[1], s, ft_strlen(s));
	//	 printf("line :-> %s\n", s);
		 free(s);
		 s = get_next_line(0);
	 }
	 return (tab);
}
