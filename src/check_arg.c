/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:17:08 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/15 19:17:09 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/stat.h>

/*
** return the type of a given arg :
** -1=error 0=unknow 1=file 2=folder 3=flag 4=link-file 5=link-folder
*/

static int	is_file(char *str)
{
	DIR				*dir;
	struct dirent	*s_dir;
	int				ret;

	ret = 0;
	if (!(dir = opendir(str)))
		return (0);
	while ((s_dir = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(s_dir->d_name, str) && s_dir->d_type == 8)
			ret = 1;
		else if (!ft_strcmp(s_dir->d_name, str) && s_dir->d_type == 4)
			ret = 0;
		if (!ft_strcmp(s_dir->d_name, str))
			break ;
	}
	if (closedir(dir) == -1)
		INT_ERROR("closedir");
	return (ret);
}

static int	is_dir(char *str)
{
	DIR		*dir;
	char	*s;

	if (!(s = ft_strnew(2 + ft_strlen(str))))
		INT_ERROR("strnew");
	s[0] = '.';
	s[1] = '/';
	s[2] = '\0';
	ft_strcat(s, str);
	if (!(dir = opendir(s)))
	{
		ft_memdel((void *)&s);
		return (0);
	}
	ft_memdel((void *)&s);
	if (dir)
		if (closedir(dir) == -1)
			INT_ERROR("closedir");
	return (2);
}

static int	is_file_or_dir(char *s)
{
	struct stat sta;

	if (!lstat(s, &sta))
	{
		if (S_ISLNK(sta.st_mode) && is_dir(s))
			return (5);
		else if (S_ISLNK(sta.st_mode))
			return (4);
		else if (sta.st_mode & S_IFDIR)
			return (2);
		else if (sta.st_mode & S_IFREG)
			return (1);
		else
			return (0);
	}
	return (0);
}

static int	is_flag(char *s)
{
	int		i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'a' && s[i] != 'l' && s[i] != 'R' &&
				s[i] != 'r' && s[i] != 't' && s[i] != '1' &&
				s[i] != 'o' && s[i] != 'n' && s[i] != '-')
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			ft_putchar_fd(s[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putendl_fd("usage: ls [-Ralnort1] [file ...]", 2);
			exit(-1);
		}
		i++;
	}
	return (3);
}

int			check_arg(char *str)
{
	int	ret;

	if ((ret = is_file(str)) == -1)
		return (-1);
	else if (ret != 1 && (ret += is_dir(str)) == -1)
		return (-1);
	else if (ret != 1 && (ret += is_flag(str)) == -1)
		return (-1);
	if (ret != 3 && is_file_or_dir(str) != ret && is_file_or_dir(str) > 0)
		ret = is_file_or_dir(str);
	return (ret);
}
