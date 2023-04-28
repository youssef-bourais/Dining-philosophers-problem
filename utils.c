/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:37:39 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/28 10:40:06 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_len(char *str)
{
	int i = 0;
	if (!str)
		return 0;
	while (str[i] != '\0')
		i ++;
	return i;	
}

long	a_toi(char *str, int *handler)
{
	int	i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (!(str[i] >= '0' && str[i] <= '9'))
		*handler = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*handler = 1;	
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || res >= INT_MAX)
		*handler = 0;
	return (res);
}

int ft_error()
{
	write(2, "Error\n", 6);
	return 1;
}

void free_table(char **table, int size)
{
	int i = 0;
	while (i < size)
	{
		free(table[i]);
		i ++;
	}
	free(table);
}

int _nbr(int argc, char *argv[])
{
	int i = 0;
	int counter = 0;
	int h;
	while (i < argc - 1)
	{
		char **temp = ft_split(argv[i + 1]);
		h = 0;
		while (temp[h] != NULL)
		{
			counter ++;
			h++;
		}
		free_table(temp, h);
		i++;
	}
	return counter;
}