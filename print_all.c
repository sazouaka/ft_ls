/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:29:33 by sazouaka          #+#    #+#             */
/*   Updated: 2019/08/06 21:29:35 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
char *trim_path(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    while (i && str[i - 1] != '/')
        i--;
    return (str + i);
    
}

// void    print_dirs(t_dlist *dirs, DIR *d, char *tab, t_dlist *tmp_file)
// {
   

    
// }

int    print_all(t_dlist  *dirs, char *tab, t_dlist  *tmp_file)
{
    t_dlist *head;
    t_dlist  *tmp_dirs = NULL;
    DIR *d;
    int i;

    tmp_dirs = dirs;
    sort_by_flag(dirs, tab[3], tab[4]);
    i = 0;
    while(dirs)
    {
        if (i != 0 || tmp_file)
            ft_putchar('\n');
        if (tmp_file || tmp_dirs->next)
        {
            ft_putstr(dirs->name);
            ft_putstr(":\n");
            i = 1;
        }
        if ((d = opendir(dirs->name)) == NULL)
        {
            ft_putstr("./ft_ls: ");
            perror(trim_path(dirs->path_name));
            dirs = dirs->next;
            continue;
        }
        //printf("--------------- 1 >>>>> heeere fucking error\n");
        head = ft_ls(d, tab[1], dirs->name);
        if (head)
        {
            ascii_sort(head);
            sort_by_flag(head, tab[3], tab[4]);
            ft_l_flag(head, tab, 1);
            //printf("--------------- 2 >>>>> heeere fucking error\n");
            if (tab[0] == 'R')
            {
                //printf("--------------- 3 >>>>> heeere fucking error\n");
                ft_R_flag(head, tab);
            }
        }
        dirs = dirs->next;
    }
    return (0);
}