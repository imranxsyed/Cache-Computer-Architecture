#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<math.h>




struct Node{

char data[49];
char tag[48];
int valid;

struct Node* linkList;

struct Node* next;

};

//global variables
int set,num_of_blocks, assoc,cache , block, hits=0, misses=0,hitsB=0, missesB=0 ,reads=0, writes=0, readsB=0,writesB=0;
//initializing the set
struct Node**sets;
struct Node** setsB;



void subStringWord(char*, char*);
void subStringWord(char first[], char second[]){

int index;

for (index= 0; index< strlen(first); index+=1){

    second[index]= first[index];

}
second[index]= '\0';
return;
}





void subStringNumber(char*, char*, int);
void subStringNumber(char first[], char second[], int size){

int index;

for (index= 0; index< size; index+=1){

    second[index]= first[index];

}
second[size]= '\0';
return;
}

char* trim (char*);
char* trim (char* input){

    if (input == NULL || strlen(input)<1){

        return input =NULL;
    }
    int i;
    i= strlen(input) -1;


    while (input[i]== ' '|| input[i]== '\n'){

        i--;
    }

    if (i == strlen(input)-1){ // no spaces found

        return NULL;
    }
    input[i+1] = '\0';

    return input;

}



int searchList(struct Node*, char[]);
int searchList(struct Node* linkList, char format[]){

    if (linkList== NULL){

        return -1;
    }
    struct Node* ptr = linkList;

    while(ptr!=NULL){


        if (strcmp(ptr->data, format)==0){


            return 0 ;
        }
        ptr = ptr->next;

    }
    return -1;

}

void bitsComputation(char[]);
void bitsComputation(char format[]){


    //initializing the variables that will be used
     int power=0,comp=0, i=strlen(format)-1, index_bit, block_bit;
     char tag[48];
     double value;
    //getting index bit, block bit , and tag bit

    value = log2((double)set);
    index_bit = ceil(value);
    value = log2((double)block);
    block_bit = ceil(value);




     i = abs( (i) - (block_bit));

    while (index_bit>0){

        value = pow((double)2,(double)power);
        comp += format[i] == '0'? 0 : ceil(value);
        power++;
        index_bit--;
        i--;

    }

    //we have the index number for now;
    printf("\nthe index is: %d\n", comp);

    //getting the tags in string
    subStringNumber(format, tag, i+1);
    index_bit = strlen(tag);
    printf("\ntag is: %s: %d\n", tag, index_bit);


    return;

}


void writeCacheB(char[]);
void writeCacheB(char format[] ){

    int index_bit , block_bit, k,comp = 0, power=0;
    char tag[48];
    tag[0]= '\0';


    //getting index bit, block bit , and tag bit
    index_bit = ceil(log2((double)set));
    block_bit =abs(ceil(log2((double)block))- 47);



   /*  printf("index_bit: %d\n", index_bit);
    printf("block_bit: %d\n", 47 - block_bit);*/

    k = (index_bit-1);

    while(k>=0){

        comp += format[k]=='0'? 0 :ceil( pow(2.0,(double)power));
        power++;
        k--;
    }
    k=0;

   // printf("The index is : %d\n\n", comp);

    while(index_bit<=block_bit){ // getting the substring

        tag[k]= format[index_bit];
        k++;
        index_bit++;
    }
    tag[k] = '\0';

    //we have the index and we have the tag, and memory itself

    struct Node* temp = setsB[comp];

    while(temp!= NULL){

        //empty space
        if (temp->valid == 0){

            subStringWord(tag, temp->tag);
            subStringWord(format, temp->data);
            temp->valid = 1;
            readsB++;
            writesB++;
            missesB++;
            break;

        }//found the tag
        else if(strcmp(temp->tag,tag)==0){
            /*   if (strcmp(temp->data, format)==0){

                        hitsB++;
                        writesB++;
                        break;
                    }
                    else if (searchList(temp->linkList, format)==0){

                        hitsB++
                        writesB++;
                        break;

                    }else{


                        //making another node adding the block bit in there
                        struct Node* subMem = (struct Node*)malloc(sizeof(struct Node));
                        subStringWord(format, subMem->data);

                        //actual list of the block that contains sub-Memories
                        subMem->next = temp->linkList;
                        temp->linkList = subMem;
                        readsB++;
                        writesB++;
                        missesB++;
                        break;

                    }
                */
            hitsB++;
            writesB++;
            break;

        }

        temp= temp->next;
    }

    //one needs to go
    if (temp == NULL){

        temp = setsB[comp];

        if (temp->next == NULL){


            subStringWord(tag, temp->tag);
            subStringWord(format, temp->data);
            missesB++;
            writesB++;
            readsB++;

        }
        else{

        //if it is atleas more than one nodes

        setsB[comp]= temp->next;
        struct Node* ptr = setsB[comp];

        //going to the last node and stopping it there

        while(ptr->next!=NULL){


            ptr = ptr->next;
        }
        //reaches the last Node
        ptr->next = temp;
        temp->next= NULL;
        subStringWord(tag, temp->tag);
        subStringWord(format, temp->data);
        missesB++;
        writesB++;
        readsB++;

        }
        /*
            struct Node* f= temp->linkList;

            while(f!=NULL){



                temp->linkList = f->next;
                free(f);
                f = temp->linkList;
            }
            //done freeing everyhitng
            */


    }


}



void ReadCacheB(char[]);
void ReadCacheB(char format[]){

     int index_bit , block_bit, k,comp = 0, power=0;
    char tag[48];
    tag[0]= '\0';


    //getting index bit, block bit , and tag bit
    index_bit = ceil(log2((double)set));
    block_bit =ceil(log2((double)block));
    block_bit = abs(47-block_bit);



   /*  printf("index_bit: %d\n", index_bit);
    printf("block_bit: %d\n", 47 - block_bit);*/

    k = (index_bit-1);

    while(k>=0){

        comp += format[k]=='0'? 0 : ceil(pow(2.0,(double)power));
        power++;
        k--;
    }
    k=0;

   // printf("The index is : %d\n\n", comp);

    while(index_bit<=block_bit){ // getting the substring

        tag[k]= format[index_bit];
        k++;
        index_bit++;
    }
    tag[k] = '\0';

    //we have comp== index, tag bits, and format

    struct Node* temp = setsB[comp];

    while(temp != NULL){

        if (temp->valid == 0 ){

            //meaning found something empty block
            readsB++;
            missesB++;
            subStringWord(tag,temp->tag);
            subStringWord(format, temp->data);
            temp->valid = 1;
            return;
        }
        else if(strcmp(temp->tag, tag)==0){
             /*
                if (strcmp(temp->data,format)==0){

                    hitsB++;
                    return;
                }
                else if (searchList(temp->linkList, format)==0){


                    hitsB++;
                    return;
                }
                else{

                    //making a new Node
                    struct Node* subMem = (struct Node*)malloc(sizeof(struct Node));
                    subStringWord(format, subMem->data);

                    subMem->next = temp->linkList;
                    temp->linkList = subMem;
                    missesB++;
                    readsB++;
                    return;

                }

            */

            hitsB++;
            return;
        }
        temp = temp->next;
    }

   if (temp == NULL){

        temp = setsB[comp];

        //if only one block in the set
        if (temp->next == NULL){


            subStringWord(tag, temp->tag);
            subStringWord(format, temp->data);
             missesB++;
            readsB++;

        }
        else{

        //if it is at leas more than one nodes

        setsB[comp]= temp->next;
        struct Node* ptr = setsB[comp];

        //going to the last node and stopping it there

        while(ptr->next!=NULL){


            ptr = ptr->next;
        }
        //reaches the last Node
        ptr->next = temp;
        temp->next= NULL;
        subStringWord(tag, temp->tag);
        subStringWord(format, temp->data);
        missesB++;
        readsB++;


        }

         /*
            struct Node* f= temp->linkList;

            while(f!=NULL){



                temp->linkList = f->next;
                free(f);
                f = temp->linkList;
            }
            //done freeing everyhitng
            */

    }

}





void ReadCache(char[]);
void ReadCache(char format[]){

    //initializing the variables that will be used
     int power=0,comp=0, i=strlen(format)-1, index_bit, block_bit;
     char tag[48];

    //getting index bit, block bit , and tag bit
    index_bit = ceil(log2((double)set));
    block_bit =ceil(log2((double)block));





     i = abs( (i) - (block_bit));

    while (index_bit>0){

        comp += format[i] == '0'? 0 :ceil(pow(2.0,(double)power));
        power++;
        index_bit--;
        i--;

    }

    //we have the index number for now;
    /*printf("\nthe index is: %d\n", comp);*/

    //getting the tags in string
    subStringNumber(format, tag, i+1);

    /*printf("\ntag is: %s: %d\n", tag, index_bit);*/


    //at this point we have index_bit and tag in tag variable

    struct Node* temp = sets[comp];

    while(temp != NULL){

        if (temp->valid ==0){
            //printf("missed\n");
            misses++;
            reads++;
            subStringWord(tag, temp->tag);
            subStringWord(format, temp->data);
            temp->valid = 1;
            return;
        }
        else if(strcmp(temp->tag, tag)==0){

                /*if (strcmp(temp->data,format)==0){

                    hits++;
                    return;
                }
                else if (searchList(temp->linkList, format)==0){


                    hits++;
                    return;
                }
                else{

                    //making a new Node
                    struct Node* subMem = (struct Node*)malloc(sizeof(struct Node));
                    subStringWord(format, subMem->data);

                    subMem->next = temp->linkList;
                    temp->linkList = subMem;
                    misses++;
                    reads++;
                    return;

                }
                */


            hits++;
            return;
        }
        temp = temp->next;

    }


    //if all blocks in set is full ,, we gotta kick one out with replcement policy of FIFO
      if (temp == NULL){

            temp = sets[comp];

            if (temp->next == NULL){


                    subStringWord(tag,temp->tag);
                    subStringWord(format, temp->data);
                    misses++;
                    reads++;
            }
            else{

        //if it is at least more than one node

                sets[comp]= temp->next;
                struct Node* ptr = sets[comp];

        //going to the last node and stopping it there

                while(ptr->next!=NULL){


                    ptr = ptr->next;
                }
                //reaches the last Node
                ptr->next = temp;
                temp->next= NULL;
                subStringWord(tag,temp->tag);
                subStringWord(format, temp->data);
                 misses++;
                 reads++;

            }


             //freeing memory
         /*   struct Node* f= temp->linkList;

            while(f!=NULL){



                temp->linkList = f->next;
                free(f);
                f = temp->linkList;
            }
            */
            //done freeing everyhitng

            return;

    }


}

void WriteCache(char[]);
void writeCache(char format[]){

     //initializing the variables that will be used
     int power=0,comp=0, i=strlen(format)-1, index_bit, block_bit;
     char tag[48];


    //getting index bit, block bit , and tag bit
     index_bit = ceil(log2((double)set));
    block_bit =ceil(log2((double)block));





     i = abs( (i) - (block_bit));
    //printf("\nthe index bit is %d\n", index_bit);

    while (index_bit>0){

        comp += format[i] == '0'? 0: ceil(pow(2.0,(double)power));
        power++;
        index_bit--;
        i--;

    }
    //printf("\nthe index is: %d\n", comp);

    //we have the index number for now;


    //getting the tags in string
    subStringNumber(format, tag, i+1);
    //printf("\ntag is: %s: %d\n", format, index_bit);


    //at this point we have index_bit and tag in tag variable

    struct Node* temp = sets[comp];

    while(temp!=NULL){

        if (temp->valid == 0){

            reads++;
            writes++;
            misses++;
            temp->valid = 1;
            subStringWord(tag, temp->tag);
            subStringWord(format, temp->data);

            break;

        }
        else if ( (strcmp(temp->tag, tag)==0)){

                /*    if (strcmp(temp->data, format)==0){

                        hits++;
                        writes++;
                        break;
                    }
                    else if (searchList(temp->linkList, format)==0){

                        hits++;
                        writes++;
                        break;

                    }else{


                        //making another node adding the block bit in there
                        struct Node* subMem = (struct Node*)malloc(sizeof(struct Node));
                        subStringWord(format, subMem->data);

                        //actual list of the block that contains sub-Memories
                        subMem->next = temp->linkList;
                        temp->linkList = subMem;
                        reads++;
                        writes++;
                        misses++;
                        break;

                    }
                    */



            hits++;
            writes++;
            break;
        }
        temp= temp->next;

    }



        if (temp == NULL){

            temp = sets[comp];

            if (temp->next == NULL){


                    subStringWord(tag,temp->tag);
                    subStringWord(format, temp->data);
                    misses++;
                    writes++;
                    reads++;

            }
            else{


        //if it is atleas more than one nodes

                sets[comp]= temp->next;
            struct Node* ptr = sets[comp];

        //going to the last node and stopping it there

                while(ptr->next!=NULL){


                    ptr = ptr->next;
            }
                //reaches the last Node
                ptr->next = temp;
                temp->next= NULL;
                subStringWord(tag,temp->tag);
                subStringWord(format, temp->data);
                misses++;
                writes++;
                reads++;

            }
            //freeing the memory

        /*    struct Node* f= temp->linkList;

            while(f!=NULL){



                temp->linkList = f->next;
                free(f);
                f = temp->linkList;
            }
            */
            //done freeing everyhitng


    }


    return;

}




int isPowerOfTwo(int);
int isPowerOfTwo ( int x)
{
  return ((x != 0) && !(x & (x - 1)));
}





void getBinaryFormat(char[], char[]);
void getBinaryFormat(char mem[], char format[]){

    int  length, diff, i;

    //getting the length without 0x, and getting the difference if there is anything missing from 12 memory block
    length = strlen(mem)-2;
    diff = abs(12-length);

   /* printf("length: %d\ndiff: %d\n", length,diff);*/


    while(diff>0){


    strcat(format, "0000");
        diff--;
    }

    i = 2;


    while(i <(length+2)){

        //getting each digit from the memory ex:123456789abcdefg
        char letter = mem[i];


        switch(letter){
    case '0': strcat(format, "0000");break;
        case '1': strcat(format, "0001"); break;
        case '2': strcat(format, "0010");break;
        case '3': strcat(format, "0011");break;
        case '4': strcat(format, "0100"); break;
        case '5': strcat(format, "0101"); break;
        case '6': strcat(format, "0110"); break;
        case '7': strcat(format, "0111");break;
        case '8': strcat(format, "1000");break;
        case '9': strcat(format, "1001"); break;
        case 'a': strcat(format, "1010"); break;
        case 'b': strcat(format, "1011"); break;
        case 'c': strcat(format, "1100");break;
        case 'd': strcat(format, "1101");break;
        case 'e': strcat(format, "1110"); break;
        case 'f': strcat(format, "1111"); break;
        case 'A': strcat(format, "1010"); break;
        case 'B': strcat(format, "1011"); break;
        case 'C': strcat(format, "1100");break;
        case 'D': strcat(format, "1101");break;
        case 'E': strcat(format, "1110"); break;
        case 'F': strcat(format, "1111"); break;
        default : printf("Error with the Hexa Format"); exit(8);

        }

        i++;
    }


       /*printf("\nthe format is : %s\n", format);*/

    return;


}






