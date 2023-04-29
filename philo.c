/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:43:52 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/29 16:50:16 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

pthread_mutex_t mutex;

void *ft_action(void *arg)
{
	int nbr = *(int *)arg;

	// sleep(1);
	while (1)
	{
		pthread_mutex_lock(&mutex);
		printf("philosopher %d is thinking\n", nbr);
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

	int *nb;
	int i = 0;

	while (i < nbr)
	{
		nb = (int *)malloc(sizeof(int));
		*nb = i + 1;
		if(pthread_create(&philo[i], NULL, &ft_action, nb))
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

t_philo get_data(int *info, int nbr)
{
	t_philo param;
	param.number_of_philosophers = info[0];
	param.time_to_die = info[1];
	param.time_to_eat = info[2];
	param.time_to_sleep = info[3];
	if (nbr == 5)
		param.number_of_times_each_philosopher_must_eat = info[4];
	return param;
}

t_beta fill_data(t_param *param, int argc, char **argv)
{
	t_beta info = {0, 0};
	
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
	t_param	param = {0, 0, 0, 0, 0, 0};
	t_beta beta;
	t_philo ph;
	int p;

	beta = fill_data(&param, argc, argv);
	ph = get_data(beta.arr, param.j);
	free(beta.arr);
	if (param.e == 1 || beta.e == 1)
	{
		ft_error();
		return 1;
	}
	p = creat_phiolosofers(ph.number_of_philosophers);
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
