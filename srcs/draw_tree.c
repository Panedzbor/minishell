#include "../includes/minishell.h"
#include <math.h>

static void save_matrix(t_tree_node *tree, int depth, int width, t_tree_node *matrix[][width]);
static void save_matrix_val(t_tree_node *tree, int level, int depth, int width, t_tree_node *matrix[][width], int *index_state);
// static void print_matrix(int depth, int width, t_tree_node *matrix[][width]);
static void print_line(int max_nodes_line, int field, int level, int depth, t_tree_node *matrix[][max_nodes_line], FILE *file);
static void init_slashes(char *str, int len);
static char *get_symbol(t_tree_node *node);
static int count_tree_depth(t_tree_node *node, int curlevel);

void draw_tree(t_tree_node *tree)
{
	FILE *file = fopen("tree.txt", "w");

	int depth;
	int width = 0;
	int field = 10;

	depth = count_tree_depth(tree, 0);/* printf("depth: %d\n", depth); */
	width = (int)pow(2, depth);/* printf("width: %d\n", width); */
	t_tree_node *matrix[depth + 1][width];

	save_matrix(tree, depth, width, matrix);
	/* print_matrix(depth, width, matrix); */

	for (int level = 0; level <= depth; level++)
		print_line(width, field, level, depth, matrix, file);

	fclose(file);
}

static void save_matrix(t_tree_node *tree, int depth, int width, t_tree_node *matrix[][width])
{
	for (int i = 0; i <= depth; i++)
		ft_bzero(matrix[i], sizeof(t_tree_node *) * width);

	int index_state[depth + 1];
	ft_bzero(index_state, sizeof(int) * (depth + 1));

	save_matrix_val(tree, 0, depth, width, matrix, index_state);
}

static void save_matrix_val(t_tree_node *tree, int level, int depth, int width, t_tree_node *matrix[][width], int *index_state)
{
	if (!tree)
		return ;
	matrix[level][index_state[level]] = tree;
	(index_state[level])++;
	if (tree->left)
		save_matrix_val(tree->left, level + 1, depth, width, matrix, index_state);
	else
	{
		for (int i = level + 1, e = 0; i <= depth; i++, e++)
		{
			for (int z = (int)pow(2, e), y = 0; y < z; y++)
				(index_state[i])++;
		}
	}
	if (tree->right)
		save_matrix_val(tree->right, level + 1, depth, width, matrix, index_state);
	else
	{
		for (int i = level + 1, e = 0; i <= depth; i++, e++)
		{
			for (int z = (int)pow(2, e), y = 0; y < z; y++)
				(index_state[i])++;
		}
	}
}

// *** DO NOT DELETE! ***
// static void print_matrix(int depth, int width, t_tree_node *matrix[][width])
// {
// 	for (int i = 0; i <= depth; i++)
// 	{
// 		int nodes_cur_line = (int)pow(2, i);
// 		for (int j = 0; j < nodes_cur_line; j++)
// 		{
// 			if (matrix[i][j])
// 				printf("%s ", get_symbol(matrix[i][j]));
// 			else
// 				printf("[_empt_] ");
// 		}
// 		printf("\n");
// 	}
// }
// *** DO NOT DELETE! ***

static void print_line(int max_nodes_line, int field, int level, int depth, t_tree_node *matrix[][max_nodes_line], FILE *file)
{
	t_tree_node **print_arr = matrix[level];

	int width = max_nodes_line * field;/* printf("line width: %d\n", width); */
	int nodes_cur_line = (int)pow(2, level);/* printf("nodes: %d\n", nodes_cur_line); */
	int start = (int)round((double)width / (nodes_cur_line * 2) + (double)field / 2);/* printf("start: %d\n", start); */
	int offset = (int)round((start - (double)field / 2) * 2);/* printf("offset: %d\n", offset); */
	int space = start;

	char slashes[width + 1];
	init_slashes(slashes, width + 1);
	
	for (int i = 0; i < nodes_cur_line; i++)
	{
		if (i)
			space = offset;
		if (print_arr[i])
		{
			fprintf(file, "%*.*s", space, space, get_symbol(print_arr[i]));
			int len = (int)ft_strlen(get_symbol(print_arr[i]));
			int fslash = start + i * offset - len - 1;
			int bslash = fslash + len + 1;
			if (print_arr[i]->left)
				slashes[fslash] = '/';
			if (print_arr[i]->right)
				slashes[bslash] = '\\';
		}
		else
			fprintf(file, "%*.*s", space, space, " ");
	}
	fprintf(file, "\n");
	
	if (level < depth)
		fprintf(file, "%s\n", slashes);
}


static void init_slashes(char *str, int len)
{
	for (int i = 0; i < len - 1; i++)
		str[i] = ' ';
	str[len - 1] = '\0';
}

static char *get_symbol(t_tree_node *node)
{
	char *str = "";

	if (node->type == NODE_AND)
		return ("[ && ]");
	else if (node->type == NODE_OR)
		return ("[ || ]");
	else if (node->type == NODE_PIPE)
		return ("[ | ]");
	else if (node->type == NODE_REDIRECT_IN)
		return ("[ < ]");
	else if (node->type == NODE_REDIRECT_IN_MANUAL)
		return ("[ << ]");
	else if (node->type == NODE_REDIRECT_OUT)
		return ("[ > ]");
	else if (node->type == NODE_REDIRECT_OUT_APPEND)
		return ("[ >> ]");
	else if (node->type == NODE_SUBSHELL)
		return ("(SUBSHELL)");
	else if (node->type == NODE_COMMAND || node->type == NODE_VAR_ASSIGN)
	{
		str = node->argv[0];
		for (int i = 1; node->argv[i]; i++)
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, node->argv[i]);
		}
		str = ft_strjoin("[", str);
		str = ft_strjoin(str, "]");
		return (str);
	}
	return NULL;
}

static int count_tree_depth(t_tree_node *node, int curlevel)
{
	int minlevel = curlevel;
	int temp_level = 0;

	if (node->left)
	{
		minlevel = count_tree_depth(node->left, curlevel + 1);
	}
	if (node->right)
	{
		temp_level = count_tree_depth(node->right, curlevel + 1);
	}
	minlevel = temp_level > minlevel ? temp_level : minlevel;
	return (minlevel);
}


