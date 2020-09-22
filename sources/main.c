/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:21 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/20 01:11:53 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	main:
**		Initializes the t_ssl structure "container" for the project
**		Parses arguments to find the algorithm, flags and files
**		Executions of the choosen algorithm follows a newly parsed file
**		Finishes by freeing all the allocated memory blocs
**		Returns zero on success or a positive value
**			if at least one of the executions could not be completed
*/

int				main(int argc, char **argv)
{
	t_ssl	*ssl;
	int		return_value;

	ssl = NULL;
	if (!(ssl = init_t_ssl(ssl, argc, argv)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	parsing(ssl);

	return_value = ssl->return_value;

	del_t_ssl(&ssl);

	return (return_value);
}
