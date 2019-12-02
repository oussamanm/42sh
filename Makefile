
_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

NAME = 42sh

SRC = ./src/
OBJS = error_handler.o\
	variable.o shell.o signals.o lexer_h.o\
	lexer_call.o\
	lexer.o execution.o  exec_built.o quote.o\
	parser.o intern.o vrbs_parse.o expansion.o \
	utility/helper_func.o utility/new.o utility/new_.o\
	utility/free.o utility/free_.o utility/ft_strsplit.o\
	utility/find_closed.o utility/helper_exec.o\
	utility/helper_contin.o utility/helper_built.o\
	utility/line_contin.o utility/initial.o \
	utility/helper_variab.o\
	features/pipe.o features/line_continuation.o\
	features/proc_sub.o features/redir_parse.o\
	features/redir_read.o features/redir_setup.o\
	features/subshell.o features/logical_opr.o\
	builtins_cmds/built_env.o builtins_cmds/builtins.o\
	builtins_cmds/cd_built.o builtins_cmds/echo_built.o\
	builtins_cmds/echo_op_parser.o builtins_cmds/type_built.o\
	builtins_cmds/type_op_func.o builtins_cmds/type_op_parser.o\
	builtins_cmds/alias_built.o builtins_cmds/alias_func.o \
	builtins_cmds/hash_built.o builtins_cmds/hash_func.o\
	builtins_cmds/free_hash_and_alias.o builtins_cmds/unaliase_built.o\
	builtins_cmds/cd_built_symb.o builtins_cmds/built_srcs.o\
	builtins_cmds/built_export.o builtins_cmds/manage_export.o\
	read_line/addition.o\
	read_line/auto_completion.o\
	read_line/copy_paste.o\
	read_line/ctrl_d.o\
	read_line/delete.o\
	read_line/read_line.o\
	read_line/home_end.o\
	read_line/initial.o\
	read_line/move_by_lines.o\
	read_line/move_by_word.o\
	read_line/moving_cursor.o\
	read_line/output.o\
	read_line/reset_position.o\
	read_line/termcap.o\
	read_line/clear_readline.o\
	read_line/heredoc_line.o read_line/tab_mode.o\
	read_line/cut.o read_line/clear_line_or_window.o\
	read_line/tab_pos.o\
	history/history_expansion.o\
	history/history_file.o history/history_readline.o\
	history/manage_history.o history/history_other.o history/history_content.o\
	history/history_search.o history/history_handling.o history/history_termcap.o\
	fc_built/fc_built.o fc_built/fc_file.o fc_built/fc_flag_l.o\
	fc_built/fc_flags.o\
	job_control/add_remove.o job_control/jobs_built.o\
	job_control/fg_built.o job_control/bg_built.o\
	job_control/index_up.o job_control/init.o\
	job_control/job_execution.o job_control/job_processing.o\
	job_control/msg_sig.o job_control/output.o\
	job_control/update_status.o

FLAG = -Wall -Wextra -Werror 
INCL = ./includes
LIBFT_PATH = libs/libft/
LIBFT = libft.a

OBJS_21SH = $(addprefix ./src/, $(OBJS))


all : LBT $(NAME)

$(NAME) : $(OBJS_21SH) $(LIBFT_PATH)$(LIBFT)
	@echo "$(_lBLUE)gcc $(FLAG) -I $(INCL)  -I $(LIBFT_PATH) $(_END) $(_lGREEN)$(OBJS_21SH)$(_END) $(_lYELLOW)$(LIBFT_PATH)$(LIBFT)$(_END) -o $(_BOLD)$(NAME)$(_END) -ltermcap"
	@echo "$(_lGREEN)											"
	@echo "	 ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄         ▄ "
	@echo "	▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌"
	@echo "	▐░▌       ▐░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌       ▐░▌"
	@echo "	▐░▌       ▐░▌          ▐░▌▐░▌          ▐░▌       ▐░▌"
	@echo "	▐░█▄▄▄▄▄▄▄█░▌          ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌"
	@echo "	▐░░░░░░░░░░░▌ ▄▄▄▄▄▄▄▄▄█░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌"
	@echo "	 ▀▀▀▀▀▀▀▀▀█░▌▐░░░░░░░░░░░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌"
	@echo "	          ▐░▌▐░█▀▀▀▀▀▀▀▀▀           ▐░▌▐░▌       ▐░▌"
	@echo "	          ▐░▌▐░█▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌"
	@echo "	          ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌"
	@echo "	           ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀ "
	@echo "	                                                 $(_END)"
	@gcc $(FLAG) -I $(INCL) -I $(LIBFT_PATH) $(OBJS_21SH) $(LIBFT_PATH)$(LIBFT) -o $(NAME) -ltermcap

%.o : %.c
	@echo "$(_lGREEN)gcc $(FLAG) -I $(INCL) -I $(LIBFT_PATH) -c $< -o $@$(_END)"
	@gcc $(FLAG) -I $(INCL) -I $(LIBFT_PATH) -c $< -o $@

LBT :
	@echo "$(_lYELLOW)starting compile $(_RED)libft$(_END) librairie .. $(_END)"
	@echo "$(_lYELLOW)make -C $(LIBFT_PATH)$(_END)"
	@make -C $(LIBFT_PATH)

clean :
	@echo "\n$(_lCYAN)Makefile :$(_END) will delete $(_RED)$(OBJS_21SH) $(_END)and clean $(_RED)libft$(_END)"
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS_21SH)

fclean : clean
	@echo "\n$(_lCYAN)Makefile :$(_END) will delete $(_RED)$(NAME)$(_END) and $(_RED)$(LIBFT)$(_END)"
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re : fclean all
