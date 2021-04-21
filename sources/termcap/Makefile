
NAME = term

all: $(NAME)

FORSE:

$(NAME): termcap.c FORSE
	gcc -g $< -ltermcap -I ../../libft/includes -L ../../libft/ -lft -o $@
	
# ./$@

phony: all FORSE