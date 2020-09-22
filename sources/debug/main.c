/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:07:33 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 19:50:38 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	main: debug
**		This file replaces the real main.c to produce a leak report
**		Returns the 'leaks' command return value
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

	return_value = system("leaks ft_ssl_leak_report &> leak_report");
	return (WEXITSTATUS(return_value));
}
