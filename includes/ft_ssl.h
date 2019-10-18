/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2019/10/18 11:20:14 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"
#include "ft_printf.h"

typedef struct		s_ssl {
	char		**files;
	char		*command_name;
	int			flags;
	int			pad_0;
}					t_ssl;

void				*del_t_ssl(t_ssl *ssl);
t_ssl				*parsing (t_ssl *ssl, int argc, char **argv);

# endif
