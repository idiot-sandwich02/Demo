#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1
char * fillVehicleInfo(int year, long mileage, char * model){
    int modelLength = strlen(model);
    char * representation = malloc(sizeof(int) + sizeof(long) + modelLength + 1); 
    if (representation == NULL) {
        return NULL; // always good to check malloc success
    }
    *((int *) representation) = year;

    char * mileagePointer = representation + sizeof(int);
    *((long *) mileagePointer) = mileage;
    
    char * modelPointer = representation + sizeof(int) + sizeof(long);
    strcpy(modelPointer, model);
    return representation;

}
int main (){
    char * model = strdup("camry");
    char * representation = fillVehicleInfo(2020, 10000, model);
    printf("%d\n", (*(int*)representation));
    printf("%ld\n", (*(long*)(representation + sizeof(int))));
    printf("%s\n", (representation + sizeof(int) + sizeof(long))); // to print the model name
}

//2
void append_in_array(int **array, int *size, int value){
    int *newArray = realloc(*array, (*size + 1) * sizeof(int));
    if (newArray == NULL){
        printf("Error in realloc\n");
        return;
    }
    // int *lastElementAddress = newArray + *size;
    // *lastElementAddress = value;
    newArray[*size] = value;
    (*size)++;
    *array = newArray;
}

int main(){
    int *array = malloc(3 * sizeof(int));
    *array = 1;
    *(array + 1) = 2;
    *(array + 2) = 3;
    int size = 3;

    append_in_array(&array, &size, 4);

    for (int i = 0; i < size; i++){
        printf("%d ", *(array + i));
    }
    printf("\n");

    free(array);
}


//3
void map_array(void * arr, int count, int elem_size, void(*func)(void *elem)){
    for (int i = 0; i< count; i++){
        void * elemAdress = ((char*) arr)+ i * elem_size;
        func(elemAdress);
    }
}

void multiplyByTwo(void *element){
    (*(int *) element) *= 2;
}

int main(){
    int data [] = {1,2,3};
    map_array(data, 3,sizeof(int), multiplyByTwo);

    for (int i = 0; i < 3; i++){
        printf("%d\n", data[i]);
    }
}



//3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

// Function to create pairs from an int array.
// For simplicity, we create pairs of consecutive elements.
Pair* create_pairs(int *arr, int count, int *pair_count) {
    *pair_count = count / 2;  // number of pairs (ignore last if odd)
    Pair *pairs = malloc(*pair_count * sizeof(Pair));

    for (int i = 0; i < *pair_count; i++) {
        pairs[i].first = arr[2*i];
        pairs[i].second = arr[2*i + 1];
    }
    return pairs;
}

// Function to compare pairs and print maximum of each
void compare_and_print_max(void *arr, int count, int elem_size, void(*func)(void *elem)){
    for (int i = 0; i < count; i++) {
        void *elemAddress = ((char*)arr) + i * elem_size;
        func(elemAddress);
    }
}

// Function to print max of a single pair
void print_max_of_pair(void *element) {
    Pair *p = (Pair *)element;
    int max = (p->first > p->second) ? p->first : p->second;
    printf("Max of pair (%d, %d) is %d\n", p->first, p->second, max);
}

int main() {
    int data[] = {1, 5, 3, 4, 2, 7};  // example array with 6 elements
    int pair_count;

    // Create pairs from the array
    Pair *pairs = create_pairs(data, 6, &pair_count);

    // Compare pairs and print max of each pair
    compare_and_print_max(pairs, pair_count, sizeof(Pair), print_max_of_pair);

    free(pairs);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

void map_2d_array(void *arr, int count, int elem_size, void (*func)(void *elem, void *result), void *output) {
    for (int i = 0; i < count; i++) {
        void *elemAddress = (char *)arr + i * elem_size;
        void *resultAddress = (char *)output + i * sizeof(int);
        func(elemAddress, resultAddress);
    }
}

void findMaxInPair(void *elem, void *result) {
    int *pair = (int *)elem;
    int *maxResult = (int *)result;
    *maxResult = (pair[0] > pair[1]) ? pair[0] : pair[1];
}

int main() {
    int pairs[3][2] = {
        {1, 5},
        {9, 4},
        {2, 8}
    };

    int output[3]; // this will hold the max values

    map_2d_array(pairs, 3, sizeof(pairs[0]), findMaxInPair, output);

    printf("Max values from each pair:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
