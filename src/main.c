/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:05 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:00:08 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	t_info *info;

	info = malloc(sizeof(t_info));
	if (info)
	{
		if (argc == 2 || argc == 3)
		{
			info->sshot = 0;
			info->scene = parser(argv[1]);
			if (argc == 3)
			{
				if (ft_strncmp("--save", argv[2], 7) == 0)
					info->sshot = 1;
				else
					exit_error("Wrong second argument", -1);
			}
			start_render(info);
		}
		else
			exit_error("Wrong number of arguments", -1);
	}
	else
		exit_error(MFAIL, 1);
	return (0);
}
