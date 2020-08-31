# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 08:56:25 by mapandel          #+#    #+#              #
#    Updated: 2020/08/31 17:08:03 by mapandel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ft_ssl

#			Compilation

CC = 				clang
CFLAGS = 			-Wall -Wextra -Werror -Weverything

#			Sources

SRC =				sources/debug.c \
					sources/display.c \
					sources/execution.c \
					sources/main.c \
					sources/md5.c \
					sources/md5_message_handling.c \
					sources/md5_computations.c \
					sources/parsing_file.c \
					sources/parsing_flags.c \
					sources/parsing.c \
					sources/sha256.c \
					sources/sha256_message_handling.c \
					sources/sha256_computations.c \
					sources/sha512.c \
					sources/sha512_message_handling.c \
					sources/sha512_computations.c \
					sources/touch_t_input.c \
					sources/touch_t_ssl.c \

OBJ =				$(SRC:.c=.o)

INC =				includes

#			Library Path

LIB =				libft
LIBPATH =			$(LIB)/libft.a
LIBINC	=			$(LIB)/includes

#			Tests

TEST =				libunit

EXE_LEAK_REPORT =	ft_ssl_leak_report

SRC_LEAK_REPORT =	$(subst sources/main.c, sources/main_leak_report.c, $(SRC))

OBJ_LEAK_REPORT =	$(SRC_LEAK_REPORT:.c=.o)

LEAK_REPORT		=	leak_report

#			Colors

DEF =				\033[0m
GRA =				\033[1m
SOU =				\033[4m
BLI =				\033[5m
BLA =				\033[30m
RED =				\033[31m
GRE =				\033[32m
YEL =				\033[33m
BLU =				\033[34m
PUR =				\033[35m
CYA =				\033[36m
WHI =				\033[37m

#			Main Rules

.PHONY:				all re glu watch

$(NAME):			$(LIBPATH) $(OBJ)
	@make compile_message
	@make compile_executable

$(EXE_LEAK_REPORT):	$(LIBPATH) $(OBJ_LEAK_REPORT)
	@make compile_leak_report_message
	@make compile_leak_report_executable

all:				$(NAME)

re:					fclean all

glu:				fclean all clean

watch:
	@fswatch $(SRC) $(LIBPATH) | \
	while read ; \
		do make test -j 8 || afplay /System/Library/Sounds/Glass.aiff ; \
	done ;

#			Compilation Rules

.PHONY:				compile_executable compile_leak_report_executable

$(LIBPATH):
	@cd $(LIB); $(MAKE) -f Makefile

%.o:				%.c
	$(CC) $(CFLAGS) -I $(INC) -I $(LIBINC) -c -o $@ $<

compile_executable:
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBPATH)

compile_leak_report_executable:
	@$(CC) $(CFLAGS) -o $(EXE_LEAK_REPORT) $(OBJ_LEAK_REPORT) $(LIBPATH)

#			Testing Rules

.PHONY:				test

test:				$(NAME) $(EXE_LEAK_REPORT)
	@ln -sfn $(shell pwd) $(TEST)/ft_ssl_tests/Ft_ssl;
	@cp $(LIBPATH) $(TEST)/libft/;
	@make test -C $(TEST)/ft_ssl_tests/;

#			Clean Rules

.PHONY:				fclean lfclean clean fclean

lclean:
	@cd $(LIB); $(MAKE) -f Makefile clean

lfclean:
	@cd $(LIB); $(MAKE) -f Makefile fclean

clean:				lclean
	@make clean_message
	@rm -rf $(OBJ) $(OBJ_LEAK_REPORT) $(LEAK_REPORT)

fclean:				clean
	@make fclean_message
	@rm -rf $(NAME) $(EXE_LEAK_REPORT) $(LIBPATH)

#			Display

.PHONY:				compile_message compile_leak_report_message clean_message \
	fclean_message

compile_message:
	@echo "$(CYA)--::Compiled Ft_ssl::--$(DEF)"

compile_leak_report_message:
	@echo "$(CYA)--::Compiled Ft_ssl_leak_report::--$(DEF)"

clean_message:
	@echo "$(PUR)--::Binary Delection::--$(DEF)"

fclean_message:
	@echo "$(RED)--::Executable and Library Delection::--$(DEF)"
