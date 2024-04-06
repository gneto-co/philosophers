/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:04 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/06 14:44:21 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if philo starve:
//  change the state to death
//  turn on the stop_signal
//  put death message
//  return 1
// else if stop_signal already on
//  return 1
// else
//  return 0
int	is_dead(t_data *data, t_global_data *global_d)
{
	if (stop_check(global_d))
		return (1);
	if ((data->left == data->right) || ((int)ft_get_time()
			- data->time_of_last_meal >= global_d->time_to_die))
	{
		ft_print_msg(data, 'd');
		data->state = 'd';
		pthread_mutex_lock(&(global_d->write_mutex));
		data->dead = 1;
		global_d->stop_signal = 1;
		pthread_mutex_unlock(&(global_d->write_mutex));
		return (1);
	}
	return (0);
}

// if stop_signal is on return 1
// else return 0
int	stop_check(t_global_data *global_d)
{
	int	r;

	r = 0;
	pthread_mutex_lock(&(global_d->write_mutex));
	if (global_d->stop_signal)
	{
		r = 1;
	}
	pthread_mutex_unlock(&(global_d->write_mutex));
	return (r);
}

// it returns the actual time in miliseconds
unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

// that function wait a certain amount of time
// if stop_signal goes on or philo starve it stop
void	ft_wait_for(t_data *data, unsigned long start_time,
		unsigned long wait_time)
{
	t_global_data	*global_d;
	int				d;
	int				s;

	global_d = data->global_d;
	d = 0;
	s = 0;
	while ((ft_get_time() < start_time + wait_time) && (!d) && (!s))
	{
		d = is_dead(data, global_d);
		s = stop_check(global_d);
		usleep(10);
	}
}

// f - fork
//   taken - l, r
//   dropped - i, o
//   waiting - j, k
// e - eating
// s - sleeping
// t - thinking
// d - died
void	ft_print_msg(t_data *data, char action)
{
	if (stop_check(data->global_d))
		return ;
	pthread_mutex_lock(&((data->global_d)->write_mutex));
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
	pthread_mutex_unlock(&((data->global_d)->write_mutex));
}
