/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:44:33 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 21:01:29 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	exit_failure:
**		Frees up all the memory allocated structures of the program
**		Exits the program as a fatal error
*/

void		exit_failure(t_ssl *ssl)
{
	del_t_arg(&ssl->arg);
	del_t_ssl(&ssl);

	exit(1);
}
