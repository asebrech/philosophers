/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:20:05 by alois             #+#    #+#             */
/*   Updated: 2021/09/28 17:57:14 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		nu;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	nu = ++philo->nu_philo;
	printf("%d\n", nu);
	pthread_mutex_unlock(&philo->mutex);
	return (philo);
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
