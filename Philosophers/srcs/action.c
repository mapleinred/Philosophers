/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:39:34 by xzhang            #+#    #+#             */
/*   Updated: 2024/05/15 10:41:23 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeps(t_philo *philo)
{
	printing(philo, "is sleeping");
	ftusleep(philo->info->tts);
}
/*int eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->froks[philo->id]);
	printing(philo, "has taken a fork");
	if (philo->info->np == 1)
	{
		pthread_mutex_unlock(&philo->info->froks[philo->id]);
		return (0);
	}
	if (philo->id + 1 != philo->info->np)
	{
		//pthread_mutex_lock(&philo->info->froks[philo->id]);
		//printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->froks[philo->id + 1]);
		printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->emutex);
		philo->tmeal = times();
		philo->eat = 1;
		printing(philo, "is eating");
		philo->meals_eat += 1;
		pthread_mutex_unlock(&philo->emutex);
		philo->eat = 0;
		ftusleep(philo->info->tte);
		pthread_mutex_unlock(&philo->info->froks[philo->id + 1]);
		pthread_mutex_unlock(&philo->info->froks[philo->id]);
	}
	else
	{	//pthread_mutex_lock(&philo->info->froks[0]);
		//printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->froks[philo->id]);
		printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->emutex);
		philo->tmeal = times();
		philo->eat = 1;
		printing(philo, "is eating");
		philo->meals_eat += 1;
		pthread_mutex_unlock(&philo->emutex);
		philo->eat = 0;
		ftusleep(philo->info->tte);
		pthread_mutex_unlock(&philo->info->froks[0]);
		pthread_mutex_unlock(&philo->info->froks[philo->id]);
		//pthread_mutex_unlock(&philo->info->froks[0]);
	}
	return (0);
}*/
/*this code on top is just need to change the last pilo to took
the [0] which is next frok the hiself fork*/
/*int first_fork = philo->id;: This line retrieves the philosopher's
ID and assigns it to the variable first_fork. Each philosopher has a
unique ID, typically ranging from 0 to n-1, where n is the total
number of philosophers.int second_fork = (philo->id + 1) %
philo->info->np;: Here, philo->id represents the ID of the philosopher
, and philo->info->np represents the total number of philosophers
(np likely stands for "number of philosophers"). Adding 1 to philo->id
ensures that we get the ID of the next philosopher in a circular manner.
Taking the modulus % by philo->info->np ensures that the ID remains within
the range of valid philosopher IDs. This way, second_fork gets the ID of
the next philosopher in the circular sequence.The if-else block ensures
that we always lock the lower numbered fork first to prevent lock-order
inversion. Lock-order inversion can lead to deadlocks.If first_fork is
less than second_fork, it means the philosopher's ID is lower than the
next philosopher's ID in the circular sequence. In this case, we lock
first_fork first and then second_fork.If first_fork is greater than or
equal to second_fork, it means the philosopher's ID is higher than the
next philosopher's ID in the circular sequence. In this case, we lock
second_fork first and then first_fork.This ensures that philosophers
always lock their forks in a consistent order, avoiding potential
deadlocks caused by lock-order inversions.*/

static int	eatsub(t_philo *philo)
{
	printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->emutex);
	philo->tmeal = times();
	philo->eat = 1;
	printing(philo, "is eating");
	philo->meals_eat += 1;
	philo->eat = 0;
	pthread_mutex_unlock(&philo->emutex);
	ftusleep(philo->info->tte);
	return (0);
}

int	eat(t_philo *philo)
{
	int	second_fork;

	if (philo->info->np == 1)
	{
		pthread_mutex_lock(&philo->info->froks[philo->id]);
		printing(philo, "has taken a fork");
		return (pthread_mutex_unlock(&philo->info->froks[philo->id]), 0);
	}
	second_fork = (philo->id + 1) % philo->info->np;
	if (philo->id < second_fork)
	{
		pthread_mutex_lock(&philo->info->froks[philo->id]);
		printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->froks[second_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->froks[second_fork]);
		printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->froks[philo->id]);
	}
	eatsub(philo);
	pthread_mutex_unlock(&philo->info->froks[philo->id]);
	pthread_mutex_unlock(&philo->info->froks[second_fork]);
	return (0);
}

int	checkend(t_philo *philo)
{
	int	simend;

	pthread_mutex_lock(&philo->info->endm);
	simend = philo->info->sime;
	if (simend == 1)
		return (pthread_mutex_unlock(&philo->info->endm), 1);
	pthread_mutex_unlock(&philo->info->endm);
	return (0);
}

void	*sim(void *phil)
{
	int		y;
	t_philo	*philo;

	philo = (t_philo *)phil;
	y = philo->info->nmpe;
	if ((philo->id + 1) % 2 == 0)
		ftusleep(1);
	while (!checkend(philo) && ((philo->meals_eat < y && y > 0) || y == 0))
	{
		eat(philo);
		if (philo->info->np > 0)
		{
			if (philo->info->np == 1)
				break ;
			else
			{
				sleeps(philo);
				printing(philo, "is thinking");
				if ((philo->info->np % 2))
					ftusleep(1);
			}
		}
	}
	return (NULL);
}
