//2019007892 박준성

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include "cachelab.h"

//address
typedef unsigned long long int mem_addr_t;

//Line
typedef struct {
	int valid;
	mem_addr_t tag;
	mem_addr_t time;  //need for eviction base on LRU rule
} Line;

//Set
typedef struct{
	Line *lineList;
} Set;

//Cache
typedef struct{
	Set *setList;
	int S;	//number of sets
	int E;  //Associativity (number of lines per set)
} Cache;


Cache cache;
mem_addr_t set_index_mask;
int s = 0, b = 0, hits = 0, misses = 0, evictions = 0; // s = Number of set index bits, b = Number of block bits
mem_addr_t lru_counter = 1; //num for lru



void cacheSimulate(mem_addr_t address){
	//extract set_index from address
	mem_addr_t set_index = (address >> b) & set_index_mask;
	//extract tag from address
	mem_addr_t tag = address >> (s+b);
	
	//find set
	Set *set = &cache.setList[set_index];
	
	for(int i = 0; i < cache.E; i++){
		Line *line = &set->lineList[i];
		
		//check valid and tag
		if(!line->valid || tag != line->tag) continue;
		
		//found in cache
		line->time = lru_counter++;
		hits++;
		return;
	}
	
	//missed
	misses++;
	
	int  evict_line = 0;
	mem_addr_t eviction_lru = 0xFFFFFFFF;
	
	//find lines of the set which has smallest time value
	for(int i = 0; i<cache.E; i++){
		Line *line = &set->lineList[i];
		if(eviction_lru > line->time){
			evict_line = i;
			eviction_lru = line->time;
		}
	}
	
	//if there is no empty place, evict it and replace it
	if(set->lineList[evict_line].valid){
		evictions++;
	}

	//write in cache
	set->lineList[evict_line].tag = tag;
	set->lineList[evict_line].valid = 1;
	set->lineList[evict_line].time = lru_counter++;
}

int main(int argc, char *argv[])
{
	// use getopt to interpret command_line
	FILE *f = NULL;
	int option = 0;
	while((option = getopt(argc, argv, "s:E:b:t:")) != EOF){
		switch (option) {
			case 's':
				s = atoi(optarg);
				cache.S = 2<<s;
				break;
			case 'E':
				cache.E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				if(!(f = fopen(optarg, "r"))) return 0; //open trace file
				break;
			default:
				return 0;
			}

	}
	
	// construct cache according to information from argument
	cache.setList = malloc(sizeof(Set)*cache.S);
	for(int i = 0; i < cache.S; i++){
		cache.setList[i].lineList = calloc(sizeof(Line), cache.E);
	}
	set_index_mask = (mem_addr_t)(pow(2, s) -1);

	// parse trace file
	char operation;
	mem_addr_t address;
	int size;
	while (fscanf(f, " %c %llx, %d", &operation, &address, &size) != EOF){
		switch(operation){
			case 'L': cacheSimulate(address); break;
			case 'S': cacheSimulate(address); break;
			case 'M': cacheSimulate(address); cacheSimulate(address); break;	//Modify access cache twice
			default: break;
		}
	}

	printSummary(hits, misses, evictions);	//print simulation result
	
	fclose(f);
	for (int i = 0; i < cache.S; i++) free(cache.setList[i].lineList);
	free(cache.setList);
    	return 0;
}
