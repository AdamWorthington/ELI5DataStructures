#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node* left;
	struct node* right;
	int value;
} node;

void print_tree(node* root, int level);
node* insert_node(node* root, int value);
node* create_node(int value);

int main()
{
	node* root = NULL;

	int buffer = 0;
	while(buffer != -1){
    	scanf("%d", &buffer);
    	root = insert_node(root, buffer);
    	printf("\e[1;1H\e[2J"); //clears terminal for tree prints
    	print_tree(root, 0);
	}
    return 0;
}

node* create_node(int value){
	node* ret_node = (node*)malloc(sizeof(node));
	ret_node -> value = value;
	ret_node -> left = NULL;
	ret_node -> right = NULL;
	return ret_node;
}

node* insert_node(node* root, int value){
	if(root == NULL){
		return create_node(value);
	}
	if(root->value >= value){
		if(root -> left == NULL){
			root -> left = create_node(value);
		}
		else{
			insert_node(root -> left, value);
		}
	}
	else{
		if(root -> right == NULL){
			root -> right = create_node(value);
		}
		else{
			insert_node(root -> right, value);
		}
	}
	return root;
}

void print_tree(node* root, int level){
	if(root == NULL){
      return;
	}
	int counter = 0;
    print_tree(root -> left, level + 1);
    while(counter++ < level){
		printf(" ");
	}
    printf("%d\n",root -> value);
    print_tree(root -> right, level + 1);
}