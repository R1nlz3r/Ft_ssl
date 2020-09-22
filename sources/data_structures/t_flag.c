/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:45:56 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 01:08:43 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_flag:
**		Frees up a t_flag* structure pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void		del_t_flag(t_flag **flag)
{
	if (!(flag && *flag))
		return ;
	remove_t_flag_s(*flag);
	ft_memdel((void**)flag);
	*flag = NULL;
}


/*
**	remove_one_shot_flags:
**		Removes flags that are effective for only one execution of the command
**		Frees up the char* parameters associated with them
**		This function do not return a value
*/

void		remove_one_shot_flags(t_flag *flag)
{
	if (!flag)
		return ;
	remove_t_flag_s(flag);
	if (flag->masks_sum & FLAG_P)
		flag->masks_sum -= FLAG_P;
}

/*
**	remove_t_flag_s:
**		Removes the 's' flag mask to the int sum of bitwise masks
**			of the t_flag* structure
**		Frees up the char* parameter of the flag 's'
**		The function do not return a value
*/

void		remove_t_flag_s(t_flag *flag)
{
	if (!flag)
		return ;
	if (flag->masks_sum & FLAG_S)
		flag->masks_sum -= FLAG_S;
	if (flag->s)
		ft_strdel(&flag->s);
}

/*
**	remove_t_flag_mask:
**		Removes a mask to the sum of bitwise masks of the t_flag* structure
**		Frees up the optional char* parameter linked to the flag
**		The function do not return a value
*/

void		remove_t_flag_mask(t_flag *flag, int mask_nb)
{
	if (!flag || !(flag->masks_sum & mask_nb))
		return ;
	else if (mask_nb == FLAG_S)
		remove_t_flag_s(flag);
	else
		flag->masks_sum -= mask_nb;
}


/*
**	add_t_flag_mask:
**		Adds a new mask to the sum of bitwise masks of the t_flag* structure
**		Links an optional char* parameter to the flag
**		The function do not return a value
*/

void		add_t_flag_mask(t_flag *flag, int mask_nb, char *parameter)
{
	if (!flag)
		return ;
	if (!(flag->masks_sum & mask_nb))
	{
		flag->masks_sum += mask_nb;
		if (!parameter)
			return ;
		if (mask_nb == FLAG_S)
			flag->s = ft_strdup(parameter);
	}
}


/*
**	init_t_flag:
**		Allocates memory for a new t_flag* structure
**		Initializes its variables
**		Returns it or NULL if an allocation failed
*/

t_flag		*init_t_flag(void)
{
	t_flag		*flag;

	if (!(flag = ft_memalloc(sizeof(t_flag))))
		return (NULL);

	flag->masks_sum = 0;
	flag->s = NULL;

	return (flag);
}
