/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:04 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/12 16:24:43 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* FLUID FUNCTIONS */
/*
	-summary-
	they are basically the functions how can use mutex
	mutex will be used only there to avoid conflicts

	-version 2-
	will be the specific status actions functions

	-funtions-
	thinking()
	eating()
	sleeping()
	ft_wait_for_all()
*/

// wait for left and right (fork_mutex) and start eating
void	thinking(t_data *data, t_global_data *global_d)
{
	// wait for the left fork
	pthread_mutex_lock(&(global_d->forks_mutex[data->left]));
	print_msg(data, 'f');
	// wait for the right fork
	pthread_mutex_lock(&(global_d->forks_mutex[data->right]));
	print_msg(data, 'f');
	// print & set eating
	data->state = 'e';
	print_msg(data, 'e');
}

// eat and then release the forks, next start sleeping
void	eating(t_data *data, t_global_data *global_d)
{
	// set last meal time
	pthread_mutex_lock(&(global_d->last_meal));
	data->time_of_last_meal = ft_get_time();
	data->meals_eaten++;
	pthread_mutex_unlock(&(global_d->last_meal));
	// start eating and wait (time_to_eat) ms
	ft_wait_for(data, ft_get_time(), global_d->time_to_eat);
	// drop the forks when finished eating
	pthread_mutex_unlock(&(global_d->forks_mutex[data->left]));
	pthread_mutex_unlock(&(global_d->forks_mutex[data->right]));
	// print & set sleep
	data->state = 's';
	print_msg(data, 's');
}

// sleep and start thinking
void	sleeping(t_data *data, t_global_data *global_d)
{
	// start sleeping and wait (time_to_sleep) ms
	ft_wait_for(data, ft_get_time(), global_d->time_to_sleep);
	// print & set think
	data->state = 't';
	print_msg(data, 't');
}

void	ft_wait_for_all(t_global_data *global_d)
{
	pthread_mutex_lock(&(global_d->run1_mutex));
	pthread_mutex_unlock(&(global_d->run1_mutex));
}
