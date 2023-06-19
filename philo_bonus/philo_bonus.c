/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:31:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/12 12:42:28 by bbenidar         ###   ########.fr       */
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

void	eatcheck(t_philo *philosopher)
{
	if (philosopher->flag)
	{
		if (philosopher->count_eting == philosopher->each_philo_must_eat)
		{
			philosopher->flag = 0;
			sem_post(philosopher->hada);
		}
	}
}

void	main_2(int ac, int nb_philo, char **av)
{
	t_philo	*tmp;
	int		i;
	int		pid;
	int		childstatus;

	i = nb_philo;
	tmp = ft_creat_philosophers(ac, av);
	pthread_create(&tmp->checker_2, NULL, ft_checker_2, tmp);
	while (nb_philo > 0)
	{
		pid = fork();
		if (pid == 0)
			ft_philo(tmp, i - nb_philo + 1);
		nb_philo--;
		usleep(200);
	}
	waitpid(-1, &childstatus, 0);
	ft_free_close(tmp);
}

int	main(int ac, char **av)
{
	int				nb_philo;
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
	main_2(ac, nb_philo, av);
	return (0);
}
