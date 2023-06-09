/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheacker_bous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:51:47 by bbenidar          #+#    #+#             */
/*   Updated: 2023/06/09 11:52:00 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_ac(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31mError:\033[0;33m Wrong number of arguments\n\033[0m\n");
		return (0);
	}
	return (1);
}

int	ft_check_av(char av)
{
	if (av < '0' || av > '9')
	{
		printf("\033[0;31mError:\033[0;33m Wrong argument\n\033[0m\n");
		return (0);
	}
	return (1);
}
