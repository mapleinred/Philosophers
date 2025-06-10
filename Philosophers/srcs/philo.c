/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:13:37 by xzhang            #+#    #+#             */
/*   Updated: 2024/03/05 13:07:20 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	checkargs1(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (errorprint("Error: Wrong number of arguments"));
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '+')
			j++;
		else if (av[i][0] == '-')
			return (errorprint("Error: Number is not postive"));
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (errorprint("Error: Argument is not digit"));
			j++;
		}
		i++;
	}
	return (0);
}

static int	checkargs2(char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (errorprint("Error: Number of philosophers is invalid"));
	if (ft_atoi(av[2]) <= 0)
		return (errorprint("Error: Time to die is invalid"));
	if (ft_atoi(av[3]) <= 0)
		return (errorprint("Error: Time to eat is invalid"));
	if (ft_atoi(av[4]) <= 0)
		return (errorprint("Error: Time to sleep is invalid"));
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (errorprint("Error: Number of times to eat is invalid"));
	return (0);
}

int	threadscreate(t_info *info)
{
	int	i;

	i = 0;
	while (info->np > i)
	{
		if (pthread_create(&info->philo[i].thread, NULL, \
		sim, &info->philo[i]) != 0)
			return (errorprint("Error: Thread Create Error"));
		i++;
	}
	if (i == info->np)
	{
		if (pthread_create(&info->monitor, NULL, \
		monitoring, info) != 0)
			return (errorprint("Error: Thread Create Error"));
		else
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_info	info;

	i = 0;
	if (checkargs1(ac, av) == 1)
		return (1);
	if (checkargs2(av) == 1)
		return (1);
	infoin(ac, av, &info);
	philoin(&info);
	threadscreate(&info);
	while (info.np > i)
	{
		pthread_join(info.philo[i].thread, NULL);
		i++;
	}
	pthread_join(info.monitor, NULL);
	ftfree(&info);
}
