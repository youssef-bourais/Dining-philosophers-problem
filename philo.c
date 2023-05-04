// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/17 12:43:52 by ybourais          #+#    #+#             */
// /*   Updated: 2023/04/30 10:05:47 by ybourais         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

# include "philo.h"

// ◦ timestamp_in_ms X has taken a fork 
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

void *ft_action(void *arg)
{
	s_philo *philosofers = (s_philo *)arg;

	while (1)
	{
		if (philosofers->philo_id % 2 == 0)
		{
			pthread_mutex_lock(&philosofers->bridg.for_printing);
			printf("philosopher %d is thinking\n", philosofers->philo_id);
			pthread_mutex_unlock(&philosofers->bridg.for_printing);
		}
		else
		{
			pthread_mutex_lock(&philosofers->bridg.forks[philosofers->left_fork]);
			pthread_mutex_lock(&philosofers->bridg.forks[philosofers->right_fork]);
			printf("philosopher %d pick the forks\n", philosofers->philo_id);

			pthread_mutex_lock(&philosofers->bridg.for_printing);
			printf("philosopher %d is etating\n", philosofers->philo_id);
			pthread_mutex_unlock(&philosofers->bridg.for_printing);

			// usleep(philosofers->bridg.time_to_eat);
			// sleep(1);

			printf("philosopher %d put the forks \n", philosofers->philo_id);
			pthread_mutex_unlock(&philosofers->bridg.forks[philosofers->right_fork]);
			pthread_mutex_unlock(&philosofers->bridg.forks[philosofers->left_fork]);

			// pthread_mutex_lock(&philosofers->bridg.for_printing);
			// printf("philosopher %d is sleeping\n", philosofers->philo_id);
			// pthread_mutex_unlock(&philosofers->bridg.for_printing);

			// usleep(philosofers->bridg.time_to_sleep);
		}
		sleep(1);
	}
	return NULL;
}

s_philo *init_philo(s_philo *philo, t_argument *philo_info)
{
	int i = 0;

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		philo[i].bridg.forks = malloc(sizeof(pthread_mutex_t));
		philo[i].philo_id = i + 1;

		philo[i].left_fork = i;
		philo[i].right_fork = (philo_info->number_of_philosophers + i - 1) % philo_info->number_of_philosophers;
		
		philo[i].bridg.time_to_eat = philo_info->time_to_eat;
		philo[i].bridg.time_to_die = philo_info->time_to_die;
		philo[i].bridg.time_to_sleep = philo_info->time_to_sleep;
		i++;
	}

	philo->bridg.for_printing = philo_info->for_printing;

	i = 0;
	while (i < philo_info->number_of_philosophers)
		pthread_mutex_init(&philo->bridg.forks[i++], NULL);

	pthread_mutex_init(&philo->bridg.for_printing, NULL);
	return philo;
}

int creat_phiolosofers(t_argument *philo_info)
{
	philo_info->philo_init = malloc(sizeof(pthread_t) * philo_info->number_of_philosophers);
	s_philo *philosofers;

	int i;

	philosofers = malloc(sizeof(s_philo) * philo_info->number_of_philosophers);

	philosofers = init_philo(philosofers, philo_info);
	
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if(pthread_create(&philo_info->philo_init[i], NULL, &ft_action, &philosofers[i]))
			return 1;
		i++;
	}
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (pthread_join(philo_info->philo_init[i], NULL))
			return 1;
		i++;
	}

	i = 0;
	while (i < philo_info->number_of_philosophers)
		pthread_mutex_destroy(&philosofers->bridg.forks[i++]);
	
	pthread_mutex_destroy(&philosofers->bridg.for_printing);

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		free(&philosofers[i++]);
		free(&philosofers->bridg.forks[i++]);
	}
	free(philo_info->philo_init);
	return  0;
}

t_argument get_data(int *info, int nbr)
{
	t_argument arg;
	arg.number_of_philosophers = info[0];
	arg.time_to_die = info[1];
	arg.time_to_eat = info[2];
	arg.time_to_sleep = info[3];
	if (nbr == 5)
		arg.number_of_times_each_philosopher_must_eat = info[4];
	return arg;
}

s_info fill_data(s_indices *param, int argc, char **argv)
{
	s_info info = {0, 0};
	
	info.arr = malloc(sizeof(int) * _nbr(argc, argv));
	if (argc > 1 && (_nbr(argc, argv) == 4 || _nbr(argc, argv) == 5)) // cheak num of args
	{
		while (param->i < argc - 1)
		{
			param->temp = ft_split(argv[param->i + 1]); // fill the table
			param->k = 0;
			while (param->temp[param->k] != NULL)
			{
				if ((!a_toi(param->temp[param->k], &(param->h)) || a_toi(param->temp[param->k], &(param->h))) && param->h == 1)
					info.arr[param->j++] = a_toi(param->temp[param->k], &(param->h)); // fill the array
				else
					info.e = 1;
				param->k++;
			}
			free_table(param->temp, param->k);
			param->i++;
		}
	}
	else
		info.e = 1;
	return info;
}

int main(int argc, char *argv[])
{
	s_indices	indices = {0, 0, 0, 0, 0, 0};
	s_info info;
	t_argument arg;
	int p;

	info = fill_data(&indices, argc, argv);
	arg = get_data(info.arr, indices.j);
	free(info.arr);
	if (indices.e == 1 || info.e == 1)
	{
		ft_error();
		return 1;
	}

	p = creat_phiolosofers(&arg);
	if (p == 1)
	{
		ft_error();
		return 1;
	}
	// struct timeval start, end;
	// int i = 0;
	
	// gettimeofday(&start, 0);

	// while (i < 1e5)
	// 	i++;

	// gettimeofday(&end, 0);
	// printf("%d\n", end.tv_usec - start.tv_usec);
	return 0;
}
