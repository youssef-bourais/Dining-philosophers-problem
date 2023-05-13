/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:22:40 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:34:57 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->bridg->print);
	if (philo->bridg->flage != 0)
		printf("%d %d %s\n", timer(philo), philo->philo_id, msg);
	pthread_mutex_unlock(philo->bridg->print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->bridg->forks[philo->left_fork]));
	if (philo->bridg->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&(philo->bridg->forks[philo->right_fork]));
		return ;
	}
	pthread_mutex_lock(&(philo->bridg->forks[philo->right_fork]));
	ft_print("has taken a fork", philo);
	ft_print("has taken a fork", philo);
	ft_print("is eating", philo);
	gettimeofday(&philo->bridg->last_meal[philo->philo_id - 1], 0);
	ft_usleep((philo->bridg->time_to_eat), philo);
	pthread_mutex_lock(philo->bridg->print);
	philo->bridg->nbr_of_meals[philo->philo_id - 1]++;
	pthread_mutex_unlock(philo->bridg->print);
	pthread_mutex_unlock(&(philo->bridg->forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->bridg->forks[philo->left_fork]));
}

void	sleeping(t_philo *philosofers)
{
	ft_print("is sleeping", philosofers);
	ft_usleep((philosofers->bridg->time_to_sleep), philosofers);
}

void	thinking(t_philo *philosofers)
{
	ft_print("is thinking", philosofers);
}
