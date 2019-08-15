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

int		cmp(char *s1, char *s2)
{
	return (ft_strcmp(trim_path(s1), s2));
}

void	ft_r_helper(t_dlist *head_r, t_dlist *node, char *tab)
{
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

void	p_denided(char *str)
{
	ft_putchar('\n');
	ft_putstr(str);
	ft_putstr(":\n");
	ft_putstr_error("./ft_ls: ");
	perror(trim_path(str));
}

void	ft_recursive_flag(t_dlist *head, char *tab)
{
	t_dlist	*node;
	DIR		*d;

	node = head;
	while (node)
	{
		if (verify_type(node->path_name) == 1)
		{
			if (cmp((node->name), ".") == 0 || cmp((node->name), "..") == 0)
			{
				node = node->next;
				continue;
			}
			if ((d = opendir(node->path_name)) == NULL)
				p_denided(node->path_name);
			else
				ft_r_helper(ft_ls(d, tab[1], node->path_name,
					tab[8]), node, tab);
		}
		node = node->next;
	}
}
