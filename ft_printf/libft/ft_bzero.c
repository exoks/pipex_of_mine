/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:18:19 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/02 18:02:37 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	char	*med;
	size_t	i;

	med = (char *)b;
	i = 0;
	while (i < len)
		med[i++] = 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	int	index;

	index = atoi(av[2]);
	bzero(av[1], index);
	printf("%s\n", av[1]);
	printf("%s\n", &av[1][index]);
	return (0);
}*/
