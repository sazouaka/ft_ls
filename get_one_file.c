/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_one_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:51:58 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 16:52:00 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//****************************//
//Function to get list element//
//****************************//
t_dlist *get_one_file(char *str, char *s2)
{
    t_dlist *files;
    struct stat st;

    lstat(s2, &st);
    files = (t_dlist *)malloc(sizeof(t_dlist));
    files->mtime = st.st_mtime;
    files->name = ft_strdup(str);
    files->path_name = ft_strdup(s2);
    files->next = NULL;
    return (files);
}
