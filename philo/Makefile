# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 13:58:21 by mmachida          #+#    #+#              #
#    Updated: 2025/09/29 12:16:55 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror #-D DEBUG=1
NAME = philo

SRC_PHILO = main.c thread_monitor.c thread_philo.c \
			wait_threads.c create_threads.c init_philo.c print_stat.c
SRC_PHILO := $(addprefix src/, $(SRC_PHILO))

SRC_LST = 	ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c \
			ft_lstadd_back.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstsize.c
SRC_LST := $(addprefix ft_lst/, $(SRC_LST))

SRC_TOOLS = ft_atoi.c err_tools.c data_tools.c time_tools.c
SRC_TOOLS := $(addprefix tools/, $(SRC_TOOLS))

SRC = $(SRC_PHILO) $(SRC_LST) $(SRC_TOOLS)

BUILDDIR = build

OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -Iinclude $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
