#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) (((a)>(b))?(a):(b)) // If A>B return A else return B


typedef struct node{
    struct node *left;
    struct node *right;
    int height;
    int data;
}Node;


int findHeight(Node *root){
    if(root == NULL)
        return -1;
    return root->height;

}

Node *rightRotate(Node *root){
    Node *temp = root->left;
    Node *temp1 = temp->right;

    temp->right = root;
    root->left = temp1;

    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
    temp->height = MAX(findHeight(temp->left), findHeight(temp->right)) + 1;

    return temp;
}

Node *leftRotate(Node *root) {
    Node *temp = root->right;
    Node *temp1 = temp->left;

    temp->left = root;
    root->right = temp1;

    root->height = MAX(findHeight(root->left), findHeight(root->right)) + 1;
    temp->height = MAX(findHeight(temp->left), findHeight(temp->right)) + 1;

    return temp;
}

int diffRNL(Node *root){
    if(root == NULL)
        return 0;
    return findHeight(root->left) - findHeight(root->right);
}

Node *createNode(int data){
    Node *root = malloc(sizeof(Node));
    root->left = root->right = NULL;
    root->data = data;
    root->height = 1;
    return root;
}

Node *addNode(Node *root,int data){

    if (root == NULL)
        return(createNode(data));

    if (data < root->data)
        root->left  = addNode(root->left, data);

    else if (data > root->data)
        root->right = addNode(root->right, data);

    else
        return root;

    int difference;
    difference = diffRNL(root);

    root->height = 1 + MAX(findHeight(root->left), findHeight(root->right));

    if(difference > 1 && data < root->left->data)
        return rightRotate(root);

    if(difference < -1 && data > root->right->data)
        return leftRotate(root);

    if(difference > 1 && data > root->left->data)
    {
        root->left =  leftRotate(root->left);
        return leftRotate(root);
    }

    if(difference < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return rightRotate(root);

    }

    return root;

}


void preOrder(Node *root){
    if(root != NULL){
        printf("%d ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node *root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}


int main(void)
{
    clock_t t;
    t = clock();

    Node *root = NULL;

    root = addNode(root, 10);
    root = addNode(root, 20);
    root = addNode(root, 30);
    root = addNode(root, 40);
    root = addNode(root, 50);
    root = addNode(root, 25);
    root = addNode(root, 13);
    root = addNode(root, 60);
    root = addNode(root, 1);
    root = addNode(root, 9);
    

    /* PRINT THE TREE*/

    printf("PREORDER\n");
    printf("===================\n");
    preOrder(root);
    printf("\n===================");
    printf("\nPOSTORDER\n");
    printf("===================\n");
    postOrder(root);
    printf("\n===================");
    printf("\nINORDER\n");
    printf("===================\n");
    inOrder(root);
    printf("\n===================\n");


    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("\nExecution Time : %f\n", time_taken);



    return 0;
}
