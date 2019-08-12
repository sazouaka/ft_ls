/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:52:57 by sazouaka          #+#    #+#             */
/*   Updated: 2018/10/11 12:51:17 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	long long x;

	if (n < 0)
	{
		ft_putchar('-');
		x = n * -1;
	}
	else
	{
		x = n;
	}
	if (x < 10)
	{
		ft_putchar(x + '0');
	}
	if (x >= 10)
	{
		ft_putnbr(x / 10);
		ft_putnbr(x % 10);
	}
}
