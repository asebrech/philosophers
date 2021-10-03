/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alois <alois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:16:48 by alois             #+#    #+#             */
/*   Updated: 2021/10/03 17:00:23 by alois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_info
{
	int				nb_philo;
	long long		t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
}				t_info;	

typedef struct s_philo
{
	t_info			*info;
	int				nu_philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

void		philosophers(t_philo *philo);
int			ft_isallnum(char *str);
long int	ft_atoi(const char *str);
long long	actualtime(void);
int			ft_usleep(int ms);	
long long	timestamp(long long time);

#endif