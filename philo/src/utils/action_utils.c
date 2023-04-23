/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:20:13 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 11:04:41 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void    philo_eat(t_philo *self)
{
	time_t	time;
	
	if (!self->ctx->all_alive) return ;

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
		if ( usleep(time_ms_to_mc(self->ctx->time_to_eat)) != 0 )
			printf("Error no usleep \n");
		philo_put_forks(self);
		self->time_until_die = self->ctx->time_to_die;
		self->times_have_eat++;
	}
	philo_print_state(self, 0);
}

static void philo_think(t_philo *self)
{
	self->state = THINK;
	philo_print_state(self, 0);
}

static void	philo_sleep(t_philo *self)
{
	 if (!self->ctx->all_alive) return ;
	self->state = SLEEP;
	philo_print_state(self, 0);
	if (usleep(time_ms_to_mc(self->ctx->time_to_sleep)) != 0)
		printf("Error no usleep \n");
	self->time_until_die -= self->ctx->time_to_sleep;
	if (self->time_until_die <= 0) self->state = DIED;
}

void *init_routine(void *self)
{
	t_philo *p = (t_philo *) self;
	if (p->ctx->number_of_philosofers == 1)
	{
		time_t time = philo_get_current_time();
		pthread_mutex_lock(p->ctx->forks);
		printf("%ldms %d has taken a fork\n", philo_get_current_time() - time, p->position);
		usleep(time_ms_to_mc(p->ctx->time_to_die));
		pthread_mutex_unlock(p->ctx->forks);
		p->state = DIED;
	}
	else
	{
		if (p->ctx->must_eat > 0)
			while ((p->state != DIED) && (p->ctx->all_alive) && (p->times_have_eat < p->ctx->must_eat))
			{
				philo_think(p);
				philo_eat(p);
				philo_sleep(p);
			}
		else
			while ((p->state != DIED) && (p->ctx->all_alive))
			{
				philo_think(p);
				philo_eat(p);
				philo_sleep(p);
			}
	}
	return (NULL);
}

byte	philo_one_philo(t_philo *array_of_philos)
{
	time_t time = philo_get_current_time();
	if (pthread_create(&array_of_philos[0].task, NULL, &init_routine, (void *)array_of_philos))
		return 0;
	pthread_detach(array_of_philos[0].task);
	while (array_of_philos->state != DIED) ; 
	philo_print_state(array_of_philos, time);
	return (0);
}