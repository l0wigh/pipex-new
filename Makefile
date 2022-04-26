# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thomathi <thomathi@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 11:17:33 by thomathi          #+#    #+#              #
#    Updated: 2022/04/22 23:07:48 by thomathi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		= srcs/pipex.c
NAME		= pipex
OBJS_DIR	= objs/
PROJECT_H	= srcs/pipex.h
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra -g3

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED)
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) 
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
	@make -C ../ft_printf/

clean:
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END)"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END)"

valgrind: all
	@./pipex arg1.txt "ls -la" "grep utils" arg2.txt

re: fclean all

.PHONY:		all clean fclean re
