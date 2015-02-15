/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 18:48:36 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/06 19:05:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		calc(t_lst **a_l)
{
	int		j;
	t_lst	*tmp;

	j = 0;
	tmp = *a_l;
	while (tmp && (tmp->file)[0] != '.')
	{
		j += (tmp->block);
		tmp = tmp->next;
	}
	ft_putnbr(j);
	ft_putchar('\n');
}

void		calc2(t_lst **a_l)
{
	int		j;
	t_lst	*tmp;

	j = 0;
	tmp = *a_l;
	while (tmp)
	{
		j += (tmp->block);
		tmp = tmp->next;
	}
	ft_putnbr(j);
	ft_putchar('\n');
}
