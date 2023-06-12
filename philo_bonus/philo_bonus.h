/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:33:37 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/11 17:02:04 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H


# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>
# include <semaphore.h>
# include <sys/time.h>
#include <sys/types.h>
# include <unistd.h>

typedef struct s_philo
{
	sem_t	*fork;
	pthread_t 		checker;
	pthread_t 		checker_2;
	sem_t	*printf_lock;
	sem_t	*eat_lock;
	sem_t	*flag_p;
	sem_t	*hada;
	int 			id;
	int 			nb_philo;
	long			time;
	int				t_to_die;
	int				t_to_eat;
	long			start_eating;
	int				t_to_sleep;
	int				flag;
	int				each_philo_must_eat;
	int				count_eting;
}					t_philo;


//utils.c
int					ft_atoi(const char *str);
long long int		ft_atoi_long(const char *str);

//creat_philo_bonus.c
t_philo				*creat_list(int ac, char **av, int i);
t_philo				*ft_creat_philosophers(int ac, char **av);
long				get_time(void);
void				ft_my_sleep(int sleep);

//chaecker_bous.c
int					ft_check_ac(int ac);
int					ft_check_av(char av);

#endif