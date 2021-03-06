/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:07:36 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 19:52:56 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_temp(char **temp, t_env *data)
{
	if (ft_strlen(*temp) != 0)
	{
		if (get_lexed(temp, data, STR))
			return (-1);
	}
	return (0);
}

int	is_str_env(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_char_env(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

char	**ft_cpy(char **temp, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		(*temp)[i] = s1[i];
		i++;
	}
	return (temp);
}

void	*ft_calloc(size_t nmem)
{
	char	*ret;
	size_t	i;

	ret = malloc(nmem);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmem)
	{
		ret[i] = 0;
		i++;
	}
	return ((void *)ret);
}
