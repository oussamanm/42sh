/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:18:15 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/09 00:08:08 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define TYPE_OEMSG	"invalid option\ntype: usage: type [-afptP] name [name ...]"
# define CD_OEMSG	"invalid option\ncd: usage: cd [-L][-P] [dir]"
# define SIZE		100

typedef struct s_alias			t_alias;
typedef struct s_aliaspkg		t_aliaspkg;
typedef struct s_cdpkg			t_cdpkg;
typedef struct s_hash			t_hash;
typedef struct s_aliasswitcher	t_aliashel;

enum	e_flags {
	n_flg = 1,
	e_flg = 2,
	E_flg = 4,
	L_flg = 8,
	P_flg = 16,
	a_flg = 32,
	t_flg = 64,
	p_flg = 128,
	maj_p_flg = 256,
	f_flg = 1024
};

struct			s_cdpkg
{
	char		*path;
	struct stat	buf;
	char		buff[1024];
	int			flag;
	char		*sym_path;
	int			index;
};

struct			s_alias
{
	char		*shortcut;
	char		*equal;
	char		*cmd;
	int			flag;
	t_alias		*next;
};

struct			s_aliaspkg
{
	t_alias		*head_ref;
	t_alias		*tail_ref;
};

struct			s_aliasswitcher
{
	char		*string;
	t_aliashel	*next;
};

struct			s_hash
{
	char		*key;
	char		*value;
	int			counter;
	t_hash		*next;
};

/*
** CALL OF BUILT
*/

int				built_cd(char **arg, char **env);
int				built_type(char **args, char **tmpenv);
int				hash_table(char **args);
int				built_unset(char **args);

/*
** - COMMAND (TYPE) FUNCTIONS
*/

int				at_option(char *arg);
int				t_option(char *arg, int flag);
int				p_option(char *arg, int maj_p);
int				a_option(char *arg);
void			no_options(char *arg, int *flag);
int				a_op(char ch, int flag);
int				p_op(char ch, int flag);
int				maj_p_op(char ch, int flag);
int				t_op(char ch, int flag);
int				ft_check_built(char *arg);
int				t_fake_option(char *str, int *j);
int				type_options(char **arg, int *flag);
void			buil_putstr(char *arg, char *s1, char *s2, int fd);

/*
** - ECHO FUNCTIONS;
*/

int				echo_options_(char *arg, int *flag);
int				e_interpretation_1(char *arg);
int				echo_meta_char(char c);
char			echo_charcmp(char c, char *str);

/*
** ALIAS FUNCTIONS
*/

t_aliaspkg		*storeaddrstruct(t_aliaspkg *addr);
void			pushtolist(char *key, char *value, int flag);
int				rm_alias_by_elem_flag(char *shortcut);
char			*handleqoutes(char *str);
void			importaliasfilecontent(char *tmp);
int				freealiaslist(void);
void			ft_buil_updatealias(char **args);
void			printlist(void);
void			createaliasfile(void);
int				value_found_as_key(t_aliaspkg *data, char *valueaskey);
void			freetmplistalias(t_aliashel **head);
char			*get_value(t_aliaspkg *data, char *key);
void			init_var(t_aliashel **head, t_aliashel **tail, char ***arr);
int				free_elem(char *lastkey, char **arr, t_aliashel **head);
void			ft_checker(char **arr, char **newvalue);
char			*aliasfinder(t_alias *curr, char *value, char *lastkey);
int				ft_list(t_aliashel **head, t_aliashel **tail, char *shortkey,
	char **ptr);
t_alias			*get_next_node(t_aliaspkg *data, char *value);

/*
** HASH FUNCTIONS
*/

t_hash			**store_addr_of_hash(t_hash **hash_arr, int flag);
void			insert_hash(char *key, char *value);
char			*lookup_hash(char *key);
void			erase_hash_table();
unsigned int	hash(char *key);
void			display_hash_table();

/*
** FREE HASH AND ALIAS
*/

void			free_hash_and_alias(void);
void			importaliasfilecontent_1(char *line);

/*
** CD FUNCTIONS
*/

char			*handlepath(t_cdpkg *v, char *pwd);
int				ft_error_cd(char *path, char **arg, char *oldpwd);
char			*createnewpath(char *path, char *pwd);
char			*rmbackslashs(char *path);

/*
** HELPER FUNCTIONS
*/

int				alias_invalid_option(char *str);
void			ft_free2d(char **p);
#endif
