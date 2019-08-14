/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 23:56:33 by afaraji           #+#    #+#             */
/*   Updated: 2019/08/12 23:56:39 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		acl_attr(char *str)
{
	acl_t		acl;
	acl_entry_t	buff;
	ssize_t		xattr;

	xattr = 0;
	acl = NULL;
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
		return ('@');
	else if (acl != NULL)
		return ('+');
	else
		return (' ');
	if (acl)
		acl_free(acl);
}

char		file_type(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISREG(mode))
		return ('-');
	if (S_ISSOCK(mode))
		return ('s');
	return ('?');
}

void		permission(char *str, mode_t mode, nlink_t nlink, t_max *max)
{
	char		*tab;

	tab = (char *)malloc(sizeof(char) * 12);
	tab[0] = file_type(mode);
	(mode & S_IRUSR) ? (TAB(1, 'r')) : (TAB(1, '-'));
	(mode & S_IWUSR) ? (TAB(2, 'w')) : (TAB(2, '-'));
	(mode & S_IXUSR) ? (TAB(3, 'x')) : (TAB(3, '-'));
	(mode & S_IRGRP) ? (TAB(4, 'r')) : (TAB(4, '-'));
	(mode & S_IWGRP) ? (TAB(5, 'w')) : (TAB(5, '-'));
	(mode & S_IXGRP) ? (TAB(6, 'x')) : (TAB(6, '-'));
	(mode & S_IROTH) ? (TAB(7, 'r')) : (TAB(7, '-'));
	(mode & S_IWOTH) ? (TAB(8, 'w')) : (TAB(8, '-'));
	(mode & S_IXOTH) ? (TAB(9, 'x')) : (TAB(9, '-'));
	if (mode & S_ISUID)
		(tab[3] == '-') ? (TAB(3, 'S')) : (TAB(3, 's'));
	if (mode & S_ISGID)
		(tab[6] == '-') ? (TAB(6, 'S')) : (TAB(6, 's'));
	if (mode & S_ISVTX)
		(tab[9] == '-') ? (TAB(9, 'T')) : (TAB(9, 't'));
	tab[10] = acl_attr(str);
	tab[11] = '\0';
	ft_putstr(tab);
	IFREE(tab);
	nbr_space(nlink, max->nlink);
}

int			nbr_len(long long n)
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

void		nbr_space(long long link, int max)
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
