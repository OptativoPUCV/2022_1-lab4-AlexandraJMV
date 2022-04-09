#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

	int pos = hash(key, map->capacity);
	Pair * par = createPair(key, value);

	if ( (map->buckets[pos] != NULL) && (is_equal(key, map->buckets[pos]->key)) != 1 )
	{
		map->current = pos;
		pos = (pos + 1) % (map->capacity);
		
		while ( (map->buckets[pos] != NULL) )
		{
			if (is_equal(key, map->buckets[pos]->key) == 1 )
				return;
			else pos = (pos + 1)%(map->capacity);
		}

		map->buckets[pos] = par;
		map->size++;
	}
	else
	{
		map->current = pos;
		map->buckets[pos] = par;
		map->size++;
	}
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
	
	HashMap * new_map = (HashMap *) malloc (sizeof(HashMap));
	//comprobar reserva

	new_map->buckets = (Pair**) malloc (capacity*sizeof(Pair*));
	//comprobar reserva
	
	new_map->capacity = capacity;
	new_map->current = -1;
	new_map->size = 0;

	for (int i = 0 ; i < capacity ; i++)
	{
		new_map->buckets[i] = NULL;
	}

    return new_map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   

	int pos = hash(key, map->capacity);

	if (map->buckets[pos] == NULL) return NULL;
	while(is_equal(key, map->buckets[pos]->key) != 1 )
	{
		pos = (pos + 1) % (map->capacity);
	}

	if (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) 
		return NULL;
	
	map->current = pos;
	return map->buckets[pos];
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
