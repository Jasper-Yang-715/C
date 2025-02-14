/*
 * Author: 
 * Purpose: 
 * Language:  C
 * File: ASN5.c 
 * Solution to assignment 5, CECD 3401 Fall 2021
 */

#include "ASN5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


LinkedList* llist_initialize(){

    //int a = malloc(sizeof(int));
    LinkedList *linkedlist = malloc(sizeof(LinkedList));
    if(linkedlist == NULL){
        return NULL;
    }


    linkedlist->size = 0;
    linkedlist->first = NULL;
    linkedlist->last = NULL;

    return linkedlist;
}


Node * make_Node(char * word){

    Node * node = (Node *) malloc(sizeof(Node));
    //initialize node members' value
    strcpy(node->word, word);
    node->next = NULL;
    node->prev = NULL;

    return node;
}


bool llist_add_node(LinkedList * linkedlist, char * word){
    if(linkedlist == NULL || word == NULL){
        return false;
    }

    Node * node = make_Node(word);

    if(linkedlist->size == 0){
        linkedlist->first = node;
        linkedlist->last = node;
        linkedlist->size++;
        //printf("at add node, the added new node is %s\n", node->word);       
    }
    else if (checkWord(linkedlist, word)){

        Node * node_copy = linkedlist->first;   
        for(int i = 0; i < linkedlist->size - 1; i++){            
            if(strcmp(node_copy->next->word, word) == 0){
                if(node_copy->next == NULL){
                    node_copy = NULL;  
                }
                else{
                    node_copy->next = node_copy->next->next;
                }
                linkedlist->size--;
            }
            node_copy = node_copy->next;
        }
    }
    else {
        //if the word is not in the list
        //!false == true
        node->next = linkedlist->first;
        linkedlist->first = node;
        linkedlist->size++;
        //printf("at add node, the added new node is %s\n", node->word);
    }


    return true;
}


void llist_remove(LinkedList *linkedList, int index){
    Node *prev = linkedList->first;
    int i = 0;
    while(i < index - 1){
        prev = prev->next;
        i += 1;
    }
    prev->next = prev->next->next;
    linkedList->size--;
}



//check if the word is already exit in the list
//if it is there, then return the index, otherwise return -1
bool checkWord(LinkedList * linkedlist, char * word){
    if(linkedlist == NULL || word == NULL){
        return false;
    }
    else{
        Node * node = linkedlist->first;
        for(int i = 0; i < linkedlist->size; i++){
            if(strcmp(node->word, word) == 0){
                return true;
            }
            node = node->next;
        }
        return false;
    }
    return false;
}




Node * SearchWord(LinkedList * linkedlist, int index){
    //initialize a node point to linkedlist first node
    Node * node = linkedlist->first;
    for(int i = 1; i < index; i++){
        node = node->next;
    }
    printf("%s", node->word);
    return node;
}



int main () {

    FILE * fptr;
    //initialzie a linked list

    LinkedList * linkedlist = llist_initialize();

    fptr = fopen("test1 comp.dat", "r");

    //fptr = fopen("test3.txt", "r");
    /* 
     * Open file in r (read) mode. 
     * input is complete path to read file
     */

    /* fopen() return NULL if last operation was unsuccessful */
    if(fptr == NULL)
    {
        /* File not read hence exit */
        printf("Unable to read file.\n");
        exit(EXIT_FAILURE);
    }

    char input;
    char word[50];
    int i = 0;
    int flag = 0;
    //flag 1 means it's a word
    //flag 2 means it's a number

    while (!feof(fptr)){

        //read char
        input = fgetc(fptr);

        //A to Z in ASCII is 65 to 90 and a to z is 97 to 122 

        if((input >= 65 && input <= 90) || (input >= 97 && input <= 122)){
            word[i] = input;
            i++;
            flag = 1;
        }
        //0 to 9 in ASNII is 48 to 57
        //'1' 1
        else if(input > 48 && input <= 57){
            word[i] = input;
            i++;
            flag = 2;
        }

        //if the character read is one of the symbols then it means a word is read completely
        //10 represent for new line, others represent for symbols
        //10 represent '\n'
        else if((input >= 32 && input <= 47) || (input >= 58 && input <= 64) || input == 10){

            if(flag == 1){
                llist_add_node(linkedlist, word);
                printf("%s", word);

                //set word to empty
                //1 要改变的内容的地址
                //2 改成什么东西
                //3 要改多少/多大一大块的空间
                //sizeof word -> word大小
                memset(word, 0, sizeof word);
                i = 0;
                flag = 0;
            }

            else if(flag == 2){

                if(strcmp(word, "0") == 0){
                    break;
                }

                int index = atoi(word); //"123" -> int 123

                Node * node = SearchWord(linkedlist, index);
                char word_copy[50];

                strcpy(word_copy, node->word);
                //pointer struct use '->' to get member value, node->word 
                //normal struct '.', node.word
                //delete_node
                llist_add_node(linkedlist, word_copy);// delete original word
                llist_add_node(linkedlist, word_copy);// add to front
                memset(word, 0, sizeof word);
                i = 0;
                flag = 0;
            }
            printf("%c", input);           
        }
    }
    
    fclose(fptr);
    return 0;
}