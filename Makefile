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
SRC = minishell.c create_command_list.c environ.c parameter_expansion.c tilde_expansion.c handle_command_list.c expansions.c exec.c functions.c ./builtins/builtins.c ./builtins/setenv.c ./builtins/unsetenv.c ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/exit.c pipe.c set_redirection.c tokens.c create_token_list.c create_redir.c create_word.c term.c sh.c key.c input.c motion.c copy.c history.c reprint.c putint.c qph_check.c 
OBJECTS = minishell.o create_command_list.o environ.o parameter_expansion.o tilde_expansion.o handle_command_list.o expansions.o exec.o functions.o builtins.o setenv.o unsetenv.o cd.o echo.o env.o exit.o pipe.o set_redirection.o tokens.o create_token_list.o create_redir.o create_word.o term.o sh.o key.o input.o motion.o copy.o history.o reprint.o putint.o qph_check.o
INC = includes

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc -Wextra -Werror -Wall -c $(SRC) -g
	gcc -Wextra -Werror -Wall -ltermcap -I $(INC) $(OBJECTS) -L libft/ -lft -o $(NAME) -g

clean:
	make clean -C libft/
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all
