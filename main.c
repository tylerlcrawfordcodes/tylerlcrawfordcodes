
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#define MAXSTRING 101
typedef char str100[101];
typedef struct BST_node
{
    char *word;
    int counter;
    struct BST_node* left;
    struct BST_node* right;
    
}BST_node;

BST_node *current;
struct BST_node *newNode;

struct BST_node* nodeCreate(str100 stringData, int counter);
struct BST_node* insertNode(BST_node *root, char *insertData, int caseFlag);
int caseSenStrCmp(char *string1, char *string2);
int caseInsStrCmp(char *string1, char *string2);
void printInOrder(FILE *outFile,BST_node* node);
void deletePostOrder(BST_node* node);

/**
 * Reads a textFile (if indicated, else stdin) and sorts the lines via ASCI comparison and outputs sorted 
 * lines along with count to output text file (or stdout)
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char **argv)
{
    int counter;
    extern char *optarg; 
    extern int optind; 
    FILE* outFile; 
    FILE* inFile; 
    BST_node *root;
    
    int caseFlag;
    int c, err = 0; 
    int cflag=0, oflag=0;
    char *oname;
    char inputBuffer[101]; 
    static char usage[] = "usage: % bstsort [-c] [-o output_file_name] [input_file_name] \n";

    while ((c = getopt(argc, argv, "co:")) != -1)
    {
        switch (c) {
        case 'c':
            cflag =1;
            if(caseSenStrCmp("\n", inputBuffer) == 0) 
            {
                int length = strlen(inputBuffer);
                inputBuffer[length - 1] = '\0'; 
                root = nodeCreate(inputBuffer, counter);
                insertNode(root, inputBuffer, caseFlag);
            }
            break;
        case 'o':
            oflag = 1;
            oname = optarg;
            break;
        case '?':
            err = 1;
            break;
        }
    }
    
    caseFlag = 0;
    inFile = fopen(argv[argc - 1], "r"); 
        if(inFile)
        {
            while(fgets(inputBuffer, 101, inFile) != NULL) 
            {
                        int length = strlen(inputBuffer);
                        inputBuffer[length - 1] = '\0'; //not exactly sure
                        root = nodeCreate(inputBuffer, counter);
                        insertNode(root, inputBuffer, caseFlag);
                 
            }
        if(ferror(inFile))
        {
            printf("Error in reading your file! \n%s", usage);  
            exit(1);
        }
        fclose(inFile);
        }
    
    if(oflag)
    {
        outFile = fopen(oname, "w"); 
            if(outFile == NULL)
            {
                fprintf(stderr, "Can't open output file.");
                exit(1);
            }
            printInOrder(outFile, current); //changed from root
            fclose(outFile);
            deletePostOrder(root);
            root = NULL;
    }
return 0;
}

    /**
     * creates a new tree node using the value passed as the parameter
     * @param stringData
     * @param counter
     * @return pointer to a newly created binary search tree node (BST_node*)
     */
    struct BST_node* nodeCreate(str100 stringData, int counter)
    {
        newNode = (BST_node*)malloc(sizeof(BST_node*));
        newNode->word = (char*)malloc((strlen(stringData))+1); 
        //newNode->word = stringData;
        strcpy(newNode->word, stringData); //added &
        //newNode -> inputBuffer = stingData;
        newNode -> counter = 1;
        newNode -> right = newNode -> left = NULL; //changed from 0
        return newNode;
        
    }

    /**
     * Inserts a new node into binary tree
     * @param root
     * @param insertData
     * @param caseFlag
     * @return unchanged node pointer
     */
    struct BST_node* insertNode(struct BST_node *root, char *insertData, int caseFlag) //changed from char *insertData
    {
        int compare;
        if( root == NULL)
        {
            return nodeCreate(insertData, 1);
        }
        else
        {
            current = root;
            while(current != NULL)
            {
                if(caseFlag == 1) 
                {
                    compare = caseSenStrCmp(insertData, current->word);
                    if (compare == 0)
                    {
                       current->counter++; 
                    }
                    else if (compare < 0)
                    {
                        current->left = insertNode(root->left, insertData, caseFlag);
                        return root;
                    }
                    else if (compare > 0)
                    {
                        current->right = insertNode(root->right, insertData, caseFlag);
                        return root;
                    }
                }
                else if(caseFlag == 0)
                {
                    compare = caseInsStrCmp(insertData, current->word);
                    if (compare == 0)
                    {
                       current->counter++; 
                    }
                    else if (compare < 0)
                    {
                        current->left = insertNode(root->left, insertData, caseFlag);
                        return root;
                    }
                    else if (compare > 0)
                    {
                        current->right = insertNode(root->right, insertData, caseFlag);
                        return root;
                    }
                }
            }
        }
        return root;
    }
    
    /**
     * Compares strings case sensitive
     * @param string1 string 1
     * @param string2 string 2
     * @return value based on ASCI string comparison
     */
    int caseSenStrCmp(char *string1, char *string2)
    {
        int i = 0;
        while((string1[i] != ('\0' | '\n')) && (string2[i] != ('\0' | '\n')))
        {
            if(string1[i] < string2[i])
            {
                return -1;
            }
            else if(string1[i] == string2[i])
            {
                return 0;
            }
            else
                return 1;
            i++;
        }
        if((string1[i] == ('\0' | '\n')) && (string2[i] != ('\0' | '\n')))
        {
            return 1;
        }
        else if((string1[i] != ('\0' | '\n')) && (string2[i] == ('\0' | '\n')))
        {
            return -1;
        }
        else return 0;
    }
    
    /**
     * Compares strings case insensitive
     * @param string1
     * @param string2
     * @return value on ASCI string comparison
     */
    int caseInsStrCmp(char *string1, char *string2)
    {
        int i = 0;
        while((string1[i] != ('\0' | '\n')) && (string2[i] != ('\0' | '\n')))
        {
            if(string1[i] >= 'A' && string1[i] <= 'Z')
            {
                string1[i] = string1[i] + 32;
            }
            if(string2[i] >= 'A' && string2[i] <= 'Z')
            {
                string2[i] = string1[i] + 32;
            }
            if(string1[i] < string2[i])
            {
                return -1;
            }
            else if(string1[i] == string2[i])
            {
                return 0;
            }
            else
                return 1;
            i++;
        }
        if((string1[i] == ('\0' | '\n')) && (string2[i] != ('\0' | '\n')))
        {
            return 1;
        }
        else if((string1[i] != ('\0' | '\n')) && (string2[i] == ('\0' | '\n')))
        {
            return -1;
        }
        else return 0;
    }
    
    /**Prints output file with bst nodes via inorder traversal.
     */
    void printInOrder(FILE *outFile,struct BST_node* root)
    {
        if(root == NULL)
        {
            printf("No elements to display");
            return;
        }
        else
        if (root->left != NULL)
        {
        printInOrder(outFile, root->left);
        }
        if(root->word != NULL)
        {
        fprintf(outFile, "%s [%d] \n", root->word, root->counter);
        }
        if(root->right != NULL)
        {
        printInOrder(outFile, root->right);
        }
    }
    
    /**
     * Clears the BST via post order traversal.
     * @param node
     */
    
    void deletePostOrder(BST_node* node)
    {
        if(node == NULL)
        {
            return;
        }
        deletePostOrder(node->left);
        deletePostOrder(node->right);
        //free(node->word); - not included (maybe dont need it)
        free(node);
    }
