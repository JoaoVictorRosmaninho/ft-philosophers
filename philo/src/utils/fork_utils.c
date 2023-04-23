/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:07:00 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 18:28:58 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_byte	philo_get_left_fork(t_philo *self)
{
	return ((self->position - 1 + self->ctx->number_of_philosofers)
		% self->ctx->number_of_philosofers);
}

static t_byte	philo_get_right_fork(t_philo *self)
{
	return ((self->position) % self->ctx->number_of_philosofers);
}

time_t	philo_get_forks(t_philo *self)
{
	pthread_mutex_t	*forks;
	struct timeval	current_time;
	time_t			diff;

	forks = self->ctx->forks;
	diff = 0;
	gettimeofday(&current_time, NULL);
	diff = current_time.tv_usec;
	pthread_mutex_lock(forks + philo_get_left_fork(self));
	gettimeofday(&current_time, NULL);
	if (!self->ctx->all_alive)
		return (0);
	ft_puts_fork(current_time.tv_usec / 1000, self->position, " has taken a fork", self);
	pthread_mutex_lock(forks + philo_get_right_fork(self));
	gettimeofday(&current_time, NULL);
	if (!self->ctx->all_alive)
		return (0);
	ft_puts_fork(current_time.tv_usec / 1000, self->position, " has taken a fork", self);
	diff = current_time.tv_usec - diff;
	return (diff / 1000);
}

void	philo_put_forks(t_philo *self)
{
	pthread_mutex_unlock(self->ctx->forks + philo_get_left_fork(self));
	pthread_mutex_unlock(self->ctx->forks + philo_get_right_fork(self));
}
