/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:04:02 by jv                #+#    #+#             */
/*   Updated: 2023/07/31 23:17:56 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	execute(t_philosopher *philosophers)
{
	int				index;
	pthread_t		monitor;

	pthread_create(&monitor, NULL, &monitor_routine, philosophers);
	index = 0;
	while (index < philosophers->context->number_of_philosophers)
	{
		pthread_create(&(philosophers + index)->thread, NULL, &routine, (philosophers + index));
		index++;
	}
	index = 0;
	while(index < philosophers->context->number_of_philosophers)
	{
		pthread_join((philosophers + index)->thread, NULL);
		index++;
	}
	pthread_join(monitor, NULL);
}

int main(int argc, char *argv[])
{
	t_params		params;
	t_philosopher	*philosophers;
	if (ft_parse_cmd_line(argc, argv, &params) == TRUE)
	{
		philosophers =	build_philosophers(&params);
		execute(philosophers);
	} else {
		 printf("Inválid Params!\n");
	}
	return (0);
}