#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>

/*
 
 Created Date: 24/08/13
 Mohammed Kashem - 1030250
 
 Advance Programming coursework: ==
 
 This program should be able to read in two text files and detect the most common words from file 1 and file 2
 and print them out on the console. There are some testing that I have left in but commented out, this was done
 to make sure the program works and no errors were found while implementing.
 
 The Binary Search tree method was used for efficency and to ensure that the words were stored and making sure it
 was processing the words correctly by detecting the words from file 1 and that appears the same in file 2 and
 then printing them out in a aphabetical order.
 
 Task Brief -
 
 1. First Argument is set for xxxx.txt that i§s located on your system and that would be read
 in by an another argument
 
 2. Second Argument is that it reads the xxxx.txt and detects the most common words
 
 3. This stores the words and order them in sequence and prints the common words out, it converts all of the
 words to lower case.
 
 4. Error Checkings, if the file format is not regonised it will return a error, if one file is read in, it will
 return a error, if same files have been read in, it will also return a error.
 This ensure by reading in two different text files, the correct output of the common words is printed in order.
 
 */

#define MAX_SIZE 30 // this is the maxmime size word length that the words would read, max size of buffer to copy

FILE* fileout = 0; // input file if used

// structure of bnode = Binary Tree, word, left subtree, and right subtree

struct bnode{ // The structure of the tree is created
    
    char* word;
    struct bnode* left;  // Left subtree
    struct bnode* right; // right subtree
};

// check to see it is a word or not, if not then it will be ignored

int isWord(char* letters){
    
    // loop all characters of the word to check if it is words and ingore numbers and spaces
    
    for ( ; *letters; ++letters){
        
        // if it is not 'a'..'z' and 'A'..'Z' that is invalid so it will treat it as space and ignore it
        if (!((*letters >='a' && *letters <='z')||(*letters >='A' && *letters <='Z')))
            
            return 0;
    }
    
    return 1;
}   // returns the value


// Constructor for bnode -  the structure of a tree

struct bnode* createNode(char* line){
    
    // allocates memory for the bnode, allocate the memory that is needed to work
    
    struct bnode* newNode = malloc(sizeof(struct bnode));
    // the size of the new node and will need memory when increased
    
    newNode -> word = (char*) malloc((sizeof (char))*(strlen(line)));
    // increases the memory when needed and selects from left to right by line
    
    strcpy(newNode -> word,line);
    // copies from left to right to the word and the line
    
    newNode -> left = NULL;
    newNode -> right = NULL;
    // Makes null for left search tree and right search tree
    
    return newNode;
}

//inserts a node into a tree

struct bnode* insertNode(struct bnode* root, char* line, int boolean){
    
    int leftOrRight = 0;
    //Boolean to insert left search tree or right search tree
    
    if(root == NULL){
        //tree is empty, create new node and add to the tree
        
        root = createNode(line);
        //returns created node tree
        
        return root;
    }
    
    if(boolean == 0){ //case insensitive
        leftOrRight = strcmp(line, root->word);
    }
    else{ // case sensitive
        
        leftOrRight = strcasecmp(line, root->word);
    }
    if(leftOrRight <= 0){ // if inserting to left insert to left
        
        root -> left = insertNode(root -> left, line, boolean);
        
        return root; // return node that already exists
    }
    else{ // else insert to the right
        
        root -> right = insertNode(root -> right, line, boolean);
        
        return root; // return node that already exists
        
    }
    
}

void convert(char* letters){
    
    for ( ; *letters; ++letters) *letters = tolower(*letters);
    // the error of this was that when the words were printed some were upper case words, to resolve this I used
    // this fuction to converts the words to all to lower cases
}

// in-order-traversal

void printInOrder(struct bnode* root){
    
    // this prints them in order
    if(root != NULL){
        
        if((root -> left) != NULL) // this is 0
            printInOrder(root -> left); // this checks the words from the left
        convert(root -> word); // convert to word
        
        printf("%s\n",root -> word);
        // prints all the words from the root
        
        if((root -> right) != NULL) // this is 0
            printInOrder(root -> right); // this checks the words from the right
        // convert(root -> word);
        
    }
}

//search the tree ---------------------

int searchTree(char* word,struct bnode* root, int boolean){
    
    struct bnode* current = root; // the stuct of bnode
    int leftOrRight; // variable for left or right
    
    while(current!=NULL){
        
        if(boolean==0)
            leftOrRight = strcmp(word,current->word);
        // checks the words that is left and right and compares it
        
        else
            
            leftOrRight = strcasecmp(word,current->word);
        // checks the words cases senitive.
        
        if(leftOrRight==0)
            // if it is right or left
            
            return 1;
        
        else if(leftOrRight<0){
            
            current = current->left;
            // stores the current of left
            
        } else {
            
            current = current->right; // Stores the current of right
            
            // this searches the tree and find the words and checks them
            // left and right and puts them in order
        }
    }
    
    return 0;
}

// main function as entry point of the program ----------------

int main(int argc, char** argv){
    
    int boolean = 1; //boolean remains 0 if -c not present
    
    FILE* filein1 = 0; //input file if used
    FILE* filein2 = 0; //input file if used
    
    char buffer[MAX_SIZE]; // the max size of word length, is intilised above
    char* copy = 0;
    struct bnode* root = NULL;  // this is a 0 pointer
    struct bnode* croot = NULL; // this is a 0 pointer
    char* input_file1; // char pointer for file 1
    char* input_file2; // char pointer for file 1
    
    // error checking
    
    if(argc<3)
        
    {
        // here if you don't input two input files or just one, it will give you a error
        printf("Please import two text files in order for it to work");
        
        return 0;
    }
    
    input_file1= argv[1]; // input file 1 for same file, returns a error
    input_file2= argv[2]; // input file 2 for same file, returns a error
    
    if(strcmp(input_file1,input_file2)==0) // error checking for same file input
        
    {
        // this is where the same input file is not allowed and will give you an error
        printf("The same input file is NOT ALLOWED!");
        
        return 0;
    }
    
    filein1 = fopen(input_file1, "r"); // Reads file 1
    filein2 = fopen(input_file2, "r"); // Reads file 2
    
    if(filein1 == NULL || filein2 == NULL)
        // if file 1 and file 2 is empty or not regonised, it will return an error
        
    {
        
        // This is where you read in a text format that is not regonised and will give you a error
        printf("Read in file error!");
        
        return 0;
    }
    
    //read from file and store from bother files of file 1 and file 2
    
    while(fscanf(filein1, "%s", buffer)==1){
        //while more input
        
        copy =(char*) malloc(sizeof(char)*strlen(buffer));
        // this stores the size of char pointer of malloc and strlen size
        
        strcpy(copy, buffer);
        // this copies the size of buffer to copy
        
        if(isWord(copy))
            root = insertNode(root, copy, boolean);
        // insert line to binary search tree
    }
    
    while(fscanf(filein2, "%s", buffer)==1){ // while more input
        
        copy =(char*) malloc(sizeof(char)*strlen(buffer));
        // char pointer of malloc strlen size
        
        strcpy(copy, buffer);
        // copy buffer to copy
        
        if(searchTree(copy,root,boolean)==1 && searchTree(copy,croot,boolean)==0 && isWord(copy))
            
            croot = insertNode(croot, copy, boolean);
        
        // This inserts the line to main, this makes sure that it is the words that
        // is being copied and ignoring the rest
    }
    
    fclose(filein1); // close file 1
    fclose(filein2); // close file 2
    
    printf("<--------- The list of common words that appear ------------->\n");
    // this is a print command of the common words
    
    printInOrder(croot);
    //print ordered data to stdout/file, that prints all the words in order
    
    //getchar();
    
}



