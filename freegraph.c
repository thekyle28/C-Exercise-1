#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct A {
    struct A *a, *b, *c;
    long n;
};

// bool isInArray(int x, int a[], int size){
//     for (int i = 0; i < size; i++){
//         if (a[i] == x) return true;
//     }
//     return false;

// }

/*
int sizeOfArray(int array[]){
    int n = sizeof(array) / sizeof(array[0]);
    return n;
}
*/

// a self-defined arrayList structure to be used to keep track of the visited nodes in the graph.
struct arrayList
{
    struct arrayList *next;
    struct A *pointer;
};

struct arrayList *newArrayList(struct A *pointer, struct arrayList *next)
{
    struct arrayList *p = malloc(sizeof(struct arrayList));
    p->next = next;
    p->pointer = pointer;
    return p;
}


void add(struct A *pointer, struct arrayList *a)
{
    //ensures that the end of the arrayList has been reached so that the new element may be added.
    while(a->next){ //checks that the next pointer is null.
        a = a->next;
    }
    struct arrayList *pointElem = newArrayList(pointer,NULL);
    a->next = pointElem;
}

bool isInArrayList(struct A *pointer, struct arrayList *a){ //change to the list of pointers.
    // struct arrayList *next = a->next;
    while(a){
        if (a -> pointer  == pointer) return true;
        a = a -> next;
    }
    return false;
}

void freeArrayList(struct arrayList *p){
    struct arrayList *temp = p;
    while(p){
        temp=p->next;
        free(p);
        p=temp;
    }
    free(temp);
    free(p);
}


long sumB(struct A *p, struct arrayList *visited){ 
    long sum =0;
    if(p) //check that the current pointer is not null.
    { 
        long num = p->n; //add the number at the current node.
        sum += num;    
        struct A *pointer = p->a; //get the pointer to the a node.

        if (!(isInArrayList(pointer, visited))) { //check that it hasn't been visited already.
            add(pointer,visited); //add it to the visited list
            sum += sumB(p->a,visited); // add the sum of the next node to the total sum.
        }
        //repeat for pointer b and c.
        pointer = p->b;

        if (!(isInArrayList(pointer, visited))) {
            add(pointer,visited);
            sum += sumB(p->b,visited);
        }

        pointer = p->c;

        if (!(isInArrayList(pointer, visited))) {
            add(pointer,visited);
            sum += sumB(p->c,visited);
        }

    }
    return sum;
}

long sumA(struct A *p){
    struct arrayList *visited = newArrayList(p,NULL);
    long sum = 0;
    long num = p->n;
    sum += num;
    struct A *pointer = p->a;
    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        sum += sumB(p->a,visited);
    }

    pointer = p->b;

    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        sum += sumB(p->b,visited);
    }

    pointer = p->c;

    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        sum += sumB(p->c,visited);
    }
    
    freeArrayList(visited);
    return sum;

}


void deallocateB(struct A *p, struct arrayList *visited){
    if(p){
        struct A *pointer = p->a;
        if (!(isInArrayList(pointer, visited))) {
            add(pointer,visited);
            deallocateB(pointer,visited);
        }

        pointer = p->b;
        if (!(isInArrayList(pointer, visited))) {
            add(pointer,visited);
            deallocateB(pointer,visited);
        }

        pointer = p->c;
        if (!(isInArrayList(pointer, visited))) {
            add(pointer,visited);
            deallocateB(pointer,visited);
        }
    }
    free(p);

}

void deallocateA(struct A *p){
    struct arrayList *visited = newArrayList(p,NULL);
    struct A *pointer = p->a;
    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        deallocateB(pointer,visited);
    }

    pointer = p->b;
    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        deallocateB(pointer,visited);
    }

    pointer = p->c;
    if (!(isInArrayList(pointer, visited))) {
        add(pointer,visited);
        deallocateB(pointer,visited);
    }

    
    freeArrayList(visited);
    free(p);
}

