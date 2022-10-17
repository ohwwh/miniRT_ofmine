/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 10:40:10 by ohw               #+#    #+#             */
/*   Updated: 2022/07/27 13:17:05 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check(long nbr, int bs, int digit)
{
	if (nbr == 0)
		return (digit);
	return (check(nbr / bs, bs, digit + 1));
}

int	ft_checkdigit(long nbr, int bs)
{
	if (!nbr)
		return (1);
	else if (nbr < 0)
		return (check(-nbr, bs, 0));
	else
		return (check(nbr, bs, 0));
}
