/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:54:45 by xzhang            #+#    #+#             */
/*   Updated: 2024/04/02 15:54:48 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	infoin(int ac, char **av, t_info *info)
{
	info->sime = 0;
	info->dead = 0;
	info->stime = times();
	info->np = ft_atoi(av[1]);
	info->ttd = ft_atoi(av[2]);
	info->tte = ft_atoi(av[3]);
	info->tts = ft_atoi(av[4]);
	if (ac == 6)
		info->nmpe = ft_atoi(av[5]);
	else
		info->nmpe = 0;
	info->philo = malloc(sizeof(t_philo) * info->np);
	if (!info->philo)
		return (0);
	info->froks = malloc(sizeof(pthread_mutex_t) * info->np);
	if (!info->froks)
		return (0);
	if (pthread_mutex_init(&info->print, NULL))
		return (errorprint("Error:mutex creat error"));
	if (pthread_mutex_init(&info->endm, NULL))
		return (errorprint("Error:mutex creat error"));
	return (0);
}

void	giveforks(t_info *info)
{
	int	i;

	i = 0;
	while (info->np > i)
	{
		if (info->philo[i].id != info->np)
			info->philo[i].fork = &info->froks[info->philo[i].id];
		i++;
	}
}

int	philoin(t_info *info)
{
	int	i;

	i = 0;
	while (info->np > i)
	{
		info->philo[i].id = i;
		info->philo[i].dead = 0;
		info->philo[i].info = info;
		info->philo[i].eat = 0;
		info->philo[i].meals_eat = 0;
		info->philo[i].tmeal = info->stime;
		if (pthread_mutex_init(&(info->philo[i].emutex), NULL))
			return (errorprint("Error:mutex creat error"));
		if (pthread_mutex_init(&info->froks[i], NULL))
			return (errorprint("Error:mutex creat error"));
		i++;
	}
	giveforks(info);
	return (0);
}

/*    Initialize Mutex: Create and initialize a mutex 
object using pthread_mutex_init() before using it.
    Lock Mutex: Acquire the mutex lock using pthread_mutex_lock() 
	before accessing shared resources.
    Unlock Mutex: Release the mutex lock using 
	pthread_mutex_unlock() after completing the task.*/
/*
int pthread_mutex_init(pthread_mutex_t *mutex, 
const pthread_mutexattr_t *attr);
*/