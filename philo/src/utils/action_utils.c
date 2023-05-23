/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:20:13 by jv                #+#    #+#             */
/*   Updated: 2023/05/22 23:00:24 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	philo_eat(t_philo *self)
{
	time_t	time;

	if (!self->ctx->all_alive)
		return ;
	time = philo_get_forks(self);
	if (time > self->time_until_die)
	{
		self->ctx->all_alive = 0;
		philo_put_forks(self);
		self->state = DIED;
	}
	else
	{
		self->state = EATING;
		ft_mstime(self->ctx->time_to_eat);
		self->time_until_die = self->ctx->time_to_die;
		self->times_have_eat++;
		philo_put_forks(self);
	}
	philo_print_state(self, 0);
}

static void	philo_think(t_philo *self)
{
	self->state = THINK;
	philo_print_state(self, 0);
}

static void	philo_sleep(t_philo *self)
{
	if (!self->ctx->all_alive)
		return ;
	self->state = SLEEP;
	philo_print_state(self, 0);
	ft_mstime(self->ctx->time_to_sleep);
	self->time_until_die -= self->ctx->time_to_sleep;
	if (self->time_until_die <= 0)
	{
		self->state = DIED;
		if (self->ctx->all_alive)
			philo_print_state(self, 0);
		self->ctx->all_alive = 0;
	}
}

static void	do_action(t_philo *p)
{
	if (p->ctx->must_eat > 0)
	{
		while ((p->state != DIED) && (p->ctx->all_alive)
			&& (p->times_have_eat < p->ctx->must_eat))
		{
			philo_think(p);
			philo_eat(p);
			philo_sleep(p);
		}
	}
	else
	{
		while ((p->state != DIED) && (p->ctx->all_alive))
		{
			philo_think(p);
			philo_eat(p);
			philo_sleep(p);
		}
	}
}

void	*init_routine(void *self)
{
	t_philo	*p;

	p = (t_philo *) self;
	if (p->ctx->number_of_philosofers == 1)
		one_philo(p);
	else
		do_action(p);
	return (NULL);
}
