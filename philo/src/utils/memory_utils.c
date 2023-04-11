/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:34:29 by jv                #+#    #+#             */
/*   Updated: 2023/04/07 21:35:27 by jv               ###   ########.fr       */
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
