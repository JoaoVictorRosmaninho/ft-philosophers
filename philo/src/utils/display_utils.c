/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:43:42 by jv                #+#    #+#             */
/*   Updated: 2023/08/01 10:59:09 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

time_t	ft_log_actions(t_philosopher *self)
{
	time_t	time;
	time_t	diff_start_time;

	time			= time_get_current_time();
	diff_start_time	= time - self->context->start_time; 
	pthread_mutex_lock(&self->context->in_out_mutex);
//	printf("Monitor Routine: %u\n", monitor_stop_routine(self));
	if (self->state == THINKING) {
		printf("%5ldms philosopher %2d is thinking\n", diff_start_time, self->id + 1);
	} else if (self->state == EATING) {
		printf("%5ldms philosopher %2d has take a fork\n", diff_start_time, self->id + 1);
		printf("%5ldms philosopher %2d has take a fork\n", diff_start_time, self->id + 1);
		printf("%5ldms philosopher %2d is eating\n", diff_start_time, self->id + 1);
	} else if (self->state == SLEEPING) {
		printf("%5ldms philosopher %2d is sleeping\n", diff_start_time, self->id + 1);
	} else if (self->state == DIED) {
		printf("%5ldms philosopher %2d is died\n", diff_start_time, self->id + 1);
	} else {
		printf("%5ldms philosopher %2d is stuffed\n", diff_start_time, self->id + 1);
	}

	pthread_mutex_unlock(&self->context->in_out_mutex);
	
	return (time);
}
