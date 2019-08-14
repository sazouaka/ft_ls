/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:33:36 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 23:34:40 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		uid_gid(t_max *max, char *tab, uid_t uid, gid_t gid)
{
	struct passwd	*pass;
	struct group	*grp;

	pass = getpwuid(uid);
	grp = getgrgid(gid);
	if (tab[5] != 'g')
		uid_space(pass->pw_name, max->uid);
	gid_space(grp->gr_name, max->gid, tab[5]);
}

void		size_maj_min(t_max *max, mode_t mode, dev_t rdev, off_t size)
{
	if (S_ISBLK(mode) || S_ISCHR(mode))
	{
		ft_putchar(' ');
		nbr_space(major(rdev), max->maj);
		ft_putchar(',');
		nbr_space(minor(rdev), max->min);
	}
	else
		nbr_space(size, max->size);
}

void		mtime(time_t mtime, char *date)
{
	time_t	current_time;
	char	*tmp;

	current_time = time(&current_time);
	if ((current_time - mtime) < MONTHS_6 &&
		(current_time - mtime) >= 0)
	{
		tmp = ft_strsub(date, 3, 13);
		ft_putstr(tmp);
		IFREE(tmp);
	}
	else
	{
		tmp = ft_strsub(date, 3, 8);
		ft_putstr(tmp);
		IFREE(tmp);
		tmp = ft_strsub(date, 19, 5);
		ft_putstr(tmp);
		IFREE(tmp);
	}
}

void		name_link(char *name, char *path, mode_t mode)
{
	char	buff[1024];
	ssize_t	link;

	ft_putchar(' ');
	ft_putstr(name);
	if (S_ISLNK(mode))
	{
		ft_putstr(" -> ");
		link = readlink(path, buff, 1023);
		buff[link] = '\0';
		ft_putstr(buff);
	}
	ft_putchar('\n');
}

void		ft_l_flag(t_dlist *head, char *tab, int d)
{
	t_dlist			*node;
	struct stat		sb;
	t_max			max;

	if (tab[2] == 'l' || tab[5] == 'g')
	{
		max_total(d, &head, &max);
		node = head;
		while (node)
		{
			if (lstat(node->path_name, &sb) < 0)
			{
				node = node->next;
				continue;
			}
			permission(node->path_name, sb.st_mode, sb.st_nlink, &max);
			uid_gid(&max, tab, sb.st_uid, sb.st_gid);
			size_maj_min(&max, sb.st_mode, sb.st_rdev, sb.st_size);
			mtime(sb.st_mtime, ctime(&sb.st_mtime));
			name_link(node->name, node->path_name, sb.st_mode);
			node = node->next;
		}
	}
	else
		print_list(head);
}
