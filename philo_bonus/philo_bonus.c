/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:31:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/09 15:13:55 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_overf_tcheck(char *str)
{
	long long int	i;
	int				g;

	i = ft_atoi_long(str);
	g = ft_atoi(str);
	if (i != g)
	{
		printf("\033[0;31mError:\033[0;33m Wrong argument <overflow>\n\033[0m\n");
		return (0);
	}
	return (1);
}

int	ft_par_check(int ac, char **av)
{
	int	i;
	int	j;

	if (!ft_check_ac(ac))
		return (0);
	else
	{
		i = 1;
		while (i < ac)
		{
			j = 0;
			while (av[i][j])
			{
				if (av[i][0] == '+' && j == 0)
					j++;
				if (!ft_check_av(av[i][j]))
					return (0);
				j++;
			}
			if (!ft_overf_tcheck(av[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void ft_philo(int  i)
{
	int j = 0;
	while(1)
	{
		printf("hello %d\n", i);
		if(j == 10)
			break;
		j++;
	}
		
}

int	main(int ac, char **av)
{
	t_philo			*tmp;
	int				nb_philo;
	int				i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (!ft_par_check(ac, av))
		return (1);
	nb_philo = ft_atoi(av[1]);
	if (!(nb_philo))
	{
		printf("\033[0;31mError: <wrong number of philosophers>\n\033[0m\n");
		return (0);
	}
	i = nb_philo;
	tmp = ft_creat_philosophers(ac, av);
	while (nb_philo > 0)
	{
		if(fork() == 0)
			ft_philo(nb_philo);
		
		nb_philo--;
	}
}