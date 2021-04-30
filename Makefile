# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 15:01:24 by hgrampa           #+#    #+#              #
#    Updated: 2021/04/30 14:40:35 by hgrampa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc

CC_FLAGS		:= -Wall -Wextra -Werror
CC_LIBS			:=

FT_PATH			= ./libft
FT_LIB			= $(FT_PATH)/libft.a
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
					sources/input/termcap \
					sources/history \
					sources/errors \
					sources/buildins \
					sources/utilites

OBJ_DIR			=	objects/

# ---------------------------------------------------------------------------- #
INCL			=	libft.h \
					buildin.h \
					command.h \
					dlists.h \
					environment.h \
					errors.h \
					exit_code.h \
					factory.h \
					history.h \
					input.h \
					keymap.h \
					minishell.h \
					parser.h \
					pword.h \
					sbuffer.h \
					terminal.h \
					utilities.h

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
					factory_build_command.c \
					factory_exec.c \
					factory_exec_buildin.c \
					factory_exec_bin.c \
					factory_exec_command.c \
					factory_command_set.c \
					factory_pathfinder.c \
					factory_pathfinder_stats.c \
					buildin.c \
					buildin_cd.c \
					buildin_echo.c \
					buildin_env.c \
					buildin_exit.c \
					buildin_export.c \
					buildin_export_2.c \
					buildin_pwd.c \
					buildin_unset.c \
					pword.c \
					pstate.c \
					pstate_core.c \
					pstate_squotes.c \
					pstate_wquotes.c \
					pstate_env.c \
					pstate_esc.c \
					pstate_cntr.c \
					env.c \
					env_additions.c \
					env_get.c \
					env_pair.c \
					env_represent.c \
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

$(NAME): | libft_make

$(NAME): $(FT_LIB) $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ_PATH) $(CC_LIBS) -o $@

$(OBJ_DIR):
	mkdir $@

libft_make:
	$(MAKE) -wC $(FT_PATH)

$(FT_LIB): libft_make
	
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
	valgrind --leak-check=full --log-file=vallog ./$(NAME)

.PHONY: all clean fclean re norm libft_make val
