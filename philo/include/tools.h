/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:49:00 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/29 14:51:46 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#define MICRO_MILI 1000

int		ft_atoi(const char *str);
int		err_and_return_int(char *func);
void	*err_and_return_NULL(char *func);
void	set_stopped(t_data **data, int val);
int		get_stopped(t_data *data);
void	set_lastmeal_time(t_philo **philo, long val);
long	get_lastmeal_time(t_philo *philo);
void	add_num_of_meals(t_philo **philo);
int		get_num_of_meals(t_philo *philo);
long	get_current_time();
long	get_elapsed_time(long ref_time);
void	add_fork_waitinglist(t_philo *philo, t_fork *fork);
void	upd_fork_waitinglist(t_philo *philo, t_fork *fork);
long	to_ms(long micro_s);
void	wait_micro_s(long wait_time, t_data *data);
long	to_micros(long mili_s);