/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:07:47 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/17 05:10:55 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SHELL_H
# define _SHELL_H

# include "libft.h"
# include "builtins.h"
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
# define DEBUG(msg) puts(msg)
# define DEBUGF(msg,...) printf(msg, __VA_ARGS__)
# define M_CHECK(x , y, z) ((x == y || x == z) ? 1 : 0)
# define IS_QUOTE(x) (x == 34 || x == 39)
# define M_CHECK_W(C)(C==32||C==9||C==11||C==10||C==13||C==12)
# define M_REDIR(C) (C == '>' || C == '<')
# define M_SUBSH(x) (M_REDIR(x) || x == '$')
# define M_SPEC_CHARC(x) (x=='$'||x=='`'||x=='\\'||x=='"'||x=='\n')
# define M_ESCAPED(x) (x == '\\')
# define M_BRACKET(x) (x == '(' || x == ')')
# define STR(x)  (*str)[x]
# define CHECK_TOKEN(t, a, b, c) (t == a || t == b || t == c)
# define MATCH_CLOSED(x, y)(((x == 'q' || x == 'Q') && x == y) || (x == 'S' && y == 's'))
# define PROMPT 3
# define PATHSIZE 1024
# define PREV st_tokens->prev
# define NEXT st_tokens->next
# define ERRO_IN_AND -12
# define IDENTIFIER(x) (x=="?"||x=="-"||x=="@"||x=="%"||x=="~"||x==":"||x==".")

#define MAX_MAPS 1000
#define MAX_TAB_ADDR 10
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
#define T_IS_SUBSHELL(x) (x == T_SUBSHL || x == T_PROC_IN || x == T_PROC_OUT)
#define T_IS_TXT(x) (x == T_TXT || x == T_QUO || x == T_DQUO)

# define T_TXT			0
# define T_QUO			1
# define T_DQUO			2
# define T_SUBSHL		117
# define T_PROC_IN		1337
# define T_PROC_OUT		42
# define T_JOBCTR		38
# define T_LOGOPR_AND	76
# define T_LOGOPR_OR	248
# define T_PIPE			124
# define T_EQUAL		61
# define T_HIST			33
# define T_HIST_LAST	66
# define T_BRACKET_O	40
# define T_BRACKET_C	41
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

/*
** Job control
*/

# define RUN 11
# define STOPED 22
# define TERMINATED 33
# define EXITED 44

typedef	struct			s_process
{
	pid_t				pid;
	int					status;
	int					exit_status;
}						t_process;

typedef struct			s_job
{
	pid_t				pgid;
	int					index;
	int					status;
	t_list				*proc;
	int					background;
	int 				mark_stop;
	int					sig_term;
	char 				*cmd;
	char				p;
	struct termios		term_child;
}						t_job;

t_list					*jobs;


/*
** job control
*/

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

typedef struct    s_intern
{
	char    *key;
	char    *value;
	struct s_intern *next;
}                t_intern;


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
	int					fds[2];
	int					status;
	char				**args;
	int					bl_jobctr;
	char				**tmp_env;
	t_tokens			*st_tokens;
	t_redir				*st_redir;
	//t_intern			*st_intern;
	struct s_pipes		*next;
}						t_pipes;

typedef struct 			s_logopr
{
	t_tokens			*st_tokens;
	int					status;
	t_pipes				*st_pipes;
	struct s_logopr		*next;
	int					bl_jobctr;
}						t_logopr;

typedef struct s_jobctr
{
	int					status;
	t_tokens			*st_tokens;
	t_logopr			*st_logopr;
	struct s_jobctr		*next;
}						t_jobctr;


typedef	struct s_cmds
{
	char				**args;
	t_tokens			*st_tokens;
	t_jobctr			*st_jobctr;
}						t_cmds;



t_intern	*g_intern;
char		**g_environ;

/*
** Builtins
*/

void					built_exit(t_pipes *st_pipes, char ***env);
void					built_export(t_tokens *st_tokens);

/*
** Intern variable
*/

void					add_intern_var(char *key, char *value);
void					delete_intern_var(char *key, t_intern **head);
char					**ft_fill_env(char **args);
char					*get_intern_value(char *key);
t_intern				get_key_value(t_tokens *st_tokens);


/*
**Variable
*/

char					*ft_get_vrb(char *vrb, char **env);
void					ft_set_vrb(char *vrb, char ***env, int rm);
void					ft_add_vrb(char *arg, char ***env);
void					ft_unset_vrb(char *vrb, char ***env);
void					ft_insert_vrb(char *vrb, char ***env, int rm);
int						ft_edit_vrb(char *vrb, char ***env, int rm);


/*
** Error handler
*/

void					print_error(char *msg, char *para1, char *para2, int rm);
void					ft_err_exit(char *str);
int						ft_error_cd(char *path, char **arg);
int						ft_call_lexer(t_pipes *st_pipes);
int						error_syntax_lexer(t_tokens *st_tokens);
int						error_syntax_semi(char *str_cmds, char **args);
int						error_syntax_expans(char *str_cmds);
int						ft_putchar_err(int c);

/*
** Updated Splite
*/

char					**ft_str_split(char const *s, char *c);
char					**ft_str_split_q(char *str, char *c);

/*
** Helper Splite
*/

int			find_dquot(char *str);
int			find_subsh(char *str);
int			find_quot(char *str);
int			find_closed(char *str, char c);


/*
** Helper
*/

char					*ft_find_path(char *arg, char **env);
int						ft_check_redi(t_pipes *st_pipes);
int						ft_sum_asci(char str[]);
int		find_char_escap(char *str, char c);
int				ft_all_quot(char *str);


/*
** Quote
*/

char					*ft_rm_quot(char *str);
char					*ft_corr_args(char *argv);
void					ft_remove_quot(char **args);
void					ft_update_tokens(t_tokens *st_tokens);
char			*ft_str_remp(char *str, char *remp, int start, int len);

/*
** Signals
*/

void					call_signal();
void					ft_call_handler();
void					ft_signal_default();


/*
** Pipes
*/

int						ft_pipe(t_pipes *st_pipe);
void					ft_create_pipes(t_pipes *st_pipes);
int						ft_apply_pipe(t_pipes *st_pipes);


/*
** Lexer
*/

void					ft_err_lexer(t_pipes *st_pipes);
void					ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j, int indx);
void					ft_lexer_red(t_tokens **st_tokens, char *arg, int *j, int indx);
void					ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j, int indx);
t_tokens				*ft_lexer(char **args);

void					ft_fill_token(t_tokens **st_tokens, int token, char *value, int indx);
void					ft_upd_token(t_tokens *st_tokens, int token, char *value);
void					ft_dup_token(t_tokens **st_token, t_tokens *st_src, int token);
void					ft_tokens_args(t_pipes *st_pipe);
int						ft_count_tokens(t_tokens *st_tokens);
int						ft_check_token(t_tokens *st_tokens, int token);

/*
** Redirection
*/

void					ft_redi_her(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_both(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_app(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_in(t_redir *st_redir, t_tokens *st_tokens);
void					ft_redi_out(t_redir *st_redir, t_tokens *st_tokens);
int						ft_error_redir(t_tokens *st_tokens);
void					ft_init_redi(t_redir *st_redir, int type_red);
void					ft_redi_out_h(t_redir *st_redir, t_tokens *st_tokens);
void					ft_apply_hered(t_redir *st_redi);
void					ft_apply_her_doc(t_jobctr *st_jobctr);
char					*get_value_next(t_tokens *st_token);


/*
** Parser Red
*/

int						parse_redir(t_pipes *st_pipes);

/*
** Execution
*/

void					ft_multi_cmd(char *str_cmds, int bl_subsh);
int						ft_cmds_setup(char *str_arg, int bl_subsh);
int						ft_cmd_fork(int fork_it, t_pipes *st_pipes);
int				ft_check_cmd(char *cmd, char **environ);
void		logical_ops(t_logopr *st_logopr);
void			remove_backslashs(char **args);


/*
** Exec builtens
*/

int						ft_init_built(t_pipes *st_pipes, char ***tmp_env);
int						ft_call_built(t_pipes *st_pipes, char ***tmp_env);
int						ft_check_built(char *arg);


/*
** New
*/

t_redir					*ft_new_redir(void);
t_tokens				*ft_new_token(void);
t_pipes					*ft_new_pipe(void);
t_logopr				*ft_new_logopr(void);
t_jobctr				*ft_new_jobctr(void);
t_cmds					*ft_new_cmds(void);
t_intern				*ft_new_intern(void);
t_intern				*new_intern(char *key, char *value);

/*
** Free
*/

void					free_list_cmds(t_cmds *st_cmds);
void					free_tokens(t_tokens *st_tokens, int free_content);
void		free_addresses(void *table[MAX_TAB_ADDR]);
void		free_list_redir(t_redir *st_redir);

/*
** Parse Cmds
*/

void					ft_parse_cmd(t_cmds *st_cmds);


/*
** Variable parsing
*/

int						ft_check_intern(t_pipes *st_pipe);
void					ft_fill_intern(t_pipes *st_pipe);
char					**ft_fill_env(char **args);
char					**ft_tokens_arg_env(t_tokens *st_tokens);


/*
** Line complition
*/


/*
** Sub_shell
*/

void					apply_subsh(t_tokens *st_tokens);
void    proc_substitution(t_tokens *st_tokens);

/*
** Alias
*/

void            ft_buil_alias(t_tokens *st_tokens);
int			ft_buil_unalias(t_tokens *st_token, int flag);

/*
** job
*/

void					ft_foreground(void);
void					ft_continue(void);
void					ft_catch_sigchild(int sig);
void					ft_manage_jobs(int pid, t_pipes *st_pipes, int *rtn);
void					ft_add_job(t_job *job);
void					ft_job_processing(void);
void					ft_fill_process(int pid, t_job *job);
void    ft_collect_job_status(void);
void	ft_printstatus(int status);
void	ft_putjoblst(int pgid, int pid, int status);
int		ft_termsig_fore(int sig, char *name);
void 	ft_wait(t_job *current);
int			ft_job_index(void);
t_job			*ft_inisial_job(void);
char 			*ft_cmd_value(t_tokens *st_tokens, char *cmd);
int		ft_print_termsig_back(int sig, char *name, int index, char p);
void	ft_jobs_built(void);
void		ft_update_p(void);
void		ft_update_index(void);
void	ft_print_pid(int index, int pgid);
void 			ft_foreground_job(t_job *job);
void	ft_remove_node(t_list *tmp, t_list *pr);
void	ft_free_job(t_job *job);
void			ft_single_proc(t_job *job, t_pipes *st_pipes, int pid, int *add);
void			ft_pipe_job_man(t_job *job, t_pipes *st_pipes, int *status, int add);
char	*ft_strsignal(int sig);
void	ft_print_backcmd(t_job *job);


#endif
