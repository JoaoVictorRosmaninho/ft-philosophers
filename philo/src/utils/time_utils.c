/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:55:44 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 09:57:58 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

time_t	philo_get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		 //show_message_and_die("Error: philo_get_current_time not working\n", NULL);
		 return 0;
	}
	
	return ((time.tv_sec * (time_t)1000) + (time.tv_usec / 1000));
}

unsigned int time_ms_to_mc(unsigned int time_in_ms)
{
	return (time_in_ms * 1000);
}