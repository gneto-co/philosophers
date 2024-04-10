/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_functions1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:04 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/10 15:01:23 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* FLUID FUNCTIONS 1 */
/*
	-summary-
	they are basically the functions how can use mutex
	mutex will be used only there to avoid conflicts

	-version 1-
	will be the global fuctions

	-functions-
	is_dead()
	are_all_fat()
	stop_set()
	stop_check()
	ft_print_message()
*/

// if philo starve:
//  put death message
//  return 1
// else
//  return 0
int	is_dead(t_data *data, t_global_data *global_d)
{
	int	r;

	r = 0;
	// lock last_meal mutex
	pthread_mutex_lock(&(global_d->last_meal));
	(void)data;
	if ((data->left == data->right) || ((int)ft_get_time()
			- data->time_of_last_meal >= global_d->time_to_die))
	{
		// print & set death
		print_msg(data, 'd');
		data->state = 'd';
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->last_meal));
	return (r);
}

// if all philo are fat
//  return 1
// else
//  return 0
int	are_all_fat(t_data **data, t_global_data *global_d)
{
	int	r;
	int	i;
	int	fat_philo;

	r = 0;
	i = 0;
	fat_philo = 0;
	// lock last_meal mutex
	pthread_mutex_lock(&(global_d->last_meal));
	// loop all philo and get the amount of fat philo
	while (i < global_d->philo_amount)
	{
		if ((global_d->meals_to_get_fat)
			&& ((*data)[i].meals_eaten >= global_d->meals_to_get_fat))
			fat_philo++;
		i++;
	}
	// if all philo are fat
	if (fat_philo == global_d->philo_amount)
	{
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->last_meal));
	return (r);
}

// turn on the stop_signal
int	stop_set(t_global_data *global_d)
{
	// lock stop_mutex and turn on the stop_signal
	pthread_mutex_lock(&(global_d->stop_mutex));
	global_d->stop_signal = 1;
	pthread_mutex_unlock(&(global_d->stop_mutex));
	return (1);
}

// if stop_signal is on return 1
// else return 0
int	stop_check(t_global_data *global_d)
{
	int	r;

	r = 0;
	// lock stop mutex and check if is on
	pthread_mutex_lock(&(global_d->stop_mutex));
	if (global_d->stop_signal)
	{
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->stop_mutex));
	return (r);
}

// f - take a fork
// e - eating
// s - sleeping
// t - thinking
// d - died
void	print_msg(t_data *data, char action)
{
	pthread_mutex_lock(&((data->global_d)->write_mutex));
	if (!stop_check(data->global_d))
	{
		ft_printf("\n%d %d ", (ft_get_time() - data->global_d->start_time),
			data->id);
		if (action == 'f')
			ft_printf("has taken a fork");
		else if (action == 'e')
			ft_printf("is eating");
		else if (action == 's')
			ft_printf("is sleeping");
		else if (action == 't')
			ft_printf("is thinking");
		else if (action == 'd')
			ft_printf("died");
		else if (action == 'a')
			ft_printf("is alive");
	}
	pthread_mutex_unlock(&((data->global_d)->write_mutex));
}
