/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 23:22:51 by jv                #+#    #+#             */
/*   Updated: 2023/05/21 11:47:35 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_puts(long int time, t_byte position, char *action, t_philo *self)
{
	char	*t;
	char	*pos;

	t = ft_itoa(time - self->ctx->start_time);
	pos = ft_itoa((long int) position);
	pthread_mutex_lock(&self->ctx->can_print);
	write(1, t, ft_strlen(t));
	write(1, "ms", 2);
	write(1, " is ", 4);
	write(1, pos, ft_strlen(pos));
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
	write(1, "\n", 1);
	free(t);
	free(pos);
	pthread_mutex_unlock(&self->ctx->can_print);
}

void	ft_puts_fork(long int time, t_byte position, char *action, t_philo *self)
{
	char	*t;
	char	*pos;

	t = ft_itoa(time - self->ctx->start_time);
	pos = ft_itoa((long int) position);
	pthread_mutex_lock(&self->ctx->can_print);
	write(1, t, ft_strlen(t));
	write(1, "ms", 2);
	write(1, " ", 1);
	write(1, pos, ft_strlen(pos));
	write(1, action, ft_strlen(action));
	write(1, "\n", 1);
	free(t);
	free(pos);
	pthread_mutex_unlock(&self->ctx->can_print);
}
