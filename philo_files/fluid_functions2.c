/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:04 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/16 10:41:08 by gneto-co         ###   ########.fr       */
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
	pthread_mutex_lock(&(global_d->forks_mutex[data->left]));
	print_msg(data, 'f');
	pthread_mutex_lock(&(global_d->forks_mutex[data->right]));
	print_msg(data, 'f');
	data->state = 'e';
	print_msg(data, 'e');
}

// eat and then release the forks, next start sleeping
void	eating(t_data *data, t_global_data *global_d)
{
	pthread_mutex_lock(&(global_d->last_meal));
	data->time_of_last_meal = ft_get_time();
	data->meals_eaten++;
	pthread_mutex_unlock(&(global_d->last_meal));
	ft_wait_for(data, ft_get_time(), global_d->time_to_eat);
	pthread_mutex_unlock(&(global_d->forks_mutex[data->left]));
	pthread_mutex_unlock(&(global_d->forks_mutex[data->right]));
	data->state = 's';
	print_msg(data, 's');
}

// sleep and start thinking
void	sleeping(t_data *data, t_global_data *global_d)
{
	ft_wait_for(data, ft_get_time(), global_d->time_to_sleep);
	data->state = 't';
	print_msg(data, 't');
}

void	ft_wait_for_all(t_global_data *global_d)
{
	pthread_mutex_lock(&(global_d->run1_mutex));
	pthread_mutex_unlock(&(global_d->run1_mutex));
}
