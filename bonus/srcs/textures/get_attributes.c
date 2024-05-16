#include <unistd.h>

#include "cubdef.h"
#include "libft.h"
#include "cubscene.h"

static int set_attribute(char *identifier, char *str, t_elem *elem);

int get_attributes(char *identifier, t_elem *elem)
{
	char *token;


	token = ft_strtok(NULL, " ");
	while (token)
	{
		if (0 != set_attribute(identifier, token, elem))
			return (-1);
		token = ft_strtok(NULL, " ");
	}
	return (0);
}

static int set_attribute(char *identifier, char *str, t_elem *elem)
{
	const char	*option[] = {ATTR_1, ATTR_2, ATTR_3, ATTR_4, ATTR_5, ATTR_6,
		NULL};
	int			i;
	int			len;

	i = 0;
	while (option[i])
	{
		len = ft_strlen(option[i]);
		if (0 == ft_strncmp(option[i], str, len))
		{
			return (0);
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_ATTR);
	return (-1);
	(void)elem;
}

// int set_frametime(char *identifier, char *str,)
// {

// }