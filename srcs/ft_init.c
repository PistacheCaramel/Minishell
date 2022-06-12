#include "minishell.h"

void	set_null(t_env *data)
{
	data->lexed = NULL;
	data->parsed = NULL;
	data->error = NULL;
	data->temp = NULL;
	data->nb_token = 0;
	data->nb_parsed = 0;
	data->error = NULL;
	data->temp = NULL;
	data->c_tbls = NULL;
	data->env = NULL;
}

int	ft_init(t_env *data)
{
	data->tab = NULL;
	set_null(data);
	if (token_init(data) == -1)
		return (-1);
	return (0);
}
