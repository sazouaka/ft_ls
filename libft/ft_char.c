/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:03:35 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/04 17:03:37 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char(char *s, char c)
{
	int i;

	i = 0;
	if (s[0] == c)
	{
		return (1);
	}
	return (0);
}
