/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:25:39 by hoh               #+#    #+#             */
/*   Updated: 2022/07/27 13:27:16 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getbuf(int n, int base)
{
	int	buf;

	buf = 1;
	if (n <= 0)
	{	
		buf ++;
		n *= -1;
	}
	while (n)
	{
		n /= base;
		buf ++;
	}
	return (buf);
}

char	*ft_itoa_base(int n, int base, int capital)
{
	int		buf;
	long	temp;
	char	*ret;

	if (n >= 0)
		temp = n;
	else
		temp = -(long)n;
	ret = (char *)malloc(sizeof(char) * (buf = getbuf(n, base)));
	ret[(buf--) - 1] = 0;
	while (temp)
	{
		if (temp % 10 >= 10 && !capital)
			ret[(buf--) - 1] = temp % base + 87;
		else if (temp % 10 >= 10 && capital)
			ret[(buf--) - 1] = temp % base + 55;
		else
			ret[(buf--) - 1] = temp % base + '0';
		temp /= base;
	}
	if (n < 0)
		ret[buf - 1] = '-';
	else if (n == 0)
		ret[buf - 1] = '0';
	return (ret);
}
