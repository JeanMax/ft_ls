/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:37:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/01/22 19:07:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free a link
*/

#include "libft.h"

void	ft_lfree(t_lst **lst)
{
	ft_memdel((void *)&((*lst)->user));
	ft_memdel((void *)&((*lst)->group));
	ft_memdel((void *)&((*lst)->dir));
	ft_memdel((void *)&((*lst)->file));
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
	ft_memdel((void *)lst);
}
