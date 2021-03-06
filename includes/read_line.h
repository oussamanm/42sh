/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:27:03 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/13 21:19:33 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <sys/ioctl.h>
# include "shell.h"

# define MAX_HISTORY 20
# define MAX_LINES 20

/*
** - selection right 		Alt + Right.
** - selection left 		Alt + Left
** - COPY					Alt + C
** - PASTE					Alt + P
** - CUT					Alt + X
** - moving by words		Alt + Q  // Alt + W
** - moving by lines		Alt + UP // Alt + Down
*/

# define ENTER 10
# define DEL 127
# define UP 4283163
# define DO 4348699
# define RI 4414235
# define LE 4479771
# define SEL_RI 1130044187
# define SEL_LE 1146821403
# define COPY 42947
# define PASTE 32975
# define CUT 8948194
# define LE_WOR	37829
# define RI_WOR 9537762
# define HOME 4741915
# define END 4610843
# define ALT_UP 1096489755
# define ALT_DO 1113266971
# define CTRL_D 4
# define CTRL_T 20
# define TAB 9
# define CTRL_U 21
# define CTRL_L 12
# define CTRL_R 18

# define SUB_S 5
# define QUOTE 7
# define PR_S 8
# define HEREDOC 9
# define DQUOTE 10
# define EXIT_CLD -10

# define CAST(x) *((int *)x)

# define FC_E 0x1
# define FC_L 0x2
# define FC_N 0x4
# define FC_R 0x8
# define FC_S 0x10

typedef struct s_history	t_history;

typedef struct		s_cursor
{
	int				index;
	int				p;
	int				x;
	int				y;
	int				num_lines;
	int				num_col;
	int				*end;
	char			*cmd;
	int				exit;
	int				i;
	int				r;
	struct termios	enable;
	struct termios	disable;
}					t_cursor;

typedef	struct		s_select
{
	int				start;
	int				end;
	char			*save;
}					t_select;

typedef	struct		s_info
{
	int				index;
	char			*cmd;
	struct s_info	*prev;
	struct s_info	*next;
}					t_info;

struct				s_history
{
	struct s_info	*head;
	struct s_info	*tail;
	char			*home;
	int				len;
	int				bg;
};

t_cursor			g_pos;
t_history			g_history;
int					g_sign;

char				*ft_read_line(t_history *his, t_select *select, int p);
void				ft_free_tab(char **tableau);
void				ft_catch_signal(int signal);
void				ft_see_touch(char *buf, char *s, t_cursor *pos);
int					ft_get_size_windz(void);
int					ft_set_termcap(void);
void				ft_stock_history(char **history, char *line, int his_count);
int					my_outc(int c);
void				ft_movecur_up_and_right(int up, int size);
int					ft_get_num_of_lines(int num_col, char *s, int p);
void				ft_set_last_position(t_cursor pos, int num_lines);
void				ft_move_cursor_zero(t_cursor pos);
void				ft_move_cursor_end(t_cursor pos);
void				ft_copy_paste(char *buf, char **s, \
t_cursor *pos, t_select *select);
void				ft_init(int **d, int size);
void				ft_putstr_term(int num_col, char *s, t_cursor *pos);
void				ft_get_end_of_line_pos(t_cursor *pos, char *s, int num_col);
void				ft_get_new_pos(t_cursor *pos, int len);
void				ft_move_by_word(t_cursor *pos, char *s, char *buf);
void				ft_home_end(t_cursor *pos, char *s, char *buf);
void				ft_move_by_lines(t_cursor *pos, char *s, char *buf);
void				ft_move_left(int n);
void				ft_quotes(char **line, t_select *select, t_history *his);
char				**ft_alloc_tab(void);
void				ft_print_with_reverse_mode(char *s, \
int start, int end, t_cursor *pos);
char				*ft_delcolomn(char *s, t_cursor *pos);
void				ft_initial(int p);
void				ft_print_history(t_history *his, \
char *buf, char **s, t_cursor *pos);
void				ft_print_touch_and_join(t_cursor *pos, char *buf, char **s);
void				ft_move_right(int n);
char				*ft_ctrl_d(t_cursor *pos, \
t_history *his, t_select *select, char *s);
void				save_address(t_select **select);
void				ft_clear_readline_struct(void);
char				*ft_read_heredoc(char *eol);
void				ft_cut(t_cursor *pos, t_select *select, char **s);
void				ft_get_save(char *s, t_select *select, t_cursor *pos);
void				ft_init_size_end_line(t_cursor *pos);
char				*ft_inside_line(char *s, t_cursor *pos, char *buf);
void				ft_enable(void);
void				ft_disable(void);
char				*ft_clear(t_cursor *pos, char *s, char *buf);
void				print_tab(int num_col, int *x);
void				num_lines_tab(char spaces, t_cursor *pos,\
int *x, int *num_lines);
void				convert_neg_to_tab(char **s);
void				convert_tab_to_neg(char **s);
void				update_tab_str(char **s, t_cursor *pos);
/*
** read for sub_shell
*/
int					ft_check_subsh(int i, char **line,\
t_select *select, t_history *his);
/*
**	history readline, '!' expansion and fc builtuin
*/
void				insert_history(t_history *history, char *cmd);
t_info				*history_index(t_info *history, int index, int len);
t_info				*history_keyword(t_info *history, char *keyword, int dir);
void				history_readline(t_history *history, int key, char **cmd);
void				init_history(t_history *history);
void				restore_history(t_history *history);
void				save_history(t_history *history);
t_info				*history_value(t_history his, char *keyword);
void				rev_his_list(t_history *lst);
void				display_his_list(t_history his, int order);
int					history_handling(char **str_cmds);
char				*history_content(t_history his);

void				his_new_line(char *line, char **cmd, t_cursor *pos);
char				*str_notnumber(char *keyword);
void				history_search(t_history his, char **s, char buf[6]);
void				his_putstr_term(int num_col, char *s,\
char *search, t_cursor *pos);
void				his_cursor_do(int nbr);
void				his_cursor_up(t_cursor pos, int nbr);
char				*history_expansion(t_history his, char *keyword);
char				is_shell_delimiter(char c);
char				*get_delimiter(char *keyword, int i);
char				*read_fc(void);
void				write_fc(char *content);
int					fc_flag_l(t_history history, unsigned char flags,
	char **args);
int					fc_built(char **args, t_history *history, char **tmp);
int					fc_flag_s(t_history *his, char *arg);
int					fc_flag_e(t_history his, char **args);
t_info				*fc_value(t_history his, char *keyword);
int					read_fc_flags(char **args, unsigned char *fl, char *err);
void				fc_usage(char c, char *msg);
int					fc_edit(t_history his,\
char *editor, unsigned char flags, char **args);
void				exec_fc(void);
void				init_fc_built();
void				tab_set_last_position(t_cursor pos, int num_lines);
void				new_pos_tab(char *s, int len, t_cursor *pos);
char				*put_tab(char *s, t_cursor *pos);
void				tab_mode(char **s);
void				ft_go_to_left(t_cursor *pos, char *s);
void				ft_go_to_right(t_cursor *pos, char *s);
void				ft_right_touch(t_cursor *pos, int size);
void				save_address(t_select **select);
void				initial_read_line(t_history *his, t_select **select);
char				*completing_line(char *str_cmds, t_select *select);
void				completing_line_(char **maps, char **cmd, t_select *slc,
	int bl);
int					read_quote(char **line, int quote, t_select *select,
	int bl);
int					read_subsh(char **line, t_select *select, int bl);
char				*shift_expansion(char *keyword, int *i);
int					is_expansion_syntax(char *cmd);

#endif
