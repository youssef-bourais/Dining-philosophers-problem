/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:03:27 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/28 16:31:22 by ybourais         ###   ########.fr       */
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



typedef struct s_vars
{
	int i;
	int j;
	int k;
	int h;
	int e;
	char **temp;
}	t_param;

typedef struct s_arg
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
}	t_philo;

typedef struct s_beta
{
	int e;
	int *arr;
}	t_beta;

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
