/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 07:47:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/08/31 12:16:46 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	sha512_produce_digest:
**		Transforms the hashing values into a digest
**		Returns a negative value for a failed allocation
*/

static int				sha512_produce_digest_2(t_input *input,
	uint64_t hashing_value)
{
	char			*tmp;
	char			*paded;

	if (!(tmp = ft_lltoabase_unsigned(hashing_value, 16)))
		return (-1);
	while (tmp && ft_strlen_nullcrashless(tmp) < 16)
	{
		paded = ft_strjoin("0", tmp);
		ft_strdel(&tmp);
		tmp = paded;
	}
	if (!tmp)
		return (-1);

	if (!(input->digest = ft_strjoin_leakless(input->digest, tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

static int				sha512_produce_digest(t_input *input, t_sha512 *sha)
{
	if (sha512_produce_digest_2(input, sha->h0)
		|| sha512_produce_digest_2(input, sha->h1)
		|| sha512_produce_digest_2(input, sha->h2)
		|| sha512_produce_digest_2(input, sha->h3)
		|| sha512_produce_digest_2(input, sha->h4)
		|| sha512_produce_digest_2(input, sha->h5)
		|| sha512_produce_digest_2(input, sha->h6)
		|| sha512_produce_digest_2(input, sha->h7))
		return (-1);

	return (0);
}


/*
**	sha512_setup_words:
**		Sets up the words used for the next round of encryption
*/

static void		sha512_setup_words(t_input *input, t_sha512 *sha)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		sha->w[i] = (uint64_t)((uint64_t)input->msg[i * 8] << 56
			| (uint64_t)input->msg[i * 8 + 1] << 48
			| (uint64_t)input->msg[i * 8 + 2] << 40
			| (uint64_t)input->msg[i * 8 + 3] << 32
			| (uint64_t)input->msg[i * 8 + 4] << 24
			| (uint64_t)input->msg[i * 8 + 5] << 16
			| (uint64_t)input->msg[i * 8 + 6] << 8
			| (uint64_t)input->msg[i * 8 + 7]);
		++i;
	}
	while (i < 80)
	{
		sha->s0 = ft_right_rotate_u64(sha->w[i - 15], 1)
			^ ft_right_rotate_u64(sha->w[i - 15], 8) ^ (sha->w[i - 15] >> 7);
		sha->s1 = ft_right_rotate_u64(sha->w[i - 2], 19)
			^ ft_right_rotate_u64(sha->w[i - 2], 61) ^ (sha->w[i - 2] >> 6);
		sha->w[i] = sha->w[i - 16] + sha->s0 + sha->w[i - 7] + sha->s1;
		++i;
	}
}


/*
**	sha512_main_loop:
**		Launches rounds of encryption per 1024 bits of the message
**		Sets up the next words used
**		Prepares and updates the hasing values according
**			to the results of each round
*/

static int		sha512_main_loop(t_input *input, t_sha512 *sha)
{
	int		ret;

	while (1)
	{
		if ((ret = sha512_message_obtaining(input)))
			return (ret);
		sha512_setup_words(input, sha);

		sha->a = sha->h0;
		sha->b = sha->h1;
		sha->c = sha->h2;
		sha->d = sha->h3;
		sha->e = sha->h4;
		sha->f = sha->h5;
		sha->g = sha->h6;
		sha->h = sha->h7;

		sha512_computations(sha);

		// Update hashing values
		sha->h0 += sha->a;
		sha->h1 += sha->b;
		sha->h2 += sha->c;
		sha->h3 += sha->d;
		sha->h4 += sha->e;
		sha->h5 += sha->f;
		sha->h6 += sha->g;
		sha->h7 += sha->h;

		if (sha512_message_dumping(input))
			break ;
	}

	return (0);
}


/*
**	sha512_init_constants:
**		Initializes the variables used for the sha512 algorithm
*/

static void				sha512_init_constants(t_sha512 *sha)
{
	int			i;

	i = 0;
	while (i < 80)
	{
		sha->k[i] = SHA512_K[i];
		i++;
	}
	sha->h0 = UINT64_C(0x6a09e667f3bcc908);
	sha->h1 = UINT64_C(0xbb67ae8584caa73b);
	sha->h2 = UINT64_C(0x3c6ef372fe94f82b);
	sha->h3 = UINT64_C(0xa54ff53a5f1d36f1);
	sha->h4 = UINT64_C(0x510e527fade682d1);
	sha->h5 = UINT64_C(0x9b05688c2b3e6c1f);
	sha->h6 = UINT64_C(0x1f83d9abfb41bd6b);
	sha->h7 = UINT64_C(0x5be0cd19137e2179);
}


/*
**	sha512:
**		Initializes the variables used for the sha512 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns a negative value for a failed allocation
*/

int				sha512(t_input *input)
{
	t_sha512	*sha;
	int			ret_val;

	// Data container for the computations variables
	if (!(sha = ft_memalloc(sizeof(t_sha512))))
		return (-1);

	// Initialization
	sha512_init_constants(sha);

	// Iteration
	ret_val = sha512_main_loop(input, sha);

	// Digest contraction
	if (!ret_val)
		ret_val = sha512_produce_digest(input, sha);

	ft_memdel((void**)&sha);

	return (ret_val);
}
