/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:17:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 18:39:29 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		*convert_date(time_t t_file)
{
	char		*date2;
	char		*tmp;
	char		*date;
	int			index;

	if (!(date = ft_strsub(ctime(&t_file), 4, ft_strlen(ctime(&t_file)) - 4)))
		return (NULL);
	index = ft_strlen(date);
	while (date[index + 1] != ':')
		index--;
	date2 = ft_strnew(index);
	ft_strncpy(date2, date, index + 1);
	ft_memdel((void *)&date);
	if (t_file < (time(NULL) - 15897287) || t_file > time(NULL))
	{
		date = ft_strsub(date2, 0, ft_strlen(date2) - 5);
		ft_memdel((void *)&date2);
		date2 = ft_itoa((t_file / 31557600) + 1970);
		tmp = ft_strjoin(" ", date2);
		ft_memdel((void *)&date2);
		date2 = ft_strjoin(date, tmp);
		ft_memdel((void *)&tmp), ft_memdel((void *)&date);
	}
	date2[12] = '\0';
	return (date2);
}

char		*convert_mode(mode_t mode, char *arg)
{
	char	*str;

	if (!(str = ft_strnew(11)))
		return (NULL);
	str[0] = S_ISREG(mode) == 1 ? '-' : str[0];
	str[0] = S_ISDIR(mode) == 1 ? 'd' : str[0];
	str[0] = S_ISSOCK(mode) == 1 ? 's' : str[0];
	str[0] = S_ISCHR(mode) == 1 ? 'c' : str[0];
	str[0] = S_ISLNK(mode) == 1 ? 'l' : str[0];
	str[0] = S_ISBLK(mode) == 1 ? 'b' : str[0];
	str[0] = S_ISFIFO(mode) == 1 ? 'p' : str[0];
	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	str[4] = (mode & S_IRGRP) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';
	if (listxattr(arg, NULL, 5, XATTR_NOFOLLOW) > 0)
		str[10] = '@';
	return (str);
}

char		*lnk(t_lst *tmp)
{
	char	*link_name;
	char	*ret;
	char	*tmp1;
	char	*tmp2;
	ssize_t	link_size;

	if (!(link_name = malloc(tmp->ssize + 1)))
		return (NULL);
	if (!(ret = malloc(ft_strlen(link_name) + ft_strlen(tmp->dir) + 5)))
		return (NULL);
	link_size = readlink(tmp->dir, link_name, tmp->ssize + 1);
	link_name[link_size] = '\0';
	tmp1 = ft_strjoin(link_name, "\n");
	tmp2 = ft_strjoin(" -> ", tmp1);
	ret = ft_strjoin(tmp->file, tmp2);
	ft_memdel((void *)&tmp1);
	ft_memdel((void *)&tmp2);
	ft_memdel((void *)&link_name);
	return (ret);
}

char		*convert_dirname(char *str)
{
	char	*dir2;
	int		i;

	dir2 = ft_strnew(ft_strlen(str) + 1);
	i = 0;
	while (str[i] != '\0')
		if (str[2] == '.' && str[3] == '/')
		{
			dir2[i] = str[i + 2];
			i++;
		}
		else
			return (str);
	return (dir2);
}

int			countchar(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str != '\0')
	{
		if (str[i] == '.')
			j++;
		i++;
	}
	return (j);
}
