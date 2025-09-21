/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:59 by mmachida          #+#    #+#             */
/*   Updated: 2025/09/21 19:19:33 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // pthread_t
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "ft_lst/ft_lst.h"
#include "philosophers.h"
#define NUM_THREADS 3


typedef struct s_data
{
	long			starttime;
	pthread_t		thread_monitor;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				stoped;
	long			lastmeal_time;
	pthread_t		thread;
	pthread_mutex_t mutex_philo;
	t_data			*d;
}	t_philo;


int shared_data = 0;


int	err_and_return_int(char *func, char *msg)
{
	fprintf(stderr, "Failed in %s: %s\n", func, msg);
	return (-1);
}

int	all_stopped(t_list	*list)
{
	t_list	*tmp;
	t_philo	*philo;

	tmp = list;
	while (tmp)
	{
		philo = (t_philo *)tmp->content;
		if (!philo->stoped)
			return (0);
	}
	printf("all stopped\n");
	return (1);
}

void* thread_monitor(void* arg)
{
	t_list	*tmp;
	t_list	*list = (t_list *)arg;
	t_philo	*philo;
	long	time;

	tmp = list;
	while (1)
	{
		if (!tmp)
			tmp = list;
		else
			tmp = tmp->next;
		if (tmp)
		{
			sleep(1);
			philo = (t_philo *)tmp->content;
			printf("ID:%d\n", philo->id);
			if (philo->stoped)
				continue ;
			time = get_elapsed_time(philo->lastmeal_time);
			if (time > 5000)
			{
				printf("      Stopped\n");
				philo->stoped = 1;
				//break ;
			}
			if (all_stopped(list))
				break ;
		}
	}
    return (NULL);
}

void* thread_philo(void* arg)
{
	t_philo	*philo = (t_philo *)arg;

	int idx = 0;
	printf("スレッド %d がデータを処理中\n", philo->id);
	shared_data++;
	//while(1)
	//{
	//	sleep(1);
	//	if(philo->stoped)
	//		break ;
		pthread_mutex_lock(&philo->mutex_philo);
		printf("thread:%d, idx:%d\n", philo->id, idx);
		idx++;
		pthread_mutex_unlock(&philo->mutex_philo);
	//}
	printf(" 処理結果 shared_data:%d\n", shared_data);
    return (NULL);
}

void	delete_data(t_data	*data)
{
	if (data)
		free (data);
}

void	delete_philo(void *list)
{
	t_philo	*philo;

	philo = (t_philo *)list;
	if (philo)
	{
		//if (philo->thread)
		//	free(philo->thread);
		pthread_mutex_destroy(&philo->mutex_philo);
		free (philo);
	}
}

int	add_new_philo(t_list **list, int id, t_data *data)
{
	t_philo	*philo;
	t_list 	*tmp;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	philo->id = id;
	philo->stoped = 0;
	if (pthread_mutex_init(&philo->mutex_philo, NULL) < 0)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	philo->lastmeal_time = data->starttime;
	philo->d = data;
	tmp = ft_lstnew(philo);
	if (!tmp)
		return (err_and_return_int("add_new_philo", strerror(errno)));
	ft_lstadd_back(list, tmp);
	return (0);
}

t_data	*init_data()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->starttime = get_current_time();
	return (data);
}

t_list	*init_philo(t_data	*data)
{
	t_list	*philos;
	
	int idx = 0;

	philos = NULL;
	while (idx < NUM_THREADS)
	{
		if (add_new_philo(&philos, idx, data) < 0)
			return (NULL);
		idx++;
	}
	return (philos);
}



int	create_threads(t_list	*list, t_data *data)
{
	t_philo	*philo;
	t_list	*tmp;
	int		result;

	tmp = list;
	while(tmp)
	{
		philo = tmp->content;
		result = pthread_create(&philo->thread, NULL, thread_philo, philo);
		if (result != 0)
			return (err_and_return_int("create_threads", strerror(errno)));
		tmp = tmp->next;
	}
	result = pthread_create(&data->thread_monitor, NULL, thread_monitor, list);
	if (result != 0)
		return (err_and_return_int("create_threads", strerror(errno)));
	return (0);
}

int	wait_threads(t_list	*philos, t_data *data)
{
	t_philo	*philo;
	t_list	*tmp;
	int		result;

	tmp = philos;
	while(tmp){
		philo = (t_philo *)tmp->content;
    	result = pthread_join(philo->thread, NULL);
		if (result != 0)
			return (err_and_return_int("wait_threads", strerror(errno)));
		tmp = tmp->next;
	}
	result = pthread_join(data->thread_monitor, NULL);
	if (result != 0)
		return (err_and_return_int("wait_threads", strerror(errno)));
	return (0);
}

int main() {

	// cc main.c ft_lst/ft_lstadd_back.c ft_lst/ft_lstnew.c ft_lst/ft_lstclear.c ft_lst/ft_lstlast.c get_time.c

    // スレッドの作成
	t_data	*data;
	t_list	*philos;

	data = init_data();
	philos = init_philo(data);
	if (!philos)
		return (-1);
	if (create_threads(philos, data) < 0)
		return (-1);
	if (wait_threads(philos, data) < 0)
		return (-1);
	delete_data(data);
	ft_lstclear(&philos, delete_philo);
    return 0;
}