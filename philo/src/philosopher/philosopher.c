/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:02:00 by jv                #+#    #+#             */
/*   Updated: 2023/08/01 12:32:03 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"


static void philosopher_get_forks(t_philosopher *self)
{
    unsigned char   left;
    unsigned char   right;   
    
    while (self->state == HUNGRY)
    {
        if (self->id == 0) {
            left    = self->context->number_of_philosophers - 1;
            right   = 1; 
            if (((self + left)->state != EATING) && ((self + right)->state != EATING)) {
                pthread_mutex_lock(&self->context->forks[left]);
                pthread_mutex_lock(&self->context->forks[right]); // direita
                self->state = EATING;
            }
        } else if (self->id == (self->context->number_of_philosophers - 1)) {
            left    = 1;
            right   = self->context->number_of_philosophers - 1;
            if (((self - left)->state != EATING) && ((self - right)->state != EATING)) {
                pthread_mutex_lock(&self->context->forks[self->id - 1]); // esquerda
                pthread_mutex_lock(&self->context->forks[0]); // diretas
                self->state = EATING;
            }
        } else {
            if (((self - 1)->state != EATING) && ((self + 1)->state != EATING)) {
                pthread_mutex_lock(&self->context->forks[self->id + 1]); // direita
                pthread_mutex_lock(&self->context->forks[self->id - 1]); // esquerda
                self->state = EATING;
            }
        }
    }    
}

static void philosopher_put_forks(t_philosopher *self)
{
    if (self->id == 0) {
        pthread_mutex_unlock(&self->context->forks[self->context->number_of_philosophers - 1]);
        pthread_mutex_unlock(&self->context->forks[1]); // direita
    } else if (self->id == (self->context->number_of_philosophers - 1)) {
        pthread_mutex_unlock(&self->context->forks[self->id - 1]); // esquerda
        pthread_mutex_unlock(&self->context->forks[0]); // diretas
    } else {
        pthread_mutex_unlock(&self->context->forks[self->id + 1]); // direita
        pthread_mutex_unlock(&self->context->forks[self->id - 1]); // esquerda
    }
}

static void philosopher_eat(t_philosopher *self)
{
    /* Verificar diferença depois */

    if (self->context->all_alive == FALSE)
        return ;
    self->state = HUNGRY;
    philosopher_get_forks(self);
    self->last_eat_time = ft_log_actions(self);
    self->times_have_eat++;
    time_sleep(self->context->time_to_eat);
    philosopher_put_forks(self);
}

static void philosopher_sleep(t_philosopher *self)
{
    if (self->context->all_alive == FALSE)
        return;
    self->state = SLEEPING;
    ft_log_actions(self);
    time_sleep(self->context->time_to_sleep);
}

static void philosopher_think(t_philosopher *self)
{
    if (self->context->all_alive == FALSE)
        return;
    self->state = THINKING;
    ft_log_actions(self);
}

void *routine(void *arg)
{
    t_philosopher *self = (t_philosopher *) arg;
    while (self->state != DIED && self->state != STUFFED)
    {
        philosopher_eat(self);
        philosopher_sleep(self);
        philosopher_think(self);
    }
    //ft_log_actions(self);
    return (NULL);
}