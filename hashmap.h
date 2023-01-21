/*
 * HashMap.h
 *
 *  Created on: Jun 29, 2019
 *      Author: AMUTHAN
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define HASHTABLE_SIZE 65536

typedef enum key_type{
            INTEGER,
            STRING,
            FRACTIONAL_NUMBER
}
KEY_TYPE;

#define INT_FORMAT "%d"
#define LL_FORMAT "%lld"

typedef struct hash_node{
    char* userkey;
    int index;
    void* data;
    struct hash_node* chain;
}
HashNode;

typedef struct hash_map{
	HashNode *hashtable;
	char booleanTable[HASHTABLE_SIZE];
	int capacity;
	KEY_TYPE keyType;
}
HashMap;

int hash_getkey(char* userkey);
HashMap* hashmap();
HashNode* init_hashnode(char* userkey,void* data);

void free_hashmap(HashMap* map);

//API Functions
void  hashmap_put(HashMap* map,void* keyData,void* data);
void* hashmap_get(HashMap* map,void* keyData);

#endif /* HASHMAP_H_ */