/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:31:18 by fnagy             #+#    #+#             */
/*   Updated: 2025/03/31 10:11:10 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h> 
# include <limits.h>
// # include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(char *s);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// printf functions
int		ft_printf(const char *format, ...);

int		ft_print_chr(char c);
int		ft_print_str(char *s);
int		ft_print_nbr(int n);

int		ft_count_len(unsigned int element, int n);

int		ft_print_hex(unsigned long hex, unsigned int capital);
void	ft_hex(unsigned long hex, unsigned int capital);

int		ft_print_ptr(void *ptr);
int		ft_ptr_len(unsigned long nbr);

int		ft_print_dec(unsigned long dec);
void	ft_dec(unsigned long dec);

// get_next_line functions

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

char	*get_next_line(int fd);
char	*ft_strdup2(char *s);
size_t	ft_strlen2(const char *s);
char	*ft_substr2(const char *s, unsigned int start, size_t len);
char	*ft_strjoin2(char *s1, char *s2);

// linked list stuff
typedef struct Node
{
	int			x; // value
	int			index; // index of the value
	int			fee; // push_cost
	bool		above; // above median line
	bool		lowest; // cheapest cost
	struct Node	*target; // target node
	struct Node	*next;
	struct Node	*prev;
}	t_Node;

void	insert_end(t_Node **root, int value);
void	insert_beginning(t_Node **root, int value);
void	insert_after(t_Node *node, int value);
void	insert_sorted(t_Node **root, int value);

void	deallocate(t_Node **root);
void	deallocate_double(t_Node **tail, t_Node **head);

void	remove_element(t_Node **root, int value);
void	reverse(t_Node **root);
void	remove_node(t_Node *node);
void	reverse_double(t_Node **tail, t_Node **head);

int		has_loops(t_Node *root);
int		count_nodes(t_Node *root);
bool	is_list_sorted(t_Node *root);

t_Node	*find_last(t_Node *root);
t_Node	*find_min(t_Node *root);
t_Node	*find_max(t_Node *root);
t_Node	*find_node(t_Node *tail, int value);

void	insert_beginning_double(t_Node **tail, int value);
void	init(t_Node **tail, t_Node **head, int value);
void	insert_after_double(t_Node *node, int value);
void	append_node(t_Node **root, int value);

// random functions
int		max_of_three(int x, int y, int z);
int		my_sprintf(char *buffer, const char *format, ...);

#endif
