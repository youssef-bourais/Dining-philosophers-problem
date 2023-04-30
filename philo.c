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
# include <string.h>


pthread_mutex_t mutex;

void *ft_action(void *arg)
{
	// int nbr = *(int *)arg;
	s_philo *philosofers = (s_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(&mutex);
		printf("philosopher %d is thinking\n", philosofers->philo_id);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	free(arg);
	return NULL;
}

int creat_phiolosofers(int nbr)
{
	pthread_t philo[nbr];
	pthread_mutex_init(&mutex, NULL);

	s_philo *philosofers; 
	philosofers = malloc(nbr * sizeof(s_philo));
	memset(philosofers, 0, nbr * sizeof(s_philo));

	int i = 0;

	while (i < nbr)
	{
		philosofers[i].philo_id = i + 1;
		if(pthread_create(&philo[i], NULL, &ft_action, &philosofers[i]))
			return 1;
		i++;
	}
	i = 0;
	while (i < nbr)
	{		
		if (pthread_join(philo[i], NULL))
			return 1;
		i++;
	}
	pthread_mutex_destroy(&mutex);
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
	p = creat_phiolosofers(arg.number_of_philosophers);
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
