/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:42:47 by asebrech          #+#    #+#             */
/*   Updated: 2021/10/07 14:02:52 by asebrech         ###   ########.fr       */
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

void	routine_2(t_philo *philo, int count)
{
	int	i;

	if (count == philo->nb_eat)
	{
		sem_post(philo->sema_eat);
		sem_wait(philo->toto);
		i = -1;
		while (++i < philo->nb_philo)
			sem_wait(philo->sema_eat);
		kill(philo->kill, SIGKILL);
		exit(0);
	}
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
		routine_2(philo, count);
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

void	philo_1(t_philo *philo, int i, pthread_t *thread, pid_t *pid)
{
	if (i == -1)
	{
		*pid = fork();
		if (*pid == 0)
		{
			while (1)
				;
		}
	}
	else
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo[i].kill = *pid;
			pthread_create(thread, NULL, &death, &philo[i]);
			routine(&philo[i]);
		}
	}
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	*thread;
	pid_t		pid;

	thread = malloc(sizeof(pthread_t));
	i = -2;
	while (++i < philo->nb_philo)
		philo_1(philo, i, thread, &pid);
	waitpid(pid, NULL, 0);
	i = -1;
	while (++i < philo->nb_philo)
		kill(philo[i].pid, SIGKILL);
	sem_close(philo->forks);
	sem_close(philo->semaphore);
	sem_close(philo->sema_eat);
	sem_close(philo->toto);
	free(thread);
}
