#include <pthread.h> // pthread_t
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "ft_lst/ft_lst.h"
#define NUM_THREADS 3


typedef struct s_data
{
	long	starttime;
}	t_data;

typedef struct s_philo
{
	int			id;
	long		lastmeal_time;
	pthread_t	thread;
}	t_philo;


int shared_data = 0;
pthread_mutex_t mutex;

void* thread_philo(void* arg) {
	int thread_id = *(int*)arg;
	int idx = 0;
	printf("スレッド %d がデータを処理中", thread_id);
	shared_data++;
	while(idx < 5)
	{
		printf("thread:%d, idx:%d\n", thread_id, idx);
		idx++;
	}
	//pthread_mutex_lock(&mutex);
	printf(" 処理結果 shared_data:%d\n", shared_data);
	//pthread_mutex_unlock(&mutex);
    return NULL;
}

void	delete_philo(void *list)
{
	t_philo	*philo;

	philo = (t_philo *)list;
	//if (philo->thread)
	//	free(philo->thread);
	free (philo);
}

int	add_new_philo(t_list **list, int id)
{
	t_philo	*philo;
	t_list 	*tmp;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->id = id;
	tmp = ft_lstnew(philo);
	if (!tmp)
		return (-1);
	ft_lstadd_back(list, tmp);
	return (0);
}

t_list	*init_data()
{
	t_list	*philos;
	int idx = 0;

	philos = NULL;
	while (idx < NUM_THREADS)
	{
		if (add_new_philo(&philos, idx) < 0)
			return (NULL);
		idx++;
	}
	return (philos);
}

int main() {

	// cc main.c ft_lst/ft_lstadd_back.c ft_lst/ft_lstnew.c ft_lst/ft_lstclear.c ft_lst/ft_lstlast.c
	t_philo	*philo;
	t_list	*tmp;
    int result;
	int idx = 0;
    // スレッドの作成
	t_list	*philos;

	philos = init_data();
	pthread_mutex_init(&mutex, NULL);
	tmp = philos;
	while(idx < NUM_THREADS)
	{
		philo = tmp->content;
		result = pthread_create(&philo->thread, NULL, thread_philo, (void*)&idx);
		if (result != 0) {
			fprintf(stderr, "スレッドの作成に失敗しました: %s\n", strerror(result));
			return 1;
		}
		idx++;
		tmp = tmp->next;
	}
    // スレッドの終了を待機
	tmp = philos;
	for (int i = 0; i < NUM_THREADS; i++) {
		philo = (t_philo *)tmp->content;
    	pthread_join(philo->thread, NULL);
		tmp = tmp->next;
	}
	ft_lstclear(&philos, delete_philo);
	pthread_mutex_destroy(&mutex);
    return 0;
}