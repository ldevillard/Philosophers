NAME = philo
CC = clang
FLAGS = -Wall -Wextra -Werror
SRCS =	srcs/main.c\
		srcs/eat.c\
		srcs/exit.c\
		srcs/forks.c\
		srcs/init.c\
		srcs/display.c\
		srcs/utils.c\
		srcs/threads.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
		@clear
		@echo "\033[35m█▀█ █ █ █ █   █▀█\033[0m"
		@echo "\033[35m█▀▀ █▀█ █ █▄▄ █▄█\033[0m"
		@echo "\033[35m_________________\n\033[0m"
		@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
		@echo "\033[1m\033[36mLinking\033[0m"
		@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lpthread
		@echo "\033[1m\033[32mDone !\n\033[0m"

all : $(NAME)

clean :
		@rm -rf srcs/*.o
		@echo "\033[91m...\033[0m"

fclean : clean
		@rm -rf srcs/*.o
		@rm -rf $(NAME)
		@echo "\033[1m\033[31mCleaned\033[0m"

re : fclean all

.PHONY: clean fclean re all