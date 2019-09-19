/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 12:42:31 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/20 20:56:18 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>

/*
**	Error Message
*/
# define FIL_NS "No such file or directory"
# define FIL_PD "Permission denied"
# define VRB_IA "Invalid argument"
# define CMD_NF "¯\\_(ツ)_/¯ Command not found"
# define CMD_NV "not a valid identifier"
# define FIL_NU "no such user or named directory: "
# define FIL_ND "not a directory"
# define SYN_ER "Syntax error"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *hays, const char *need, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncat(char *s1, const char *s2, unsigned int n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *s1, const char *s2, size_t size);
char				*ft_strdup(const char *s1);
void				ft_strdel(char **as);
char				*ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strclr(char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_memdel(void **ap);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memalloc(size_t size);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *str);
void				ft_memdel(void **ap);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned intstart, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(long long int n);
void				ft_putchar(char c);
int					ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_putendl_fd(char const *s, int fd);
int					ft_strequ(char const *s1, char const *s2);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
long long int		ft_strlenint(long long int nb);
int					ft_lstcount(t_list *lst);
int					ft_countw(const char *str, char c);
void				ft_lstprint(t_list *lst);
char				*ft_nstrdup(const char *s1, size_t n);

int					ft_find_file(char *path, char *file);
int					ft_check_file(char *file, int mode);
int					ft_open_file(char *file, int type);
int					ft_exist_fd(int fd);

int					ft_check_char(char *str, char c);
int					ft_find_char(char *str, char c);
int					ft_check_str(const char *src, const char *needle);
int					ft_str_alphanum(char *str);
int					ft_isalphanum(char c);
char				*ft_add_char(char *str, int index, char c, int i_free);
void				ft_rmchar(char *src, char c);
char				*ft_strrev(char *str, size_t len, int alloc);
char				*ft_shift_str(int r_l, char *str, int nbr_shift);
char				*ft_escap_str(char *str, char c);
void				ft_bchar(char *str, size_t n, char c);
int					ft_putstrr(char *s, int free_str);
char				**alloc_chain(char **env, int nbr);
char				**ft_strr_join(char **str1, char **str2);
int					ft_put_strr(char **str);
char				**ft_strr_dup(char **chaine, int len);
int					ft_strrlen(char **argv);
void				ft_strrdel(char **str);
char				**ft_strr_new(int len);
char				*ft_strnew_char(size_t size, char c);
char				*ft_strjoir(char *s1, char *s2, int rm);
int					ft_isspace(char c);
int					ft_check_charr(char *src, int str[], int exept);
void				ft_repeat_char(int c, int n);
char				*ft_rm_char(char *str, int index);
int					ft_putchar_err(int c);
int					ft_chrlen(const char *str, char c);
char				*ft_strfreejoin(char *s1, char *s2);
int					ft_isalldigit(char *str);
int					ft_isallalphanum(char *str);
int					ft_isallprint(char *str);
void				ft_print_error(char *msg, char *para1, char *para2, int rm);
char				*ft_strtrim_and_free(char *s);

#endif
