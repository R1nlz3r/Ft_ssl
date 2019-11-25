/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:21 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/25 23:20:51 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	main:
**		Initializes the t_ssl structure "container" for the project
**		Parses arguments to find the algorithm, flags and inputs
**		Executes the choosen algorithm
**		Displays all the collected digests
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
	return_value = 0;
	if (!(ssl = init_t_ssl(ssl, argc, argv)))
		return (-1);

	// Parsing
	if (parsing(ssl))
	{
		return_value = ssl->return_value;
		del_t_ssl(ssl);
		return (return_value);
	}

	// Execution

	// Display
	// display_t_ssl(ssl); // Debug purpose

	// Freeing
	return_value = ssl->return_value;
	del_t_ssl(ssl);

	// infinite_loop(&ssl); // Debug purpose

	return (return_value);
}
