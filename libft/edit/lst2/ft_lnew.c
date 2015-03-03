/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:16:02 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 19:27:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		is_ninja(char *str)
{
	char	*tmp;
	char	ret;
	int		count;

	ret = '\0';
	tmp = str;
	count = ft_strrindex(tmp, '/');
	if (count != -1)
		tmp[count] = 'z';
	if (ft_strrindex(tmp, '/') != -1 && tmp[ft_strrindex(tmp, '/') + 1] == '.' \
		&& tmp[ft_strrindex(tmp, '/') + 2] != '.')
		ret = 'z';
	tmp[count] = '/';
	return (ret);
}

static t_lst	*ft_aux2(struct stat *b, t_lst *new)
{
	new->user2 = b->st_uid ? (int)(b->st_uid) : 0;
	new->group2 = b->st_gid ? (int)(b->st_gid) : 0;
	new->mode2 = b->st_rdev ? (int)(b->st_rdev) : 0;
	new->ssize = b->st_size > -1 ? (int)b->st_size : 0;
	if (new->dir)
		new->is_hidden = ((new->file)[0] == '.' &&
							(new->file)[1] != '/') ? 'a' : '\0';
	new->is_ninja = is_ninja(new->dir);
	return (new);
}

static t_lst	*ft_aux1(t_lst *new, char *s, struct dirent *d, struct stat *b)
{
	if (s)
	{
		if (!(new->dir = ft_strdup(s)))
			return (NULL);
	}
	else
		new->dir = ft_strnew(1);
	if (d->d_name)
	{
		if (!(new->file = ft_strdup(d->d_name)))
			return (NULL);
	}
	else
		new->file = ft_strnew(1);
	if (d->d_type == 4 &&
		ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, ".."))
		new->is_dir = 'a';
	else
		new->is_dir = '\0';
	new->block = b->st_blocks ? (int)(b->st_blocks) : 0;
	new->date = b->st_mtime ? (long)(b->st_mtime) : 0;
	new->mode = b->st_mode ? (int)(b->st_mode) : 0;
	new->size = b->st_size ? (int)(b->st_size) : 0;
	new->link = b->st_nlink ? (int)(b->st_nlink) : 0;
	return (ft_aux2(b, new));
}

t_lst			*ft_lnew(struct dirent *d, struct stat *b, char *dir)
{
	struct passwd	*pwd;
	struct group	*grp;
	t_lst			*new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (!d || !b || !dir)
		return (NULL);
	pwd = getpwuid(b->st_uid);
	grp = getgrgid(b->st_gid);
	if (!pwd || !grp)
		return (NULL);
	if (pwd->pw_name)
		new->user = ft_strdup(pwd->pw_name);
	else
		new->user = ft_strnew(1);
	if (grp->gr_name)
		new->group = ft_strdup(grp->gr_name);
	else
		new->group = ft_strnew(1);
	return (ft_aux1(new, dir, d, b));
}
