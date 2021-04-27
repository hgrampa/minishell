# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 15:01:24 by hgrampa           #+#    #+#              #
#    Updated: 2021/04/27 17:22:47 by hgrampa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc

# TODO убрать -g перед eval
# TODO добавить -Wall -Wextra -Werror
CC_FLAGS		:= -g
CC_LIBS			:=

FT_PATH			= ./libft
FT_LIB			= libft.a
CC_LIBS			+= -L $(FT_PATH) -lft

CC_LIBS			+= -ltermcap

# ---------------------------------------------------------------------------- #

INCL_DIR		=	includes/ \
					libft/includes/

SRC_DIR			=	sources/ \
					sources/minishell \
					sources/parser \
					sources/parser/states \
					sources/factory \
					sources/environment \
					sources/sbuffer \
					sources/input \
					sources/termcap \
					sources/history \
					sources/errors \
					sources/buildins \
					sources/utilites

OBJ_DIR			=	objects/

# ---------------------------------------------------------------------------- #
INCL			=	minishell.h \
					libft.h \
					errors.h \
					sbuffer.h \
					environment.h \
					input.h \
					terminal.h \
					parser.h \
					keymap.h \
					factory.h \
					command.h \
					exit_code.h \
					pword.h \
					utilities.h \
					buildin.h

SRC				=	main.c \
					signals.c \
					minishell.c \
					minishell_title.c \
					errors.c \
					input.c \
					input_gnl.c \
					input_line.c \
					input_keycall.c \
					keycall.c \
					termcap.c \
					termcap_2.c \
					termcap_keys.c \
					history.c \
					history_2.c \
					parser.c \
					pbuffer.c \
					exit_code.c \
					factory.c \
					command.c \
					factory_build.c \
					factory_exec.c \
					factory_command_set.c \
					factory_pathfinder.c \
					buildin.c \
					cd.c \
					echo.c \
					env.c \
					exit.c \
					export.c \
					export_2.c \
					pwd.c \
					unset.c \
					pword.c \
					pstate.c \
					pstate_core.c \
					pstate_squotes.c \
					pstate_wquotes.c \
					pstate_env.c \
					pstate_esc.c \
					pstate_cntr.c \
					environment_1.c \
					environment_2.c \
					environment_3.c \
					environment_4.c \
					utilities.c \
					sbuffer.c \
					sbuffer_2.c

OBJ				= $(SRC:.c=.o)
OBJ_PATH		= $(addprefix $(OBJ_DIR), $(OBJ))
CC_INCL			= $(addprefix -I , $(INCL_DIR) $(LIBFT_INCL_DIR))

vpath %.c		$(SRC_DIR)
vpath %.h		$(INCL_DIR)
vpath %.o		$(OBJ_DIR)

# ---------------------------------------------------------------------------- #

all: $(NAME)

$(OBJ_DIR):
	mkdir $@

$(NAME): $(FT_LIB) $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ_PATH) $(CC_LIBS) -o $@

$(FT_LIB): libft.h
	$(MAKE) -wC $(FT_PATH)

$(OBJ): %.o: %.c $(INCL) | $(OBJ_DIR)
	$(CC) $(CC_FLAGS) $(CC_INCL) -c $< -o $(OBJ_DIR)$@

# ---------------------------------------------------------------------------- #

clean: 
	-rm -f $(OBJ_PATH)

fclean: clean
	-rm -f $(OBJ_PATH)
	-rm -f $(NAME)
	$(MAKE) -wC $(FT_PATH) fclean

re: fclean $(NAME)

norm:
	norminette libft/sources
	norminette libft/includes
	norminette includes
	norminette sources

val:
	valgrind --leak-check=full --log-file=vallog ./minishell

.PHONY: all clean fclean re norm val
