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

void	ft_sort_args(char **av, int index)
{
	char	*tmp;
	int		i;
	int		j;

	i = index;
	while (av[i + 1])
	{
		j = i + 1;
		while (av[j])
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
			j++;
		}
		i++;
	}
	if (ft_strcmp(av[index], "") == 0)
	{
		ft_putstr("./ft_ls: fts_open: No such file or directory\n");
		exit(0);
	}
}
