/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:56:45 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 11:00:29 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_philo_ctx  *build_context(char argc, char **argv)
{
	t_philo_ctx			*ctx;
	pthread_mutex_t		*forks;
	unsigned int		i;
	
	ctx = (t_philo_ctx *) calloc(1, sizeof(t_philo_ctx));
	if (!ctx)
		return (NULL);
	
	/* TIRAR o ATOI */
	ctx->number_of_philosofers	= (byte) atoi(argv[1]);
	ctx->time_to_die			= atoi(argv[2]);
	ctx->time_to_eat			= atoi(argv[3]);
	ctx->time_to_sleep			= atoi(argv[4]);
	ctx->all_alive				= 1;
	if (argc > 5)
		ctx->must_eat 			= atoi(argv[5]);
	else 
		ctx->must_eat			= 0;
	forks 	= (pthread_mutex_t *) calloc(ctx->number_of_philosofers, sizeof(pthread_mutex_t));
	if (!forks)
	{
		puts("error");
		free(ctx);
		return (NULL);
	}
	ctx->forks					= forks;
	i = 0;
	while (i < ctx->number_of_philosofers)
	{
		pthread_mutex_init(forks + i , NULL);
		i++;
	}
	
	return (ctx);
}

t_philo	*build_philos(int argc, char *argv[])
{
	t_philo_ctx	*ctx;
	t_philo		*philos;
	byte		i;

	ctx = build_context(argc, argv);
	philos	= (t_philo *) calloc(ctx->number_of_philosofers, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < ctx->number_of_philosofers)
	{
		philos[i].position 					= i;
		philos[i].time_until_die	 		= ctx->time_to_die;
		philos[i].times_have_eat 			= 0;
		philos[i].ctx						= ctx;
		philos[i].state						= BORN;
		i++;
	}
		
	return (philos);
}

void	philo_print_state(t_philo *self, time_t time)
{
	time_t 	current_time;
	struct timeval	t;

	current_time = philo_get_current_time();
	gettimeofday(&t, NULL);
	if (self->state == DIED)
	{
		printf("%ldms %d is died\n", current_time - time, self->position);
	}
	else if (self->state == THINK && self->ctx->all_alive)
		printf("%ldms %d is thinking\n", t.tv_usec / 1000, self->position);
	else if (self->state == EATING && self->ctx->all_alive)
		printf("%ldms %d is eating\n", t.tv_usec / 1000, self->position);
	else if (self->state == SLEEP && self->ctx->all_alive)
		printf("%ldms %d is sleeping\n", t.tv_usec / 1000, self->position);
}