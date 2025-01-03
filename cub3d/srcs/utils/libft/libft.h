/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:51:02 by acabarba          #+#    #+#             */
/*   Updated: 2023/10/30 13:52:53 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE_GNL
#  define BUFFER_SIZE_GNL 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*				VERIF					*/
int		ft_isalpha(int c);
int		ft_is_not_alpha(int c);
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *c);
size_t	ft_strlcat(char *dest, const char *src, size_t count);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_tablen(char **array);

/*				TRANSFORM				*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strndup(const char *s1, size_t n);

/*				WRITE					*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_print_array(char **array);

/*				COMP					*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

/*				MEMORY					*/
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
void	*safe_malloc(size_t bytes);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
/*				STRUCT					*/

/*				LINK TO STRUCTURES			*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*			GET_NEXT_LINE					*/
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_endl(char	*str);

/*			FILES DESCRIPTOR HANDLING		*/
int		ft_dup(int fildes);
int		ft_dup2(int fildes, int fildes2);

/*			RAJOUT DURANT MINISHELL			*/
size_t	ft_strspn(const char *s, const char *accept);
char	*ft_strpbrk(const char *s, const char *accept);
char	*ft_strtok(char *str, const char *delim, char **saveptr);

/*			RAJOUT DURANT CUB3D				*/
int		ft_max(int a, int b);
int		ft_isspace(char c);
long	ft_strtol(const char *str, char **endptr, int base);

#endif
