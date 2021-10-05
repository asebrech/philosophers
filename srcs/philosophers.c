/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/10/05 14:00:18 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	routine_1(t_philo *philo, int *count)
{
	printf("\e[32m%lld philo %d has taken a fork\n", timestamp(philo->timestamp),
		philo->nu_philo);
	*count += 1;
	printf("\e[33m%lld philo %d is eating (%d)\n", timestamp(philo->timestamp),
		philo->nu_philo, *count);
	if (*count == philo->nb_eat)
		philo->count = 1;
	philo->time = actualtime();
	ft_usleep(philo->t_eat);
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
		pthread_mutex_lock(philo->left);
		printf("\e[32m%lld philo %d has taken a fork\n",
			timestamp(philo->timestamp), philo->nu_philo);
		pthread_mutex_lock(philo->right);
		routine_1(philo, &count);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		if (count == philo->nb_eat)
			return (NULL);
		printf("\e[35m%lld philo %d is sleeping\n",
			timestamp(philo->timestamp), philo->nu_philo);
		ft_usleep(philo->t_sleep);
		printf("\e[34m%lld philo %d is thinking\n",
			timestamp(philo->timestamp), philo->nu_philo);
	}
	return (NULL);
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
				printf("\e[31m%lld philo %d died\n",
					timestamp(philo[i].timestamp), philo[i].nu_philo);
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
	free(thread);
}
