/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:09:14 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/24 22:49:48 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_strlen(const char *str);

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
char	*get_next_line(int fd);
char	*ft_read_the_line(int fd, char *fd_str);
char	*ft_readed_line(char *src);
char	*ft_gnl_strchr(char *s, int c);
char	*ft_move_start( char *start);
char	*ft_gnl_strjoin(char *start, char *buff);
char	*ft_join(char *new_fd_str, char *start, char *buff);
int		ft_printf(const char *string, ...);
void	ft_check_specifier(const char *str, int i, va_list args,
			unsigned int *byte_count);
void	ft_hexa_xs(unsigned int nb, char type,
			unsigned int *byte_count);
void	ft_hexa_p(unsigned long long nb, unsigned int *byte_count);
void	ft_printf_putnbr(int nb, unsigned int *byte_count);
void	ft_putnbr_u(unsigned int nb, unsigned int *byte_count);
int		ft_putchar(char c);
void	ft_writing(char *str, unsigned int *byte_count);
char	*ft_firstword(char *command);
int		ft_count(char const *s, char c);
char	*ft_find_chrs(char *main_str, char *c_to_look);
void    *s_malloc(size_t bt);

#endif