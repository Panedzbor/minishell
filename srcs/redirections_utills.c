#include "../includes/minishell.h"

int	check_file(char *filename)
{
	struct stat	info;

	if (stat(filename, &info) == -1)
	{
		perror(filename);
		return (0);
	}
	return (1);
}

int	check_folder(char *filename)
{
	char	*folder_name;
	int		i;

	if (!ft_strchr(filename, '/'))
		return (1);
	i = 0;
	while (ft_strchr(filename + i, '/'))
		i++;
	folder_name = ft_substr(filename, 0, i);
	if (!folder_name)
		return (0);
	if (access(folder_name, F_OK) == -1)
	{
		free(folder_name);
		perror(filename);
		return (0);
	}
	free(folder_name);
	return (1);
}

static char	**alloc_arg_mem(int size)
{
	char	**temp;

	temp = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!check_alloc(temp))
		return (NULL);
	return (temp);
}

static void	ft_copy_arr(char **src, int src_strt, char **dest, int dest_strt)
{
	int	s;
	int	d;

	s = src_strt;
	d = dest_strt;
	while (src[s])
	{
		dest[d] = src[s];
		s++;
		d++;
	}
}

int	move_args(t_tree_node *node)
{
	int		rlen;
	int		llen;
	char	**temp;
	char	**dupl;

	rlen = ft_arr_el_count((void **)node->right->argv + 1);
	if (!rlen)
		return (1);
	llen = ft_arr_el_count((void **)node->left->argv);
	temp = alloc_arg_mem(llen + rlen);
	if (!temp)
		return (0);
	ft_copy_arr(node->left->argv, 0, temp, 0);
	dupl = ft_charrdup(node->right->argv + 1);
	ft_copy_arr(dupl, 0, temp, llen);
	free(dupl);
	temp[llen + rlen] = NULL;
	free(node->left->argv);
	node->left->argv = temp;
	return (1);
}
