/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:05:00 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:05:01 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//*************************//
//Function to sort by ascii//
//*************************//
void    ascii_sort(t_dlist *node)
{
    t_dlist *j;
    char *tmp;
    time_t  t_ime;
    char *path_name;

    while (node->next != NULL)
    {
        j = node->next;
        while (j != NULL)
        {
            if (ft_strcmp(node->name, j->name) > 0)
            {
                tmp = node->name;
                t_ime = node->mtime;
                path_name = ft_strdup(node->path_name);
                node->name = j->name;
                node->mtime= j->mtime;
                node->path_name = ft_strdup(j->path_name);
                j->name = tmp;
                j->mtime = t_ime;
                j->path_name = path_name;
            }
            j = j->next;
        }
        node = node->next;
    }
}

//**********************************//
//Function to sort by reversed ascii//
//**********************************//
void    ascii_sort_r(t_dlist *node)
{
    t_dlist *j;
    char    *name;
    time_t  t_ime;
    char *path_name;

    while (node->next != NULL)
    {
        j = node->next;
        while (j != NULL)
        {
            if (ft_strcmp(node->name, j->name) < 0)
            {
                name = ft_strdup(node->name);
                t_ime = node->mtime;
                path_name = ft_strdup(node->path_name);
                node->name = ft_strdup(j->name);
                node->mtime= j->mtime;
                node->path_name = ft_strdup(j->path_name);
                j->name = name;
                j->mtime = t_ime;
                j->path_name = path_name;
            }
            j = j->next;
        }
        node = node->next;
    }
}

int lexico(char *s1, char *s2)
{
    int tmp;
    int i;
    char *ss1;
    char *ss2;

    ss1 = ft_strdup(s1);
    ss2 = ft_strdup(s2);
    i = 0;
    while(ss1[i])
    {
        if (ss1[i] >= 'A' && ss1[i] <= 'Z')
            ss1[i] = ss1[i] + 32;
        i++;
    }
    i = 0;
    while(ss2[i])
    {
        if (ss2[i] >= 'A' && ss2[i] <= 'Z')
            ss2[i] = ss2[i] + 32;
        i++;
    }
    tmp = ft_strcmp(ss1, ss2);
    free(ss1);
    free(ss2);
    return (tmp);
}

//************************//
//Function to sort by time//
//************************//
void    sort_time(t_dlist *node)
{
    t_dlist *j;
    time_t  t_ime;
    char    *name;
    char *path_name;

    while (node->next != NULL)
    {
        j = node->next;
        while (j != NULL)
        {
            if (node->mtime < j->mtime)
            {
                name = ft_strdup(node->name);
                t_ime = node->mtime;
                path_name = ft_strdup(node->path_name);

                node->name = ft_strdup(j->name);
                node->mtime= j->mtime;
                node->path_name = ft_strdup(j->path_name);

                j->name = name;
                j->mtime = t_ime;
                j->path_name = path_name;
            }
            else if (node->mtime == j->mtime)
            {
                if (ft_strcmp(node->name,j->name) > 0)
                {
                    name = ft_strdup(node->name);
                    t_ime = node->mtime;
                    path_name = ft_strdup(node->path_name);

                    node->name = ft_strdup(j->name);
                    node->mtime= j->mtime;
                    node->path_name = ft_strdup(j->path_name);

                    j->name = name;
                    j->mtime = t_ime;
                    j->path_name = path_name;
                }
            }
            j = j->next;
        }
        node = node->next;
    }
}

//*********************************//
//Function to sort by reversed time//
//*********************************//
void    sort_r_time(t_dlist *node)
{
    t_dlist *j;
    time_t  t_ime;
    char    *name;
    char *path_name;

    while (node->next != NULL)
    {
        j = node->next;
        while (j != NULL)
        {
            if (node->mtime > j->mtime)
            {
                name = ft_strdup(node->name);
                t_ime = node->mtime;
                path_name = ft_strdup(node->path_name);
                node->name = ft_strdup(j->name);
                node->mtime= j->mtime;
                node->path_name = ft_strdup(j->path_name);
                j->name = name;
                j->mtime = t_ime;
                j->path_name = path_name;
            }
            else if (node->mtime == j->mtime)
            {
                if (ft_strcmp(node->name,j->name) < 0)
                {
                    name = ft_strdup(node->name);
                    t_ime = node->mtime;
                    path_name = ft_strdup(node->path_name);

                    node->name = ft_strdup(j->name);
                    node->mtime= j->mtime;
                    node->path_name = ft_strdup(j->path_name);

                    j->name = name;
                    j->mtime = t_ime;
                    j->path_name = path_name;
                }
            }
            j = j->next;
        }
        node = node->next;
    }
}   

//**********************************//
//Function to sort depending on flag//
//**********************************//
void    sort_by_flag(t_dlist *head, char r, char t)
{
    if (r != 'r' && t != 't')
        ascii_sort(head);
    else if (r == 'r' && t != 't')
        ascii_sort_r(head);
    else if (r != 'r' && t == 't')
        sort_time(head);
    else if (r == 'r' && t == 't')
        sort_r_time(head);
}