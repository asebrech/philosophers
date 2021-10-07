/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:56:55 by asebrech          #+#    #+#             */
/*   Updated: 2021/10/07 13:26:33 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	*death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(100);
	while (1)
	{
		if (timestamp(philo->time) > philo->t_die)
		{
			kill(philo->kill, SIGKILL);
			sem_wait(philo->semaphore);
			printf("\e[31m%lld philo %d died\n",
				timestamp(philo->timestamp), philo->nu_philo);
			exit(0);
		}
	}
}
