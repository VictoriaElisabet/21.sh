/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:26:47 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/25 11:55:08 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

typedef struct	s_format
{
	int		f_hash;
	int		f_zero;
	int		f_minus;
	int		f_plus;
	int		f_space;
	int		width;
	int		prec;
	int		precision;
	char	length[3];
	char	conv_char;

}				t_format_struct;

void			ft_set_to_zero (t_format_struct *new);
void			ft_set_flag(char c, t_format_struct *new);
void			fill_struct(const char *format, t_format_struct *new, int i,
				va_list ap);
void			octal_hash_exception(char *str, t_format_struct *new);

int				ft_is_flag(char c);
int				ft_is_conv_char(char c);
int				count_to_dot(char *str);
int				format_strlen(const char *format);
int				ft_set_length(const char *format, t_format_struct *new);
int				create_struct(const char *format, va_list ap);
int				ft_vfprintf(const char *format, va_list ap);
int				ft_printf(const char *format, ...);
int				ft_check_flags_diouxx(char *str, t_format_struct *new);
int				ft_check_flags_float(char *str, t_format_struct *new);
int				ft_check_flags_char(char n, t_format_struct *new);
int				ft_check_flags_string(char *str, t_format_struct *new);
int				ft_va_arg_float(t_format_struct *new, va_list ap);
int				ft_va_arg_char(t_format_struct *new, va_list ap);
int				ft_va_arg_string(t_format_struct *new, va_list ap);
int				ft_va_arg_mem(t_format_struct *new, va_list ap);
int				ft_va_arg_int(t_format_struct *new, va_list ap);
int				ft_va_arg_octal(t_format_struct *new, va_list ap);
int				ft_va_arg_unsigned_int(t_format_struct *new, va_list ap);
int				ft_va_arg_hex(t_format_struct *new, va_list ap,
				unsigned long long n);
int				ft_check_conv_char(t_format_struct *new, va_list ap);
int				set_len(long long first, long long second, long double nb);
int				check_asterisk(va_list ap);
int				create_struct(const char *format, va_list ap);

char			*ft_add_ox(char *str, t_format_struct *new);
char			*ft_add_zero_diouxx(char *str, int len, int preclen);
char			*ft_set_space(char *str, t_format_struct *new, char sign);
char			*ft_set_sign(char *str, char sign);
char			*ft_copy_string(char *str, int len);
char			*ft_add_zero_float(char *str, int len, int dotlen, int i);
char			*ft_copy_string_float(char *str, t_format_struct *new,
				int dotlen);
char			*ft_itoa_double(double n, int precision, t_format_struct *new);
char			*ft_itoa_long_double(long double n, int precision,
				t_format_struct *new);
char			*diouxx_width(char *str, t_format_struct *new);
char			*diouxx_prec(char *str, t_format_struct *new);
char			*plus_sign(char *str, t_format_struct *new);
char			*long_double(long double n, int precision,
				t_format_struct *new);
char			*double_float(double n, int precision, t_format_struct *new);
#endif
