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
