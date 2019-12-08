# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 08:56:25 by mapandel          #+#    #+#              #
#    Updated: 2019/12/05 03:13:11 by mapandel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_ssl

#			Compilation

CC = 		clang
CFLAGS = 	-Wall -Wextra -Werror -Weverything

#			Sources

SRC =		sources/debug.c \
			sources/display.c \
			sources/execution.c \
			sources/main.c \
			sources/md5.c \
			sources/parsing_file.c \
			sources/parsing_flags.c \
			sources/parsing.c \
			sources/touch_t_input.c \
			sources/touch_t_ssl.c \

OBJ =		$(SRC:.c=.o)

INC =		includes

#			Library Path

LIBPATH =	libft/libft.a

LIBINC	=	libft/includes

#			Colors

DEF =		\033[0m
GRA =		\033[1m
SOU =		\033[4m
BLI =		\033[5m
BLA =		\033[30m
RED =		\033[31m
GRE =		\033[32m
YEL =		\033[33m
BLU =		\033[34m
PUR =		\033[35m
CYA =		\033[36m
WHI =		\033[37m

#			Main Rules

$(NAME): $(LIBPATH) $(OBJ)
	@make compile_message
	@make ecompile

.PHONY: all
all: $(NAME)

.PHONY: re
re: fclean all

.PHONY: glu
glu: fclean all clean

#			Compilation Rules

$(LIBPATH):
	@cd libft; $(MAKE) -f Makefile

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC) -c -o $@ $^

ecompile:
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBPATH)

#			Clean Rules

.PHONY: lclean
lclean:
	@cd libft; $(MAKE) -f Makefile clean

.PHONY: lfclean
lfclean:
	@cd libft; $(MAKE) -f Makefile fclean

.PHONY: clean
clean: lclean
	@make clean_message
	@rm -rf $(OBJ)

.PHONY: fclean
fclean: clean
	@make fclean_message
	@rm -rf $(NAME) $(LIBPATH)

#			Display

.PHONY: compile_message
compile_message:
	@echo "$(CYA)--::Compiled Ft_ssl::--$(DEF)"

.PHONY: clean_message
clean_message:
	@echo "$(PUR)--::Binary Delection::--$(DEF)"

.PHONY: fclean_message
fclean_message:
	@echo "$(RED)--::Executable and Library Delection::--$(DEF)"
