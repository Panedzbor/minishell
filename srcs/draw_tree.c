#include "../includes/minishell.h"
#include <math.h>

static void print_branches(t_tree_node **print_arr, t_tree_node **print_arr_prev, int prev_start, int prev_offset, int nodes_cur_line);
static void save_matrix(t_tree_node *tree, int depth, int width, t_tree_node *matrix[][width]);
static void save_matrix_val(t_tree_node *tree, int level, int depth, int width, t_tree_node *matrix[][width], int *index_state);
static void print_matrix(int depth, int width, t_tree_node *matrix[][width]);
static void print_line(t_tree_node *tree, int max_nodes_line, int field, int level, int depth, t_tree_node *matrix[][max_nodes_line]);

void draw_tree(t_tree_node *tree)
{
	int depth;
	int width = 0;
	int field = 10;

	depth = count_tree_depth(tree, 0);/* printf("depth: %d\n", depth); */
	width = (int)pow(2, depth);/* printf("width: %d\n", width); */
	t_tree_node *matrix[depth + 1][width];

	save_matrix(tree, depth, width, matrix);
	print_matrix(depth, width, matrix);


	for (int level = 0; level <= depth; level++)
		print_line(tree, width, field, level, depth, matrix);


   /*  if (tree->left->right)
        printf("%d\n", tree->left->right->type);
    else
        printf("no\n"); */
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

static void print_matrix(int depth, int width, t_tree_node *matrix[][width])
{
	for (int i = 0; i <= depth; i++)
	{
		int nodes_cur_line = (int)pow(2, i);
		for (int j = 0; j < nodes_cur_line; j++)
		{
			if (matrix[i][j])
				printf("%s ", get_symbol(matrix[i][j]));
			else
				printf("[_empt_] ");
		}
		printf("\n");
	}
}

static void print_line(t_tree_node *tree, int max_nodes_line, int field, int level, int depth, t_tree_node *matrix[][max_nodes_line])
{
	/*t_tree_node *print_arr[max_nodes_line + 1];
	t_tree_node *print_arr_prev[max_nodes_line + 1];

	ft_bzero(print_arr, sizeof(t_tree_node *) * (max_nodes_line));
	ft_bzero(print_arr_prev, sizeof(t_tree_node *) * (max_nodes_line));*/


	t_tree_node **print_arr = matrix[level];
	t_tree_node **print_arr_prev;
	if (level)
		print_arr_prev = matrix[level - 1];


	int width = max_nodes_line * field;/* printf("line width: %d\n", width); */
	int nodes_cur_line = (int)pow(2, level);/* printf("nodes: %d\n", nodes_cur_line); */
	/* int last_line = max_nodes_line == nodes_cur_line; */
	int start = (int)round((double)width / (nodes_cur_line * 2) + (double)field / 2);/* printf("start: %d\n", start); */
	int offset = (int)round((start - (double)field / 2) * 2);/* printf("offset: %d\n", offset); */
    static int prev_start;
	static int prev_offset;
	/* if (last_line)
	{
		start = field;
		offset = field;
	} */

	/*int index = 0;
	save_nodes(tree, level, 0, print_arr, &index);*/
    /* printf("nodes cur line:");
    for (int y = 0; y < nodes_cur_line; y++)
    {
        if (print_arr[y])
            printf(" %s", get_symbol(print_arr[y]));
        else
            printf(" _empty_");
    } */
    printf("\n");
	if (level)
	{
		/*index = 0;*/
        /*save_nodes(tree, level - 1, 0, print_arr_prev, &index);*/
        print_branches(print_arr, print_arr_prev, prev_start, prev_offset, nodes_cur_line);
	}


	if (print_arr[0])
		printf("%*.*s", start, start, get_symbol(print_arr[0]));
	else
		printf("%*.*s", start, start, "_");
	for (int i = 1; i < nodes_cur_line; i++)
	{
		if (print_arr[i])
			printf("%*.*s", offset, offset, get_symbol(print_arr[i]));
		else
			printf("%*.*s", offset, offset, "_");
	}
	printf("\n");



	prev_start = start;
	prev_offset = offset;
}





static void print_branches(t_tree_node **print_arr, t_tree_node **print_arr_prev, int prev_start, int prev_offset, int nodes_cur_line)
{
    int fslash, bslash;
    int i = 0;
    int prev_i = 0;

    if (print_arr[i])
    {
        fslash = prev_start - ft_strlen(get_symbol(print_arr_prev[prev_i]));
        /* bslash = ft_strlen(get_symbol(print_arr_prev[0])) + 1; */
        printf("%*.*s", fslash, fslash, "/");
        /* printf("%*.*s", bslash, bslash, "\\"); */
    }
    else
        printf("%*.*s", prev_start + 1, prev_start + 1, ".");
    i++;
    for (; i < nodes_cur_line; i++)
    {
        if (i % 2 == 0)
            prev_i++;
        if (print_arr[i])
        {
            fslash = prev_offset - ft_strlen(get_symbol(print_arr_prev[prev_i])) - 1;
            bslash = ft_strlen(get_symbol(print_arr_prev[prev_i])) + 1;
            if (i % 2 == 0)
                printf("%*.*s", fslash, fslash, "/");
            else
            {
                printf("%*.*s", bslash, bslash, "\\");
                //prev_i++;
            }
        }
        else if (i > 1)
            printf("%*.*s", prev_offset + 1, prev_offset + 1, ".");
        //i++;

    }
    printf("\n");
}

void save_nodes(t_tree_node *tree, int target_level, int current_level, t_tree_node **print_arr, int *index)
{
	t_tree_node *cur;

	cur = tree;
	if (current_level == target_level)
	{
		print_arr[*index] = cur;
		(*index)++;
		return ;
	}
	if (cur->left && current_level < target_level)
		save_nodes(cur->left, target_level, current_level + 1, print_arr, index);
	else if (!cur->left && current_level < target_level)
		(*index)++;
	if (cur->right && current_level < target_level)
		save_nodes(cur->right, target_level, current_level + 1, print_arr, index);
	else if (!cur->right && current_level < target_level)
		(*index)++;
}

char *get_symbol(t_tree_node *node)
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
	else if (node->type == NODE_WORDS)
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

int count_tree_depth(t_tree_node *node, int curlevel)
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


