/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:04:54 by jv                #+#    #+#             */
/*   Updated: 2023/08/01 11:11:17 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum {
	FALSE,
	TRUE
} e_bool;

typedef enum {
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	STUFFED,
	HUNGRY
} e_state;

typedef struct {
	int	number_of_philosofers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_time_must_eat;
} t_params;

typedef struct {
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_have_eat;
	int	number_of_philosophers;
	int	number_of_time_must_eat;
	time_t	start_time;
	e_bool			all_alive;
	pthread_mutex_t	set_state_mutex;
	pthread_mutex_t in_out_mutex;
	pthread_mutex_t *forks;
} t_context;

typedef struct {
	int	id;
	int	times_have_eat;
	time_t			last_eat_time;
	pthread_t		thread;

	t_context		*context;
	e_state			state;
} t_philosopher;


/* time functions */
time_t  time_get_current_time(void);
void    time_sleep(int time);


/* input output functions   */
time_t	ft_log_actions(t_philosopher *self);

/* utils functions */

e_bool ft_parse_cmd_line(int argc, char *argv[], t_params *params);

/* monitor routine	*/
void    *monitor_routine(void *args);
e_bool  monitor_stop_routine(t_philosopher *philosopher);

/* philosopher functions */
void *routine(void *arg);
t_philosopher *build_philosophers(t_params *params);

#endif