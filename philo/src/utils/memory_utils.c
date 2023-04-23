/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:34:29 by jv                #+#    #+#             */
/*   Updated: 2023/04/22 22:55:05 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*ft_calloc(size_t COUNT, size_t ELTSIZE)
{
	void	*ptr;

	ptr = malloc(COUNT * ELTSIZE);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, COUNT * ELTSIZE);
	return (ptr);
}

void philo_free(t_philo *philos)
{
	byte	index;
	byte	size;
	t_philo_ctx *ctx;

	if (philos)
	{
		index	= 0;
		ctx		= philos[0].ctx;
		size	= ctx->number_of_philosofers;
		
		while (index < size)
		{
			pthread_mutex_destroy(ctx->forks + index);
			index++;
		}
		free(ctx->forks);
		free(ctx);
		//free(philos);
	}
}
