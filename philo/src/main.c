/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:04:02 by jv                #+#    #+#             */
/*   Updated: 2023/07/25 11:44:24 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int main(int argc, char *argv[])
{
	t_params params;

	if (ft_parse_cmd_line(argc, argv, &params) == TRUE)
	{
		ft_puts("valid Params!");
	} else {
		 ft_puts("Inválid Params!");
	}
	return (0);
}