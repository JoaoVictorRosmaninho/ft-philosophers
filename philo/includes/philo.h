/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:20:33 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 18:13:38 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum {
	BORN,
	THINK,
	EATING,
	SLEEP,
	TRYING_EAT,
	DIED
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
	unsigned int number_of_philosofers;
	unsigned int time_to_die;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;
	unsigned int must_eat;
	byte	all_alive;
	pthread_mutex_t *forks;
	pthread_mutex_t can_print;
} t_philo_ctx;

typedef struct {
	int	time_until_die;
	unsigned int	times_have_eat;
	t_philo_ctx		*ctx;
	pthread_t		task;
	e_state 		state;
	byte			position;
} t_philo;

/*  utils */
void		*ft_calloc(size_t COUNT, size_t ELTSIZE);
void		*init_routine(void *self);
void		philo_free(t_philo *philos);
void		philo_put_forks(t_philo *self);
void		philo_print_state(t_philo *self, time_t time);
void		one_philo(t_philo *p);
void		ft_puts(long int time, byte position, char *action, t_philo *self);
void 		ft_puts_fork(long int time, byte position, char *action, t_philo *self);
t_philo		*build_philos(int argc, char *argv[]);
time_t		philo_get_current_time(void);
time_t		philo_get_forks(t_philo *self);
unsigned int time_ms_to_mc(unsigned int time_in_ms);
byte		show_message_and_die(const char *msg, t_philo *philo);

/*		string 		*/
size_t	ft_strlen(const char *S);
char	*ft_itoa(long int n);
#endif
