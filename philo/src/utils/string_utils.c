/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:11:11 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 18:17:32 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	ft_strlen(const char *S)
{
	char	*tmp;

	tmp = NULL;
	if (!S)
		return (0);
	tmp = (char *) S;
	while (*tmp)
		tmp++;
	return ((size_t)(tmp - S));
}

static void	convert(long int nb, char *number, int index)
{
	if (nb >= 0)
	{
		while (nb > 0)
		{
			number[index++] = '0' + (nb % 10);
			nb /= 10;
		}
		if (index == 0)
			number[index++] = '0';
		number[index] = '\0';
	}
}

static void	ft_rev(char *s1, int size)
{
	int		ini;
	char	aux;

	ini = 0;
	while (ini < size)
	{
		aux = s1[ini];
		s1[ini] = s1[size];
		s1[size] = aux;
		ini++;
		size--;
	}
}

char	*ft_itoa(long int n)
{
	char	*number;

	number = ft_calloc(12, sizeof(char));
	if (!number)
		return (NULL);
	convert(n, number, 0);
	ft_rev(number, ft_strlen(number) - 1);
	return (number);
}
