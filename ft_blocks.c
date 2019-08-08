/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 00:29:30 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/28 00:29:32 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_blocks(t_dlist *node)
{
    unsigned long blks;

    blks = 0;
    while (node != NULL)
	{
	    struct  stat sb;

		lstat(node->path_name, &sb);
        blks = sb.st_blocks + blks;
		node = node->next;
	}
    return (blks);
}
