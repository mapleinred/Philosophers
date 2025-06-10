/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:14:18 by xzhang            #+#    #+#             */
/*   Updated: 2024/01/30 18:14:20 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	errorprint(char *str)
{
	printf(RED"%s\n", str);
	return (1);
}

long int	times(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
/*gettimeofday(&t, NULL): This function gets the current time (including
 seconds and microseconds) and stores it in the t variable of type 
 struct timeval. The second argument being NULL indicates that no 
 timezone adjustment is applied.
return (t.tv_sec * 1000 + t.tv_usec / 1000): This line calculates the 
time in milliseconds. t.tv_sec represents the number of seconds since 
the epoch, and t.tv_usec represents the microseconds within the 
current second. Multiplying t.tv_sec by 1000 converts seconds to 
milliseconds. Dividing t.tv_usec by 1000 converts microseconds to 
milliseconds. Finally, these two values are added together to get the 
total time in milliseconds.
struct timeval {
    long tv_sec;  // seconds
    long tv_usec; // microseconds
};*/

int	ftusleep(long int milliseconds)
{
	long	start;

	start = times();
	while ((times() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	printing(t_philo *philo, char *str)
{
	int		i;
	long	t;

	pthread_mutex_lock(&philo->info->endm);
	if (philo->info->sime == 1)
	{
		pthread_mutex_unlock(&philo->info->endm);
		return ;
	}
	pthread_mutex_unlock(&philo->info->endm);
	i = philo->id + 1;
	t = times() - philo->info->stime;
	pthread_mutex_lock(&philo->info->endm);
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %i %s\n", t, i, str);
	pthread_mutex_unlock(&philo->info->endm);
	pthread_mutex_unlock(&philo->info->print);
}

void	ftfree(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->endm);
	pthread_mutex_destroy(&info->print);
	while (info->nmpe > i)
	{
		pthread_mutex_destroy(&info->philo[i].emutex);
		pthread_mutex_destroy(&info->froks[i]);
		i++;
	}
	if (info->philo)
		free(info->philo);
	if (info->froks)
		free(info->froks);
}
