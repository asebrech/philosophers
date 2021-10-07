/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:41:58 by asebrech          #+#    #+#             */
/*   Updated: 2021/10/07 13:43:58 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

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
		if ((i == 0 && tmp <= 0) || tmp > INT_MAX)
		{
			printf("Error\narguments too large or not large enough\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	*fill_philo_1(int ac, char **av)
{
	t_philo			*philo;
	int				i;
	int				nb;				

	nb = ft_atoi(av[0]);
	philo = malloc(sizeof(t_philo) * nb);
	i = -1;
	while (++i < nb)
	{
		philo[i].nb_philo = nb;
		philo[i].time = 0;
		philo[i].timestamp = 0;
		philo[i].count = 0;
		philo[i].t_die = ft_atoi(av[1]);
		philo[i].t_eat = ft_atoi(av[2]);
		philo[i].t_sleep = ft_atoi(av[3]);
		if (ac == 5)
			philo[i].nb_eat = ft_atoi(av[4]);
		else
			philo[i].nb_eat = -1;
	}
	return (philo);
}

void	fill_philo(t_philo *philo)
{
	int				i;
	sem_t			*forks;
	sem_t			*semaphore;
	sem_t			*sema_eat;
	sem_t			*toto;

	sem_unlink("forks");
	sem_unlink("semaphore");
	sem_unlink("sema_eat");
	sem_unlink("toto");
	forks = sem_open("forks", O_CREAT, S_IRWXU, philo->nb_philo);
	semaphore = sem_open("semaphore", O_CREAT, S_IRWXU, 1);
	sema_eat = sem_open("sema_eat", O_CREAT, S_IRWXU, 0);
	toto = sem_open("toto", O_CREAT, S_IRWXU, 1);
	i = -1;
	while (++i < philo->nb_philo)
	{
		philo[i].nu_philo = i + 1;
		philo[i].kill = 0;
		philo[i].semaphore = semaphore;
		philo[i].sema_eat = sema_eat;
		philo[i].toto = toto;
		philo[i].forks = forks;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		if (check_args(ac - 1, av + 1))
			return (1);
		philo = fill_philo_1(ac - 1, av + 1);
		fill_philo(philo);
		philosophers(philo);
		free(philo);
	}
	else if (ac != 1)
		printf("Error\nwrong number of arguments\n");
	return (0);
}
