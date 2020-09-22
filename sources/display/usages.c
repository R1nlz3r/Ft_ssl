/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:38:00 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 20:47:29 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	display_cipher_algorithm_usage:
**		Displays the program usage under a cipher algorithm command
**		This function do not return a value
*/

void	display_cipher_algorithm_usage()
{
	ft_putendl_fd("\nusage: ft_ssl command [-de] [-i file] [-o file] \
[files ...]", 2);
}


/*
**	display_md_algorithm_usage:
**		Displays the program usage under a message digest command
**		This function do not return a value
*/

void	display_md_algorithm_usage()
{
	ft_putendl_fd("\nusage: ft_ssl command [-pqr] [-s string] [files ...]", 2);
}


/*
**	display_ft_ssl_usage:
**		Displays the program usage
**		This function do not return a value
*/

void	display_ft_ssl_usage()
{
	ft_putendl_fd("usage: ft_ssl command [command opts] [command args]", 2);
}
