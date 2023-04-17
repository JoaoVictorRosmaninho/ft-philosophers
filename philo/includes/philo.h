/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:20:33 by jv                #+#    #+#             */
/*   Updated: 2023/04/16 12:08:33 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef enum {
	THINK,
	EATING,
	SLEEP,
	TRYING_EAT
} e_state;

typedef enum {
	LEFT_OCCUPED,
	RIGHT_OCCUPED,
	AVALIABLE
} e_fork_state;


/*
 
  (time_eat + time_sleep ) < time_do_die

*/
typedef unsigned char byte;

typedef struct {
	int number_of_philosofers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	pthread_mutex_t *forks;
} t_philo_ctx;

typedef struct {
	int time_until_die;
	int times_have_eat;
	e_state state;
	int position;
	pthread_t task;
	t_philo_ctx *ctx;
} t_philo;

/*  utils */
void	*ft_calloc(size_t COUNT, size_t ELTSIZE);

#endif
