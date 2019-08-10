/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 21:11:08 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/03 21:13:01 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <time.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>

# define FLAGS "Ralrt"
# define MAX(m,n) (m > n) ? m : n
# define MONTHS_6 15724800

typedef struct		s_dlist
{
	char			*name;
	char			*path_name;
	time_t			mtime;
	struct s_dlist	*next;

}					t_dlist;

typedef	struct		s_max
{
	int				nlink;
	int				uid;
	int				gid;
	int				size;
	int				min;
	int				maj;
}					t_max;

t_dlist				*get_one_file(char *str, char *s2);
void				ascii_sort(t_dlist *node);
void				ascii_sort_r(t_dlist *node);
void				sort_time(t_dlist *node);
void				sort_r_time(t_dlist *node);
void				sort_by_flag(t_dlist *head, char r, char t);
void				ft_swap_sort(t_dlist *node, t_dlist *j);
int					flag_search(char c);
char				*get_flag_tab(int ac, char **av, int *index);
void				print_list(t_dlist *head);
void				ft_l_flag(t_dlist *head, char *tab, int d);
int					ft_blocks(t_dlist *head);
t_dlist				*ft_ls(DIR *dir, char a, char *str);
t_dlist				*get_files(int index, char **argv, char *tab);
t_dlist				*get_dirs(int argc, char **argv, char *tab);
t_dlist				*get_file(char *str);
int					verify_type(char *str);
void				display_files(t_dlist *files, char *tab);
void				permission(char *str);
int					print_all(t_dlist *dirs, char *tab, t_dlist *tmp_file);
void				ft_recursive_flag(t_dlist *head, char *tab);
char				*trim_path(char *str);
void				free_list(t_dlist *head);

#endif
