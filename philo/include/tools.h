/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:49:00 by mmachida          #+#    #+#             */
/*   Updated: 2025/10/14 18:31:38 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "philosopher.h"
# define MICRO_MILI 1000

int		ft_atoi(const char *str);
int		err_and_return_int(char *func);
void	*err_and_return_null(char *func);
void	set_stopped(t_data *data, int val);
int		get_stopped(t_data *data);
void	set_lastmeal_time(t_philo **philo, long val);
long	get_lastmeal_time(t_philo *philo);
void	add_num_of_meals(t_philo **philo);
int		get_num_of_meals(t_philo *philo);
long	get_current_time(void);
long	get_elapsed_time(long ref_time);
long	to_ms(long micro_s);
void	wait_micro_s(long wait_time, t_data *data);
long	to_micros(long mili_s);

#endif