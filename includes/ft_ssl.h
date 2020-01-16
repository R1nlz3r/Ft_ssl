/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/23 04:28:06 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <math.h>
# include "../Libft/includes/libft.h"

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


typedef struct		s_sha256 {
	unsigned int	k[64];
	unsigned int	w[64];
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	ch;
	unsigned int	maj;
	unsigned int	tmp1;
	unsigned int	tmp2;
	unsigned int	h0;
	unsigned int	h1;
	unsigned int	h2;
	unsigned int	h3;
	unsigned int	h4;
	unsigned int	h5;
	unsigned int	h6;
	unsigned int	h7;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
}					t_sha256;


// MD5 hard written numbers of bitwise rotations
static unsigned int	md5_rotations[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};


/*
**	t_md5: values container for the MD5 algorithm
**		Stores all the values for used for the rotations and permutations
*/

typedef struct		s_md5 {
	unsigned int	r[64];
	unsigned int	k[64];
	unsigned int	*w;
	unsigned int	h0;
	unsigned int	h1;
	unsigned int	h2;
	unsigned int	h3;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	f;
	unsigned int	g;
}					t_md5;


/*
**	t_input:
**		Stores the variables associated to an parsed argument
**		The message used for computations and its digest output
**		Associates all potential flags the input
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
	char			*input;
	unsigned char	*msg;
	char			*digest;
	size_t			input_len;
	size_t			msg_len;
	int				flags;
	int				pad_0;
}					t_input;


/*
**	t_ssl: data container for this project
**		Stores the name of the choosen algorithm
**		A t_input* structure to access an agument and its associated variables
**		Flags used for future inputs
**		Defines the main return value in case of a failed conversion
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
	char		*command_name;
	t_input		*input;
	int			flags;
	int			return_value;
	size_t		argc;
	char		**argv;
}					t_ssl;

// debug.c
void				display_t_input(t_input *input);
void				display_t_ssl(t_ssl *ssl);
void				infinite_loop(t_ssl **ssl);

// display.c
int					display_parsing_error(t_ssl *ssl, int error_code,
	char *justification);
void				display_hash(char *command_name, t_input *input);

// execution.c
int					execution(t_ssl *ssl);

// md5.c
int					md5(t_input *input);

// parsing_file.c
int					parsing_file(t_ssl *ssl, char *input_string, int flag);

// parsing_flags.c
int					parsing_flags(t_ssl *ssl, size_t *argv_i);

// parsing.c
int					parsing (t_ssl *ssl);

// sha256.c
int					sha256(t_input *input);

// touch_t_input.c
t_input				*init_t_input(void);
void				del_t_input(t_input **input);

// touch_t_ssl.c
t_ssl				*init_t_ssl(t_ssl *ssl, int argc, char **argv);
void				del_t_ssl(t_ssl **ssl);

# endif
