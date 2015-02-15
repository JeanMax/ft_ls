/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:15:38 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/15 19:15:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_lst		*sort_name(t_lst **a_l)
{
	size_t	size;
	size_t	size_swap;

	size = ft_llen(a_l);
	while (size)
	{
		size_swap = size - 1;
		while (size_swap)
		{
			if (ft_strcmp(ft_lat(a_l, size)->file,
						ft_lat(a_l, size_swap)->file) > 0)
				ft_lswap(ft_lat(a_l, size), ft_lat(a_l, size_swap));
			if (!ft_lisfirst(a_l))
				*a_l = ft_lfirst(a_l);
			size_swap--;
		}
		size--;
	}
	return (*a_l);
}

t_lst		*sort_date(t_lst **a_l)
{
	size_t	size;
	size_t	size_swap;

	size = ft_llen(a_l);
	while (size)
	{
		size_swap = size;
		while (size_swap--, size_swap)
		{
			if (ft_lat(a_l, size)->date
					< (ft_lat(a_l, size_swap))->date)
				ft_lswap(ft_lat(a_l, size), ft_lat(a_l, size_swap));
			else if (ft_lat(a_l, size)->date
					== (ft_lat(a_l, size_swap))->date)
			{
				if (ft_strcmp(ft_lat(a_l, size)->file,
							ft_lat(a_l, size_swap)->file) > 0)
					ft_lswap(ft_lat(a_l, size), ft_lat(a_l, size_swap));
			}
			if (!ft_lisfirst(a_l))
				*a_l = ft_lfirst(a_l);
		}
		size--;
	}
	return (*a_l);
}

static void	sort_av_date(int j, char **a)
{
	struct stat	s1;
	struct stat s2;
	int			i;
	char		*swap;

	while (j)
	{
		i = j - 1;
		while (i)
		{
			lstat(a[i], &s1);
			lstat(a[j], &s2);
			if (a[i][0] != '-' && a[j][0] != '-' && s1.st_mtime < s2.st_mtime)
			{
				swap = a[j];
				a[j] = a[i];
				a[i] = swap;
			}
			i--;
		}
		j--;
	}
}

static void	sort_av_rev(int j, char **a)
{
	char		*swap;
	int			i;

	i = 0;
	j--;
	while (i < (j / 2))
	{
		swap = a[i];
		a[i] = a[j - i];
		a[j - i] = swap;
		i++;
	}
}

void		sort_av(int j, char **a, t_env *e)
{
	int		i;
	int		save;
	char	*swap;

	j--;
	e->flag_t ? sort_av_date(j, a) : NULL;
	save = j;
	if ((e->flag_rev && e->flag_t) || e->flag_t)
		j = 0;
	while (j)
	{
		i = j - 1;
		while (i)
		{
			if (a[i][0] != '-' && a[j][0] != '-' && ft_strcmp(a[j], a[i]) < 0)
			{
				swap = a[j];
				a[j] = a[i];
				a[i] = swap;
			}
			i--;
		}
		j--;
	}
	e->flag_rev && a[1] ? sort_av_rev(save, &a[1]) : NULL;
}
