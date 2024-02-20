NAME=pipex
CC=cc
CFLAG= -Werror -Wall -Wextra -g
SRCS= pipex.c error_and_free.c ft_split.c init_struct.c ft_itoa.c creat_cmd.c ft_printf.c ft_printf_utils.c main.c
OBJS=$(SRCS:.c=.o)
RM=rm -f

CYAN='\033[1;36m'
BLUE='\033[1;34m'
GREEN='\033[6;32m'
WHITE='\033[0;37m'

.c.o:
	@$(CC) $(CFLAG) -c $< -o $(<:.c=.o)
all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJS)
	@echo ${GREEN}">-Successful compilation-<"${WHITE}
clean:
	@clear
	@$(RM) $(OBJS)
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
fclean : clean
	@$(RM) $(NAME)
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}
re: fclean $(NAME)

.PHONY: clean fclean re all
