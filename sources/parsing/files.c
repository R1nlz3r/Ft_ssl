/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:59:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 22:42:40 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	no_argument_check:
**		Checks if one execution of the command has been done after parsing
**			all of the arguments
**		Launches an execution reading from STDIN if so
**		This function do not return a value
*/

static void		no_argument_check(t_ssl *ssl, size_t *argv_i)
{
	if (*argv_i == ssl->argc && !ssl->bool_one_conversion_done)
	{
		add_t_flag_mask(ssl->flags, FLAG_NO_ARGUMENT, NULL);
		execution(ssl, NULL);
	}
}


/*
**	searching_files:
**		Iterates on arguments assuming they contain file paths
**		Launches an execution of the command with every file path found
**		This function do not return a value
*/

void			searching_files(t_ssl *ssl, size_t *argv_i)
{
	no_argument_check(ssl, argv_i);

	while (*argv_i < ssl->argc)
	{
		execution(ssl, ssl->argv[*argv_i]);
		++*argv_i;
	}
}
