/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:18:13 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 19:25:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		*get_folder(char *str)
{
	char	*folder;

	if (ft_strrindex(str, '/') != -1)
	{
		folder = ft_strdup(str);
		folder[ft_strrindex(str, '/')] = '\0';
	}
	else
		folder = ft_strdup(".");
	return (folder);
}

static char	*get_file(char *str)
{
	char	*file;

	if (ft_strrindex(str, '/') != -1)
	{
		file = ft_strdup(str);
		file += ft_strrindex(str, '/') + 1;
	}
	else
		return (str);
	return (file);
}

static void	fill_list(struct dirent *s_d, char *s, char *a, t_env *e)
{
	char		go;
	struct stat	s_buf;

	if (lstat(s, &s_buf) < 0)
		VOID_ERROR("lstat", s);
	go = (a && !(ft_strcmp(s_d->d_name, get_file(a)))) ? 'z' : '\0';
	if (!a || go)
	{
		if (!(e->a_l))
			e->a_l = ft_lnew(s_d, &s_buf, s);
		else
			ft_ladd(&e->a_l, ft_lnew(s_d, &s_buf, s));
		if (a && e->a_l)
			e->a_l->file = ft_strdup(a);
	}
}

static void	read_loop(struct dirent *s_d, char *alone, char *str, t_env *e)
{
	char			*s;
	char			*d;
	char			*f;

	if (!ft_strcmp(str, "."))
		s = ft_strjoin("./", s_d->d_name);
	else if (str[0] == '/')
	{
		f = ft_strjoin("/", s_d->d_name);
		d = ft_strjoin(str, f), ft_memdel((void *)&f);
		s = ft_strjoin("/", d), ft_memdel((void *)&d);
	}
	else
	{
		f = ft_strjoin("/", s_d->d_name);
		d = ft_strjoin(str, f), ft_memdel((void *)&f);
		s = ft_strjoin("./", d), ft_memdel((void *)&d);
	}
	if (ft_strstr(s, CONTINUE))
		return ;
	fill_list(s_d, s, alone, e), ft_memdel((void *)&s);
}

void		read_dir(char *str, t_env *e, int root, char *alone)
{
	DIR				*dir;
	struct dirent	*s_d;

	e->a_l = NULL;
	if (!(dir = opendir(str)))
		VOID_ERROR("ls", str);
	while ((s_d = readdir(dir)) != NULL)
		read_loop(s_d, alone, str, e);
	if (closedir(dir) == -1)
		VOID_ERROR("closedir", str);
	print_list(e, root, alone), ft_lclean(&(e->a_l)), e->a_l = NULL;
}
