/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:18:15 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/25 12:18:16 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#define TYPE_OEMSG	"invalid option\ntype: usage: type [-afptP] name [name ...]"
#define CD_OEMSG	"invalid option\ncd: usage: cd [-L][-P] dir]"
#define SIZE 50

typedef struct s_alias t_alias;
typedef struct s_aliaspkg t_aliaspkg;
typedef struct s_cdpkg t_cdpkg;
typedef struct s_hash	t_hash;

enum flags{
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

struct s_cdpkg
{
    char	*path;
    struct  stat buf;
	char	buff[1024];
    int		flag;
    int     index;
};

struct s_alias
{
	char *shortcut;
	char *cmd;
	int  flag;
	t_alias *next;
};

struct s_aliaspkg 
{
	int fd;
	t_alias *head_ref;
	t_alias *tail_ref;
};

struct s_hash
{
	char *key;
	char *value;
	int   counter;
	t_hash *next;
};

/*
** Builtins
*/

void					built_echo(char **arg);
int						built_cd(char **arg, char **env);
int						built_type(char **args, char **tmpenv);
void					built_env(char **args, char ***tmp_env);
void					built_unset(char **args);


/*
** - COMMAND (TYPE) FUNCTIONS
*/

void    at_option(char *arg);
void    t_option(char *arg, int flag);
void	p_option(char *arg, int maj_p);
void    a_option(char *arg);
void    no_options(char *arg, int *flag);
int		a_op(char ch, int flag);
int 	p_op(char ch, int flag);
int		maj_p_op(char ch, int flag);
int		t_op(char ch, int flag);
int     ft_check_built(char *arg);
int		t_fake_option(char *str, int *j);
int		type_options(char **arg, int *flag);
void	buil_putstr(char *arg, char *s1, char *s2, int fd);

/*
** - ECHO FUNCTIONS;
*/

int echo_options(char **arg, int *flag);

/*
** ALIAS FUNCTIONS
*/

t_aliaspkg *storeaddrstruct(t_aliaspkg *addr);
void pushtolist(char *string, int flag);
int removealiasbyelemorbyflag(char *shortcut, int check);
char *handleqoutes(char *str);
void importaliasfilecontent();
void createaliasfile();
char **aliasmatched(char **args);
char *handleqoutes(char *str);
void ft_buil_updatealias(char **args);

/*
** HASH FUNCTIONS
*/

t_hash **store_addr_of_hash(t_hash **hash_arr, int flag);
void insert_hash(char *key, char *value);
char *lookup_hash(char *key);
void hash_table(char **args);
void erase_hash_table();
unsigned int hash(char *key);

//
void display_hash_table();

#endif
