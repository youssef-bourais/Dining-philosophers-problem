/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:03:27 by ybourais          #+#    #+#             */
/*   Updated: 2023/04/09 20:55:28 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

enum{
	sleeping = 1,
	sleeping1 = 2,
	sleeping2 = 3,
};

int nbr_word(char *str);
void *ft_copy(char *dst, char *src, int size);
char *ft_slice(char *str, int start, int len);
char **ft_split(char *str);
int ft_error();

#endif
