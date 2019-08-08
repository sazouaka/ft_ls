/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:27:12 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:27:14 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//**********************//
//Function to print list//
//**********************//
void    print_list(t_dlist *head)
{
    t_dlist *node;

    node = head;
    while(node)
    {
        ft_putstr(node->name);
        ft_putchar('\n');
        node = node->next;
    }
}