/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greatest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:17:58 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/15 19:18:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_lst		*grt(t_lst **a_l, int what, int i)
{
	t_lst	*greatest;
	t_lst	*tmp;

	tmp = *a_l;
	greatest = tmp;
	while (tmp)
	{
		if (what == 1)
			if (ft_strlen(tmp->user) > ft_strlen(greatest->user))
				greatest = tmp;
		if (what == 2)
		{
			((i) && ((tmp->link > greatest->link) && !ft_ishidden(tmp->file)))\
				? greatest = tmp : NULL;
			((!i) && (tmp->link > greatest->link)) ? greatest = tmp : NULL;
		}
		if (what == 3)
			if (ft_strlen(tmp->group) > ft_strlen(greatest->group))
				greatest = tmp;
		tmp = tmp->next;
	}
	return (greatest);
}

t_lst		*grt2(t_lst **a_l, int what, int i)
{
	t_lst	*greatest;
	t_lst	*tmp;

	tmp = *a_l;
	greatest = tmp;
	while (tmp)
	{
		if (what == 0)
		{
			((!i) && (tmp->size > greatest->size)) ? greatest = tmp : NULL;
			((i) && ((tmp->size > greatest->size) && !ft_ishidden(tmp->file)))\
				? greatest = tmp : NULL;
		}
		if (what == 1)
		{
			if (tmp->mode2 > greatest->mode2)
				greatest = tmp;
		}
		tmp = tmp->next;
	}
	return (greatest);
}

int			ft_ishidden(char *str)
{
	if (str[0] == '.')
		return (1);
	else
		return (0);
}
