/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:11:11 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 18:21:34 by jv               ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	n;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}
