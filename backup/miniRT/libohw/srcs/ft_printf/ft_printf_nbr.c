/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:59:50 by ohw               #+#    #+#             */
/*   Updated: 2022/07/27 13:24:29 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_di(long nbr)
{
	int	ret;

	ret = ft_checkdigit(nbr, 10);
	if (nbr < 0)
		ret ++;
	ft_putnbr_base_fd(nbr, 10, 0, 1);
	return (ret);
}

static int	print_u(long nbr)
{
	int	ret;

	ret = ft_checkdigit(nbr, 10);
	ft_putnbr_base_fd(nbr, 10, 0, 1);
	return (ret);
}

static int	print_x(long nbr)
{
	int	ret;

	ret = ft_checkdigit(nbr, 16);
	ft_putnbr_base_fd(nbr, 16, 0, 1);
	return (ret);
}

static int	print_upper_x(long nbr)
{
	int	ret;

	ret = ft_checkdigit(nbr, 16);
	ft_putnbr_base_fd(nbr, 16, 1, 1);
	return (ret);
}

int	nbr(va_list *app, const char **fmt)
{
	int	ret;

	if (**fmt == 'd' | **fmt == 'i')
		ret = print_di((long)(va_arg(*app, int)));
	else if (**fmt == 'u')
		ret = print_u((long)(va_arg(*app, unsigned int)));
	else if (**fmt == 'x')
		ret = print_x((long)(va_arg(*app, unsigned int)));
	else
		ret = print_upper_x((long)(va_arg(*app, unsigned int)));
	(*fmt)++;
	return (ret);
}
