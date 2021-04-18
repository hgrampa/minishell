
NAME = term

all: $(NAME)

FORSE:

$(NAME): termcap.c FORSE
	gcc -g $< -ltermcap -o $@
	./$@

phony: all FORSE