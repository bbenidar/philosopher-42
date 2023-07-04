/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:25:00 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/03 13:56:15 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_three(t_philo *philosopher)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philosopher->flag_mutex);
	if (philosopher->flag)
		printf("time : %ld | %d is sleeping\n", (get_time()
				- philosopher->time), philosopher->id);
	pthread_mutex_unlock(&philosopher->flag_mutex);
	ft_my_sleep(philosopher->t_to_sleep);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philosopher->flag_mutex);
	if (philosopher->flag)
		printf("time : %ld | %d is thinking\n", (get_time()
				- philosopher->time), philosopher->id);
	pthread_mutex_unlock(&philosopher->flag_mutex);
	pthread_mutex_lock(&philosopher->count_mutex);
	philosopher->count_eting++;
	pthread_mutex_unlock(&philosopher->count_mutex);
}

void	ft_philo_two(t_philo *philosopher)
{
	struct timeval	tv;

	if (philosopher->flag)
		printf("time : %ld | %d has taken a fork\n", (get_time()
				- philosopher->time), philosopher->id);
	pthread_mutex_unlock(&philosopher->flag_mutex);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philosopher->flag_mutex);
	if (philosopher->flag)
		printf("time : %ld | %d is eating\n", (get_time() - philosopher->time),
			philosopher->id);
	pthread_mutex_unlock(&philosopher->flag_mutex);
	pthread_mutex_lock(&philosopher->sef_mutex);
	philosopher->start_eating = get_time();
	pthread_mutex_unlock(&philosopher->sef_mutex);
	ft_my_sleep(philosopher->t_to_eat);
	pthread_mutex_unlock(&philosopher->next->fork);
	pthread_mutex_unlock(&philosopher->fork);
	ft_philo_three(philosopher);
}

void	*ft_philo(void *philo)
{
	struct timeval	tv;
	t_philo			*philosopher;

	philosopher = (t_philo *)philo;
	while (1)
	{
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&philosopher->fork);
		pthread_mutex_lock(&philosopher->flag_mutex);
		if (philosopher->flag)
			printf("time : %ld | %d has taken a fork\n", (get_time()
					- philosopher->time), philosopher->id);
		pthread_mutex_unlock(&philosopher->flag_mutex);
		pthread_mutex_lock(&philosopher->next->fork);
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&philosopher->flag_mutex);
		ft_philo_two(philosopher);
	}
}
