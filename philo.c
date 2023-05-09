/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:43:52 by ybourais          #+#    #+#             */
/*   Updated: 2023/05/06 18:54:06 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void thinking(s_philo *philosofers, struct timeval init);
int timer(s_philo *time, struct timeval t_1)
{
	gettimeofday(&t_1, 0);
	return(((t_1.tv_usec - time->bridg.t_0.tv_usec) + ((t_1.tv_sec - time->bridg.t_0.tv_sec) * 1000000))/1000);
}

void ft_usleep(unsigned int time)
{
	struct timeval t_0, t_1;
	gettimeofday(&t_1, 0);
	gettimeofday(&t_0, 0);

	while (1)
	{
		if ((t_1.tv_sec - t_0.tv_sec)*1000 + (t_1.tv_usec - t_0.tv_usec)/1000 >= time)
			break;
		usleep(270);
		gettimeofday(&t_1, 0);
	}
}

void eating(s_philo *philosofers, struct timeval init, int p)
{
	if ((philosofers->philo_id == 1) && p == 0 && philosofers->bridg.number_of_philosophers % 2 != 0)
	{
		thinking(philosofers, init);
		ft_usleep((philosofers->bridg.time_to_eat));
	}

	pthread_mutex_lock(&(philosofers->bridg.forks[philosofers->left_fork]));
	pthread_mutex_lock(&(philosofers->bridg.forks[philosofers->right_fork]));

	printf("%d philo %d has taken a fork\n", timer(philosofers, init), philosofers->philo_id);

	printf("%d philo %d is eating\n", timer(philosofers, init), philosofers->philo_id);

	ft_usleep((philosofers->bridg.time_to_eat));

	pthread_mutex_unlock(&(philosofers->bridg.forks[philosofers->right_fork]));
	pthread_mutex_unlock(&(philosofers->bridg.forks[philosofers->left_fork]));
}

void sleeping(s_philo *philosofers, struct timeval init)
{
	printf("%d philo %d is sleeping\n", timer(philosofers, init),philosofers->philo_id);
	ft_usleep((philosofers->bridg.time_to_sleep));
}

void thinking(s_philo *philosofers, struct timeval init)
{
	printf("%d philo %d is thinking\n", timer(philosofers, init), philosofers->philo_id);
}

void *ft_action(void *arg)
{
	struct timeval end;
    s_philo *philosofers = (s_philo *)arg;

	philosofers->philo_die = 1;

	gettimeofday(&(philosofers->bridg.t_0), 0);
	gettimeofday(&end, 0);

	if (philosofers->philo_id % 2 != 0)
	{
		thinking(philosofers, end);
		ft_usleep((philosofers->bridg.time_to_eat));
	}

	int i = 0;
    while (1)
    {
       	// if (timer(philosofers, philosofers->starving) > philosofers->bridg.time_to_die)
		// {
		// 	printf("%d\n", philosofers->bridg.time_to_die);
		// 	philosofers->flage_of_dieing = 0;
		// }
		// printf("%d\n", timer(philosofers, philosofers->starving));
		// if (philosofers->flage_of_dieing == 0)
		// {
		// 	printf("%d %d died\n", timer(philosofers, end), philosofers->philo_id);
		// 	break;
		// }
        eating(philosofers, end, i);
		// gettimeofday(&(philosofers->starving), 0);
		// sleep(1);
		// printf("%d\n", timer(philosofers, philosofers->starving));
		// exit(0);
		// if (!philosofers->philo_die)
		// {
		// 	/* do this */
		// }
		sleeping(philosofers, end);
		thinking(philosofers, end);

		if (i == philosofers->bridg.number_of_times_each_philosopher_must_eat - 1)
		{
			return NULL;
			exit(0);
		}
		i++;
    }
    return NULL;
}

void init_philo(s_philo *philo, t_argument *philo_info)
{
	int i;

	philo_info->forks = malloc(sizeof(pthread_mutex_t) * philo_info->number_of_philosophers);

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (philo_info->number_of_philosophers + i - 1) % philo_info->number_of_philosophers;

		philo[i].bridg.time_to_eat = philo_info->time_to_eat;
		philo[i].bridg.time_to_die = philo_info->time_to_die;
		philo[i].bridg.time_to_sleep = philo_info->time_to_sleep;
		philo[i].bridg.for_printing = philo_info->for_printing;
		philo[i].bridg.t_0 = philo_info->t_0;

		philo[i].bridg = *philo_info;
   		pthread_mutex_init(&(philo_info->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(philo->bridg.for_printing), NULL);
}

int creat_phiolosofers(t_argument *philo_info)
{
	s_philo *philosofers;

	philosofers = malloc(sizeof(s_philo) * philo_info->number_of_philosophers);

	int i = 0;
	
	init_philo(philosofers, philo_info);
	
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if(pthread_create(&(philosofers[i].th), NULL, &ft_action, &philosofers[i]))
			return 0;
		i++;
	}
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (pthread_join(philosofers[i].th, NULL))
			return 0;
		i++;
	}
	i = 0;
	while (i < philo_info->number_of_philosophers)
		pthread_mutex_destroy(&(philo_info->forks[i++]));

	pthread_mutex_destroy(&(philosofers->bridg.for_printing));

	free(philosofers);
	free(philo_info->forks);
	return  1;
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

	info = fill_data(&indices, argc, argv);
	arg = get_data(info.arr, indices.j);
	free(info.arr);
	if (indices.e == 1 || info.e == 1)
	{
		ft_error();
		return 1;
	}
	if (!creat_phiolosofers(&arg))
	{
		ft_error();
		return 1;
	}
	return 0;
}
