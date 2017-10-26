#include"first.h"

int main(int argc, char** argv){



//taking care of number of argumetns
   if (argc< 5){

        printf("%s", "Input Less than 4\n");
        return 0;
    }

    //variables
   int i, length, j, block_track;


    //getting all the paramters

    cache  = atoi(argv[1]);
    block = atoi(argv[3]);
    assoc = strcmp(argv[2],"direct")==0 ? 0 : (cache/block) ;
    

	//if it is not assoc
	if (strcmp(argv[2], "assoc")==1){
		char str[2];
		 str[0] = argv[2][6];
		
		assoc = atoi(str);
	
	}
	//printf("associativity: %d\n", assoc);

   

    //checking if everything is a power of 2

    if (isPowerOfTwo(cache)!= 1 || isPowerOfTwo(block)!= 1){

        printf("%s", "Power Error");
        return 0 ;
    }

    

    //putting the formula = #of Sets = (cache/ (block * assoc))
    set = assoc == 0? 0: cache / (block*assoc);


    //putting the formula for number_of_blocks =  cache/ block
    num_of_blocks = cache / block;

    //if there are zero sets it means it is direct mapped cache
    if (set==0){

        sets = (struct Node**)malloc(sizeof(struct Node)* num_of_blocks);
	setsB =  (struct Node**)malloc(sizeof(struct Node)* num_of_blocks);
        length = num_of_blocks;
        set = num_of_blocks;
	assoc = 1;
    }

    else {

         //setting hashtable for the sets
         sets = (struct Node**)malloc(sizeof(struct Node)* set);
	 setsB = (struct Node**)malloc(sizeof(struct Node)* set);
         length = set;
    }



    //setting each one equals to null just to be on save side
    for (i =0 ; i<length ; i++ ){

        sets[i]= NULL;
	setsB[i]= NULL;
    }

  
    //goes all the way num of blocks
    i=1;

    //keeps track of how many blocks are put in each set
    block_track = 1;

    //each index of the set
    j=0;

    while(i<= num_of_blocks){


        if (block_track<= assoc){

            struct Node* temp = (struct Node*)(malloc(sizeof(struct Node)));
            temp->valid = 0;
            temp->next = sets[j];
            sets[j] = temp;
 	    
            struct Node* tempB = (struct Node*)(malloc(sizeof(struct Node)));
	    tempB->valid = 0;
            tempB->next = setsB[j];
            setsB[j] = tempB;

            block_track++;
            i++;
        }
        else{


            j++;
            block_track = 1;
        }
    }
	//some variables for memory format and stuff
	char mem[49];
	char instruction[5];
	char format[49];
	char garbage[20];

	FILE *file;
	

	if (!(file = fopen(argv[4], "r"))) {
	    printf(" Error: Couldn't open the file\n");
	    return 0;
	}

	

	while(!feof(file)){

		fscanf(file, "%s %s %s", garbage,instruction, mem);
		//printf("%s  %s\n",instruction,mem );
		
		if (strcmp(garbage, "#eof")==0){
			
			
			break;
		}
		
		if (strcmp(instruction,"W")==0){

			getBinaryFormat(mem, format);
			writeCache(format);
			writeCacheB(format);
			format[0] = '\0';
		}else{
			
			getBinaryFormat(mem,format);
			ReadCache(format);
			ReadCacheB(format);
			format[0] = '\0';

		}
		
	}

	printf("cache A\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", reads,writes,hits,misses);
	printf("cache B\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", readsB,writesB,hitsB,missesB);
	
/*printf("cache: %d\nSets: %d\neach block size: %d\nAssoc: %d\n#Blocks: %d\n", cache,set,block, assoc,num_of_blocks);

    for (i= 0; i< length; i++){

        struct Node* temp = setsB[i];

        while (temp!= NULL){

            printf("[%d]==>", temp->valid);
            temp= temp->next;
        }
        printf("\n");
    }
	*/
	 

   return 0;
}

