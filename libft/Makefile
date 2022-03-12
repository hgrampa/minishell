# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 11:39:03 by hgrampa           #+#    #+#              #
#    Updated: 2021/04/30 14:48:50 by hgrampa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

CC				= gcc
FLAGS			= -Wall -Wextra -Werror

INCL_DIR 		= includes/
OBJ_DIR			= objects/
SRC_DIR 		= sources/
SUBDIRS			:= 

INCL			= libft.h
SRC 			:=

# ---------------------------------------------------------------------------- #

MEMORY_DIR		= ft_memory
SUBDIRS			+= $(MEMORY_DIR)

SRC_MEMORY		= 	ft_bzero.c \
					ft_memccpy.c \
					ft_memcmp.c \
					ft_memmove.c \
					ft_memset.c \
					ft_calloc.c \
					ft_realloc.c \
					ft_memchr.c \
					ft_memcpy.c

SRC				+= $(SRC_MEMORY)
OBJ_MEMORY		= $(SRC_MEMORY:.c=.o)

# ---------------------------------------------------------------------------- #

QUEUE_DIR		= ft_queue
SUBDIRS			+= $(QUEUE_DIR)

SRC_QUEUE		= ft_queue.c

SRC				+= $(SRC_QUEUE)
OBJ_QUEUE		= $(SRC_QUEUE:.c=.o)

# ---------------------------------------------------------------------------- #

STACK_DIR		= ft_stack
SUBDIRS			+= $(STACK_DIR)

SRC_STACK		= ft_stack.c

SRC				+= $(SRC_STACK)
OBJ_STACK		= $(SRC_STACK:.c=.o)

# ---------------------------------------------------------------------------- #

DLIST_DIR		= ft_dlist
SUBDIRS			+= $(DLIST_DIR)

SRC_DLIST		= ft_dlist.c

SRC				+= $(SRC_DLIST)
OBJ_DLIST		= $(SRC_DLIST:.c=.o)

# ---------------------------------------------------------------------------- #

STRINGS_DIR		= ft_strings
SUBDIRS			+= $(STRINGS_DIR)

SRC_STRINGS		= 	ft_atoi.c \
					ft_atof.c \
					ft_atoi_rwnd.c \
					ft_digit_char.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_itoa_base.c \
					ft_split.c \
					ft_sstrlen.c \
					ft_strcdup.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncat.c \
					ft_strncmp.c \
					ft_strcmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_ultoa_base.c \
					ft_utoa_base.c \
					ft_concat.c \
					ft_strndup.c

SRC				+= $(SRC_STRINGS)
OBJ_STRINGS		= $(SRC_STRINGS:.c=.o)

# ---------------------------------------------------------------------------- #

FD_DIR			= ft_fd
SUBDIRS			+= $(FD_DIR)

SRC_PUTFD		= 	ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_gnl_cash.c \
					ft_gnl.c \
					ft_putchar.c

SRC				+= $(SRC_PUTFD)
OBJ_PUTFD		= $(SRC_PUTFD:.c=.o)

# ---------------------------------------------------------------------------- #

LISTS_DIR		= ft_lists
SUBDIRS			+= $(LISTS_DIR)

SRC_LISTS		= 	ft_lists.c \
					ft_list_tosa.c \
					ft_lstadd_back.c \
					ft_lstadd_front.c \
					ft_lstclear.c \
					ft_lstdelone.c \
					ft_lstiter.c \
					ft_lstlast.c \
					ft_lstmap.c \
					ft_lstnew.c \
					ft_lstsize.c \
					ft_list_at.c

SRC				+= $(SRC_LISTS)
OBJ_LISTS		= $(SRC_LISTS:.c=.o)

# ---------------------------------------------------------------------------- #

OBJ				= $(SRC:.c=.o)
OBJ_PATH		= $(addprefix $(OBJ_DIR), $(OBJ))

vpath %.h		$(INCL_DIR) $(SRC_DIR)$(FD_DIR)
vpath %.c		$(addprefix $(SRC_DIR), $(SUBDIRS))
vpath %.o		$(OBJ_DIR)

# ---------------------------------------------------------------------------- #

_BLU = \033[34m
_DGR = \033[90m
_LBL = \033[94m
_NRM = \033[39m

# ---------------------------------------------------------------------------- #

all: $(NAME)
 
$(NAME): $(NAME)($(OBJ))

$(OBJ_DIR):
	@ -echo "$(_LBL)==>$(_NRM) mkdir -p $@"
	@mkdir -p $@

$(NAME)(%.o): %.o
	@ -echo "$(_BLU)==>$(_NRM) ar -rcs $(NAME) $(OBJ_DIR)$%"
	@ar -rcs $@ $(OBJ_DIR)$%

ft_gnl.o ft_gnl_cash.o : ft_gnl_service.h

$(OBJ): %.o: %.c $(INCL) | $(OBJ_DIR)
	@ -echo "$(_DGR)"
	$(CC) $(FLAGS) -I $(INCL_DIR) -c $< -o $(OBJ_DIR)$@
	@ -echo "$(_NRM)"

clean: 
	@ -echo "$(_BLU)==>$(_NRM) -rm -f $(addprefix \n\t\t, $(OBJ_PATH))\n"
	@ -rm -f $(OBJ_PATH)

fclean: clean
	@ -echo "$(_BLU)==>$(_NRM) -rm -f \t$(NAME)\n"
	@ -rm -f $(NAME)

re: fclean $(NAME)

# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re
 