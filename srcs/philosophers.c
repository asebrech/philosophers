/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alois <alois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/09/28 23:35:54 by alois            ###   ########.fr       */
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

long long	timestamp(t_philo *philo)
{
	return (actualtime() - philo->time);
}

void	died(t_philo *philo, int nu, long long *total)
{
	*total += timestamp(philo);
	printf("timestamp : %lld philo %d died\n", *total, nu);
}

void	take_fork(t_philo *philo, int nu, long long *total)
{
	pthread_mutex_lock(&philo->mutex);
	philo->nb_philo -= 2;
	pthread_mutex_unlock(&philo->mutex);
	*total += timestamp(philo);
	printf("timestamp : %lld philo %d has taken a fork\n", *total, nu);
}

void	eating(t_philo *philo, int nu, long long *total)
{
	*total += timestamp(philo);
	printf("timestamp : %lld philo %d is eating\n", *total, nu);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(&philo->mutex);
	philo->nb_philo += 2;
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeping(t_philo *philo, int nu, long long *total)
{
	*total += timestamp(philo);
	printf("timestamp : %lld philo %d is sleeping\n", *total, nu);
	ft_usleep(philo->t_sleep);
}

void	thinking(t_philo *philo, int nu, long long *total)
{
	*total += timestamp(philo);
	printf("timestamp : %lld philo %d is thinkping\n", *total, nu);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	int			nu;
	long long	total;

	philo = (t_philo *)arg;
	nu = get_philo_nu(philo);
	total = 0;
	while (1)
	{
		if (total > philo->t_die)
		{
			died(philo, nu, &total);
			return (NULL);
		}
		if (philo->nb_philo >= 2)
		{
			take_fork(philo, nu, &total);
			eating(philo, nu, &total);
			sleeping(philo, nu, &total);
			thinking(philo, nu, &total);
			total = 0;
		}
		total += timestamp(philo);
	}
	return (philo);
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	pthread_mutex_init(&philo->mutex, NULL);
	thread = malloc(sizeof(thread) * philo->nb_philo);
	philo->time = actualtime();
	i = -1;
	while (++i < philo->nb_philo)
		pthread_create(&thread[i], NULL, &routine, philo);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&philo->mutex);
	free(thread);
}
