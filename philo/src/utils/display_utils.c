/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:43:42 by jv                #+#    #+#             */
/*   Updated: 2023/07/25 10:51:39 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static unsigned int	ft_strlen(const char *S)
{
	char	*tmp;

	tmp = NULL;
	if (!S)
		return (0);
	tmp = (char *) S;
	while (*tmp)
		tmp++;
	return ((unsigned int)(tmp - S));
}

void    ft_puts(const char *str)
{
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);   
}