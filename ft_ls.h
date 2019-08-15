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
# include <sys/ioctl.h>

# define FLAGS "RalrtgG1A"
# define MAX(m,n) (m > n) ? m : n
# define IFREE(m) (m != NULL) ? (free(m), (m = NULL)) : 0
# define TAB(i,c) tab[i] = c
# define IF_ELS(test, var, i, o) (test) ? (var = i) : (var = o)
# define INIT(a,b,c,d,e,f) a = b = c = d = e = f = 0
# define MONTHS_6 15724800
# define F_BLK  "\x1b[30m"
# define F_NRM  "\x1b[39m"
# define F_RED  "\x1B[31m"
# define F_GRN  "\x1B[32m"
# define F_YEL  "\x1B[33m"
# define F_BLU  "\x1B[34m"
# define F_MAG  "\x1B[35m"
# define F_CYN  "\x1B[36m"
# define F_WHT  "\x1B[37m"

# define B_BLK  "\x1b[40m"
# define B_NRM  "\x1b[49m"
# define B_RED  "\x1b[41m"
# define B_GRN  "\x1b[42m"
# define B_YEL  "\x1b[43m"
# define B_BLU  "\x1b[44m"
# define B_MAG  "\x1b[45m"
# define B_CYN  "\x1b[46m"
# define B_WHT  "\x1b[47m"

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
void				print_list(t_dlist *head, char c, char col);
void				ft_l_flag(t_dlist *head, char *tab, int d);
long long			ft_blocks(t_dlist *head);
t_dlist				*ft_ls(DIR *dir, char a, char *str, char aa);
t_dlist				*get_files(int index, char **argv, char *tab);
t_dlist				*get_dirs(int argc, char **argv, char *tab);
t_dlist				*get_file(char *str);
int					verify_type(char *str);
void				display_files(t_dlist *files, char *tab);
void				permission(char *str, mode_t mode, nlink_t nlink,
					t_max *max);
int					print_all(t_dlist *dirs, char *tab, t_dlist *tmp, int n_av);
void				ft_recursive_flag(t_dlist *head, char *tab);
char				*trim_path(char *str);
void				free_list(t_dlist *head);
void				free_list2(t_dlist *head);
void				uid_space(char *str, int max);
void				gid_space(char *str, int max, char c);
void				print_total(long long total);
void				max_total2(int maj_min, int d, long long blks, t_max **max);
long long			max_total(int d, t_dlist **head, t_max *max);
char				acl_attr(char *str);
char				file_type(mode_t mode);
int					nbr_len(long long n);
void				nbr_space(long long link, int max);
void				ft_putstr_clr(char *s, mode_t mode);
void				ft_sort_args(char **av, int i);
void				ft_putstr_error(char const *s);
void				print_list_colum(t_dlist *head, char c);
void				ft_putstr_clr_colum(char *s, char *f_color, char *b_color);
char				*get_f_color(mode_t mode);
char				*get_b_color(mode_t mode);
void				free_tab(char **tab);
void				free_tab_tab(char ***tab);
int					max_colum(int *nb, t_dlist *head, char c);
int					get_col(int max, int *r, int nb);
void				print_to_colum_clr(char ***tab, int row, int nb);
char				**ft_fill_clr(t_dlist *node, int max);
char				***list_to_clr(t_dlist *head, int max, int nb);
char				*ft_fill_end_space(char *src, int len);
int					cmp(char *s1, char *s2);

#endif
