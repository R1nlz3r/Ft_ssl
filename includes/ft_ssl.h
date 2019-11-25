/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/26 00:16:59 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"

// Error codes
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
	int		pad_0;
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
	size_t	argc;
	char	**argv;
}					t_ssl;

// debug.c
void				display_inputs(t_ssl *ssl);
void				display_t_ssl(t_ssl *ssl);
void				infinite_loop(t_ssl **ssl);

// display.c
int					display_parsing_error(t_ssl *ssl, int error_code,
	char *justification);

// parsing_file.c
int					parsing_file(t_ssl *ssl, char *input_string, int flag);

// parsing_flags.c
int					parsing_flags(t_ssl *ssl, size_t *argv_i);

// parsing.c
int					parsing (t_ssl *ssl);

// touch_t_input.c
t_input				*add_t_input_to_t_list(t_ssl *ssl);
t_input				*init_t_input(void);
void				del_t_input(t_input *node, size_t unused_value);

// touch_t_ssl.c
t_ssl				*init_t_ssl(t_ssl *ssl, int argc, char **argv);
void				del_t_ssl(t_ssl *ssl);

# endif
