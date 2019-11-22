/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/22 06:04:17 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"
#include "ft_printf.h"

// Par la suite, inplémenter ici la data en dur des algorithmes md5 et sha256

// Parsing error codes given to display
# define ERR_NO_ARG					1
# define ERR_INVALID_CMD_NAME		2
# define ERR_OPT_WITHOUT_ARG		3
# define ERR_INVALID_OPT			4

// Flags masks
# define FLAG_END_OF_PARAMETERS		1
# define FLAG_P						2
# define FLAG_Q						4
# define FLAG_R						8
# define FLAG_S						16

/*
**	t_input:
**		Used in a chain list to store every parsed file
**		Associates all potential int flags to a file
**		Stores the digest of the algorithm too as a char*
**
**	Flags considered:
**		-p: Input is STDIN											- mask 2
**		-q: Quiet mode												- mask 4
**		-r: Reverse format on the output							- mask 8
**		-s: Input is the next argv string rather than a file name	- mask 16
**	A future implementation for this one is possible:
**		-t: Time trial on convertions								- mask 32
*/

typedef struct		s_input {
	char	*input;
	char	*digest;
	int		flags;
}					t_input;

/*
**	t_ssl: data container for this project
**		Stores the name of algorithm as a char*
**		And a chained list of parsed inputs under the t_input structure
**		Triggers flags for future inputs
**		Defines the return value
**		Duplicates argv and stores argc value for easy access
**
**	Flags considered:
**		--: Stops parsing parameters								- mask 1
**		-q: Quiet mode												- mask 4
**		-r: Reverse format on the output							- mask 8
**	A future implementation for those is possible:
**		-t: Time trial on convertions								- mask 32
**		-x: Adds test strings				 						- mask 64
*/

typedef struct		s_ssl {
	char	*command_name;
	t_list	*inputs;
	int		flags;
	int		return_value;
	int		argc;
	char	**argv;
}					t_ssl;

t_input				*init_t_input();
int					parsing (t_ssl *ssl);
void				display_inputs(t_ssl *ssl);
void				display_t_ssl(t_ssl *ssl);
void				infinite_loop(t_ssl **ssl);

# endif
