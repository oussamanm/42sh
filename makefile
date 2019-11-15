
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
	lexer.o execution.o  exec_built.o quote.o\
	parser.o intern.o vrbs_parse.o expansion.o \
	utility/helper_func.o utility/new.o\
	utility/free.o utility/ft_strsplit.o\
	utility/find_closed.o\
	features/pipe.o features/line_continuation.o\
	features/proc_sub.o features/redir_parse.o\
	features/redir_read.o features/redir_setup.o\
	features/subshell.o\
	builtins_cmd/built_env.o builtins_cmd/builtins.o\
	builtins_cmd/cd_built.o builtins_cmd/echo_built.o\
	builtins_cmd/echo_op_parser.o builtins_cmd/type_built.o\
	builtins_cmd/type_op_func.o builtins_cmd/type_op_parser.o\
	builtins_cmd/alias_built.o builtins_cmd/alias_func.o \
	builtins_cmd/hash_built.o builtins_cmd/hash_func.o \
	builtins_cmd/unaliase_built.o\
	read_line/addition.o\
	read_line/auto_completion.o\
	read_line/copy_paste.o\
	read_line/ctrl_d.o\
	read_line/delete.o\
	read_line/read_line.o\
	read_line/history.o\
	read_line/home_end.o\
	read_line/initial.o\
	read_line/move_by_lines.o\
	read_line/move_by_word.o\
	read_line/moving_cursor.o\
	read_line/output.o\
	read_line/reset_position.o\
	read_line/selection1.o\
	read_line/selection2.o\
	read_line/termcap.o\
	read_line/clear_readline.o\
	read_line/heredoc_line.o\
	read_line/cut.o\
	read_line/clear_line_or_window.o

FLAG = -Wall -Wextra -Werror 
INCL = ./includes
LIBFT_PATH = libs/libft/
LIBFT = libft.a

OBJS_21SH = $(addprefix ./src/, $(OBJS))


all : LBT $(NAME)

$(NAME) : $(OBJS_21SH) $(LIBFT_PATH)$(LIBFT)
	@echo "$(_lGREEN)										"
	@echo " ▄▄▄▄▄▄▄▄▄▄▄    ▄▄▄▄     ▄▄▄▄▄▄▄▄▄▄▄ ▄         ▄ "
	@echo "▐░░░░░░░░░░░▌ ▄█░░░░▌   ▐░░░░░░░░░░░▐░▌       ▐░▌"
	@echo " ▀▀▀▀▀▀▀▀▀█░▌▐░░▌▐░░▌   ▐░█▀▀▀▀▀▀▀▀▀▐░▌       ▐░▌"
	@echo "          ▐░▌ ▀▀ ▐░░▌   ▐░▌         ▐░▌       ▐░▌"
	@echo "          ▐░▌    ▐░░▌   ▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄█░▌"
	@echo " ▄▄▄▄▄▄▄▄▄█░▌    ▐░░▌   ▐░░░░░░░░░░░▐░░░░░░░░░░░▌"
	@echo "▐░░░░░░░░░░░▌    ▐░░▌    ▀▀▀▀▀▀▀▀▀█░▐░█▀▀▀▀▀▀▀█░▌"
	@echo "▐░█▀▀▀▀▀▀▀▀▀     ▐░░▌             ▐░▐░▌       ▐░▌"
	@echo "▐░█▄▄▄▄▄▄▄▄▄ ▄▄▄▄█░░█▄▄▄ ▄▄▄▄▄▄▄▄▄█░▐░▌       ▐░▌"
	@echo "▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░▌       ▐░▌"
	@echo " ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀         ▀  $(_END)"
	@echo "$(_lBLUE)gcc $(FLAG) -I $(INCL)  -I $(LIBFT_PATH) $(_END) $(_lGREEN)$(OBJS_21SH)$(_END) $(_lYELLOW)$(LIBFT_PATH)$(LIBFT)$(_END) -o $(_BOLD)$(NAME)$(_END) -ltermcap"
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


