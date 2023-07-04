/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:22:38 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/04 12:32:21 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_dead_check(void *philo)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)philo;
	while (1)
	{
		if (get_time() - philosopher->start_eating > philosopher->t_to_die)
		{
			sem_wait(philosopher->flag_p);
			philosopher->flag = 0;
			sem_wait(philosopher->printf_lock);
			printf("time : %ld | %d died\n", (get_time() - philosopher->time),
				philosopher->id);
			exit(3);
		}
		sem_post(philosopher->eat_lock);
		eatcheck(philosopher);
		usleep(200);
	}
}

void	*ft_checker_2(void *philo)
{
	t_philo	*philosopher;
	int		i;

	philosopher = (t_philo *)philo;
	i = philosopher->nb_philo;
	while (i > 0)
	{
		sem_wait(philosopher->hada);
		i--;
	}
	kill(0, SIGINT);
	return (NULL);
}

void	ft_philo_3(t_philo *philosopher, int id)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (philosopher->flag)
	{
		sem_wait(philosopher->printf_lock);
		printf("time : %ld | %d is eating\n", (get_time() - philosopher->time),
			id);
		sem_post(philosopher->printf_lock);
	}
	philosopher->count_eting++;
	sem_wait(philosopher->eat_lock);
		philosopher->start_eating = get_time();
	ft_my_sleep(philosopher->t_to_eat);
	sem_post(philosopher->fork);
	sem_post(philosopher->fork);
	gettimeofday(&tv, NULL);
	if (philosopher->flag)
	{
		sem_wait(philosopher->printf_lock);
		printf("time : %ld | %d is sleeping\n", (get_time()
				- philosopher->time), id);
		sem_post(philosopher->printf_lock);
	}
}

void	ft_philo_2(t_philo *philosopher, int id)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	sem_wait(philosopher->fork);
	if (philosopher->flag)
	{
		sem_wait(philosopher->printf_lock);
		printf("time : %ld | %d has taken a fork\n", (get_time()
				- philosopher->time), id);
		sem_post(philosopher->printf_lock);
	}
	sem_wait(philosopher->fork);
	gettimeofday(&tv, NULL);
	sem_wait(philosopher->printf_lock);
	printf("time : %ld | %d has taken a fork\n", (get_time()
			- philosopher->time), id);
	sem_post(philosopher->printf_lock);
}

void	ft_philo(t_philo *philosopher, int id)
{
	struct timeval	tv;

	philosopher->id = id;
	pthread_create(&philosopher->checker, NULL, ft_dead_check, philosopher);
	while (1)
	{
		ft_philo_2(philosopher, id);
		ft_philo_3(philosopher, id);
		ft_my_sleep(philosopher->t_to_sleep);
		gettimeofday(&tv, NULL);
		if (philosopher->flag)
		{
			sem_wait(philosopher->printf_lock);
			printf("time : %ld | %d is thinking\n", (get_time()
					- philosopher->time), id);
			sem_post(philosopher->printf_lock);
		}
	}	
}
