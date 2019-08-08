/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:22:57 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:22:59 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//*****************************//
//Function to search for a flag//
//*****************************//
int flag_search(char c)
{
    int i;

    char *str = "Ralrt";
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

//************************************//
//Function to get table of flags Ralrt//
//************************************//
char    *get_flag_tab(int ac, char **av, int *index)
{
    int i;
    int j;
    int z;
    char *tab;

    tab = (char *)malloc(sizeof(char) * 5);
    i = 0;
    while (i < 5)
        tab[i++] = '0';
    i = 1;
    while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
    {
        if (av[i][1] == '-')
        {
            if (av[i][2] == '\0')
            {
                i++;
                break;
            }
            else
            {
                ft_putstr("./ft_ls: illegal option -- -\n");
                ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
                exit(1);
            }
        }
        z = 1;
        while (av[i][z])
        {
            j = flag_search(av[i][z]);
            if (j == -1)
            {
                printf("./ft_ls: illegal option -- %c\n", av[i][z]);
                printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
                exit(1);
            }
            else
                tab[j] = av[i][z];
            z++;
        }
        i++;
    }
    *index = i;
    return (tab);
}
