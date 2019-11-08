#include "shell.h"

t_aliaspkg *storeaddrstruct(t_aliaspkg *addr)
{
	static t_aliaspkg *ret;

	if (addr == NULL)
		return (ret);
	else
		ret = addr;
	return (ret);
}

void pushtolist(char *string, int flag)
{
	t_alias *node;
	t_aliaspkg *data;
	int	i;
	
	data = storeaddrstruct(NULL);
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	i = -1;
	while (string[++i] && string[i] != '=')
		;
	node->shortcut = ft_strsub(string, 0, ++i);
	node->cmd = handleqoutes(ft_strdup(string+i));
	node->flag = flag;
	node->next = NULL;
	if (!data->head_ref && !data->tail_ref)
		data->head_ref = data->tail_ref = node;
	else 
	{
		data->tail_ref->next = node;
		data->tail_ref = node;
	}
}

void createaliasfile()
{
	if (!(access("42shrc", F_OK) == 0))
		open("42shrc", O_CREAT, 0777);
}

void importaliasfilecontent()
{
	char	*line;
	char	*tmp;
	int		i;
	int	fd;
	
	line = NULL;
	fd = open("42shrc", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] && line[i] != '=')
			i++;
		tmp = ft_strsub(line, 0, i);
		removealiasbyelemorbyflag(tmp, 0);
		pushtolist(line, 1);
	}
}
