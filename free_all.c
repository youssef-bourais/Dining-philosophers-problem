/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:25:54 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:29:13 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_argument *philo_info, t_philo *philosofers)
{
	int	i;

	i = 0;
	while (i < philo_info->number_of_philosophers)
		pthread_mutex_destroy(&(philo_info->forks[i++]));
	pthread_mutex_destroy((philo_info->print));
	free(philosofers);
	free(philo_info->print);
	free(philo_info->nbr_of_meals);
	free(philo_info->forks);
	free(philo_info->last_meal);
	free(philo_info->th);
}
