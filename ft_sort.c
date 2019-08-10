/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:05:00 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:05:01 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ascii_sort(t_dlist *node)
{
	t_dlist	*j;
	char	*tmp;
	time_t	t_ime;

	while (node->next != NULL)
	{
		j = node->next;
		while (j != NULL)
		{
			if (ft_strcmp(node->name, j->name) > 0)
			{
				tmp = node->name;
				t_ime = node->mtime;
				node->name = j->name;
				node->mtime = j->mtime;
				j->name = tmp;
				j->mtime = t_ime;
				tmp = node->path_name;
				node->path_name = j->path_name;
				j->path_name = tmp;
			}
			j = j->next;
		}
		node = node->next;
	}
}

void	ascii_sort_r(t_dlist *node)
{
	t_dlist *j;
	char	*name;
	time_t	t_ime;

	while (node->next != NULL)
	{
		j = node->next;
		while (j != NULL)
		{
			if (ft_strcmp(node->name, j->name) < 0)
			{
				name = node->name;
				t_ime = node->mtime;
				node->name = j->name;
				node->mtime = j->mtime;
				j->name = name;
				j->mtime = t_ime;
				name = node->path_name;
				node->path_name = j->path_name;
				j->path_name = name;
			}
			j = j->next;
		}
		node = node->next;
	}
}

void	sort_time(t_dlist *node)
{
	t_dlist *j;

	while (node->next != NULL)
	{
		j = node->next;
		while (j != NULL)
		{
			if (node->mtime < j->mtime)
			{
				ft_swap_sort(node, j);
			}
			else if (node->mtime == j->mtime)
			{
				if (ft_strcmp(node->name, j->name) > 0)
				{
					ft_swap_sort(node, j);
				}
			}
			j = j->next;
		}
		node = node->next;
	}
}

void	sort_r_time(t_dlist *node)
{
	t_dlist *j;

	while (node->next != NULL)
	{
		j = node->next;
		while (j != NULL)
		{
			if (node->mtime > j->mtime)
			{
				ft_swap_sort(node, j);
			}
			else if (node->mtime == j->mtime)
			{
				if (ft_strcmp(node->name, j->name) < 0)
				{
					ft_swap_sort(node, j);
				}
			}
			j = j->next;
		}
		node = node->next;
	}
}

void	sort_by_flag(t_dlist *head, char r, char t)
{
	if (r != 'r' && t != 't')
		ascii_sort(head);
	else if (r == 'r' && t != 't')
		ascii_sort_r(head);
	else if (r != 'r' && t == 't')
		sort_time(head);
	else if (r == 'r' && t == 't')
		sort_r_time(head);
}
