/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/09/29 16:36:56 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_philo_nu(t_philo *philo)
{
	int	nu;

	pthread_mutex_lock(&philo->mutex);
	nu = ++philo->nu_philo;
	pthread_mutex_unlock(&philo->mutex);
	return (nu);
}

void	take_fork(t_philo *philo, int nu, long long *time)
{
	pthread_mutex_lock(&philo->mutex);
	if (nu == philo->nb_philo)
	{
		philo->fork[nu] = 0;
		philo->fork[1] = 0;
	}
	else
	{
		philo->fork[nu] = 0;
		philo->fork[nu + 1] = 0;
	}
	printf("\e[32m%lld philo %d has taken a fork\n", timestamp(*time), nu);
	printf("\e[31m%lld philo %d is eating\n", timestamp(*time), nu);
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(philo->t_eat);
}

void	sleeping(t_philo *philo, int nu, long long *time)
{
	pthread_mutex_lock(&philo->mutex);
	if (nu == philo->nb_philo)
	{
		philo->fork[nu] = 1;
		philo->fork[1] = 1;
	}
	else
	{
		philo->fork[nu] = 1;
		philo->fork[nu + 1] = 1;
	}
	printf("\e[33mtimestamp : %lld philo %d is sleeping\n", timestamp(*time), nu);
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(philo->t_sleep);
}

int	philo_routine(t_philo *philo, int nu, long long *time)
{
	pthread_mutex_unlock(&philo->mutex);
	take_fork(philo, nu, time);
	pthread_mutex_lock(&philo->mutex);
	if (philo->nb_eat != -1)
	{
		philo->count_eat += 1;
		if (philo->count_eat == philo->nb_eat)
			return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	sleeping(philo, nu, time);
	pthread_mutex_lock(&philo->mutex);
	printf("\e[34mtimestamp : %lld philo %d is thinking\n", timestamp(*time), nu);
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	int			nu;
	long long	time;

	philo = (t_philo *)arg;
	nu = get_philo_nu(philo);
	time = actualtime();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if ((nu == philo->nb_philo && philo->fork[nu] == 1
				&& philo->fork[1] == 1) || (philo->fork[nu + 1]
				&& philo->fork[nu] == 1 && philo->fork[nu + 1] == 1))
		{
			if (philo_routine(philo, nu, &time))
				return (NULL);
		}
		else
			pthread_mutex_unlock(&philo->mutex);
		usleep(200);
	}
	return (NULL);
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	pthread_mutex_init(&philo->mutex, NULL);
	thread = malloc(sizeof(thread) * philo->nb_philo);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_create(&thread[i], NULL, &routine, philo);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&philo->mutex);
	free(thread);
}
