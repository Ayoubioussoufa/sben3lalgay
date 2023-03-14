CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g2
READ = -L/goinfre/sben-ela/homebrew/opt/readline/lib
INCLUDE = -I/goinfre/sben-ela/homebrew/opt/readline/include
PROG = minishell
LIBFT = Libft/libft.a
PARSING = handle_quotes.c  expanding.c  parse.c parse_read.c parse_line.c  signals.c
BUILTIN = cd_builtin.c echo_builtin.c env_builtin.c exit_builtin.c export_builtin.c pwd_builtin.c unset_builtin.c
UTILS = env_utils.c  environment.c  ft_error.c  ft_split_v2.c utils1.c utils2.c utils3.c \
	env_utils2.c env_utils3.c  echo_utils.c  export_utils.c  exit_utils.c  init.c
EXECUTE = ft_execute.c  redirection.c  if_builtin.c  here_doc.c  execute_cmd.c 
SOURCES = $(addprefix ./parsing/,$(PARSING))\
	$(addprefix ./builtin/,$(BUILTIN))\
	$(addprefix ./utils/,$(UTILS))\
	$(addprefix ./execute/,$(EXECUTE))\
	$(LIBFT)\
	mini_shell.c 

OBJECTS = $(SOURCES:.c=.o)

all : $(PROG)
$(PROG) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJECTS) -lreadline $(READ)
	rm -f $(OBJECTS)
	make -C libft clean

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(LIBFT) :
	make -C ./Libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(PROG) $(LIBFT)
	make -C libft fclean

bonus: all
	ar rc $(NAME)

re: fclean all