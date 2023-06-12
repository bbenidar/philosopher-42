/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creat_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:41:25 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/11 18:59:44 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

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


t_philo	*ft_creat_philosophers(int ac, char **av)
{
	t_philo	*philo;
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	
	philo = malloc(sizeof(t_philo));
	sem_unlink("/forks");
	int i = ft_atoi(av[1]);
	philo->fork =  sem_open("/forks",O_CREAT | O_EXCL,0644, i);
	if (philo->fork == SEM_FAILED)
	{
		printf("Error: sem_open\n");
		exit(1);
	}
	sem_unlink("/PHILO_PRINTF");
	philo->printf_lock = sem_open("/PHILO_PRINTF",O_CREAT| O_EXCL,0644, 1);
	if (philo->printf_lock == SEM_FAILED)
	{
		printf("Error: sem_printf\n");
		exit(1);
	}
	sem_unlink("/PHILO_EAT");
	philo->eat_lock = sem_open("/PHILO_EAT",O_CREAT| O_EXCL,0644, 1);
	if (philo->eat_lock == SEM_FAILED)
	{
		printf("Error: sem_eat\n");
		exit(1);
	}
		sem_unlink("/hada");
	philo->hada = sem_open("/hada",O_CREAT| O_EXCL,0644, 0);
	if (philo->hada == SEM_FAILED)
	{
		printf("Error: sem_eat\n");
		exit(1);
	}
	sem_unlink("/PHILO_hh");
	philo->flag_p = sem_open("/PHILO_hh",O_CREAT| O_EXCL,0644, 1);
	if (philo->flag_p == SEM_FAILED)
	{
		printf("Error: sem_hh\n");
		exit(1);
	}
	philo->nb_philo = ft_atoi(av[1]);
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
	
	return (philo);
}




//fork()
//fork()