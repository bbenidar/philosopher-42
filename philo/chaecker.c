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

int	ft_check_eating(t_philo *tmp, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (tmp->each_philo_must_eat > tmp->count_eting)
			return (0);
		i++;
	}
	return (1);
}
