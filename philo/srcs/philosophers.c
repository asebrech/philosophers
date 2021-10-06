/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/10/05 17:05:24 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	routine_1(t_philo *philo, int *count)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->mutex);
	printf("\e[32m%lld philo %d has taken a fork\n",
		timestamp(philo->timestamp), philo->nu_philo);
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->mutex);
	printf("\e[32m%lld philo %d has taken a fork\n", timestamp(philo->timestamp),
		philo->nu_philo);
	pthread_mutex_unlock(philo->mutex);
	*count += 1;
	pthread_mutex_lock(philo->mutex);
	printf("\e[33m%lld philo %d is eating (%d)\n", timestamp(philo->timestamp),
		philo->nu_philo, *count);
	pthread_mutex_unlock(philo->mutex);
	if (*count == philo->nb_eat)
		philo->count = 1;
	philo->time = actualtime();
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	int			count;

	philo = (t_philo *)arg;
	philo->timestamp = actualtime();
	philo->time = actualtime();
	count = 0;
	while (1)
	{
		routine_1(philo, &count);
		if (count == philo->nb_eat)
			return (NULL);
		pthread_mutex_lock(philo->mutex);
		printf("\e[35m%lld philo %d is sleeping\n",
			timestamp(philo->timestamp), philo->nu_philo);
		pthread_mutex_unlock(philo->mutex);
		ft_usleep(philo->t_sleep);
		pthread_mutex_lock(philo->mutex);
		printf("\e[34m%lld philo %d is thinking\n",
			timestamp(philo->timestamp), philo->nu_philo);
		pthread_mutex_unlock(philo->mutex);
	}
	return (NULL);
}

void	death_1(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->mutex);
	printf("\e[31m%lld philo %d died\n",
		timestamp(philo[i].timestamp), philo[i].nu_philo);
}

void	*death(void *arg)
{
	int		i;
	int		count;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		count = 0;
		i = -1;
		while (++i < philo->nb_philo)
		{
			if (timestamp(philo[i].time) > philo->t_die && !philo[i].count)
			{
				death_1(philo, i);
				return (NULL);
			}
			if (philo[i].count)
			{
				count++;
				if (count == philo->nb_philo)
					return (NULL);
			}
		}
	}
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * philo->nb_philo + 1);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_init(philo[i].left, NULL);
	pthread_mutex_init(philo->mutex, NULL);
	i = -1;
	while (++i < philo->nb_philo)
	{
		pthread_create(thread + i, NULL, &routine, philo + i);
		usleep(100);
	}
	pthread_create(thread + i, NULL, &death, philo);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_detach(thread[i]);
	pthread_join(thread[i], NULL);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(philo[i].left);
	pthread_mutex_destroy(philo->mutex);
	free(thread);
}
