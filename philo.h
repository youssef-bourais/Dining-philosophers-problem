/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:03:27 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/13 16:15:24 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_info
{
	int e;
	int *arr;
}	t_info;

typedef struct s_argument
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int flage;
	int *nbr_of_meals;
	struct timeval *last_meal;
	struct timeval t_0;
	pthread_t kill;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
	pthread_t *th;
	
}	t_argument;

typedef struct s_philosofers
{
	int philo_id;
	int left_fork;
	int right_fork;
	pthread_t th;
	t_argument *bridg;
}	t_philo;

t_info 		fill_data(int argc, char **argv);
t_argument 	get_data(int *info, int nbr);
void 		allocation(t_argument *philo_info);
int			ft_error();
int 		ft_len(char *str);
long 		a_toi(char *str, int *handler);
void		free_resources(t_argument *philo_info, t_philo *philosofers);
void		ft_print(char *msg, t_philo *philo);
void		ft_usleep(unsigned int time, t_philo *philo);
int			timer(t_philo *time);
void		*check_and_kill(void *arg);
int			check_nbr_of_meals(t_argument *philo_info);
void		thinking(t_philo *philosofers);
void		eating(t_philo *philosofers);
void		sleeping(t_philo *philosofers);
void		*ft_action(void *arg);
int			creat_phiolosofers(t_argument *philo_info);
void		init_philo(t_philo *philo, t_argument *philo_info);

#endif