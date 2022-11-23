/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:28:36 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/02 18:44:02 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0 && s[len] != c)
		len--;
	if (len == -1)
		return (0);
	return ((char *) &s[len]);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	str[7] = "oussama";

	printf("%s\n", strrchr(str, 7));
	return (0);
}
*/
