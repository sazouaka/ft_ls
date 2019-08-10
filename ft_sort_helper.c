/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:37:48 by afaraji           #+#    #+#             */
/*   Updated: 2019/08/10 19:37:52 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap_sort(t_dlist *node, t_dlist *j)
{
	char	*name;
	char	*path_name;
	time_t	t_ime;

	name = node->name;
	t_ime = node->mtime;
	path_name = node->path_name;
	node->name = j->name;
	node->mtime = j->mtime;
	node->path_name = j->path_name;
	j->name = name;
	j->mtime = t_ime;
	j->path_name = path_name;
}
