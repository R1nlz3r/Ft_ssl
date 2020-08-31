/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2020/08/08 20:17:02 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

// Error codes
# define ERR_NO_ARG					1
# define ERR_INVALID_CMD_NAME		2
# define ERR_OPT_WITHOUT_ARG		3
# define ERR_INVALID_OPT			4

// Flags masks
# define FLAG_END_OF_PARAMETERS		1
# define FLAG_NO_ARGUMENT			2
# define FLAG_P						4
# define FLAG_Q						8
# define FLAG_R						16
# define FLAG_S						32


static const		uint64_t SHA512_K[80] =
{
	UINT64_C(0x428a2f98d728ae22), UINT64_C(0x7137449123ef65cd),
	UINT64_C(0xb5c0fbcfec4d3b2f), UINT64_C(0xe9b5dba58189dbbc),
	UINT64_C(0x3956c25bf348b538), UINT64_C(0x59f111f1b605d019),
	UINT64_C(0x923f82a4af194f9b), UINT64_C(0xab1c5ed5da6d8118),
	UINT64_C(0xd807aa98a3030242), UINT64_C(0x12835b0145706fbe),
	UINT64_C(0x243185be4ee4b28c), UINT64_C(0x550c7dc3d5ffb4e2),
	UINT64_C(0x72be5d74f27b896f), UINT64_C(0x80deb1fe3b1696b1),
	UINT64_C(0x9bdc06a725c71235), UINT64_C(0xc19bf174cf692694),
	UINT64_C(0xe49b69c19ef14ad2), UINT64_C(0xefbe4786384f25e3),
	UINT64_C(0x0fc19dc68b8cd5b5), UINT64_C(0x240ca1cc77ac9c65),
	UINT64_C(0x2de92c6f592b0275), UINT64_C(0x4a7484aa6ea6e483),
	UINT64_C(0x5cb0a9dcbd41fbd4), UINT64_C(0x76f988da831153b5),
	UINT64_C(0x983e5152ee66dfab), UINT64_C(0xa831c66d2db43210),
	UINT64_C(0xb00327c898fb213f), UINT64_C(0xbf597fc7beef0ee4),
	UINT64_C(0xc6e00bf33da88fc2), UINT64_C(0xd5a79147930aa725),
	UINT64_C(0x06ca6351e003826f), UINT64_C(0x142929670a0e6e70),
	UINT64_C(0x27b70a8546d22ffc), UINT64_C(0x2e1b21385c26c926),
	UINT64_C(0x4d2c6dfc5ac42aed), UINT64_C(0x53380d139d95b3df),
	UINT64_C(0x650a73548baf63de), UINT64_C(0x766a0abb3c77b2a8),
	UINT64_C(0x81c2c92e47edaee6), UINT64_C(0x92722c851482353b),
	UINT64_C(0xa2bfe8a14cf10364), UINT64_C(0xa81a664bbc423001),
	UINT64_C(0xc24b8b70d0f89791), UINT64_C(0xc76c51a30654be30),
	UINT64_C(0xd192e819d6ef5218), UINT64_C(0xd69906245565a910),
	UINT64_C(0xf40e35855771202a), UINT64_C(0x106aa07032bbd1b8),
	UINT64_C(0x19a4c116b8d2d0c8), UINT64_C(0x1e376c085141ab53),
	UINT64_C(0x2748774cdf8eeb99), UINT64_C(0x34b0bcb5e19b48a8),
	UINT64_C(0x391c0cb3c5c95a63), UINT64_C(0x4ed8aa4ae3418acb),
	UINT64_C(0x5b9cca4f7763e373), UINT64_C(0x682e6ff3d6b2b8a3),
	UINT64_C(0x748f82ee5defb2fc), UINT64_C(0x78a5636f43172f60),
	UINT64_C(0x84c87814a1f0ab72), UINT64_C(0x8cc702081a6439ec),
	UINT64_C(0x90befffa23631e28), UINT64_C(0xa4506cebde82bde9),
	UINT64_C(0xbef9a3f7b2c67915), UINT64_C(0xc67178f2e372532b),
	UINT64_C(0xca273eceea26619c), UINT64_C(0xd186b8c721c0c207),
	UINT64_C(0xeada7dd6cde0eb1e), UINT64_C(0xf57d4f7fee6ed178),
	UINT64_C(0x06f067aa72176fba), UINT64_C(0x0a637dc5a2c898a6),
	UINT64_C(0x113f9804bef90dae), UINT64_C(0x1b710b35131c471b),
	UINT64_C(0x28db77f523047d84), UINT64_C(0x32caab7b40c72493),
	UINT64_C(0x3c9ebe0a15c9bebc), UINT64_C(0x431d67c49c100d4c),
	UINT64_C(0x4cc5d4becb3e42b6), UINT64_C(0x597f299cfc657e2a),
	UINT64_C(0x5fcb6fab3ad6faec), UINT64_C(0x6c44198c4a475817)
};


/*
**	t_sha512: values container for the SHA512 algorithm
**		Stores all the values for used for the rotations and permutations
*/

typedef struct		s_sha512 {
	uint64_t		k[80];
	uint64_t		w[80];
	uint64_t		s0;
	uint64_t		s1;
	uint64_t		ch;
	uint64_t		maj;
	uint64_t		tmp1;
	uint64_t		tmp2;
	uint64_t		h0;
	uint64_t		h1;
	uint64_t		h2;
	uint64_t		h3;
	uint64_t		h4;
	uint64_t		h5;
	uint64_t		h6;
	uint64_t		h7;
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
}					t_sha512;


static const		uint32_t SHA256_K[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


/*
**	t_sha256: values container for the SHA256 algorithm
**		Stores all the values for used for the rotations and permutations
*/

typedef struct		s_sha256 {
	uint32_t		k[64];
	uint32_t		w[64];
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		maj;
	uint32_t		tmp1;
	uint32_t		tmp2;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
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
	uint32_t		r[64];
	uint32_t		k[64];
	uint32_t		*w;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		f;
	uint32_t		g;
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
	size_t			msg_len;
	size_t			msg_total_len;
	char			*digest;
	int				fd;
	int				flags;
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
	char			*command_name;
	t_input			*input;
	int				flags;
	int				bool_one_conversion_done;
	int				return_value;
	int				pad_0;
	size_t			argc;
	char			**argv;
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

// md5_message_handling.c
int					md5_message_dumping(t_input *input);
int 				md5_message_obtaining(t_input *input);

// md5_computations.c
void				md5_computations(t_md5 *md);

// parsing_file.c
int					parsing_file(t_ssl *ssl, char *input_string, int flag);

// parsing_flags.c
int					parsing_flags(t_ssl *ssl, size_t *argv_i);

// parsing.c
int					parsing (t_ssl *ssl);

// sha256.c
int					sha256(t_input *input);

// sha256_message_handling.c
int					sha256_message_dumping(t_input *input);
int 				sha256_message_obtaining(t_input *input);

// sha256_computations.c
void				sha256_computations(t_sha256 *sha);

// sha512.c
int					sha512(t_input *input);

// sha512_message_handling.c
int					sha512_message_dumping(t_input *input);
int 				sha512_message_obtaining(t_input *input);

// sha512_computations.c
void				sha512_computations(t_sha512 *sha);

// touch_t_input.c
t_input				*init_t_input(void);
void				del_t_input(t_input **input);

// touch_t_ssl.c
t_ssl				*init_t_ssl(t_ssl *ssl, int argc, char **argv);
void				del_t_ssl(t_ssl **ssl);

# endif
