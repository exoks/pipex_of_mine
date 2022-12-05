/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:25:27 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/05 20:07:19 by oezzaou          ###   ########.fr       */
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

char  **ft_here_doc(int ac, char **av)
{
     char    **tab;
     int     i;
     int     fd;
	 char	*s;
 

     tab = (char **) malloc(sizeof(char *) * (ac - 1));
     if (!tab)
         return (0);
     tab[0] = av[0];
     tab[1] = "file1";
     i = -1;
	 while (av[++i + 3])
	 	tab[i + 2] = av[i + 3];
	 tab[i + 2] = NULL;
//	 i = -1;
//	 while (tab[++i])
//		 printf("=====> %s\n", tab[i]);
	 fd = open(tab[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	 if (fd == -1)
		 return (0);
	 s = get_next_line(0);
	 // i have to work with the greater len
	 while (ft_strncmp(s, av[2], ft_strlen(av[2])) != 0)
	 {
		 write(fd, s, ft_strlen(s));
		 s = get_next_line(0);
	 }
	 close(fd);
	 return (tab);
}
