# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xzhang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 13:26:08 by xzhang            #+#    #+#              #
#    Updated: 2023/12/26 12:57:33 by xzhang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
RED    = '\033[1;31m'
GREEN  = '\033[1;32m'
BLUE   = '\033[1;34m'
CYAN   = '\033[0;36m'

#Variables
NAME   = philo

SRCS = action.c ft_atoi.c ft_isdigit.c init.c monitor.c philo.c utils.c
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
MAIN = srcs/philo.c

SRC_DIR = srcs/
OBJ_DIR = objs/

HEADER = -Iinclude

CC     = gcc
RM     = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
ARGS   = 2 800 200 200

#Main targets
all: ${NAME} 
	@echo $(CYAN)Hello Welcome to philo!
	@echo *****************************************************
	@echo *██████╗x██╗xx██╗██╗██╗xxxxxx██████╗xxxxxxxxxxxxxxxx*
	@echo *██╔══██╗██║xx██║██║██║xxxxx██╔═══██╗xxxxxxxxxxxxxxx*
	@echo *██████╔╝███████║██║██║xxxxx██║xxx██║xxxxxxxxxxxxxxx*
	@echo *██╔═══╝x██╔══██║██║██║xxxxx██║xxx██║xxxxxxxxxxxxxxx*
	@echo *██║xxxxx██║xx██║██║███████╗╚██████╔╝xxxxxxxxxxxxxxx*
	@echo *╚═╝xxxxx╚═╝xx╚═╝╚═╝╚══════╝x╚═════╝xxxxxxxxxxxxxxxx*
	@echo *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*
	@echo *██╗xx██╗███████╗██╗xx██╗x█████╗x███╗xxx██╗x██████╗x*
	@echo *╚██╗██╔╝╚══███╔╝██║xx██║██╔══██╗████╗xx██║██╔════╝x*
	@echo *x╚███╔╝xxx███╔╝x███████║███████║██╔██╗x██║██║xx███╗*
	@echo *x██╔██╗xx███╔╝xx██╔══██║██╔══██║██║╚██╗██║██║xxx██║*
	@echo *██╔╝x██╗███████╗██║xx██║██║xx██║██║x╚████║╚██████╔╝*
	@echo *╚═╝xx╚═╝╚══════╝╚═╝xx╚═╝╚═╝xx╚═╝╚═╝xx╚═══╝x╚═════╝x*
	@echo *****************************************************

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYAN)\33[1mPhilo made!"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

leaks :
	@valgrind --leak-check=full --show-leak-kinds=all \  valgrind --leak-check=full ./your_program
	--track-origins=yes --error-limit=no --tool=memcheck -s ./philo $(ARGS)

clean:
	${RM} $(OBJ_DIR)

fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
