/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:42:47 by asebrech          #+#    #+#             */
/*   Updated: 2021/10/06 18:54:29 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	routine_1(t_philo *philo, int *count)
{
	sem_wait(philo->forks);
	sem_wait(philo->semaphore);
	printf("\e[32m%lld philo %d has taken a fork\n",
		timestamp(philo->timestamp), philo->nu_philo);
	sem_post(philo->semaphore);
	sem_wait(philo->forks);
	sem_wait(philo->semaphore);
	printf("\e[32m%lld philo %d has taken a fork\n", timestamp(philo->timestamp),
		philo->nu_philo);
	sem_post(philo->semaphore);
	*count += 1;
	sem_wait(philo->semaphore);
	printf("\e[33m%lld philo %d is eating (%d)\n", timestamp(philo->timestamp),
		philo->nu_philo, *count);
	sem_post(philo->semaphore);
	philo->time = actualtime();
	ft_usleep(philo->t_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	routine(t_philo *philo)
{
	int			count;

	philo->timestamp = actualtime();
	philo->time = actualtime();
	count = 0;
	while (1)
	{
		routine_1(philo, &count);
		if (count == philo->nb_eat)
			exit(0);
		sem_wait(philo->semaphore);
		printf("\e[35m%lld philo %d is sleeping\n",
			timestamp(philo->timestamp), philo->nu_philo);
		sem_post(philo->semaphore);
		ft_usleep(philo->t_sleep);
		sem_wait(philo->semaphore);
		printf("\e[34m%lld philo %d is thinking\n",
			timestamp(philo->timestamp), philo->nu_philo);
		sem_post(philo->semaphore);
	}
}

void	*death(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (timestamp(philo[philo->nu].time) > philo->t_die)
		{
			printf("\e[31m%lld philo %d died\n",
				timestamp(philo[philo->nu].timestamp), philo[philo->nu].nu_philo);
			i = -1;
			while (++i < philo->nb_philo)
				kill(philo[i].pid, SIGKILL);
			exit(0);
		}
	}
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	i = -1;
	thread = malloc(sizeof(pthread_t));
	while (++i < philo->nb_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo->nu = i;
			pthread_create(thread, NULL, &death, philo);
			routine(&philo[i]);
		}
		usleep(100);
	}
	i = -1;
	while (++i < philo->nb_philo)
		wait(NULL);
	sem_close(philo->forks);
	sem_close(philo->semaphore);
}
