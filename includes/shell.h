/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:07:47 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/22 17:07:50 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SHELL_H
# define _SHELL_H

# include "libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <curses.h>

# define BUFF_SIZE 10
# define UNUSED(x) (void)(x)
# define M_CHECK(x , y, z) ((x == y || x == z) ? 1 : 0)
# define M_C (arg[i][0]==34||arg[i][0]==39)
# define M_CC (arg[i][ft_strlen(arg[i])-1]==34||arg[i][ft_strlen(arg[i])-1]==39)
# define M_CHECK_W(C)(C==32||C==9||C==11||C==10||C==13||C==12)
# define M_REDIR(C) (C == '>' || C == '<')
# define STR(x)  (*str)[x]
# define CHECK_TOKEN(t, a, b, c) (t == a || t == b || t == c)
# define PROMPT 3
# define PATHSIZE 1024
# define M_QUOTE 34
# define M_DQUOTE 39
# define PREV st_tokens->prev
# define NEXT st_tokens->next
# define ERRO_IN_AND -12

/*
**Buttons
*/

# define BTN_ESC 27
# define BTN_SPC 32
# define BTN_ENT 10
# define BTN_DEL 2117294875
# define BTN_BAK 127
# define BTN_UP 4283163
# define BTN_DW 4348699
# define BTN_RG 4414235
# define BTN_LF 4479771

/*
**Tokens
*/

# define T_TXT 0
# define T_QUO 1
# define T_RED_IN_S		-60
# define T_RED_IN_A		-98
# define T_RED_IN_B		-143
# define T_RED_OUT_S	-62
# define T_RED_OUT_A	-100
# define T_RED_OUT_B	-145
# define T_RED_APP_S	-124
# define T_RED_APP_A	-162
# define T_RED_APP_M	-169
# define T_RED_HER_D	-120
# define T_RED_BOTH		-122

/*
**Parsing
*/

# define PARSE_KO 0
# define PARSE_OK 1
# define REDI_OK 1
# define REDI_KO 0

typedef struct termios	t_termios;

typedef struct			s_tokens
{
	int					token;
	char				*value;
	int					indx;
	int					is_arg;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}						t_tokens;

typedef struct			s_filedes
{
	int					fd;
	struct s_filedes	*next;
}						t_filedes;

typedef struct			s_redir
{
	int					type_red;
	int					fd_red;
	int					fd_des;
	int					fd_err;
	int					fd_close;
	char				*fd_file;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_pipes
{
	char				*cmd;
	int					fds[2];
	char				**args;
	t_tokens			*st_tokens;
	t_redir				*st_redir;
	struct s_pipes		*next;
}						t_pipes;

/*
**Builtins
*/

void					ft_built_exit(t_pipes *st_pipes, char ***env);
void					ft_buil_echo(char **arg);
void					ft_buil_cd(char **arg, char ***env);
void					ft_builtenv_cmd(char **args, char ***env);
void					ft_buil_env(char **args, char ***env);
void					ft_buil_setenv(char **args, char ***env);
void					ft_buil_unsetenv(char **args, char ***env);

/*
**Variable
*/

char					*ft_get_vrb(char *vrb, char **env);
void					ft_set_vrb(char *vrb, char ***env, int rm);
void					ft_add_vrb(char *arg, char ***env);
void					ft_unset_vrb(char *vrb, char ***env);

/*
**Error handler
*/

void					ft_print_error(char *msg, char *para1, char *para2,
	int rm);
void					ft_err_exit(char *str);
int						ft_error_cd(char *path, char **arg);
int						ft_error_semic(char *str_arg, char **args_cmd);
int						ft_error_separ(char *str_arg, char c);
int						ft_error_syn(t_pipes *st_pipes);
int						ft_pipe_error(char *str);
int						ft_parse_error(char *str_cmds);

/*
**Updated Splite
*/

char					**ft_str_split(char const *s, char *c);
char					**ft_str_split_q(char *str, char *c);
int						ft_index_of_first_split(char *s1, char *s2);
char					**ft_strsplit_by_arr(char *str, char *split);

/*
**Helper
*/

char					*ft_find_path(char *arg, char **env);
int						ft_count_word(const char *str, char *c);
t_pipes					*ft_strr_list(char **args_pipe);

/*
**Quote
*/
void					ft_rm_quot(char **str);
char					*ft_corr_args(char *argv, char **environ);
void					ft_remove_quot(char **args);
void					ft_update_tokens(t_tokens *st_tokens);

/*
**Signals
*/

void					ft_call_signal();
void					ft_call_handler();
void					ft_signal_default();

/*
**Dimention
*/

void					ft_move_cur(char capa[2], int c, int r);
void					ft_capa_str(char capa[2]);
int						ft_putchar_err(int c);

/*
**Pipes
*/

void					ft_create_pipes(t_pipes *st_pipes);
void					ft_apply_pipe(t_pipes *st_pipes, char ***environ);

/*
**Lexer
*/

void					ft_err_lexer(t_pipes *st_pipes);
void					ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j,
	int indx);
void					ft_lexer_red(t_tokens **st_tokens, char *arg, int *j,
	int indx);
void					ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j,
	int indx);
t_tokens				*ft_lexer(char **args);

t_tokens				*ft_new_token();
void					ft_fill_token(t_tokens **st_tokens, int token,
	char *value, int indx);
int						ft_sum_asci(char str[]);
void					ft_upd_token(t_tokens *st_tokens, int token,
	char *value);

/*
**Redirection
*/

void					ft_redi_her(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_both(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_app(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_in(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_out(t_redir *st_redir, t_tokens *st_tokens);
int						ft_error_redir(t_tokens *st_tokens);
t_redir					*ft_new_redir();
void					ft_init_redi(t_redir *st_redir, int type_red);
void					ft_redi_out_h(t_redir *st_redir, t_tokens *st_tokens);
void					ft_apply_hered(t_redir *st_redi);

/*
**Parser Red; ft_read_tokens,ft_apply_redi,ft_update_args
*/

int						ft_parse_cmd(t_pipes *st_pipes);

/*
**Execution
*/

int						ft_cmd_exec(t_pipes *st_pipes, char **env);
void					ft_split_cmd(int fork_it, t_pipes *st_pipes,
	char ***env);
int						ft_call_cmdss(char *str_arg, char ***environ);
int						ft_check_redi(t_pipes *st_pipes);

/*
**Exec builtens
*/

void					ft_init_built(t_pipes *st_pipes, char ***env);
int						ft_call_built(t_pipes *st_pipes, char ***env);
int						ft_check_built(char *arg);

/*
**Free
*/

void					ft_clear_cmds(t_pipes *st_pipes);
void					ft_clear_tokens(t_tokens *st_tokens);

#endif
