/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:43:52 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/07 21:21:52 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "philo.h"
# include <time.h>
# include <limits.h>

// number_of_philosophers time_to_die time_to_eat time_to_sleep  %% [number_of_times_each_philosopher_must_eat]
// nbr_philo time_d time_e time_s nbr_eting

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

void philo_eating(int nbr, pthread_mutex_t mutex1)
{
	pthread_mutex_lock(&mutex1);
	printf("philosopher %d has take the fork to his right\n", nbr);
	printf("philosopher %d has take the fork to his left\n", nbr);
	printf("philosopher %d is eating\n", nbr);
	pthread_mutex_unlock(&mutex1);
}

void philo_sleeping(int nbr, pthread_mutex_t mutex1)
{
	pthread_mutex_lock(&mutex1);
	printf("philosopher %d has left the fork to his right\n", nbr);
	printf("philosopher %d has left the fork to his left\n", nbr);
	printf("philosopher %d is sleeping\n", nbr);
	pthread_mutex_unlock(&mutex1);
}

void philo_thinking(int nbr, pthread_mutex_t mutex1)
{
	pthread_mutex_lock(&mutex1);
	printf("philosopher %d is sleeping\n", nbr);
	pthread_mutex_unlock(&mutex1);
}

pthread_mutex_t mutex1;

void *ft_action(void *arg)
{
	int nbr = *(int *)arg;

	while (1)
	{
		if (nbr == 1)
			philo_sleeping(nbr, mutex1);
		else if (nbr == 2)
			philo_thinking(nbr, mutex1);
		else if (nbr == 3)
			philo_eating(nbr, mutex1);
		else if (nbr == 4)
			philo_thinking(nbr, mutex1);
		else if (nbr == 5)
			philo_eating(nbr, mutex1);
		sleep(1);
	}
	free(arg);
	return NULL;
}

int creat_phiolosofers(int nbr)
{
	pthread_t philo[nbr];
	pthread_mutex_init(&mutex1, NULL);

	int *nb;
	int i = 1;

	while (i <= nbr)
	{
		nb = (int *)malloc(sizeof(int));
		*nb = i;
		if(pthread_create(&philo[i], NULL, ft_action, nb))
			return 1;
		sleep(1);
		i++;
	}
	i = 1;
	while (i <= nbr)
	{		
		if (pthread_join(philo[i], NULL))
			return 1;
		i++;
	}
	printf("finish\n");
	pthread_mutex_destroy(&mutex1);
	return  0;
}

int parameters(int *info, int nbr)
{
	int e;
	int number_of_philosophers = info[0];
	// int time_to_die = info[1];
	// int time_to_eat = info[2];
	// int time_to_sleep = info[3];
	int number_of_times_each_philosopher_must_eat;
	if (nbr == 5)
		number_of_times_each_philosopher_must_eat = info[4];
	e = creat_phiolosofers(number_of_philosophers);
	return e;
}

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int h;
	int e = 0;
	char **temp;
	int info[_nbr(argc, argv)];

	if (argc > 1 && (_nbr(argc, argv) == 4 || _nbr(argc, argv) == 5))
	{
		while (i < argc - 1)
		{
			temp = ft_split(argv[i + 1]);
			k = 0;
			while (temp[k] != NULL)
			{
				if ((!a_toi(temp[k], &h) || a_toi(temp[k], &h)) && h == 1)
					info[j++] = a_toi(temp[k], &h);
				else
				{
					ft_error();
					return 1;
				}
				k++;
			}
			free_table(temp, k);
			i++;
		}
		e = parameters(info, j);
	}
	else if(!(argc > 1 && (_nbr(argc, argv) == 4 || _nbr(argc, argv) == 5)) || e != 1)
	{
		ft_error();
		return 1;	
	}
	return 0;
}
