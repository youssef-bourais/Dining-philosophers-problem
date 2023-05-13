/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:24:26 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 17:09:21 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_argument	get_data(int *info, int nbr)
{
	t_argument	arg;

	arg.number_of_philosophers = info[0];
	arg.time_to_die = info[1];
	arg.time_to_eat = info[2];
	arg.time_to_sleep = info[3];
	if (nbr == 5)
		arg.number_of_times_each_philosopher_must_eat = info[4];
	return (arg);
}

t_info	fill_data(int argc, char **argv)
{
	int		i;
	int		flage;
	t_info	info;

	info.arr = malloc(sizeof(int) * (argc - 1));
	i = 0;
	flage = 0;
	if (argc == 5 || argc == 6)
	{
		while (i < argc - 1)
		{
			if ((!a_toi(argv[i + 1], &flage) || a_toi(argv[i + 1], &flage))
				&& flage == 1)
				info.arr[i] = a_toi(argv[i + 1], &flage);
			else
				info.e = 1;
			i++;
		}
	}
	else
		info.e = 1;
	return (info);
}
