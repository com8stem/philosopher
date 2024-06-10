NAME = philo
SRCS = check_arg.c dinner.c init.c init_2.c main.c monitor.c print_status.c simulation.c simulation_2.c utils_sleep.c
OBJS = $(SRCS:.c=.o)
DEPENDS = $(OBJS:.o=.d)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -MMD -MP

-include $(DEPENDS)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS):	$(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -rf $(OBJS) $(DEPENDS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
