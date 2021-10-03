/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alois <alois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:19:02 by alois             #+#    #+#             */
/*   Updated: 2021/10/03 17:41:28 by alois            ###   ########.fr       */
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

void	fill_info(int ac, char **av, t_info *info)
{
	info->nb_philo = ft_atoi(av[0]);
	info->t_die = ft_atoi(av[1]);
	info->t_eat = ft_atoi(av[2]);
	info->t_sleep = ft_atoi(av[3]);
	if (ac == 5)
		info->nb_eat = ft_atoi(av[4]);
	else
		info->nb_eat = -1;
}

void	fill_philo(t_info *info, t_philo *philo)
{
	int				i;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*mutex;

	i = -1;
	mutex = NULL;
	left = malloc(sizeof(left) * info->nb_philo);
	right = malloc(sizeof(left) * info->nb_philo);
	philo = malloc(sizeof(philo) * info->nb_philo);
	while (++i < info->nb_philo)
	{
		philo[i].nu_philo = i + 1;
		philo[i].mutex = mutex;
		philo[i].info = info;
		philo[i].left_fork = left + i;
		if (i == info->nb_philo)
			philo[i].right_fork = right;
		else
			philo[i].right_fork = right + i + 1;
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		if (check_args(ac - 1, av + 1))
			return (1);
		fill_info(ac - 1, av + 1, &info);
		fill_philo(&info, philo);
		//philosophers(philo);
	}
	else if (ac != 1)
		printf("Error\nwrong number of arguments\n");
	return (0);
}
