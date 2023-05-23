/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:07:00 by jv                #+#    #+#             */
/*   Updated: 2023/05/21 00:30:05 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

time_t	philo_get_forks(t_philo *self)
{
	t_fork	*forks;
	struct timeval	current_time;
	time_t			diff;

	forks = self->ctx->forks;
	diff = philo_get_current_time();

	pthread_mutex_lock(&self->left->fork);
	ft_puts_fork(philo_get_current_time(), self->position, " has taken a fork", self);
	pthread_mutex_lock(&self->right->fork);
	ft_puts_fork(philo_get_current_time(), self->position, " has taken a fork", self);
	diff = philo_get_current_time() - diff;
	return (diff);
}

void	philo_put_forks(t_philo *self)
{
	pthread_mutex_unlock(&self->left->fork);
	pthread_mutex_unlock(&self->right->fork);
}