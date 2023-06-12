/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:14:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/10 14:01:55 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	sef_mutex;
	pthread_mutex_t	flag_mutex;
	long			time;
	int				t_to_die;
	int				t_to_eat;
	long			start_eating;
	int				t_to_sleep;
	int				flag;
	int				each_philo_must_eat;
	int				count_eting;
	struct s_philo	*next;
}					t_philo;

//utils.c
int					ft_atoi(const char *str);
long long int		ft_atoi_long(const char *str);

//chaecker.c
int					ft_check_ac(int ac);
int					ft_check_av(char av);
int					ft_check_eating(t_philo *tmp, int nb_philo);

//creat_philo.c
t_philo				*creat_list(int ac, char **av, int i);
t_philo				*ft_creat_philosophers(int ac, char **av);
long				get_time(void);
void				ft_my_sleep(int sleep);

//routine.c
void				*ft_philo(void *philo);
void				ft_philo_two(t_philo *philosopher);

#endif
