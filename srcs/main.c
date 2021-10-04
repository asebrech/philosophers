/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alois <alois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:19:02 by alois             #+#    #+#             */
/*   Updated: 2021/10/04 16:42:42 by alois            ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	t_philo			*philo;
	int				nb;				

	nb = ft_atoi(av[0]);
	fork = malloc(sizeof(pthread_mutex_t) * nb);
	philo = malloc(sizeof(t_philo) * nb);
	i = -1;
	while (++i < nb)
	{
		philo[i].time = 0;
		philo[i].nb_philo = nb;
		philo[i].death = 0;
		philo[i].t_die = ft_atoi(av[1]);
		philo[i].t_eat = ft_atoi(av[2]);
		philo[i].t_sleep = ft_atoi(av[3]);
		if (ac == 5)
			philo[i].nb_eat = ft_atoi(av[4]);
		else
			philo[i].nb_eat = -1;
		philo[i].nu_philo = i + 1;
		philo[i].left = fork + i;
		if (i == philo->nb_philo - 1)
			philo[i].right = fork;
		else
			philo[i].right = fork + i + 1;
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
		/*for (int i = 0; i < philo->nb_philo; i++)
		{
			printf("nb %d\n", philo[i].nb_philo);
			printf("n_eat %d\n", philo[i].nb_eat);
			printf("nu %d\n", philo[i].nu_philo);
			printf("die %lld\n", philo[i].t_die);
			printf("t_eat %d\n", philo[i].t_eat);
			printf("sleep %d\n", philo[i].t_sleep);
			
		}*/
		philosophers(philo);
	}
	else if (ac != 1)
		printf("Error\nwrong number of arguments\n");
	return (0);
}
