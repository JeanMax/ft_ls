/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:37:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 17:53:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free a link
*/

#include "libft.h"

void	ft_lfree(t_lst **lst)
{
	(*lst)->user ? ft_memdel((void *)&((*lst)->user)) : NULL;
	(*lst)->group ? ft_memdel((void *)&((*lst)->group)) : NULL;
	(*lst)->dir ? ft_memdel((void *)&((*lst)->dir)) : NULL;
	(*lst)->file ? ft_memdel((void *)&((*lst)->file)) : NULL;
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
	ft_memdel((void *)lst);
	*lst = NULL;
	lst = NULL;
}
