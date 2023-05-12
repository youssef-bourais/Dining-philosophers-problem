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

void thinking(s_philo *philosofers);

int timer(s_philo *time)
{
	struct timeval t_1;
	gettimeofday(&t_1, 0);
	return((t_1.tv_sec*1000 + t_1.tv_usec/1000) - (time->bridg->t_0.tv_sec*1000 + time->bridg->t_0.tv_usec/1000));
}

void ft_usleep(unsigned int time)
{
	struct timeval t_0, t_1;

	gettimeofday(&t_1, 0);
	gettimeofday(&t_0, 0);

	while (1)
	{
		if ((t_1.tv_sec*1000 + t_1.tv_usec/1000) - (t_0.tv_sec*1000 + t_0.tv_usec/1000) >= time)
			break;
		usleep(250);
		gettimeofday(&t_1, 0);
	}
}

void eating(s_philo *philosofers)
{
	if (philosofers->bridg->flage != 0)
	{
		pthread_mutex_lock(&(philosofers->bridg->forks[philosofers->left_fork]));
		pthread_mutex_lock(&(philosofers->bridg->forks[philosofers->right_fork]));

		printf("%d %d has taken a fork\n", timer(philosofers), philosofers->philo_id);

		printf("%d %d is eating\n", timer(philosofers), philosofers->philo_id);

		philosofers->bridg->nbr_of_meals[philosofers->philo_id - 1]++;

		gettimeofday(&philosofers->bridg->last_meal[philosofers->philo_id - 1], 0);
		
		ft_usleep((philosofers->bridg->time_to_eat));

		pthread_mutex_unlock(&(philosofers->bridg->forks[philosofers->right_fork]));
		pthread_mutex_unlock(&(philosofers->bridg->forks[philosofers->left_fork]));
	}
}

void sleeping(s_philo *philosofers)
{
	if (philosofers->bridg->flage != 0)
	{
		printf("%d %d is sleeping\n", timer(philosofers),philosofers->philo_id);
		ft_usleep((philosofers->bridg->time_to_sleep));
	}
}

void thinking(s_philo *philosofers)
{
	if (philosofers->bridg->flage != 0)
	{
		printf("%d %d is thinking\n", timer(philosofers), philosofers->philo_id);
	}
}

void *ft_action(void *arg)
{
    s_philo *philosofers = (s_philo *)arg;

	if (philosofers->philo_id % 2 != 0)
	{
		thinking(philosofers);
		ft_usleep((philosofers->bridg->time_to_eat));
	}

    while (1)
    {
		if (philosofers->bridg->flage == 0)
		{
			// write(1, "alah\n", 5);
			return NULL;
		}

		eating(philosofers);
		sleeping(philosofers);
		thinking(philosofers);
    }
    return NULL;
}

void *check_and_kill(void *arg)
{
	t_argument *philo_info = (t_argument *)arg;
	struct timeval t_now;
	int id;

	while (1)
	{
		id = 0;
		gettimeofday(&t_now, 0);
		while (id < philo_info->number_of_philosophers)
		{
			if ((t_now.tv_sec*1000 + t_now.tv_usec/1000) - (philo_info->last_meal[id].tv_sec*1000 + philo_info->last_meal[id].tv_usec/1000) >= philo_info->time_to_die)
			{
				pthread_mutex_lock(&(philo_info->forks[philo_info->number_of_philosophers]));
				philo_info->flage = 0;
				printf("%ld %d died\n", (t_now.tv_sec*1000 + t_now.tv_usec/1000) - (philo_info->t_0.tv_sec*1000 + philo_info->t_0.tv_usec/1000), id + 1);
				return NULL;
			}
			else
				id++;
		}
	}
	return NULL;
}

void init_philo(s_philo *philo, t_argument *philo_info)
{
	int i;

	philo_info->forks = malloc(sizeof(pthread_mutex_t) * philo_info->number_of_philosophers + 1);

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (philo_info->number_of_philosophers + i - 1) % philo_info->number_of_philosophers;
		philo[i].bridg = philo_info;
		gettimeofday(&philo_info->last_meal[i], 0);
   		pthread_mutex_init(&(philo_info->forks[i]), NULL);
		i++;
	}
   	pthread_mutex_init(&(philo->bridg->forks[i]), NULL);
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		philo_info->nbr_of_meals[i++] = 0;
	}
}

void free_resources(t_argument *philo_info, s_philo *philosofers)
{
	int i = 0;

	pthread_mutex_unlock(&(philo_info->forks[philo_info->number_of_philosophers]));
	
	while (i <= philo_info->number_of_philosophers)
		pthread_mutex_destroy(&(philo_info->forks[i++]));
	
	i = 0;
	while (i < philo_info->number_of_philosophers)
		pthread_detach((philosofers[i++].th));

	pthread_detach(philo_info->kill);

	free(philosofers);
	free(philo_info->nbr_of_meals);
	free(philo_info->forks);
	free(philo_info->last_meal);
}

int check_nbr_of_meals(t_argument *philo_info)
{
	int i;
	int j;

	if (philo_info->number_of_philosophers % 2 == 0)
		j = philo_info->number_of_times_each_philosopher_must_eat;
	else
		j = philo_info->number_of_times_each_philosopher_must_eat + 1;

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (philo_info->nbr_of_meals[i] >= j)
			i ++;
		else
			return 0;
	}
	return 1;
}

int creat_phiolosofers(t_argument *philo_info)
{
	s_philo *philosofers;

	philo_info->flage = 1;

	philosofers = malloc(sizeof(s_philo) * philo_info->number_of_philosophers);
	philo_info->last_meal = malloc(sizeof(struct timeval) * philo_info->number_of_philosophers);
	philo_info->nbr_of_meals = malloc(sizeof(int) * philo_info->number_of_philosophers);

	int i;

	init_philo(philosofers, philo_info);
	gettimeofday(&philosofers->bridg->t_0, 0);

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if(pthread_create(&(philosofers[i].th), NULL, &ft_action, &philosofers[i]))
			return 0;
		i++;
	}
	pthread_create(&philo_info->kill, NULL, &check_and_kill, philo_info);
	pthread_join((philo_info->kill), NULL);
	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		pthread_join((philosofers[i++].th), NULL);
	}
	free_resources(philo_info, philosofers);
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
	if (argc > 1 && (_nbr(argc, argv) == 4 || _nbr(argc, argv) == 5))
	{
		while (param->i < argc - 1)
		{
			param->temp = ft_split(argv[param->i + 1]);
			param->k = 0;
			while (param->temp[param->k] != NULL)
			{
				if ((!a_toi(param->temp[param->k], &(param->h)) || a_toi(param->temp[param->k], &(param->h))) && param->h == 1)
					info.arr[param->j++] = a_toi(param->temp[param->k], &(param->h));
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

	memset(&arg, 0, sizeof(t_argument));

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
