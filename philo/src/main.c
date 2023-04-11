/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:18:36 by jv                #+#    #+#             */
/*   Updated: 2023/04/10 22:49:38 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void philo_free(t_philo *philos)
{
	if (philos)
	{
		free(philos->ctx->forks);
		free(philos->ctx);
		free(philos);
	}
}

t_philo	*build_philos(int argc, char *argv[])
{
	t_philo		*philos;
	byte		*forks;
	t_philo_ctx	*ctx;


	ctx = (t_philo_ctx *) calloc(1, sizeof(ctx));
	if (!ctx)
		return (NULL);
	ctx->number_of_philosofers	= atoi(argv[1]);
	ctx->time_to_die			= atoi(argv[2]);
	ctx->time_to_eat			= atoi(argv[3]);
	ctx->time_to_sleep			= atoi(argv[3]);
	philos	= (t_philo *) calloc(ctx->number_of_philosofers, sizeof(t_philo));
	if (!philos)
	{
		free(ctx);
		return (NULL);
	}
	forks 	= (byte *) calloc(ctx->number_of_philosofers, sizeof(byte));
	if (!forks)
	{
		free(philos);
		free(ctx);
		return (NULL);
	}
	ctx->forks					= forks;
	if (argc > 5)
		ctx->must_eat 			= atoi(argv[4]);
	for (int i = 0; i < ctx->number_of_philosofers; i++)
	{
		
		philos[i].position 					= i;
		philos[i].time_until_die	 		= ctx->time_to_die;
		philos[i].times_have_eat 			= 0;
		philos[i].ctx						= ctx;
	}
	
	return (philos);
}

void philo_think(t_philo *self)
{
	printf("filosofo %d está pensando\n", self->position);
	self->state = THINK;
}

byte philo_get_left_fork(t_philo *self)
{
	if (self->position < 1)
		return (self->ctx->number_of_philosofers - 1);
	return (self->ctx->number_of_philosofers - 1);
}

byte philo_get_right_fork(t_philo *self)
{
	byte last;
	last = self->ctx->number_of_philosofers - 1;
	if (self->position == last)
		return (0);
	return (self->ctx->number_of_philosofers + 1);
}

e_fork_state philo_get_forks(t_philo *self)
{

	byte left;
	byte right;
	byte *forks;

	forks = self->ctx->forks;
	left  = philo_get_left_fork(self);
	right = philo_get_right_fork(self);

	if (forks[left])
		return (LEFT_OCCUPED);
	if (forks[right])
		return (RIGHT_OCCUPED);
	forks[left] = 1;
	forks[right] = 1;

	return (AVALIABLE);
}

void philo_put_forks(t_philo *self)
{
	self->ctx->forks[philo_get_left_fork(self)] = 0;
	self->ctx->forks[philo_get_right_fork(self)] = 0;
}


void philo_eat(t_philo *self)
{
	int now;
	int index;
	
	/* 
		# Philosofo self está tendando começar a comer
	*/

	self->state = TRYING_EAT;
	printf("filosofo %d está tendando comer.\n", self->position);
	
	/*
		# ele tem que pegar seu garfo esquerdo e seu direito
	*/
	if (philo_get_forks(self) != AVALIABLE)
		printf("Filósofo: %u, não conseguiu pegar os garfos, esperando\n", (unsigned int) self->position);
	else
	{
		printf("Filósofo: %u, conseguiu pegar os garfos\n", (unsigned int) self->position);
		self->state = EATING;
		
	}
	/*
		# Para alterar o estado de um filosofo, eu terei que alterar o daquele filosofo em especifico
	*/
 	
}

void *init_routine(void *self)
{
	philo_think((t_philo *) self);
	philo_eat((t_philo *) self);

	return (NULL);
}

int main(int argc, char *argv[])
{
	t_philo *philos = NULL;
	t_philo_ctx *ctx;
	int index;

	if (argc < 4 || argc > 5)
		return (-1);
	philos = build_philos(argc, argv);
	ctx = philos[0].ctx;
	
	printf("Numero de filosofod: %d\n", ctx->number_of_philosofers);
	for (int index = 0; index < ctx->number_of_philosofers; index++)
	{
		if (pthread_create(&philos[index].task, NULL, &init_routine, (void *)(philos + index)) != 0) {
			printf("Error\n");
			return (1);
		} 	
	}
	for (int index = 0; index < ctx->number_of_philosofers; index++)
	{
		if (pthread_join(philos[index].task, NULL) != 0) {
			printf("Error ao juntar as threads\n");
			return (1);
		} 	
	}
}
