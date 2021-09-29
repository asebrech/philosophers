/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/09/29 12:36:18 by asebrech         ###   ########.fr       */
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

void	died(int nu, long long time)
{
	printf("timestamp : %lld philo %d died\n", timestamp(time), nu);
	exit (0);
}

void	philo_routine(t_philo *philo, int nu, long long *time)
{
	pthread_mutex_unlock(&philo->mutex);
	*time = actualtime();
	pthread_mutex_lock(&philo->mutex);
	philo->nb_philo -= 2;
	pthread_mutex_unlock(&philo->mutex);
	printf("\e[32mtimestamp : %lld philo %d has taken a fork\n",
		timestamp(*time), nu);
	printf("\e[31mtimestamp : %lld philo %d is eating\n", timestamp(*time), nu);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(&philo->mutex);
	if (philo->nb_eat != -1)
	{
		philo->count_eat += 1;
		if (philo->count_eat == philo->nb_eat)
			exit (0);
	}
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->nb_philo += 2;
	pthread_mutex_unlock(&philo->mutex);
	printf("\e[33mtimestamp : %lld philo %d is sleeping\n", timestamp(*time), nu);
	ft_usleep(philo->t_sleep);
	printf("\e[34mtimestamp : %lld philo %d is thinking\n", timestamp(*time), nu);
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
		if (timestamp(time) > philo->t_die)
			died(nu, time);
		if (philo->nb_philo >= 2)
			philo_routine(philo, nu, &time);
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
