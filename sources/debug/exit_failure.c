/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 22:30:54 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 19:51:11 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	exit_failure: debug
**		This file replaces the real exit_failure.c to produce a leak report
**		Returns the 'leaks' command return value
*/

void		exit_failure(t_ssl *ssl)
{
	int		return_value;

	del_t_arg(&ssl->arg);
	del_t_ssl(&ssl);

	return_value = system("leaks ft_ssl_leak_report &> leak_report");
	exit(WEXITSTATUS(return_value));
}
