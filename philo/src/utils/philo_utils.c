/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:56:45 by jv                #+#    #+#             */
/*   Updated: 2023/05/21 11:48:15 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_philo_ctx	*build_context(char argc, char **argv)
{
	t_philo_ctx			*ctx;

	ctx = (t_philo_ctx *) ft_calloc(1, sizeof(t_philo_ctx));
	if (!ctx)
		return (NULL);
	ctx->number_of_philosofers = (t_byte) ft_atoi(argv[1]);
	ctx->time_to_die = ft_atoi(argv[2]);
	ctx->time_to_eat = ft_atoi(argv[3]);
	ctx->time_to_sleep = ft_atoi(argv[4]);
	ctx->all_alive = 1;
	ctx->start_time = philo_get_current_time();
	if (argc > 5)
		ctx->must_eat = ft_atoi(argv[5]);
	else
		ctx->must_eat = 0;
	ctx->forks = (t_fork *)
		ft_calloc(ctx->number_of_philosofers, sizeof(t_fork));
	if (!ctx->forks)
	{
		free(ctx);
		return (NULL);
	}
	return (ctx);
}

t_philo	*build_philos(int argc, char *argv[])
{
	t_philo_ctx	*ctx;
	t_philo		*philos;
	t_byte		i;

	ctx = build_context(argc, argv);
	philos = (t_philo *) ft_calloc(ctx->number_of_philosofers, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < ctx->number_of_philosofers)
	{
		philos[i].left = ctx->forks + min(i, (i + 1) % ctx->number_of_philosofers);
		philos[i].right = ctx->forks + max(i, (i + 1) % ctx->number_of_philosofers);
		philos[i].time_until_die = ctx->time_to_die;
		philos[i].position = i;
		philos[i].times_have_eat = 0;
		philos[i].ctx = ctx;
		philos[i].state = BORN;
		i++;
	}
	i = 0;
	while (i < ctx->number_of_philosofers)
	{
		pthread_mutex_init(&(ctx->forks + i)->fork, NULL);
		i++;
	}
	return (philos);
}

void	philo_print_state(t_philo *self, time_t time)
{
	if (self->state == DIED)
	{
		if (time > 0)
			ft_puts(philo_get_current_time() - time, self->position, "died", self);
		else
			ft_puts(philo_get_current_time(), self->position, "died", self);
	}
	else if (self->state == THINK && self->ctx->all_alive)
		ft_puts(philo_get_current_time(), self->position, "thinking", self);
	else if (self->state == EATING && self->ctx->all_alive)
		ft_puts(philo_get_current_time(), self->position, "eating", self);
	else if (self->state == SLEEP && self->ctx->all_alive)
		ft_puts(philo_get_current_time(), self->position, "sleeping", self);
}

void	one_philo(t_philo *p)
{
	time_t	time;

	time = philo_get_current_time();
	pthread_mutex_lock(&p->ctx->forks->fork);
	usleep(time_ms_to_mc(p->ctx->time_to_die));
	pthread_mutex_unlock(&p->ctx->forks->fork);
	p->state = DIED;
}
