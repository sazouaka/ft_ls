/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:27:12 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:27:14 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_dlist *head, char c)
{
	t_dlist		*node;
	struct stat	sb;

	node = head;
	while (node)
	{
		if (c == 'G')
		{
			lstat(node->path_name, &sb);
			ft_putstr_clr(node->name, sb.st_mode);
		}
		else
			ft_putstr(node->name);
		ft_putchar('\n');
		node = node->next;
	}
}
