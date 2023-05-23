/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:55:44 by jv                #+#    #+#             */
/*   Updated: 2023/05/21 11:27:44 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

time_t	philo_get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		return (0);
	}
	return ((time.tv_sec * (time_t)1000) + (time.tv_usec / 1000));
}

unsigned int	time_ms_to_mc(time_t time_in_ms)
{
	return (time_in_ms * 1000);
}

void	ft_mstime(time_t time)
{
	time_t start;

	start = philo_get_current_time();

	
	while (time > (philo_get_current_time() - start))
		usleep(time_ms_to_mc(DELAY));
}
