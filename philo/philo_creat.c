/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:08:23 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/08 14:42:13 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_my_sleep(int sleep)
{
	long	x;

	x = get_time();
	while ((get_time() - x) < sleep)
		usleep(100);
}

t_philo	*creat_list(int ac, char **av, int i)
{
	t_philo			*philo;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo = malloc(sizeof(t_philo));
	philo->id = i + 1;
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->printf_mutex, NULL);
	pthread_mutex_init(&philo->sef_mutex, NULL);
	pthread_mutex_init(&philo->flag_mutex, NULL);
	pthread_mutex_init(&philo->count_mutex, NULL);
	philo->t_to_die = ft_atoi(av[2]);
	philo->t_to_eat = ft_atoi(av[3]);
	philo->t_to_sleep = ft_atoi(av[4]);
	philo->count_eting = 0;
	philo->flag = 1;
	philo->start_eating = get_time();
	philo->time = get_time();
	if (ac == 6)
		philo->each_philo_must_eat = ft_atoi(av[5]);
	else
		philo->each_philo_must_eat = -1;
	philo->next = NULL;
	return (philo);
}

t_philo	*ft_creat_philosophers(int ac, char **av)
{
	t_philo	*philo;
	t_philo	*head;
	int		nb_philo;
	int		i;

	nb_philo = ft_atoi(av[1]);
	i = 1;
	philo = creat_list(ac, av, 0);
	head = philo;
	while (i < nb_philo)
	{
		philo->next = creat_list(ac, av, i);
		philo = philo->next;
		i++;
	}
	philo->next = head;
	return (head);
}
