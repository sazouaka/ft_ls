/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 23:56:51 by afaraji           #+#    #+#             */
/*   Updated: 2019/08/12 23:56:53 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		uid_space(char *str, int max)
{
	int i;
	int l;

	i = 0;
	l = max - ft_strlen(str);
	ft_putchar(' ');
	ft_putstr(str);
	while (i < l)
	{
		ft_putchar(' ');
		i++;
	}
}

void		gid_space(char *str, int max)
{
	int i;
	int l;

	i = 0;
	l = max - ft_strlen(str) + 1;
	ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr(str);
	while (i < l)
	{
		ft_putchar(' ');
		i++;
	}
}

void		print_total(long long total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void		max_total2(int maj_min, int d, long long blks, t_max **max)
{
	((maj_min > -1) && d) ? print_total(blks) : 0;
	if (maj_min)
	{
		(*max)->maj = MAX((*max)->maj, (*max)->size - (*max)->min - 3);
		(*max)->size = MAX((*max)->size, (*max)->min + (*max)->maj + 3);
	}
}

long long	max_total(int d, t_dlist **head, t_max *max)
{
	t_dlist			*node;
	struct stat		sb;
	long long		blks;
	int				m;

	INIT(max->nlink, max->uid, max->gid, max->size, max->min, max->maj);
	node = *head;
	m = -1;
	blks = ft_blocks(node);
	while (node)
	{
		if (lstat((node)->path_name, &sb) == 0)
		{
			max->nlink = MAX(nbr_len((long long)sb.st_nlink), max->nlink);
			max->uid = MAX(ft_strlen((getpwuid(sb.st_uid)->pw_name)), max->uid);
			max->gid = MAX(ft_strlen((getgrgid(sb.st_gid)->gr_name)), max->gid);
			max->size = MAX(nbr_len((long long)sb.st_size), max->size);
			max->min = MAX(nbr_len((long long)minor(sb.st_rdev)), max->min);
			max->maj = MAX(nbr_len((long long)major(sb.st_rdev)), max->maj);
			IF_ELS(S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode), m, 1, MAX(m, 0));
		}
		node = node->next;
	}
	max_total2(m, d, blks, &max);
	return (blks);
}
