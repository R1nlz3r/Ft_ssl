/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 02:22:20 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/22 06:02:01 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	infinite_loop(t_ssl **ssl)
{
	if (!ssl)
		return ;
	*ssl = NULL;
	while (1) {}
}

void	display_inputs(t_ssl *ssl)
{
	t_list		*lst = ssl->inputs;
	t_input		*input = NULL;
	int			index = 0;
	lst = ft_lststart(lst);
	while (lst)
	{
		input = (t_input*)lst->content;
		ft_printf("Node: %3d \033[34m|\033[0m\
 Flags: %3d \033[34m|\033[0m\
 Input: %20s \033[34m|\033[0m\
 Digest: %20s\n",
 			index, input->flags, input->input, input->digest);
		lst = lst->next;
		++index;
	}
}

void	display_t_ssl(t_ssl *ssl)
{
	ft_putendl("Ssl:");
	ft_printf("Command name: %8s \033[34m|\033[0m\
 Flags: %2d\n\
Return value: %8d \033[34m|\033[0m\
 Argc: %3d",
		ssl->command_name, ssl->flags, ssl->return_value, ssl->argc);
	ft_putendl("\n\nInputs:");
	display_inputs(ssl);
}
