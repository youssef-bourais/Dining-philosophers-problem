/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:24:26 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/04 21:53:00 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int nbr_word(char *str)
{
	int i = 0;
	int counter = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i + 1] == ' ') || (str[i] != ' ' && str[i + 1] == '\0'))
			counter ++;
		i++;
	}
	return counter;
}


void *ft_copy(char *dst, char *src, int size)
{
	int i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return dst;	
}

char *ft_slice(char *str, int start, int len)
{
	char *s = (char *)malloc(sizeof(char ) * (len + 1));
	if (!s)
		return NULL;
	ft_copy(s, str + start, len);
	s[len] = '\0';
	return s;
}

int end_word(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i + 1] == ' ') || (str[i] != ' ' && str[i + 1] == '\0'))
			return i + 1;
		i++;
	}
	return 0;
}

char **ft_split(char *str)
{
	int i = 0;
	int nbr = nbr_word(str);
	char **tab = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!tab)
		return NULL;
	
	int j = 0;
	int k = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
		{
			j = end_word(str + i);
			tab[k] = ft_slice(str, i, j);
			i = i + j;
			k++;
		}
	}
	tab[k] = 0;
	return (tab);
}
