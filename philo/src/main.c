/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:18:36 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 11:01:09 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	main(int argc, char *argv[])
{
	t_philo_ctx	*ctx;
	t_philo		*philos;
	byte		index;

	if (argc < 5 || argc > 6)
		return (-1);
	philos = build_philos(argc, argv);
	ctx = philos[0].ctx;
	if (ctx->number_of_philosofers ==  1)
		philo_one_philo(philos);
	else
	{
		index = 0;
		while(index < ctx->number_of_philosofers)
		{
			if (pthread_create(&philos[index].task, NULL, &init_routine, (void *)(philos + index)) != 0)
			{
				printf("Error ao criar thread\n");
				return 0;
			}
			index++;
		}
		index = 0;
		while(index < ctx->number_of_philosofers)
		{
			if (pthread_join(philos[index].task, NULL) != 0)
				return 0;
			index++;
		}
	}
	//philo_free(philos);
}
