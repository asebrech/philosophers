/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:19:02 by alois             #+#    #+#             */
/*   Updated: 2021/09/29 11:59:37 by asebrech         ###   ########.fr       */
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

void	fill_struct(int ac, char **av, t_philo *philo)
{
	philo->nb_philo = ft_atoi(av[0]);
	philo->nu_philo = 0;
	philo->t_die = ft_atoi(av[1]);
	philo->t_eat = ft_atoi(av[2]);
	philo->t_sleep = ft_atoi(av[3]);
	if (ac == 5)
		philo->nb_eat = ft_atoi(av[4]) * philo->nb_philo;
	else
		philo->nb_eat = -1;
	philo->count_eat = 0;
	/*
	printf("nb_philo = %d\n", philo->nb_philo);
	printf("t_die = %d\n", philo->t_die);
	printf("t_eat = %d\n", philo->t_eat);
	printf("t_sleep = %d\n", philo->t_sleep);
	if (ac == 5)
		printf("nb_eat = %d\n", philo->nb_eat);
	*/
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (check_args(ac - 1, av + 1))
			return (1);
		fill_struct(ac - 1, av + 1, &philo);
		philosophers(&philo);
	}
	else if (ac != 1)
		printf("Error\nwrong number of arguments\n");
	return (0);
}
