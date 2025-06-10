/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:20 by xzhang            #+#    #+#             */
/*   Updated: 2024/04/30 13:34:22 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	eats(t_info *info)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = info->nmpe;
	while (info->np > i)
	{
		pthread_mutex_lock(&info->philo[i].emutex);
		if ((k > info->philo[i].meals_eat && k > 0) || k == 0)
			j = 0;
		pthread_mutex_unlock(&info->philo[i].emutex);
		i++;
	}
	if (j == 1)
	{
		pthread_mutex_lock(&info->endm);
		info->sime = 1;
		pthread_mutex_unlock(&info->endm);
	}
	return (j);
}

int	death(long ttd, t_philo *philo)
{
	int	x;

	pthread_mutex_lock(&philo->emutex);
	x = times() - philo->tmeal;
	if (x >= ttd && philo->eat == 0)
	{
		pthread_mutex_unlock(&philo->emutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->emutex);
	return (0);
}

static void	printi(t_philo *philo, char *str)
{
	int		i;
	long	t;

	i = philo->id + 1;
	t = times() - philo->info->stime;
	pthread_mutex_lock(&philo->info->endm);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %i %s\n", t, i, str);
	pthread_mutex_unlock(&philo->info->endm);
	pthread_mutex_unlock(&philo->info->print);
}

void	monitoringsub(t_info *info, int i)
{
	pthread_mutex_lock(&info->endm);
	info->sime = 1;
	info->philo[i].dead = 1;
	pthread_mutex_unlock(&info->endm);
	printi(&info->philo[i], "died");
}

void	*monitoring(void *inf)
{
	int		i;
	t_info	*info;

	i = 0;
	info = (t_info *)inf;
	while (1)
	{
		i = 0;
		while (info->np > i)
		{
			if (death(info->ttd, &info->philo[i]))
			{
				monitoringsub(info, i);
				return (NULL);
			}
			i++;
		}
		if (eats(info) == 1)
		{
			printf("all philo have eaten enough\n");
			break ;
		}
	}
	return (NULL);
}
