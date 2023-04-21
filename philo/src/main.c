/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:18:36 by jv                #+#    #+#             */
/*   Updated: 2023/04/21 19:16:43 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void philo_free(t_philo *philos)
{
	if (philos)
	{
		free(philos[0].ctx->forks);
		free(philos[0].ctx);
		//free(philos);
	}
}

t_philo	*build_philos(int argc, char *argv[])
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	t_philo_ctx			*ctx;


	ctx = (t_philo_ctx *) calloc(1, sizeof(ctx));
	if (!ctx)
		return (NULL);
	/* TIRAR o ATOI */
	ctx->number_of_philosofers	= (byte) atoi(argv[1]);
	ctx->time_to_die			= atoi(argv[2]);
	ctx->time_to_eat			= atoi(argv[3]);
	ctx->time_to_sleep			= atoi(argv[4]);
	ctx->all_alive				= 1;
	philos	= (t_philo *) calloc(ctx->number_of_philosofers, sizeof(t_philo));
	if (!philos)
	{
		free(ctx);
		return (NULL);
	}
	forks 	= (pthread_mutex_t *) calloc(ctx->number_of_philosofers, sizeof(pthread_mutex_t));
	if (!forks)
	{
		free(philos);
		free(ctx);
		return (NULL);
	}
	ctx->forks					= forks;
	if (argc > 5)
		ctx->must_eat 			= atoi(argv[5]);
	else 
		ctx->must_eat			= 0;
	for (byte i = 0; i < ctx->number_of_philosofers; i++)
	{
		
		philos[i].position 					= i;
		philos[i].time_until_die	 		= ctx->time_to_die;
		philos[i].times_have_eat 			= 0;
		philos[i].ctx						= ctx;
		philos[i].state						= BORN;
		if (pthread_mutex_init((forks + i), NULL) != 0)
		{
			// Error 
			free(philos);
			free(ctx);
			free(forks);
			return NULL;
		}
	}
	
	return (philos);
}


byte philo_get_left_fork(t_philo *self)
{
	if (self->position < 1)
		return (self->ctx->number_of_philosofers - 1);
	return (self->position - 1);
}

byte philo_get_right_fork(t_philo *self)
{
	byte last;
	last = self->ctx->number_of_philosofers - 1;
	if (self->position == last)
		return (0);
	return (self->position + 1);
}

time_t philo_get_forks(t_philo *self)
{

	pthread_mutex_t *forks;
	struct timeval 	current_time;
	time_t 			diff; 

	forks = self->ctx->forks;
	diff = 0;

	gettimeofday(&current_time, NULL);	
	diff = current_time.tv_usec;
	
	pthread_mutex_lock(forks + philo_get_left_fork(self));
	gettimeofday(&current_time, NULL);
	//if (!self->ctx->all_alive) return (0);
	printf("%ldms %d has taken a fork\n", current_time.tv_usec / 1000, self->position);
	
	pthread_mutex_lock(forks + philo_get_right_fork(self));
	gettimeofday(&current_time, NULL);
	//if (!self->ctx->all_alive) return (0);
	printf("%ldms %d has taken a fork\n", current_time.tv_usec / 1000, self->position);
	
	diff = current_time.tv_usec - diff;
	return (diff / 1000);
}

void philo_put_forks(t_philo *self)
{
	byte left_fork;
	byte right_fork;

	left_fork  = philo_get_left_fork(self);
	right_fork = philo_get_right_fork(self);

	pthread_mutex_unlock(self->ctx->forks + left_fork);
	pthread_mutex_unlock(self->ctx->forks + right_fork);
}

void	philo_print_state(t_philo *self)
{
	struct timeval 	current_time;
	gettimeofday(&current_time, NULL);

	if (self->state == THINK)
	{
		printf("%ldms %d is thinking\n", current_time.tv_usec / 1000, self->position);
	}
	else if (self->state == EATING)
	{
		printf("%ldms %d is eating\n", current_time.tv_usec / 1000, self->position);
	}
	else if (self->state == SLEEP)
	{
		printf("%ldms %d is sleeping\n", current_time.tv_usec / 1000, self->position);
	}
	else if (self->state == DIED)
	{
		printf("%ldms %d is died\n", current_time.tv_usec / 1000, self->position);
	}
}

unsigned int time_ms_to_mc(unsigned int time_in_ms)
{
	return (time_in_ms * 1000);
}

void philo_eat(t_philo *self)
{
	time_t time;
	
	//if (!self->ctx->all_alive) return ;

	if ((time = philo_get_forks(self)) >= self->time_until_die)
	{
		philo_put_forks(self);
		self->state = DIED;
		self->ctx->all_alive = 0;
	}
	else //if (time > 0)
	{
		self->state = EATING;
		if ( usleep(time_ms_to_mc(self->ctx->time_to_eat)) != 0 )
			printf("Error no usleep \n");
		philo_put_forks(self);
		self->time_until_die = self->ctx->time_to_die;
		self->times_have_eat++;
	}
	philo_print_state(self);
}

void philo_think(t_philo *self)
{
	self->state = THINK;
	philo_print_state(self);
}

void	philo_sleep(t_philo *self)
{
	// if (!self->ctx->all_alive) return ;
	self->state = SLEEP;
	philo_print_state(self);
	if (usleep(time_ms_to_mc(self->ctx->time_to_sleep)) != 0)
		printf("Error no usleep \n");
	self->time_until_die -= self->ctx->time_to_sleep;
}

void *init_routine(void *self)
{
	t_philo *p = (t_philo *) self;
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
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_philo *philos = NULL;
	t_philo_ctx *ctx;

	if (argc < 5 || argc > 6)
		return (-1);
	philos = build_philos(argc, argv);
	ctx = philos[0].ctx;
	
	for (byte index = 0; index < ctx->number_of_philosofers; index++)
	{
		if (pthread_create(&philos[index].task, NULL, &init_routine, (void *)(philos + index)) != 0) {
			printf("Error\n");
			return (1);
		} 	
	}

	for (byte index = 0; index < ctx->number_of_philosofers; index++)
	{
		if (pthread_join(philos[index].task, NULL) != 0) {
			printf("Error ao juntar as threads\n");
			return (1);
		} 	
	}
	philo_free(philos);
}
