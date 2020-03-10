/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_leak_report.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:07:33 by mapandel          #+#    #+#             */
/*   Updated: 2020/02/19 05:23:09 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	main:
**		Initializes the t_ssl structure "container" for the project
**		Parses arguments to find the algorithm, flags and inputs
**		Executions of the choosen algorithm follows a newly parsed argument
**		And finishes by freeing all the allocated memory blocs
**		Returns zero on success or a positive value
**			if at least one of the input files could not be read
*/

int				main(int argc, char **argv)
{
	t_ssl	*ssl;
	int		return_value;

	// Initialization
	ssl = NULL;
	if (!(ssl = init_t_ssl(ssl, argc, argv)))
	{
		return_value = system("leaks ft_ssl_leak_report &> leak_report");
		return (WEXITSTATUS(return_value));
	}

	// Parsing
	if (parsing(ssl))
	{
		del_t_ssl(&ssl);
		return_value = system("leaks ft_ssl_leak_report &> leak_report");
		return (WEXITSTATUS(return_value));
	}

	// Freeing
	del_t_ssl(&ssl);

	return_value = system("leaks ft_ssl_leak_report &> leak_report");
	return (WEXITSTATUS(return_value));
}
