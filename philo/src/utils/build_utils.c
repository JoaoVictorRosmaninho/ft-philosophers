/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:04:00 by jv                #+#    #+#             */
/*   Updated: 2023/08/01 11:11:13 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/philosophers.h"

static t_context *build_context_data(t_params *params)
{
    t_context       *context;
    unsigned char   index;

    context = (t_context *) malloc(sizeof(t_context));   
    if (!context)
        return (NULL);
    /*  Criando garfos */
    context->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * params->number_of_philosofers);
    if (!context->forks)
    {
        free(context);
        return (NULL);
    }
    index = 0;
    while (index < params->number_of_philosofers)
    {
        pthread_mutex_init(context->forks + index, NULL);
        index++;
    }
    context->time_to_die    = params->time_to_die;
    context->time_to_eat    = params->time_to_eat;
    context->time_to_sleep  = params->time_to_sleep;
    context->number_of_philosophers = params->number_of_philosofers;
    context->number_of_time_must_eat = params->number_of_time_must_eat;
    context->all_alive      = TRUE;
    context->start_time     = time_get_current_time();
    pthread_mutex_init(&context->set_state_mutex, NULL);
    pthread_mutex_init(&context->in_out_mutex, NULL);
    return (context);
}

t_philosopher *build_philosophers(t_params *params)
{
    t_philosopher   *philosophers;
    t_context       *context;
    int             index;

    philosophers = malloc(sizeof(t_philosopher) * params->number_of_philosofers);
    if (!philosophers)
        return (NULL);
    index   = 0;
    context = build_context_data(params);
    while (index < params->number_of_philosofers)
    {
        philosophers[index].id              = index;
        philosophers[index].times_have_eat  = 0;
        philosophers[index].last_eat_time   = 0;
        philosophers[index].context         = context;
        index++;
    }

    return (philosophers);
}
