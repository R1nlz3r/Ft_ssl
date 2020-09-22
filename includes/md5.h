/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:18:20 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 17:50:16 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

/* Hard written numbers of bitwise rotations */
static uint32_t			MD5_R[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
 	6, 10, 15, 21
};


/*
**	t_md5:
**		Stores all the values used for the rotations and permutations
**			of the MD5 algorithm
*/

typedef struct			s_md5 {
	uint32_t			r[64];		/* Bitwise number of rotations */
	uint32_t			k[64];		/* Salt constants */
	uint32_t			*w;			/* Word computed */
	uint32_t			h0;			/* Hashing values */
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			a;			/* Permutation values */
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			f;
	uint32_t			g;
}						t_md5;

# endif
