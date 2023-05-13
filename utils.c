/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:37:39 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:28:43 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

long	a_toi(char *str, int *handler)
{
	int		i;
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

int	ft_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

int	timer(t_philo *time)
{
	struct timeval	t_1;

	gettimeofday(&t_1, 0);
	return ((t_1.tv_sec * 1000 + t_1.tv_usec / 1000) - (time->bridg->t_0.tv_sec
			* 1000 + time->bridg->t_0.tv_usec / 1000));
}

void	ft_usleep(unsigned int time, t_philo *philo)
{
	struct timeval	t_0;
	struct timeval	t_1;

	gettimeofday(&t_1, 0);
	gettimeofday(&t_0, 0);
	while (1)
	{
		if ((t_1.tv_sec * 1000 + t_1.tv_usec / 1000) - (t_0.tv_sec * 1000
				+ t_0.tv_usec / 1000) >= time)
			return ;
		pthread_mutex_lock(philo->bridg->print);
		if (philo->bridg->flage == 0)
		{
			pthread_mutex_unlock(philo->bridg->print);
			return ;
		}
		pthread_mutex_unlock(philo->bridg->print);
		usleep(200);
		gettimeofday(&t_1, 0);
	}
}
