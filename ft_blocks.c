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

long long	ft_blocks(t_dlist *head)
{
	long long		blks;
	struct stat		sb;
	t_dlist			*node;

	blks = 0;
	node = head;
	while (node != NULL)
	{
		lstat(node->path_name, &sb);
		blks = sb.st_blocks + blks;
		node = node->next;
	}
	return (blks);
}
