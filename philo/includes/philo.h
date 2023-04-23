/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:20:33 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 18:36:18 by jv               ###   ########.fr       */
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

typedef enum e_state {
	BORN,
	THINK,
	EATING,
	SLEEP,
	TRYING_EAT,
	DIED
}	t_state;

typedef unsigned char	t_byte;

typedef struct s_philo_ctx {
	unsigned int	number_of_philosofers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	t_byte			all_alive;
	pthread_mutex_t	*forks;
	pthread_mutex_t	can_print;
}	t_philo_ctx;

typedef struct s_philo {
	unsigned int	times_have_eat;
	t_philo_ctx		*ctx;
	pthread_t		task;
	t_state			state;
	t_byte			position;
	int				time_until_die;
}	t_philo;

/*  utils */
void			*ft_calloc(size_t COUNT, size_t ELTSIZE);
void			*init_routine(void *self);
void			philo_free(t_philo *philos);
void			philo_put_forks(t_philo *self);
void			philo_print_state(t_philo *self, time_t time);
void			one_philo(t_philo *p);
void			ft_puts(long int time,
					t_byte position, char *action, t_philo *self);
void			ft_puts_fork(long int time,
					t_byte position, char *action, t_philo *self);
t_philo			*build_philos(int argc, char *argv[]);
time_t			philo_get_current_time(void);
time_t			philo_get_forks(t_philo *self);
unsigned int	time_ms_to_mc(unsigned int time_in_ms);
t_byte			show_message_and_die(const char *msg, t_philo *philo);

/*		string 		*/
size_t			ft_strlen(const char *S);
char			*ft_itoa(long int n);
int				ft_atoi(const char *str);
#endif
