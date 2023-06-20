/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chaecker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:04:23 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/10 14:02:27 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_ac(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31mError:\033[0;33m Wrong number of arguments\n\033[0m\n");
		return (0);
	}
	return (1);
}

int	ft_check_av(char av)
{
	if (av < '0' || av > '9')
	{
		printf("\033[0;31mError:\033[0;33m Wrong argument\n\033[0m\n");
		return (0);
	}
	return (1);
}

int	ft_check_av_eat(int ac, char **av)
{
	if (ac == 6)
	{
		if(ft_atoi(av[5]) == 0)
		{
			printf("\033[0;31m each philo must eat at least 1 time\n\033[0m\n");
			return(0);
		}
	}
	return (1);
}

int	ft_check_eating(t_philo *tmp, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&tmp->count_mutex);
		if (tmp->each_philo_must_eat != tmp->count_eting)
			return (pthread_mutex_unlock(&tmp->count_mutex), 0);
		pthread_mutex_unlock(&tmp->count_mutex);
		i++;
	}
	return (1);
}
