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
void eatcheck(t_philo *philosopher)
{
	if (philosopher->flag)
	{
	if (philosopher->count_eting == philosopher->each_philo_must_eat)
	{
		philosopher->flag = 0;
		sem_wait(philosopher->printf_lock);
		printf("time : %ld | %d is full\n", (get_time() - philosopher->time),
			philosopher->id);
		sem_post(philosopher->printf_lock);
		sem_post(philosopher->hada);
	}
	 	
	}
	
}

void *ft_dead_check(void *philo)
{
	t_philo	*philosopher;
	pthread_t		dead;


	philosopher = (t_philo *)philo;
	while(1)
	{
	
			
			if (get_time() - philosopher->start_eating > philosopher->t_to_die)
			{
				sem_wait(philosopher->flag_p);
				philosopher->flag = 0;
				
			sem_wait(philosopher->printf_lock);
				printf("time : %ld | %d died\n", (get_time() - philosopher->time),
					philosopher->id);
			// sem_post(philosopher->printf_lock);
					// usleep(100);
				exit(3);
			}
			sem_post(philosopher->eat_lock);
			eatcheck(philosopher);
			
	}


}

void ft_philo(t_philo *philosopher ,int id)
{
philosopher->id = id;
struct timeval	tv;


	pthread_create(&philosopher->checker, NULL, ft_dead_check, philosopher);
	while (1)
	{
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
	
	if (philosopher->flag){
		sem_wait(philosopher->printf_lock);
		printf("time : %ld | %d is sleeping\n", (get_time()
				- philosopher->time), id);
				sem_post(philosopher->printf_lock);
	}
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

void *ft_checker_2(void *philo)
{
	t_philo	*philosopher;

	int i;
	
	philosopher = (t_philo *)philo;
	i = philosopher->nb_philo;

	while(i > 0)
	{
		sem_wait(philosopher->hada);
		i--;
	}
	kill(0, SIGINT);
	return NULL;
}

int	main(int ac, char **av)
{
	t_philo			*tmp;
	int				nb_philo;
	int				childStatus;
	int exitStatus;
	int				i;
	int j= 0;
	pid_t tabl[atoi(av[1]) + 1];
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
pthread_create(&tmp->checker_2, NULL, ft_checker_2, tmp);
	while (nb_philo > 0)
	{
		int pid = fork();
		if(pid == 0)
			ft_philo(tmp, i - nb_philo + 1);
		// printf("|%d|\n", pid);
		nb_philo--;
	}

	waitpid(-1, &childStatus, 0);
	kill(0, SIGINT);
	return (0);
}