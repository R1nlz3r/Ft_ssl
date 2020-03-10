/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 04:00:58 by mapandel          #+#    #+#             */
/*   Updated: 2020/03/10 14:23:47 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	sha256_produce_digest:
**		Transforms the hashing values into a digest
**		Returns a negative value for a failed allocation
*/

static int				sha256_produce_digest_2(t_input *input,
	unsigned int hashing_value)
{
	char			*tmp;
	char			*paded;

	if (!(tmp = ft_lltoabase_unsigned(hashing_value, 16)))
		return (-1);
	while (tmp && ft_strlen_nullcrashless(tmp) < 8)
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

static int				sha256_produce_digest(t_input *input, t_sha256 *sha)
{
	if (sha256_produce_digest_2(input, sha->h0)
		|| sha256_produce_digest_2(input, sha->h1)
		|| sha256_produce_digest_2(input, sha->h2)
		|| sha256_produce_digest_2(input, sha->h3)
		|| sha256_produce_digest_2(input, sha->h4)
		|| sha256_produce_digest_2(input, sha->h5)
		|| sha256_produce_digest_2(input, sha->h6)
		|| sha256_produce_digest_2(input, sha->h7))
		return (-1);

	return (0);
}


/*
**	sha256_setup_words:
**		Sets up the words used for the next round of encryption
*/

static void		sha256_setup_words(t_input *input, t_sha256 *sha)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		sha->w[i] = (unsigned int)
			(input->msg[i * 4 + 0] << 24
			| input->msg[i * 4 + 1] << 16
			| input->msg[i * 4 + 2] << 8
			| input->msg[i * 4 + 3]);
		++i;
	}
	while (i < 64)
	{
		sha->s0 = ft_right_rotate_u32(sha->w[i - 15], 7)
			^ ft_right_rotate_u32(sha->w[i - 15], 18) ^ (sha->w[i - 15] >> 3);
		sha->s1 = ft_right_rotate_u32(sha->w[i - 2], 17)
			^ ft_right_rotate_u32(sha->w[i - 2], 19) ^ (sha->w[i - 2] >> 10);
		sha->w[i] = sha->w[i - 16] + sha->s0 + sha->w[i - 7] + sha->s1;
		++i;
	}
}


/*
**	sha256_main_loop:
**		Launches rounds of encryption per 512bits of the message
**		Sets up the next words used
**		Prepares and updates the hasing values according
**			to the results of each round
*/

static int		sha256_main_loop(t_input *input, t_sha256 *sha)
{
	int		ret;

	while (1)
	{
		if ((ret = sha256_message_obtaining(input)))
			return (ret);
		sha256_setup_words(input, sha);

		sha->a = sha->h0;
		sha->b = sha->h1;
		sha->c = sha->h2;
		sha->d = sha->h3;
		sha->e = sha->h4;
		sha->f = sha->h5;
		sha->g = sha->h6;
		sha->h = sha->h7;

		sha256_computations(sha);

		// Update hashing values
		sha->h0 += sha->a;
		sha->h1 += sha->b;
		sha->h2 += sha->c;
		sha->h3 += sha->d;
		sha->h4 += sha->e;
		sha->h5 += sha->f;
		sha->h6 += sha->g;
		sha->h7 += sha->h;

		if (sha256_message_dumping(input))
			break ;
	}

	return (0);
}


/*
**	sha256_init_constants:
**		Initializes the variables used for the sha256 algorithm
*/

static void				sha256_init_constants(t_sha256 *sha)
{
	int			i;
	int			j;

	i = 0;
	j = 2;
	while (i < 64)
	{
		if (ft_isprime(j))
			sha->k[i++] = (unsigned int)(floor(cbrt(j) * pow(2, 32)));
		++j;
	}
	sha->h0 = 1779033703;
	sha->h1 = 3144134277;
	sha->h2 = 1013904242;
	sha->h3 = 2773480762;
	sha->h4 = 1359893119;
	sha->h5 = 2600822924;
	sha->h6 = 528734635;
	sha->h7 = 1541459225;
}


/*
**	sha256:
**		Initializes the variables used for the sha256 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns a negative value for a failed allocation
*/

int				sha256(t_input *input)
{
	t_sha256	*sha;
	int			ret_val;

	// Data container for the computations variables
	if (!(sha = ft_memalloc(sizeof(t_sha256))))
		return (-1);

	// Initialization
	sha256_init_constants(sha);

	// Iteration
	ret_val = sha256_main_loop(input, sha);

	// Digest contraction
	if (!ret_val)
		ret_val = sha256_produce_digest(input, sha);

	ft_memdel((void**)&sha);

	return (ret_val);
}
