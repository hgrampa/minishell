/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:17:58 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:53:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# define _FT_ASCII_MIN 0

# define _FT_ASCII_MIN 0
# define _FT_ASCII_MAX 127
# define _FT_PRINT_MIN 32
# define _FT_PRINT_MAX 126
# define _FT_ALFAUP_MIN 65
# define _FT_ALFAUP_MAX 90
# define _FT_ALFADWN_MIN 97
# define _FT_ALFADWN_MAX 122
# define _FT_DIGIT_MIN 48
# define _FT_DIGIT_MAX 57
# define _FT_ASCII_NUM_OFFSET '0'
# define _FT_ASCII_ALFAREG_OFFSET 32

# define _FT_SINT32_LAST -2147483648
# define _FT_SINT32_LAST_STR "-2147483648"
# define _FT_SINT32_MAXLEN 11

# define _FT_SINT64_MAX 9223372036854775807

# define _FT_FLT_MAX 3.40282346638528859811704183484516925e+38F
# define _FT_FLT_MIN 1.17549435082228750796873653722224568e-38F
# define _FT_DBL_MAX ((double)1.79769313486231570814527423731704357e+308L)
# define _FT_DBL_MIN ((double)2.22507385850720138309023271733240406e-308L)

# define _FT_FALSE 0
# define _FT_TRUE 1

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

typedef struct s_queue
{
	void			*data;
	struct s_queue	*next;
}				t_queue;

typedef struct s_stack
{
	void			*data;
	struct s_stack	*next;
}				t_stack;

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*next;
	struct s_dlist	*previous;
}					t_dlist;

typedef char	t_bool;

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_realloc(void *ptr, size_t old_size, ssize_t new_size);

size_t			ft_strlen(const char *s);
size_t			ft_sstrlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strncat(char *dst, char *src, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *h, const char *n, size_t len);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strdup(const char *s1);
char			*ft_strcdup(const char *str, char ch);
char			*ft_strndup(const char *s1, int len);
char			*ft_gnwrd(char **str);
int				ft_isnwrd(char *str, char *substr);
int				ft_chnwrd(const char *str, const char *set);

int				ft_atoi(const char *str);
int				ft_atoi_rwnd(char **str);
double			ft_atof(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_base_lw(int value, int base, size_t wight);
char			*ft_itoa_base_up(int value, int base, size_t wight);
char			*ft_utoa_base_lw(unsigned int value, int base, size_t wight);
char			*ft_utoa_base_up(unsigned int value, int base, size_t wight);
char			*ft_ultoa_base_lw(unsigned long value, int base, size_t wight);
char			*ft_ultoa_base_up(unsigned long value, int base, size_t wight);
char			ft_digit_char_lw(int digit);
char			ft_digit_char_up(int digit);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_concat2(char *str1, char *str2);
char			*ft_concat3(char *str1, char *str2, char *str3);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
int				ft_putchar(int c);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_gnl(int fd, char **line, int size);

t_list			*ft_lstnew(void *data);
void			ft_lstadd_front(t_list **lst, t_list *newnode);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *newnode);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));

t_queue			*ft_queue_new(void *data);
int				ft_queue_enqueue(t_queue **root, void *data);
void			*ft_queue_dequeue(t_queue **root);
void			*ft_queue_peek(t_queue *root);
void			ft_queue_free(t_queue **root, void (*del)(void *));

t_stack			*ft_stack_new(void *data);
int				ft_stack_push(t_stack **root, void *data);
void			*ft_stack_pop(t_stack **root);
void			*ft_stack_peek(t_stack *root);
void			ft_stack_free(t_stack **root, void (*del)(void *));

t_list			*ft_list_new(void *data);
int				ft_list_add(t_list **root, void *data);
int				ft_list_count(t_list *root);
void			ft_list_foreach(t_list *root, void (*f)(void *));
void			ft_list_free(t_list **root, void (*del)(void*));
t_list			*ft_list_at(t_list *root, int index);
char			**ft_list_tosa(t_list *list);

t_dlist			*ft_dlist_new(void *data);
void			ft_dlist_free(t_dlist **root, void (*del)(void*));
int				ft_dlist_pull(t_dlist **root, void *data);
void			ft_dlist_foreach(t_dlist *root, void (*f)(void *));
int				ft_dlist_add(t_dlist **root, void *data);

#endif
