/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 12:17:30 by sazouaka          #+#    #+#             */
/*   Updated: 2018/10/21 14:37:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str)
	{
		i = 0;
		while (i < len && s[start] != '\0')
		{
			str[i] = s[start];
			start++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (0);
}
