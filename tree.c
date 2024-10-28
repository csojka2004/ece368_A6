#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char type;
    int width;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* buildTree(const char* filename) {

    FILE* file = fopen(filename, "r");
    if(!file) return NULL;

    TreeNode* stack[100];
    int top = -1;
    
    char line[100];
    while(fgets(line, sizeof(line), file)) {
        if(line[0] == 'V' || line[0] == 'H'){
            TreeNode* node = malloc(sizeof(TreeNode));
            node->type = line[0];
            node->left = node->right = NULL;
                 
            if(top >= 1){
                node->right = stack[top--];
                node->left = stack[top--];
            }
            stack[++top] = node;
        }else{ // If we read 3(1,4) for example...
            TreeNode* node = malloc(sizeof(TreeNode));
            sscanf(line, "%c(%d,%d)", &node->type, &node->width, &node->height);
            node->left = node->right = NULL;
            stack[++top] = node;
        }
    }

    fclose(file);

    if(top == 0) return stack[0];
    
    return NULL;
}

void freeTree(TreeNode* node) {
    if(node){
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void preorder(TreeNode* node, FILE* file) {
    if(node){
        // Write the type of the node to the file
        if(node->type == 'H' || node->type == 'V'){
            fprintf(file, "%c\n", node->type);
        }else{
            fprintf(file, "%c(%d,%d)\n", node->type, node->width, node->height);
        }

        // Traverse the left subtree
        preorder(node->left, file);
        
        // Traverse the right subtree
        preorder(node->right, file);
    }
}

void dimension(TreeNode* node, FILE* file){
    if(node){

        // Traverse the left subtree
        dimension(node->left, file);
        
        // Traverse the right subtree
        dimension(node->right, file);

        // Add on dimensions
        if(node->type == 'H'){
            node->width = node->left->width > node->right->width ? node->left->width : node->right->width;
            node->height = node->left->height + node->right->height;
        }else if(node->type == 'V'){
            node->height = node->left->height > node->right->height ? node->left->height : node->right->height;
            node->width = node->left->width + node->right->width;
        }

        fprintf(file, "%c(%d,%d)\n", node->type, node->width, node->height);
    }
}

void coords(TreeNode* node, FILE* file, int x, int y) {
    if(node){
        // If leaf node, write the coordinates
        if(node->type != 'H' && node->type != 'V'){
            fprintf(file, "%c((%d,%d)(%d,%d))\n", node->type, node->width, node->height, x, y);
        
        // Otherwise, adjust the coordinates
        }else if (node->type == 'H'){
            coords(node->left, file, x, y + node->right->height);
            coords(node->right, file, x, y);
        }else if (node->type == 'V'){
            coords(node->left, file, x, y);
            coords(node->right, file, x + node->left->width, y);
        }
        
    }
}