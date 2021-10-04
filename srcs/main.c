/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:19:02 by alois             #+#    #+#             */
/*   Updated: 2021/10/04 12:00:38 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_args(int ac, char **av)
{
	int			i;
	long int	tmp;

	i = 0;
	tmp = 0;
	while (i < ac && ft_isallnum(av[i]))
		i++;
	if (i != ac)
	{
		printf("Error\narguments must be only numerical\n");
		return (1);
	}
	i = 0;
	while (i < ac)
	{
		tmp = ft_atoi(av[i]);
		if (tmp > INT_MAX)
		{
			printf("Error\narguments too long\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	*fill_philo(int ac, char **av)
{
	int				i;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	int				nb;				

	nb = ft_atoi(av[0]);
	i = -1;
	mutex = malloc(sizeof(mutex));
	fork = malloc(sizeof(fork) * nb);
	philo = malloc(sizeof(philo) * nb);
	while (++i < nb)
	{
		philo[i].nu_philo = i + 1;
		//philo[i].mutex = mutex;
		philo[i].left = fork + i;
		if (i == philo->nb_philo)
			philo[i].right = fork;
		else
			philo[i].right = fork + i + 1;
		philo->nb_philo = nb;
		philo->t_die = ft_atoi(av[1]);
		philo->t_eat = ft_atoi(av[2]);
		philo->t_sleep = ft_atoi(av[3]);
		if (ac == 5)
			philo->nb_eat = ft_atoi(av[4]);
		else
			philo->nb_eat = -1;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		if (check_args(ac - 1, av + 1))
			return (1);
		philo = fill_philo(ac - 1, av + 1);
		philosophers(philo);
	}
	else if (ac != 1)
		printf("Error\nwrong number of arguments\n");
	return (0);
}
