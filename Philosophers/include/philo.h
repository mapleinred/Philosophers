/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:12:34 by xzhang            #+#    #+#             */
/*   Updated: 2024/01/30 18:12:36 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RED "\033[1;31m"

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <stdarg.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eat;
	int				eat;
	int				dead;
	long int		tmeal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	emutex;
	struct s_info	*info;
}			t_philo;

typedef struct s_info
{
	int				sime;
	int				dead;
	long			np;
	long			ttd;
	long			tte;
	long			tts;
	long			nmpe;
	long int		stime;
	pthread_t		monitor;
	pthread_mutex_t	*froks;
	pthread_mutex_t	print;
	pthread_mutex_t	endm;
	t_philo			*philo;
}			t_info;

/*action.c*/
void		sleeps(t_philo *philo);
int			eat(t_philo *philo);
int			checkend(t_philo *philo);
void		*sim(void *phil);

/*ft_atoi.c*/
long		ft_atoi(const char *nptr);

/*ft_isdigit.c */
int			ft_isdigit(int i);

/*init.c*/
int			infoin(int ac, char **av, t_info *info);
void		giveforks(t_info *info);
int			philoin(t_info *info);

/*monitor.c*/
int			eats(t_info *info);
int			death(long ttd, t_philo *philo);
void		*monitoring(void *inf);

/*philo.c */
int			threadscreate(t_info *info);
int			main(int ac, char **av);

/*utils.c*/
int			errorprint(char *str);
long int	times(void);
int			ftusleep(long milliseconds);
void		printing(t_philo *philo, char *str);
void		ftfree(t_info *info);

#endif
