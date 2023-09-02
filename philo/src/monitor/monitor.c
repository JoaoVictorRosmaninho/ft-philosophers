/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:46:34 by jv                #+#    #+#             */
/*   Updated: 2023/07/31 21:22:57 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/philosophers.h"

void monitor_notify_dead_or_stuff(t_philosopher *philosopher)
{
    time_t  time;
    if (philosopher->last_eat_time == 0)
        time = philosopher->context->start_time;
    else 
        time = philosopher->last_eat_time;
    if ((time_get_current_time() - time) > philosopher->context->time_to_die)
    {
        philosopher->state = DIED;
        philosopher->context->all_alive = FALSE;
        return ;
    }
    if (philosopher->context->times_to_have_eat != 0)
    {
        if (philosopher->times_have_eat == philosopher->context->number_of_time_must_eat)
            philosopher->state   = STUFFED;
    }
}

e_bool  monitor_stop_routine(t_philosopher *philosopher)
{
    return (philosopher->context->all_alive);
}

e_bool monitor_not_all_stuffed(t_philosopher *philosophers)
{
    int    index;

    index   = 0;
    while (index < philosophers->context->number_of_philosophers)
    {
        if (philosophers[index].state != STUFFED)
            break;
        index++;
    }
    if (index == philosophers->context->number_of_philosophers)
        return (FALSE);
    return (TRUE);
}

void    *monitor_routine(void *args)
{               
    e_bool          monitor_run;
    unsigned char   index;
    t_philosopher   *philosophers;
    t_context       *context;

    philosophers    = (t_philosopher *) args;
    context         = philosophers->context;
    monitor_run     = TRUE;
    while (monitor_run == TRUE)
    {
        index   = 0;
        while (index < context->number_of_philosophers)
        {
            monitor_notify_dead_or_stuff(philosophers + index);
            index++;
        }
        if (context->all_alive != TRUE || monitor_not_all_stuffed(philosophers) != TRUE)
            monitor_run = FALSE;
    }
    return (NULL);    
}