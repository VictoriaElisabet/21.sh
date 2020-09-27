# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 10:52:00 by vgrankul          #+#    #+#              #
#    Updated: 2020/09/16 15:21:57 by vgrankul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
SRC = shell.c environ.c functions.c help_functions.c ./lex_parse/*.c ./builtins/*.c ./line_edit/*.c ./execution/*.c
OBJECTS = shell.o create_command_list.o environ.o parameter_expansion.o tilde_expansion.o handle_command_list.o expansions.o exec.o functions.o builtins.o setenv.o unsetenv.o cd.o echo.o env.o exit.o pipe.o set_redirection.o tokens.o create_token_list.o create_redir.o create_word.o term.o sh.o key.o input.o motion.o copy.o history.o reprint.o putint.o qph_check.o esc_removal.o quote_removal.o redir_functions.o set_fd.o create_command_list_functions.o help_functions.o heredoc.o
INC = includes

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc -Wextra -Werror -Wall -c $(SRC)
	gcc -Wextra -Werror -Wall -ltermcap -I $(INC) $(OBJECTS) -L libft/ -lft -o $(NAME)

clean:
	make clean -C libft/
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all
