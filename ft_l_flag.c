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

//****************************//
//Function to get ls -l result//
//****************************//
void	permission(char *str)
{
	char    *tab;
	struct  stat sb;
	acl_t acl = NULL;
    acl_entry_t buff;
    ssize_t xattr = 0;

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
	if(lstat(str, &sb) == 0)
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
		(sb.st_mode & S_IRUSR) ? (tab[1] = 'r') : (tab[1] = '-');
		(sb.st_mode & S_IWUSR) ? (tab[2] = 'w') : (tab[2] = '-');
		(sb.st_mode & S_IXUSR) ? (tab[3] = 'x') : (tab[3] = '-');
		(sb.st_mode & S_IRGRP) ? (tab[4] = 'r') : (tab[4] = '-');
		(sb.st_mode & S_IWGRP) ? (tab[5] = 'w') : (tab[5] = '-');
		(sb.st_mode & S_IXGRP) ? (tab[6] = 'x') : (tab[6] = '-');
		(sb.st_mode & S_IROTH) ? (tab[7] = 'r') : (tab[7] = '-');
		(sb.st_mode & S_IWOTH) ? (tab[8] = 'w') : (tab[8] = '-');
		(sb.st_mode & S_IXOTH) ? (tab[9] = 'x') : (tab[9] = '-');
		if (sb.st_mode & S_ISUID)
			(tab[3] == '-') ? (tab[3] = 'S') : (tab[3] = 's');
		if (sb.st_mode & S_ISGID)
			(tab[6] == '-') ? (tab[6] = 'S') : (tab[6] = 's');
		if (sb.st_mode & S_ISVTX)
			(tab[9] == '-') ? (tab[9] = 'T') : (tab[9] = 't');
		tab[11] = '\0';
		ft_putstr(tab);
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

	i = 0;
	while (i < max - nbr_len(link) + 1)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(link);

}

void	uid_space(char *str, int max)
{
	int i;

	i = 0;
	
	ft_putchar(' ');
	ft_putstr(str);
	while (i < max - ft_strlen(str))
	{
		ft_putchar(' ');
		i++;
	}
}

void	gid_space(char *str, int max)
{
	int i;

	i = 0;
	
	ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr(str);
	while (i < max - ft_strlen(str) + 1)
	{
		ft_putchar(' ');
		i++;
	}
}

void    ft_l_flag(t_dlist *head, char *tab, int d)
{
	t_dlist *node;
	t_dlist *node2;
	struct  stat sb;
	t_max	max = {0,0,0,0,0,0};
	struct  passwd  *pass;
	struct  group   *grp;
	char    buff[1024];
	ssize_t	link;
	int maj_min = 0;
	time_t	current_time;
	
	if (tab[2] == 'l')
	{
		node2 = head;
		if (d && lstat(node2->path_name, &sb) == 0)
		{
			ft_putstr("total ");
			ft_putnbr(ft_blocks(node2));
			ft_putchar('\n');
		}
		node = head;
		while (node)
		{
			lstat(node->path_name, &sb);
			if(nbr_len((long long)sb.st_nlink) > max.nlink)
				max.nlink = nbr_len((long long)sb.st_nlink);
			if (ft_strlen((getpwuid(sb.st_uid)->pw_name)) > max.uid)
				max.uid = ft_strlen((getpwuid(sb.st_uid)->pw_name));
			if (ft_strlen((getgrgid(sb.st_gid)->gr_name)) > max.gid)
				max.gid = ft_strlen((getgrgid(sb.st_gid)->gr_name));
			if (nbr_len((long long)sb.st_size) > max.size)
				max.size = nbr_len((long long)sb.st_size);
			if (nbr_len((long long)minor(sb.st_rdev)) > max.min)
				max.min = nbr_len((long long)minor(sb.st_rdev));
			if (nbr_len((long long)major(sb.st_rdev)) > max.maj)
				max.maj = nbr_len((long long)major(sb.st_rdev));
			if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode))
				maj_min = 1;
			node = node->next;
		}
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
			if (maj_min)
			{
				max.maj = MAX(max.maj, max.size - max.min - 3);
				max.size = MAX(max.size, max.min + max.maj + 3);
			}
			if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode))
			{
				ft_putchar(' ');
				nbr_space(major(sb.st_rdev) ,max.maj);
				ft_putchar(',');
				nbr_space(minor(sb.st_rdev) ,max.min);
			}
			else
				nbr_space(sb.st_size, max.size);
			current_time = time(&current_time);
			if ((current_time - sb.st_mtime) < 15552000 && (current_time - sb.st_mtime) >= 0)
				ft_putstr(ft_strsub(ctime(&sb.st_mtime), 3, 13));
			else 
			{
				ft_putstr(ft_strsub(ctime(&sb.st_mtime), 3, 8));
				ft_putstr(ft_strsub(ctime(&sb.st_mtime), 19, 5));
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
