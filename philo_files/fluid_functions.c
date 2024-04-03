/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:04 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/03 12:34:07 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void ft_print_msg(t_data *data, char action)
{
	if (stop_check(data->global_d))
		return ;

    if (action == 'i' || action == 'o' || action == 'j' || action == 'k')
        return ;
        
    pthread_mutex_lock(&((data->global_d)->write_mutex));
    ft_printf("\n%d philo nº %d ", (ft_get_time() - data->global_d->start_time), data->id);
        
    // fork tests
    if (action == 'l')
    {
        ft_color(5);
        ft_printf("has taken the left fork nº %d", data->left);
        ft_color(0);
    }
    if (action == 'r')
    {
        ft_color(5);   
        ft_printf("has taken the right fork nº %d", data->right);
        ft_color(0);
    }
    if (action == 'i')
        ft_printf("has dropped the left fork nº %d", data->left);
    if (action == 'o')
        ft_printf("has dropped the right fork nº %d", data->right);
    if (action == 'j')
        ft_printf("is waiting for the left fork nº %d", data->left);
    if (action == 'k')
        ft_printf("is waiting for the right fork nº %d", data->right);
    else if (action == 'e')
    {
        ft_color(2);
        ft_printf("is eating is %dº meal", data->meals_eaten);
        ft_color(0);
    }
    else if (action == 's')
    {
        ft_color(6);
        ft_printf("is sleeping");
        ft_color(0);
    }
    else if (action == 't')
    {
        ft_color(8);
        ft_printf("thinking");
        ft_color(0);
    }
    else if (action == 'd')
    {
        ft_color(1);
        ft_printf("died");
        ft_color(0);        
    }
    pthread_mutex_unlock(&((data->global_d)->write_mutex));
}
