#include"hashmap.h"

HashNode* init_hashnode(char* userkey,void* data){
    HashNode* node;
    node=(HashNode*)malloc(sizeof(HashNode));
    node->data=(void*)data;
    node->userkey=userkey;
    node->index=hash_getkey(userkey);
    node->chain=(struct hash_node*)NULL;
    return node;
}

HashMap* hashmap(KEY_TYPE keyType){
	HashMap* map;
	map=(HashMap*) malloc(sizeof(HashMap));
	map->hashtable=(HashNode *)malloc(sizeof(HashNode)*HASHTABLE_SIZE);
	memset(map->hashtable,0,sizeof(HashNode)*HASHTABLE_SIZE);
	map->capacity=HASHTABLE_SIZE;
	map->keyType=keyType;
	return map;
}

void free_hashmap(HashMap* map){
  free(map->hashtable);
  free(map);
}

int hash_getkey(char* userkey){
    unsigned short hash = 0;
    for (int i = 0 ; userkey[i] != '\0' ; i++)
    {
        hash = 31*hash + userkey[i];
    }
    return hash % HASHTABLE_SIZE;
}



void hashmap_put(HashMap* map,void* keyData,void* data){
   char key[50];
   HashNode *hashNode,*currentNode;
   if(map->keyType==STRING){
    hashNode=init_hashnode((char*)keyData,data);
   }
   else if(map->keyType==FRACTIONAL_NUMBER){
    sprintf(key,"%lld",*((long long int*)keyData));
    hashNode=init_hashnode(key,data);
   }
   else{
   sprintf(key,"%d",*((int*)keyData));
   hashNode=init_hashnode(key,data);
   }
   currentNode=&(map->hashtable[hashNode->index]);
     if(map->booleanTable[hashNode->index]==1){
        while(currentNode->chain!=NULL){
            currentNode=currentNode->chain;
        }
        currentNode->chain=hashNode;
        }

   else{
     map->hashtable[hashNode->index]=*hashNode;
     map->booleanTable[hashNode->index]=1;
   }
}

void* hashmap_get(HashMap* map,void* keyData){
   char key[50];
   int index;
   if(map->keyType==STRING){
   index=hash_getkey((char*)keyData);
   }
   else if(map->keyType==FRACTIONAL_NUMBER){
   sprintf(key,"%lld",*((long long int*)keyData));
   index=hash_getkey(key);
   }
   else{
   sprintf(key,"%d",*((int*)keyData));
   index=hash_getkey(key);
   }

   HashNode* curr;
   curr=map->hashtable+index;
   if(curr->chain!=NULL){
    if(strcmp(curr->userkey,key)!=0){
        while(curr->chain!=NULL){
         curr=curr->chain;
         if(strcmp(curr->userkey,key)==0){
           return curr->data;
         }
     }
     return NULL;
   }
   }

   else{
   return map->hashtable[index].data;
   }
   return NULL;
}