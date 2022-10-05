/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdigit_address.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:45:22 by ohw               #+#    #+#             */
/*   Updated: 2022/07/27 13:17:24 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check(unsigned long n, int digit)
{
	if (n == 0)
		return (digit);
	return (check(n / 16, digit + 1));
}

int	ft_checkdigit_address(void *p)
{
	unsigned long	n;

	n = (unsigned long)p;
	if (!n)
		return (1);
	else
		return (check(n, 0));
}
