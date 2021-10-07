/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:41:20 by asebrech          #+#    #+#             */
/*   Updated: 2021/10/07 13:26:58 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	pid_t			pid;
	pid_t			kill;
	long long		time;
	long long		timestamp;
	int				count;
	int				nu_philo;
	int				nb_philo;
	long long		t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	sem_t			*forks;
	sem_t			*semaphore;
	sem_t			*sema_eat;
	sem_t			*toto;
}				t_philo;

void		philosophers(t_philo *philo);
int			ft_isallnum(char *str);
long int	ft_atoi(const char *str);
long long	actualtime(void);
int			ft_usleep(int ms);	
long long	timestamp(long long time);
void		quit(t_philo *philo);
void		*death(void *arg);

#endif