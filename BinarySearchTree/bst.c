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
node* find_node(node* root, int value);
node* delete_node(node* root, int value, int direction);
node* find_min(node* root);

int main()
{
	node* root = NULL;
	int buffer = 0;
	int choice = 0;
	while(1){
		printf("1: Insert\n2: Traverse\n3: Delete\n4: Quit\n");
		scanf("%d", &choice);
		
		if(choice == 1){
			printf("Node to insert: ");
			scanf("%d", &buffer);
			printf("\e[1;1H\e[2J"); //clears terminal for tree prints
    		root = insert_node(root, buffer);
    	}
    	else if(choice == 2){
    		printf("Node to find: ");
    		scanf("%d", &buffer);
    		printf("\e[1;1H\e[2J"); //clears terminal for tree prints
    		printf("Path to %d:\n", buffer);
    	
    		find_node(root, buffer);
    		printf("_______________________\n");
    	}
    	else if(choice == 3){
    		printf("Node to delete: ");
    		scanf("%d", &buffer);
    		printf("\e[1;1H\e[2J"); //clears terminal for tree prints
    		root = delete_node(root, buffer, 0);

    	}
    	else if(choice == 4){
    		exit(0);
    	}
    	else{
    		printf("\e[1;1H\e[2J"); //clears terminal for tree prints
    		printf("Invalid choice try again\n");
    		printf("_______________________\n");
    	}
    	printf("Tree:\n");
    	print_tree(root, 0);
    	printf("_______________________\n");
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

node* find_node(node* root, int value){
	printf("%d", root -> value);
	if(value == root -> value){
		printf("\n");
		return root;
	}
	if(root -> value >= value){
		printf(" <- ");
		return find_node(root -> left, value);
	}
	else{
		printf(" -> ");
		return find_node(root -> right, value);
	}
}

node* delete_node(node* root, int value, int direction){
	if(value == root -> value){
		node* new_root = NULL;
		if(root -> right != NULL){
			new_root = find_min(root -> right);
			if(new_root != root -> left && root -> left != NULL){
				new_root -> left = root -> left;
			}
		}
		else{
			if(root -> left != NULL){
				new_root = root -> left;
			}
		}
		free(root);
		return new_root;
	}
	if(root -> value >= value){
		root -> left = delete_node(root -> left, value, -1);
		return root;
	}
	else{
		root -> right = delete_node(root -> right, value, 1);
		return root;
	}
}

node* find_min(node* root){ //finds the minimum value node for the delete_node function
	if(root -> left == NULL){
		return root;
	}
	else{
		return find_min(root -> left);
	}
}

void print_tree(node* root, int level){
	if(root == NULL){
      return;
	}
	int counter = 0;
    print_tree(root -> left, level + 1);
    while(counter++ < level){ printf(" "); } //Used to format the printed tree
    printf("%d\n",root -> value);
    print_tree(root -> right, level + 1);
}