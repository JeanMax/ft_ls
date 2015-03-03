/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:17:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 18:22:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		get_flags(char *str, t_env *e)
{
	e->flag_a = (!e->flag_a && ft_strchr(str, 'a')) ? '1' : '\0';
	e->flag_l = (!e->flag_l && ft_strchr(str, 'l')) ? '1' : '\0';
	e->flag_rec = (!e->flag_rec && ft_strchr(str, 'R')) ? '1' : '\0';
	e->flag_rev = (!e->flag_rev && ft_strchr(str, 'r')) ? '1' : '\0';
	e->flag_t = (!e->flag_t && ft_strchr(str, 't')) ? '1' : '\0';
	e->flag_1 = (!e->flag_1 && ft_strchr(str, '1')) ? '1' : '\0';
	e->flag_o = (!e->flag_o && ft_strchr(str, 'o')) ? '1' : '\0';
	e->flag_n = (!e->flag_n && ft_strchr(str, 'n')) ? '1' : '\0';
}

static int		put_files(int ac, char **av, t_env *e, int i)
{
	int	input;
	int	dir;
	int	check;

	dir = 0;
	input = 0;
	sort_av(ac, &av[0], e);
	while (av[i])
	{
		if ((check = check_arg(av[i])) == -1)
			return (0);
		if (check == 1 || check == 4 || (check == 5 && e->flag_l))
		{
			read_dir(get_folder(av[i]), e, 1, av[i]);
			input += 1;
		}
		if (check == 2 || (check == 5 && !e->flag_l))
			dir = 1;
		i++;
	}
	if (input >= 1 && dir)
		ft_putchar('\n');
	return (0);
}

static void		is_last_folder(char **av)
{
	int	i;
	int	check;

	i = 1;
	while (av[i])
	{
		check = check_arg(av[i]);
		if (check == 2 || check == 5)
			break ;
		i++;
	}
	if (av[i])
		ft_putchar('\n');
}

static int		init(t_env *e, int ac, char **av, int i)
{
	int		check;
	char	input;

	input = '\0';
	e->flag_a = '\0';
	e->flag_l = '\0';
	e->flag_rec = '\0';
	e->flag_rev = '\0';
	e->flag_t = '\0';
	e->flag_1 = '\0';
	e->flag_o = '\0';
	e->flag_n = '\0';
	while (av[i])
	{
		if ((check = check_arg(av[i])) != 3)
			input = '1';
		else if (check == 3 && !input && av[i][0] == '-')
			get_flags(av[i], e);
		if ((check == 3 && input) || check == 0)
			FLAG_E(av[i], ": No such file or directory");
		i++;
	}
	return (put_files(ac, av, e, 1));
}

int				main(int ac, char **av)
{
	int		i;
	t_env	e;
	int		check;
	int		input;

	i = init(&e, ac, av, 1);
	while (av[++i] && ac != 1)
	{
		if ((check = check_arg(av[i])) == -1)
			return (0);
		input = (check != 0 && check != 3) ? 1 : 0;
		if (check == 2 || (check == 5 && !e.flag_l))
		{
			if (av[i + 1] || (check_arg(av[i - 1]) != 3 && ac != 2))
			{
				ft_putstr(av[i]);
				ft_putendl(":");
			}
			read_dir(av[i], &e, 0, NULL);
		}
		(check == 2 || check == 5) ? is_last_folder(&av[i]) : NULL;
	}
	(!input || i == 1) ? read_dir(".", &e, 1, NULL) : NULL;
	return (0);
}
