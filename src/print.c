/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:18:26 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 19:17:46 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		print_block(t_lst *l, t_env *e)
{
	int			min;
	int			maj;
	char		*s;

	s = convert_mode(l->mode, l->dir), ft_putstr(s), ft_memdel((void *)&s);
	!e->flag_a ? space(ln(l->link), ln(grt(&(e->a_l), 2, 1)->link), 2, atr\
(l->dir)) : space(ln(l->link), ln(grt(&(e->a_l), 2, 0)->link), 2, atr(l->dir));
	PUT_NBR_STR(l->link, " ");
	e->flag_n ? flagn(&l, e) : noflagn(&l, e);
	!e->flag_a ? space(ln(l->size), ln(grt2(&(e->a_l), 0, 1)->size), 1, 1) :\
		space(ln(l->size), ln(grt2(&(e->a_l), 0, 0)->size), 1, 1);
	if (S_ISCHR(l->mode) || S_ISBLK(l->mode))
	{
		min = (l->mode2) % 256;
		maj = (l->mode2) / 256;
		while ((maj / 256) > 0)
			maj = maj / 256;
		ft_putstr(" "), space(ln(maj), 2, 3, 0), ft_putnbr(maj);
		ft_putstr(", "), space(ln(min), 3, 3, 0), ft_putnbr(min);
	}
	(!S_ISCHR(l->mode) && !S_ISBLK(l->mode)) ? ft_putnbr(l->size) : NULL;
	s = convert_date(l->date), PUT_DATE(s), ft_memdel((void *)&s);
	S_ISLNK(l->mode) ? s = lnk(l), ft_putstr(s), ft_memdel((void *)&s) : \
		ft_putendl(l->file);
}

static void		print_rev(t_env *e)
{
	t_lst	*l;

	l = e->a_l;
	while (l)
	{
		if (e->flag_a || (!e->flag_a && (l->file)[0] != '.' && !l->is_ninja))
			(e->flag_l) ? print_block(l, e) : ft_putendl(l->file);
		l = l->next;
	}
}

static void		print_norm(t_env *e)
{
	t_lst	*l;

	l = ft_llast(&(e->a_l));
	while (l)
	{
		if (e->flag_a || (!e->flag_a && (l->file)[0] != '.' && !l->is_ninja))
			(e->flag_l) ? print_block(l, e) : ft_putendl(l->file);
		l = l->prev;
	}
}

static t_lst	*init_print(t_env *e, char *alone)
{
	if (e->flag_l && !alone)
		ft_putstr("total ");
	if (e->flag_l && !alone)
		e->flag_a ? calc2(&(e->a_l)) : calc(&(e->a_l));
	e->a_l = e->flag_t ? sort_date(&(e->a_l)) : sort_name(&(e->a_l));
	e->flag_rev ? print_rev(e) : print_norm(e);
	return (e->flag_rev ? e->a_l : ft_llast(&(e->a_l)));
}

void			print_list(t_env *e, int root, char *alone)
{
	t_lst	*tmp;
	char	*name;

	tmp = init_print(e, alone);
	while (tmp && e->flag_rec)
	{
		if (tmp->is_dir)
		{
			name = tmp->dir;
			while ((!root && name[0] == '.' && name[1] == '/') ||\
			!strncmp("././", name, 4))
				name += 2;
			while (name[0] == '/' && name[1] == '/' && name[3])
				name++;
			if (ft_strrindex(name, '.') <= ft_strrindex(name, '/') || e->flag_a)
				PUT_NAME(name);
			tmp->mode != 16384 ? read_dir(tmp->dir, e, root, NULL) : NULL;
			if (tmp->mode == 16384)
				while (name[0] == '.' && name[1] == '/')
					name += 2;
			tmp->mode == 16384 ? PER_ERROR(name, ": Permission denied") : NULL;
		}
		tmp = e->flag_rev ? tmp->next : tmp->prev;
	}
}
