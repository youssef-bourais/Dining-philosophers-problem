/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:03:27 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/06 13:27:46 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
# include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
# include <limits.h>

typedef struct indices
{
	int i;
	int j;
	int k;
	int h;
	int e;
	char **temp;
} s_indices;

typedef struct info
{
	int e;
	int *arr;
}	s_info;

typedef struct argument t_argument;

typedef struct argument
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;

	pthread_mutex_t *forks;
	pthread_mutex_t for_printing;
	struct timeval t_0;
}	t_argument;

typedef struct philosofers
{
	int philo_id;
	int left_fork;
	int right_fork;
	int flage_of_eating;
	pthread_t th;
	t_argument bridg;
}	s_philo;

int nbr_word(char *str);
void *ft_copy(char *dst, char *src, int size);
char *ft_slice(char *str, int start, int len);
int end_word(char *str);
char **ft_split(char *str);
int ft_error();
int ft_len(char *str);
long	a_toi(char *str, int *handler);
void free_table(char **table, int size);
int _nbr(int argc, char *argv[]);

#endif
