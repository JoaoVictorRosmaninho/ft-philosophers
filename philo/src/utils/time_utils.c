/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:31:57 by jv                #+#    #+#             */
/*   Updated: 2023/08/01 11:46:12 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

time_t  time_get_current_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void    time_sleep(int time)
{
    time_t  start;

    start = time_get_current_time();

    while (time > time_get_current_time() - start) {
        usleep(100);
    }
}