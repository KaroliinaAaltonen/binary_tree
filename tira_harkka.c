//Student: Karoliina Aaltonen
//Student ID: 0612213
//Date: 13/12/2021
//Sources: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
//       : https://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/
//       : Course material.
//       : https://www.programiz.com/dsa/avl-tree

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Linked list node
struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *first = NULL;

//BST node
struct TreeNode
{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
};

int maximum(int a, int b);
//height of the tree
int height(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
    }
//returns bigger from two int
int maximum(int a, int b)
{
    return (a > b)? a : b;
}
//Malloc new node for BST
struct TreeNode* newNode(int key)
{
    struct TreeNode* node = (struct TreeNode*)
    malloc(sizeof(struct TreeNode));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}
//right rotation as done in 7th week assignment on the course
struct TreeNode *rotate_right(struct TreeNode *temp_y)
{
    struct TreeNode *temp_x = temp_y->left;
    struct TreeNode *temp = temp_x->right;
    temp_x->right = temp_y;
    temp_y->left = temp;
    temp_y->height = maximum(height(temp_y->left), height(temp_y->right))+1;
    temp_x->height = maximum(height(temp_x->left), height(temp_x->right))+1;
    return temp_x;
}
//left rotation as done in 7th week assignment on the course
struct TreeNode *rotate_left(struct TreeNode *node)
{
    struct TreeNode *temp_y = node->right;
    struct TreeNode *temp = temp_y->left;
    temp_y->left = node;
    node->right = temp;
    node->height = maximum(height(node->left), height(node->right))+1;
    temp_y->height = maximum(height(temp_y->left), height(temp_y->right))+1;
    return temp_y;
}
//maintaining tree balance
int get_tree_balance(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}  
//inserting node from linked list (key) to BST
struct TreeNode* insert(struct TreeNode* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);

    else if (key > node->key)
        node->right = insert(node->right, key);

    else
        return node;

    node->height = 1 + maximum(height(node->left),height(node->right));

    int balance = get_tree_balance(node);

    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    if (balance < -1 && key > node->right->key)
        return rotate_left(node);
        
    if (balance > 1 && key > node->left->key)
        {
        node->left =  rotate_left(node->left);
        return rotate_right(node);
        }
    if (balance < -1 && key < node->right->key)
        {
        node->right = rotate_right(node->right);
        return rotate_left(node);
        }
    return node;
}   

//used with delete_node() to see if node is minimum not part of the assignment!
struct TreeNode * minimum_value_node(struct TreeNode* node)
{
    struct TreeNode* current = node;
    //most left child is the smallest
    while (current->left != NULL)
        current = current->left;
    return current;
}

//deleting a node (not part of the assignment!)
struct TreeNode* delete_node(struct TreeNode* base, int key)
{
    if (base == NULL)
        return base;

    if ( key < base->key )
        base->left = delete_node(base->left, key);

    else if( key > base->key )
        base->right = delete_node(base->right, key);

    else{
        if( (base->left == NULL) || (base->right == NULL) ){
                struct TreeNode *temp = base->left ? base->left :base->right;
                if (temp == NULL){           
                    temp = base;
                    base = NULL;
                }
        else
            *base = *temp;
        free(temp);
    }
        else{
            struct TreeNode* temp = minimum_value_node(base->right);
            base->key = temp->key;
            base->right = delete_node(base->right, temp->key);
        }
}   
    if (base == NULL)
        return base;

    base->height = 1 + maximum(height(base->left),
    height(base->right));
    int balance = get_tree_balance(base);
    if (balance > 1 && get_tree_balance(base->left) >= 0)
        return rotate_right(base);

    if (balance > 1 && get_tree_balance(base->left) < 0){
        base->left =  rotate_left(base->left);
        return rotate_right(base);
    }
    if (balance < -1 && get_tree_balance(base->right) <= 0)
        return rotate_left(base);
    if (balance < -1 && get_tree_balance(base->right) > 0){
        base->right = rotate_right(base->right);
        return rotate_left(base);
    }   
    return base;
}
//Printing preordered BST
void print_preorder(struct TreeNode *base)
    {
    if(base != NULL)
        {
        printf("%d ", base->key);
        print_preorder(base->left);
        print_preorder(base->right);
    }
}
//2D representation of the BST
void print_in_2D(struct TreeNode *root, int place, int ordinal){
    ordinal++;
    // Prints the balanced tree out so that the node is on the left, right child below and left side above.
    int count = 10;
    if(root==NULL){
        return;
    }
    
    place += count;
    print_in_2D(root->right, place, ordinal);

    printf("\n");
    for(int i= count; i < place; i++){
        printf(" ");
    }
    printf("%d (%d)\n", root->key, ordinal);
    
    print_in_2D(root->left, place, ordinal);
    return;
}
//user menu option 1 -- create file
void create_file(){
    // Creates file with the name user chooses and then asks user to input the integers that are made into a balanced tree.
    char file_name[20];
    int user_input;
    int integer_written_in_file;
    FILE *fp;

    printf("Please give the name of the file where integers will be stored:");
    fgets(file_name, sizeof(file_name), stdin);
    gets(file_name);
    printf("Integers are stored in file %s\n", file_name);

    
    fp = fopen (file_name, "w");
    if(fp==NULL){
        printf("Error opening file. Terminating program.");
        exit(1);
    }

    printf("Please input the number of integers you wish to write in the file %s:", file_name);
    scanf("%d", &user_input);
    printf("Please give %d integers to be written in the file.\n", user_input);

    for(int i=0; i< user_input; i++){
        printf("%d:",i+1);
        scanf("%d", &integer_written_in_file);
        fprintf(fp, "%d\n", integer_written_in_file);
    }

    fclose(fp);
    printf("\nFile was written succesfully!\n");
}
//creating linked list from a file user gives
int create_linked_list(){
    int number_array[100000];
    char file_name[20];
    FILE *fp;

    struct ListNode *temp;
    struct ListNode *last;

    //allocate memory for the node
    first = (struct ListNode *)malloc(sizeof(struct ListNode));

    //name of the file as user input
    printf("Please give the name of the file you want to read:");
    fgets(file_name, sizeof(file_name),stdin);
    gets(file_name);

    //opening file
    fp = fopen(file_name, "r");
    if(fp==NULL){
        printf("Error opening file. Terminating program.");
        exit(1);
    }

    //integers from the file are added to an array first
    int count;
    int i=0;
    while(fscanf(fp, "%d", &number_array[i]) != EOF){
        i++;
        count++;
    }
    fclose(fp);
    number_array[i] = '\0';

    //numbers in the created array 'number_array'
    printf("\nThe numbers you gave are: ");
    for(i=0; number_array[i] != '\0'; i++){
        printf("%d, ",number_array[i]);
    }

    //assing first array element as first element in linked list
    first->data = number_array[0];
    first->next = NULL;
    last = first;

    //create the rest of linked list from array data
    for (i=1; i < count; i++){
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp->data = number_array[i];
        temp ->next = NULL;
        last->next = temp;
        last = temp;
    }

    return 0;
}
//sorting linked list so it is easier to make into a BST
void sort_linked_list(){
    //sorting linked list
    struct ListNode *current = first, *index = NULL;
    int temp;

    //if list is empty
    if(first == NULL){
        return;
    }

    else{
        while(current != NULL){
            //index points to the next node from current node
            index = current->next;
        
        //while next node is not end of list
        while(index != NULL){
            //compare current and next number
            if(current->data > index->data){
                temp = current->data;
                current->data = index->data;
                index->data = temp;
                }
            //move pointer to next by one
            index = index->next;
            }
        //move current to next
        current = current->next;
        }
    }
}
//display linked list for user
int display_linked_list(struct ListNode *pointer){
    int count;
    printf("\n\nContents of linked list are ");
    while( pointer != NULL){
        count++;
        printf("%d, ", pointer->data);
        pointer = pointer->next;
    }
    return count;
}
//search BST for given key
struct TreeNode* search_balanced_tree_key(struct TreeNode *root, int key, const char* child){

    if(root==NULL){
        printf("\nKey was not found from the balanced tree.\n");
        return root;
    }

    if (root->key == key){
        if(strcmp(child, "root")==0){
            printf("\nKey is the root of the balanced tree.\n");
            return root;
        }
        else if(strcmp(child, "left")==0){
            printf("\nKey is a left child in the balanced tree.\n");
            return root;
        }
        else if(strcmp(child, "right")==0){
            printf("\nKey is a right child in the balanced tree.\n");
            return root;
        }
        
    }
    
    if (root->key < key){
        return search_balanced_tree_key(root->right, key, "right");
    }
    
    if(root->key > key){
        return search_balanced_tree_key(root->left, key, "left");
    }
    return root;
}
//helper function for search_balanced_tree_key()
void search_helper_function(struct TreeNode *root){
    int key;
    printf("\nInput a key you want to find from the balanced tree: ");
    scanf("%d",&key);
    search_balanced_tree_key(root, key, "root");
    }

// Start of the program
int main()
{
    int menu_choice;
    struct TreeNode *base = NULL;
    int count;
    printf("Welcome to binary tree creator by Karoliina Aaltonen\n\n");

    while(menu_choice != 0){
        printf("\nWhat would you like to do?\n");
        printf("\n1) create a new file\n2) read a pre-existing file into a linked list\n3) Print print preorder traversal of the balanced tree\n4) Print balanced tree\n5) Search for key\n6) Insert a key\n7) Delete a key\n0) End\n");
        printf("Your choice: ");
        scanf("%d",&menu_choice);
        if(menu_choice==1){
            create_file();
            continue;
        }
        else if(menu_choice==2){
            create_linked_list();
            sort_linked_list();     
            display_linked_list(first);
            while(first != NULL){
                first->data;
                base = insert( base, first->data);
                first = first->next;
                count++;
            }
            continue;
        }
        else if(menu_choice==3){
            print_preorder(base);
            continue;
        }
        else if(menu_choice==4){
            print_in_2D(base, 0, 0);
            continue;
        }
        else if(menu_choice == 5){
            search_helper_function(base);
            continue;
        }
        else if(menu_choice == 6){
            int new_key;
            printf("Input a key you want to insert to the balanced tree: ");
            scanf("%d", &new_key);
            insert(base, new_key);
            continue;
        }
        else if(menu_choice==7){
            int key_to_delete;
            printf("Input a key you want to delete from the balanced tree: ");
            scanf("%d", &key_to_delete);
            delete_node(base, key_to_delete);
            continue;
        }
        else if(menu_choice==0){
            printf("Thank you for using the program!\n");
            break;
        }
    }
    return 0;
}