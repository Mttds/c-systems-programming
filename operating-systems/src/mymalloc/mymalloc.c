#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

void initialize() {
  freeList->size = 20000 - sizeof(struct block); 
  freeList->free = 1; // not allocated
  freeList->next = NULL; // no next metadata block
}

/* Making way for a new block allocation by splitting a free block -- (Assume first fit algorithm) */
/**
  * If we find a free block that exactly fits the required size, we don’t need to split it. This function is only required when we have more than we need.
  * It accepts the following arguments: — A pointer to the metadata block which refers to the memory block that is larger than necessary (fitting_slot) and the desired size of the memory chunk.
  * We create a new metadata block pointer called “new” here. It should point to the location provided by passing(setting aside) a block of memory which is equal to the_size_of_the_metadata_block_we_considered + the_size_requested_to_be_allocated
  * The new pointer points to the next free chunk in the metadata block. In the code, you can see that both the new and fitting_slot metadata blocks have their attributes set accordingly.
 */
void split(struct block *fitting_slot, size_t size) {
  struct block *new = (void*)((void*)fitting_slot+size+sizeof(struct block));
  new->size = (fitting_slot->size) - size - sizeof(struct block);
  new->free = 1;
  new->next = fitting_slot->next;
  fitting_slot->size = size;
  fitting_slot->free = 0;
  fitting_slot->next = new;
}

void *MyMalloc(size_t noOfBytes) {
  struct block *curr, *prev;
  void *result;

  if (!(freeList->size)) {
    initialize();
    printf("Memory initialized\n");
  }

  curr = freeList;
  while((((curr->size) < noOfBytes) || ((curr->free) == 0)) && (curr->next != NULL)) {
    prev = curr;
    curr = curr->next;
    printf("One block checked\n");
  }

  if ((curr->size) == noOfBytes) {
    curr->free = 0;
    result = (void*)(++curr);
    printf("Exact fitting block allocated\n");
    return result;
  } else if ((curr->size) > (noOfBytes+sizeof(struct block))) {
    split(curr, noOfBytes);
    result = (void*)(++curr);
    printf("Fitting block allocated with a split\n");
    return result;
  } else {
    result = NULL;
    printf("Sorry. No sufficient memory to allocate\n");
    return result;
  }
}

/**
 * It is possible to have consecutive blocks that are released by deallocating
 * after they have previously been allocated. This creates external fragmentation,
 * causing the MyMalloc() function to return a NULL pointer despite the fact that
 * we have enough memory to allocate. We use the merge() function to combine
 * the consecutive free blocks by removing the metadata blocks in between.
 */
void merge(){
  struct block *curr,*prev;
  curr = freeList;

  while ((curr->next) != NULL) {
    if ((curr->free) && (curr->next->free)) {
      curr->size += (curr->next->size) + sizeof(struct block);
      curr->next = curr->next->next;
    }

    prev = curr;
    curr = curr->next;
  }
}

void MyFree(void* ptr){
  if(((void*)memory <= ptr) && (ptr <= (void*)(memory+20000))){
    struct block* curr = ptr;
    --curr;
    curr->free = 1;
    merge();
  } else {
    printf("Please provide a valid pointer allocated by MyMalloc\n");
  }
}
