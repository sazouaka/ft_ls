/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 00:02:38 by sazouaka          #+#    #+#             */
/*   Updated: 2019/08/07 00:02:39 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_recursive_flag(t_dlist *head, char *tab)
{
	t_dlist	*head_r;
	t_dlist	*node;
	DIR		*d;

	node = head;
	while (node)
	{
		if (verify_type(node->path_name) == 1)
		{
			if (ft_strcmp(trim_path(node->name), ".") == 0 ||
			ft_strcmp(trim_path(node->name), "..") == 0)
			{
				node = node->next;
				continue;
			}
			if ((d = opendir(node->path_name)) == NULL)
			{
				ft_putchar('\n');
				ft_putstr(node->path_name);
				ft_putstr(":\n./ft_ls: ");
				perror(trim_path(node->path_name));
				node = node->next;
				continue;
			}
			head_r = ft_ls(d, tab[1], node->path_name);
			ft_putchar('\n');
			ft_putstr(node->path_name);
			ft_putstr(":\n");
			if (head_r)
			{
				ascii_sort(head_r);
				sort_by_flag(head_r, tab[3], tab[4]);
				ft_l_flag(head_r, tab, 1);
				ft_recursive_flag(head_r, tab);
				free_list(head_r);
			}
		}
		node = node->next;
	}
}
