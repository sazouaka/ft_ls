/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 18:29:17 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/07 18:29:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*a;
	size_t	i;
	char	*s;

	s = (char *)s1;
	i = 0;
	while (s[i])
		i++;
	a = (char *)malloc(sizeof(*s) * (i + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
