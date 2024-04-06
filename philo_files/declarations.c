/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:47:06 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/06 10:47:06 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int nb)
{
	if (nb == 1)
		ft_printf("Incorrect arguments, it should be like this:\n"
			"./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"number_of_times_each_philosopher_must_eat (optional)");
	else if (nb == 2)
		ft_printf("Incorrect arguments,"
			"they should be numerics args greater than 0");
	return (1);
}

int	global_declarations(t_global_data *global_d, int ac, char **av)
{
	global_d->stop_signal = 0;
	if (!ft_atoi(av[1]) || !ft_atoi(av[2]) || !ft_atoi(av[3])
		|| !ft_atoi(av[4]))
		return (ft_error(2));
	global_d->philo_amount = ft_atoi(av[1]);
	global_d->time_to_die = ft_atoi(av[2]);
	global_d->time_to_eat = ft_atoi(av[3]);
	global_d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		global_d->meals_to_get_fat = ft_atoi(av[5]);
	else
		global_d->meals_to_get_fat = 0;
	return (0);
}

void	data_allocation(t_data **data, t_global_data *global_d,
		pthread_t **threads)
{
	*data = malloc(sizeof(t_data) * global_d->philo_amount);
	*threads = malloc(sizeof(pthread_t) * global_d->philo_amount);
	global_d->forks_mutex = malloc(sizeof(pthread_mutex_t)
			* global_d->philo_amount);
}

void	mutex_declarations(t_global_data *global_d)
{
	int	i;

	pthread_mutex_init(&(global_d->write_mutex), NULL);
	pthread_mutex_init(&(global_d->run_mutex), NULL);
	i = 0;
	while (i < global_d->philo_amount)
		pthread_mutex_init(&(global_d->forks_mutex[i++]), NULL);
}

void	create_philo(t_data **data, t_global_data *global_d,
		pthread_t **threads)
{
	int	i;

	i = 0;
	ft_color(8);
	while (i < global_d->philo_amount)
	{
		pthread_mutex_lock(&(global_d->write_mutex));
		(*data)[i].id = i + 1;
		(*data)[i].global_d = global_d;
		(*data)[i].meals_eaten = 0;
		(*data)[i].dead = 0;
		(*data)[i].state = 't';
		(*data)[i].left = (*data)[i].id;
		(*data)[i].right = (*data)[i].id - 1;
		if ((*data)[i].left >= global_d->philo_amount)
			(*data)[i].left = 0;
		pthread_create(&(*threads)[i], NULL, philo_process,
			(void *)&((*data)[i]));
		ft_printf("Philosopher nº %d arrived, left: %d right: %d\n",
			(*data)[i].id, (*data)[i].left, (*data)[i].right);
		i++;
		pthread_mutex_unlock(&(global_d->write_mutex));
	}
	ft_color(0);
}
