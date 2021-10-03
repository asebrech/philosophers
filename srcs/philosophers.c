/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alois <alois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/10/03 17:03:26 by alois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	long long	time;
	int			count;

	philo = (t_philo *)arg;
	time = actualtime();
	count = 0;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("\e[32m%lld philo %d has taken a fork\n", timestamp(time), philo->nu_philo);
		pthread_mutex_lock(philo->right_fork);
		printf("\e[32m%lld philo %d has taken a fork\n", timestamp(time), philo->nu_philo);
		if (philo->info->nb_eat != -1)
		{
			count += 1;
			if (count == philo->info->nb_eat)
				return (NULL);
		}
		printf("\e[33m%lld philo %d is eating (%d)\n", timestamp(time), philo->nu_philo, count);
		ft_usleep(philo->info->t_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("\e[33m%lld philo %d is sleeping\n", timestamp(time), philo->nu_philo);
		ft_usleep(philo->info->t_sleep);
		printf("\e[34m%lld philo %d is thinking\n", timestamp(time), philo->nu_philo);
		usleep(200);
	}
	return (NULL);
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	printf("%d\n", philo->info->nb_philo);
	thread = malloc(sizeof(thread) * philo->info->nb_philo);
	write(1, "test\n", 5);
	pthread_mutex_init(philo->mutex, NULL);
	i = -1;
	while (++i < philo->info->nb_philo)
	{
		pthread_mutex_init(philo[i].right_fork, NULL);
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_create(&thread[i], NULL, &routine, philo + i);
	}
	i = -1;
	while (++i < philo->info->nb_philo)
	{
		pthread_join(thread[i], NULL);
		pthread_mutex_destroy(philo[i].right_fork);
		pthread_mutex_destroy(philo[i].left_fork);
	}
	pthread_mutex_destroy(philo->mutex);
	free(thread);
}
