/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:04:54 by jv                #+#    #+#             */
/*   Updated: 2023/07/25 11:43:28 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef enum {
    TRUE,
    FALSE
} e_bool;

typedef struct {
    unsigned int number_of_philosofers;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int number_of_time_must_eat;
} t_params;


/* input output functions   */

void    ft_puts(const char *str);

/* utils functions */

e_bool ft_parse_cmd_line(int argc, char *argv[], t_params *params);


#endif