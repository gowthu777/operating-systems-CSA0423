#include <stdio.h>
#include <stdlib.h>

// define the memory block structure
typedef struct {
    int size;
    int is_free;
} mem_block;

// define the memory block array


// initialize the memory block array
void initialize_memory() {
    for (int i = 0; i <1; i++) {
  
 
    }

// display the current state of the memory block array
void display_memory() 

    printf("Memory Layout:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d ", memory[i].size);
        if (memory[i].is_free) {
            printf("(Free)\n");
        } else {
            printf("(Occupied)\n");
        }
    }
    printf("\n");
}

// first-fit memory allocation strategy
int first_fit(int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].is_free && memory[i].size >= size) {
            memory[i].size = size;
            memory[i].is_free = 0;
            return i;
        }
    }
    return -1;
}

// best-fit memory allocation strategy
int best_fit(int size) {
    int best_index = -1;
    int best_size = MEMORY_SIZE;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].is_free && memory[i].size >= size && memory[i].size < best_size) {
            best_index = i;
            best_size = memory[i].size;
        }
    }
    if (best_index != -1) {
        memory[best_index].size = size;
        memory[best_index].is_free = 0;
    }
    return best_index;
}

// worst-fit memory allocation strategy
int worst_fit(int size) {
    int worst_index = -1;
    int worst_size = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].is_free && memory[i].size >= size && memory[i].size > worst_size) {
            worst_index = i;
            worst_size = memory[i].size;
        }
    }
    if (worst_index != -1) {
        memory[worst_index].size = size;
        memory[worst_index].is_free = 0;
    }
    return worst_index;
}

// deallocate memory at the given index
void deallocate(int index) {
    memory[index].size = 0;
    memory[index].is_free = 1;
}

int main() {
    initialize_memory();
    display_memory();

    // allocate memory using first-fit strategy
    int index = first_fit(100);
    if (index != -1) {
        printf("Allocated memory at index %d using first-fit strategy.\n", index);
        display_memory();
    } else {
        printf("Failed to allocate memory using first-fit strategy.\n");
    }

    // allocate memory using best-fit strategy
    index = best_fit(200);
    if (index != -1) {
        printf("Allocated memory at index %d using best-fit strategy.\n", index);
        display_memory();
    } else {
        printf("Failed to allocate memory using best-fit strategy.\n");
}
        return 0:
        }
