/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:14:18 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/11 19:43:53 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if (!ft_check_av_eat(ac, av))
		return (0);
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

void	ft_free(t_philo *tmp, int nb_philo)
{
	t_philo *tmp2;
	while (nb_philo > 0)
	{
			tmp2 = tmp->next;
		pthread_mutex_destroy(&tmp->printf_mutex);
		pthread_mutex_destroy(&tmp->fork);
		pthread_mutex_destroy(&tmp->sef_mutex);
		pthread_detach(tmp->thread);
		free(tmp);
		tmp = tmp2;
		nb_philo--;
	}
}

void	main_two(t_philo *tmp, int i, int j)
{
	while (1)
	{
		pthread_mutex_lock(&tmp->sef_mutex);
		if (((get_time() - tmp->start_eating) > tmp->t_to_die))
		{
			while (i > 0)
			{
				pthread_mutex_lock(&tmp->flag_mutex);
				tmp->flag = 0;
				tmp = tmp->next;
				i--;
				pthread_mutex_unlock(&tmp->flag_mutex);
			}
			pthread_mutex_lock(&tmp->printf_mutex);
			usleep(50);
			printf("time : %ld |  %d is dead\n", (get_time() - tmp->time),
				tmp->id);
			pthread_mutex_unlock(&tmp->printf_mutex);
			break ;
		}
		if (ft_check_eating(tmp, j))
			break ;
		pthread_mutex_unlock(&tmp->sef_mutex);
		tmp = tmp->next;
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
		pthread_create(&tmp->thread, NULL, ft_philo, tmp);
		usleep(100);
		tmp = tmp->next;
		nb_philo--;
	}
	main_two(tmp, i, i);
	ft_free(tmp, i);
}
