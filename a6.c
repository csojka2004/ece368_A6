#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.c"

int main(int argc, char *argv[]) {

    // Executable must have 5 arguments
    if (argc != 5) return EXIT_FAILURE;

    // Build the tree based on in_file
    TreeNode* root = buildTree(argv[1]);

    // Write the preorder in out_file1
    FILE* out_file1 = fopen(argv[2], "w");
    if (!out_file1) {
        freeTree(root);
        return EXIT_FAILURE;
    }
    preorder(root, out_file1);
    fclose(out_file1);

    // Write the dimensions in out_file2
    FILE* out_file2 = fopen(argv[3], "w");
    if (!out_file2) {
        freeTree(root);
        return EXIT_FAILURE;
    }
    dimension(root, out_file2);
    fclose(out_file2);

    
    // Write the coords in out_file3
    FILE* out_file3 = fopen(argv[4], "w");
    if (!out_file3) {
        freeTree(root);
        return EXIT_FAILURE;
    }

    int x = 0;
    int y = 0;

    coords(root, out_file3, x, y);
    fclose(out_file3);
    
    freeTree(root);

    return EXIT_SUCCESS;
}