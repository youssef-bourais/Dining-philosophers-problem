/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:10:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:26:27 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nbr_of_meals(t_argument *philo_info)
{
	int	i;
	int	j;

	j = philo_info->number_of_times_each_philosopher_must_eat;
	if (j == 0)
		return (0);
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (philo_info->nbr_of_meals[i] >= j)
			i++;
		else
			return (0);
	}
	return (1);
}

void	kill(t_argument *philo_info, struct timeval t_now, int id)
{
	usleep(500);
	gettimeofday(&t_now, 0);
	pthread_mutex_lock(philo_info->print);
	philo_info->flage = 0;
	printf("%ld %d died\n", (t_now.tv_sec * 1000 + t_now.tv_usec / 1000)
		- (philo_info->t_0.tv_sec * 1000 + philo_info->t_0.tv_usec / 1000),
		id + 1);
	pthread_mutex_unlock(philo_info->print);
}

int	stop(t_argument *philo_info, struct timeval t_now, int id)
{
	if ((t_now.tv_sec * 1000 + t_now.tv_usec / 1000)
		- (philo_info->last_meal[id].tv_sec * 1000
			+ philo_info->last_meal[id].tv_usec
			/ 1000) >= philo_info->time_to_die)
	{
		return (1);
	}
	return (0);
}

int	check_philosophers(t_argument *philo_info, struct timeval t_now)
{
	int	id;

	id = 0;
	while (id < philo_info->number_of_philosophers)
	{
		if (stop(philo_info, t_now, id))
		{
			kill(philo_info, t_now, id);
			return (0);
		}
		pthread_mutex_lock(philo_info->print);
		if (check_nbr_of_meals(philo_info))
		{
			philo_info->flage = 0;
			pthread_mutex_unlock(philo_info->print);
			return (0);
		}
		pthread_mutex_unlock(philo_info->print);
		id++;
	}
	return (1);
}

void	*check_and_kill(void *arg)
{
	t_argument		*philo_info;
	struct timeval	t_now;

	philo_info = (t_argument *)arg;
	while (1)
	{
		gettimeofday(&t_now, 0);
		if (!check_philosophers(philo_info, t_now))
			return (NULL);
	}
	return (NULL);
}
