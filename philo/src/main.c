/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:18:36 by jv                #+#    #+#             */
/*   Updated: 2023/04/23 15:14:21 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	create_threads(t_philo *philos)
{
	byte	index;

	index = 0;
	while (index < philos[0].ctx->number_of_philosofers)
	{
		if (pthread_create(&philos[index].task, NULL,
				&init_routine, (void *)(philos + index)) != 0)
			return (-1);
		index++;
	}
	return (0);
}

static int	join_threads(t_philo *philos)
{
	byte	index;

	index = 0;
	while (index < philos[0].ctx->number_of_philosofers)
	{
		if (pthread_join(philos[index].task, NULL) != 0)
			return (-1);
		index++;
	}
	return (0);
}

static byte	philo_one_philo(t_philo *array_of_philos)
{
	time_t	time;

	time = philo_get_current_time();
	if (pthread_create(&array_of_philos[0].task, NULL,
			&init_routine, (void *)array_of_philos))
		return (0);
	pthread_detach(array_of_philos[0].task);
	while (array_of_philos->state != DIED) // pode tirar ?
		;
	philo_print_state(array_of_philos, time);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	byte		index;

	if (argc < 5 || argc > 6)
		return (-1);
	philos = build_philos(argc, argv);
	if (philos[0].ctx->number_of_philosofers == 1)
		philo_one_philo(philos);
	else
	{
		if (create_threads(philos) < 0)
			printf("Error: Error ao criar threads\n");
		if (join_threads(philos) < 0)
			printf("Error: Error ao juntar threads\n");
	}
	philo_free(philos);
}
