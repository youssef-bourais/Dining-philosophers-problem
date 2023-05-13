/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:43:52 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:15:12 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_action(void *arg)
{
	t_philo	*philosofers;

	philosofers = (t_philo *)arg;
	if (philosofers->philo_id % 2 != 0)
	{
		ft_print("is thinking", philosofers);
		ft_usleep((philosofers->bridg->time_to_eat), philosofers);
	}
	while (1)
	{
		pthread_mutex_lock(philosofers->bridg->print);
		if (philosofers->bridg->flage == 0)
		{
			pthread_mutex_unlock(philosofers->bridg->print);
			return (NULL);
		}
		pthread_mutex_unlock(philosofers->bridg->print);
		eating(philosofers);
		sleeping(philosofers);
		thinking(philosofers);
	}
	return (NULL);
}

void	init_philo(t_philo *philo, t_argument *philo_info)
{
	int	i;

	philo_info->forks = malloc(sizeof(pthread_mutex_t)
			* philo_info->number_of_philosophers);
	philo_info->print = malloc(sizeof(pthread_mutex_t));
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (philo_info->number_of_philosophers + i - 1)
			% philo_info->number_of_philosophers;
		philo[i].bridg = philo_info;
		gettimeofday(&philo_info->last_meal[i], 0);
		gettimeofday(&philo[i].bridg->t_0, 0);
		pthread_mutex_init(&(philo_info->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(philo->bridg->print, NULL);
	i = 0;
	while (i < philo_info->number_of_philosophers)
		philo_info->nbr_of_meals[i++] = 0;
}

void	allocation(t_argument *philo_info)
{
	philo_info->last_meal = malloc(sizeof(struct timeval)
			* philo_info->number_of_philosophers);
	philo_info->nbr_of_meals = malloc(sizeof(int)
			* philo_info->number_of_philosophers);
	philo_info->th = malloc(sizeof(pthread_t)
			* (philo_info->number_of_philosophers + 1));
}

int	creat_phiolosofers(t_argument *philo_info)
{
	t_philo	*philosofers;
	int		i;

	philo_info->flage = 1;
	philosofers = malloc(sizeof(t_philo) * philo_info->number_of_philosophers);
	allocation(philo_info);
	init_philo(philosofers, philo_info);
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (pthread_create(&(philo_info->th[i]), NULL, &ft_action,
				&philosofers[i]))
			return (0);
		i++;
	}
	pthread_create(&(philo_info->th[i]), NULL, &check_and_kill, philo_info);
	i = 0;
	while (i <= philo_info->number_of_philosophers)
		pthread_join(((philo_info->th[i++])), NULL);
	free_resources(philo_info, philosofers);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_argument	arg;

	info = fill_data(argc, argv);
	arg = get_data(info.arr, argc - 1);
	free(info.arr);
	if (info.arr[0] == 0)
		return (0);
	if (info.e == 1 || !creat_phiolosofers(&arg))
	{
		ft_error();
		return (1);
	}
	return (0);
}
