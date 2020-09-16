//temporary until part of libft

#include "./includes/sh.h"

int	ft_putint(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

