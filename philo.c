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

void *ft_action(void *arg)
{
	s_philo *philosofers = (s_philo *)arg;

	while (1)
	{
		if (1)
		{
			// pthread_mutex_lock(&philosofers->forks);
			// printf("philosopher %d take left fork\n", philosofers->philo_id);

			// pthread_mutex_lock(&philosofers->data.forks);
			// printf("philosopher %d take right fork\n", philosofers->philo_id);

			printf("philosopher %d is etating\n", philosofers->data.philo->philo_id);

			// pthread_mutex_unlock(&philosofers->data.forks);
			// printf("philosopher %d put left fork\n", philosofers->philo_id);

			// pthread_mutex_unlock(&philosofers->forks);
			// printf("philosopher %d put right fork\n", philosofers->philo_id);
		}
		// else if ((philosofers->philo_id + 1 )% 2 == 0)
		// {
		// 	pthread_mutex_lock(&philosofers->forks);
		// 	printf("philosopher %d is thinking\n", philosofers->philo_id);
		// 	pthread_mutex_unlock(&philosofers->forks);
		// }
		sleep(1);
	}
	return NULL;
}

void init_philo(t_argument *ptr)
{
	int i = 0;
	ptr->philo = malloc(sizeof(s_philo) * ptr->number_of_philosophers);

	while (i < ptr->number_of_philosophers)
	{
		ptr->philo[i].philo_id = i + 1;
		ptr->philo[i].forks_l = i;
		ptr->philo[i].forks_r = i + 1;
		i++;
	}
	ptr->forks = malloc(sizeof(pthread_mutex_t) * ptr->number_of_philosophers);
	i = 0;
	while (i < ptr->number_of_philosophers)
	{
		pthread_mutex_init(&ptr->forks[i++], NULL);
	}
}

int creat_phiolosofers(int nbr)
{
	pthread_t philo[nbr];

	s_philo *philosofers;
	philosofers = malloc(nbr * sizeof(s_philo));

	int i = 0;
	// while (i < nbr)
	// 	pthread_mutex_init(&philosofers[i++].forks, NULL);
	init_philo(&philosofers->data);

	i = 0;
	while (i < nbr)
	{
		philosofers[i].philo_id = i + 1;
		if(pthread_create(&philo[i], NULL, &ft_action, &philosofers[i]))
			return 1;
		i++;
	}
	// exit(0);
	i = 0;
	while (i < nbr)
	{		
		if (pthread_join(philo[i], NULL))
			return 1;
		i++;
	}
	// i = 0;
	// while (i < nbr)
	// 	pthread_mutex_destroy(&philosofers[i++].forks);
	free(philosofers);
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
