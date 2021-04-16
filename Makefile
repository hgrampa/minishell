# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 15:01:24 by hgrampa           #+#    #+#              #
#    Updated: 2021/04/16 14:41:07 by hgrampa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc

# TODO убрать перед eval
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
					sources/parser \
					sources/parser/states \
					sources/environment

OBJ_DIR			=	objects/

# ---------------------------------------------------------------------------- #
INCL			=	minishell.h \
					libft.h \
					input.h \
					parser.h

SRC				=	main.c \
					input.c \
					parser.c \
					pbuffer.c \
					pword.c \
					pstate.c \
					core_state.c \
					squotes_state.c \
					wquotes_state.c	\
					env_state.c \
					cntr_state.c \
					environment_1.c \
					environment_2.c \
					environment_3.c \
					environment_4.c

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

.PHONY: all clean fclean re norm
