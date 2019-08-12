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

void	permission(char *str)
{
	char		*tab;
	struct stat	sb;
	acl_t		acl;
	acl_entry_t	buff;
	ssize_t		xattr;

	xattr = 0;
	acl = NULL;
	tab = (char *)malloc(sizeof(char) * 12);
	acl = acl_get_link_np(str, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &buff) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(str, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		tab[10] = '@';
	else if (acl != NULL)
		tab[10] = '+';
	else
		tab[10] = ' ';
	if (acl)
		acl_free(acl);
	if (lstat(str, &sb) == 0)
	{
		if (S_ISBLK(sb.st_mode))
			tab[0] = 'b';
		if (S_ISCHR(sb.st_mode))
			tab[0] = 'c';
		if (S_ISDIR(sb.st_mode))
			tab[0] = 'd';
		if (S_ISFIFO(sb.st_mode))
			tab[0] = 'p';
		if (S_ISLNK(sb.st_mode))
			tab[0] = 'l';
		if (S_ISREG(sb.st_mode))
			tab[0] = '-';
		if (S_ISSOCK(sb.st_mode))
			tab[0] = 's';
		(sb.st_mode & S_IRUSR) ? (TAB(1, 'r')) : (TAB(1, '-'));
		(sb.st_mode & S_IWUSR) ? (TAB(2, 'w')) : (TAB(2, '-'));
		(sb.st_mode & S_IXUSR) ? (TAB(3, 'x')) : (TAB(3, '-'));
		(sb.st_mode & S_IRGRP) ? (TAB(4, 'r')) : (TAB(4, '-'));
		(sb.st_mode & S_IWGRP) ? (TAB(5, 'w')) : (TAB(5, '-'));
		(sb.st_mode & S_IXGRP) ? (TAB(6, 'x')) : (TAB(6, '-'));
		(sb.st_mode & S_IROTH) ? (TAB(7, 'r')) : (TAB(7, '-'));
		(sb.st_mode & S_IWOTH) ? (TAB(8, 'w')) : (TAB(8, '-'));
		(sb.st_mode & S_IXOTH) ? (TAB(9, 'x')) : (TAB(9, '-'));
		if (sb.st_mode & S_ISUID)
			(tab[3] == '-') ? (TAB(3, 'S')) : (TAB(3, 's'));
		if (sb.st_mode & S_ISGID)
			(tab[6] == '-') ? (TAB(6, 'S')) : (TAB(6, 's'));
		if (sb.st_mode & S_ISVTX)
			(tab[9] == '-') ? (TAB(9, 'T')) : (TAB(9, 't'));
		tab[11] = '\0';
		ft_putstr(tab);
		free(tab);
	}
}

int		nbr_len(long long n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

void	nbr_space(long long link, int max)
{
	int i;
	int l;

	i = 0;
	l = max - nbr_len(link) + 1;
	while (i < l)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(link);
}

void	uid_space(char *str, int max)
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

void	gid_space(char *str, int max)
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

void	max_total2(int maj_min, int d, int blks, t_max **max)
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
	while (node)
	{
		if (lstat((node)->path_name, &sb) == 0 && !(blks = 0))
		{
			max->nlink = MAX(nbr_len((long long)sb.st_nlink), max->nlink);
			max->uid = MAX(ft_strlen((getpwuid(sb.st_uid)->pw_name)), max->uid);
			max->gid = MAX(ft_strlen((getgrgid(sb.st_gid)->gr_name)), max->gid);
			max->size = MAX(nbr_len((long long)sb.st_size), max->size);
			max->min = MAX(nbr_len((long long)minor(sb.st_rdev)), max->min);
			max->maj = MAX(nbr_len((long long)major(sb.st_rdev)), max->maj);
			IF_ELS(S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode), m, 1, MAX(m, 0));
			blks = sb.st_blocks + blks;
		}
		node = node->next;
	}
	max_total2(m, d, blks, &max);
	return (blks);
}

void	ft_l_flag(t_dlist *head, char *tab, int d)
{
	t_dlist			*node;
	struct stat		sb;
	t_max			max;
	struct passwd	*pass;
	struct group	*grp;
	char			buff[1024];
	char			*tmp;
	ssize_t			link;
	time_t			current_time;

	if (tab[2] == 'l')
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
			permission(node->path_name);
			nbr_space(sb.st_nlink, max.nlink);
			pass = getpwuid(sb.st_uid);
			grp = getgrgid(sb.st_gid);
			uid_space(pass->pw_name, max.uid);
			gid_space(grp->gr_name, max.gid);
			if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode))
			{
				ft_putchar(' ');
				nbr_space(major(sb.st_rdev), max.maj);
				ft_putchar(',');
				nbr_space(minor(sb.st_rdev), max.min);
			}
			else
				nbr_space(sb.st_size, max.size);
			current_time = time(&current_time);
			if ((current_time - sb.st_mtime) < MONTHS_6 &&
				(current_time - sb.st_mtime) >= 0)
			{
				tmp = ft_strsub(ctime(&sb.st_mtime), 3, 13);
				ft_putstr(tmp);
				free(tmp);
			}
			else
			{
				tmp = ft_strsub(ctime(&sb.st_mtime), 3, 8);
				ft_putstr(tmp);
				free(tmp);
				tmp = ft_strsub(ctime(&sb.st_mtime), 19, 5);
				ft_putstr(tmp);
				free(tmp);
			}
			ft_putchar(' ');
			ft_putstr(node->name);
			if (S_ISLNK(sb.st_mode))
			{
				ft_putstr(" -> ");
				link = readlink(node->path_name, buff, 1023);
				buff[link] = '\0';
				ft_putstr(buff);
			}
			ft_putchar('\n');
			node = node->next;
		}
	}
	else
		print_list(head);
}
