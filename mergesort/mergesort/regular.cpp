#include <iostream>
#include <tuple>
#include <stdlib.h>
#include <time.h>


void printArray(int a[], int start, int end, std::ostream& o = std::cout)
{
  o << "{";
  for (int i = start; i < end; ++i)
  {
    o << a[i] << ", ";
  }
  o << a[end] << "}\n";
}

std::tuple<int, int, int, int> divide(int startLeft, int endRight) {
    int endLeft = startLeft + ((endRight - startLeft) / 2);
    int startRight = endLeft + 1;
    return { startLeft, endLeft, startRight, endRight };
}

void merge(int sourceArray[], int destinationArray[], int startLeft, int endLeft, int startRight, int endRight) {
    int leftCursor = startLeft;
    int rightCursor = startRight;
    int destinationCursor = startLeft;

    while(leftCursor <= endLeft && rightCursor <= endRight) {// TODO simplify copy
        if(sourceArray[leftCursor] <= sourceArray[rightCursor]){
            destinationArray[destinationCursor] = sourceArray[leftCursor];
            leftCursor++;
        } else {
            destinationArray[destinationCursor] = sourceArray[rightCursor];
            rightCursor++;
        }
        destinationCursor++;
    }

    while(leftCursor <= endLeft){
        destinationArray[destinationCursor] = sourceArray[leftCursor];
        leftCursor++;
        destinationCursor++;
    }

    while(rightCursor <= endRight){
        destinationArray[destinationCursor] = sourceArray[rightCursor];
        rightCursor++;
        destinationCursor++;
    }
}

void mergesort (int sourceArray[], int destinationArray[], int start, int end) {
    if (end == start) { //TODO siplify edge case;
        destinationArray[start] = sourceArray[start];
        return;
    };
    const auto [startLeft, endLeft, startRight, endRight] = divide(start, end);
    mergesort(destinationArray, sourceArray, startLeft, endLeft);
    mergesort(destinationArray, sourceArray, startRight, endRight);
    merge(sourceArray, destinationArray, startLeft, endLeft, startRight, endRight);
}

void copyArray(int a[], int b[], int size){
    for (int i = 0; i<size; ++i){
        b[i] = a[i];
    }
}

int main() {
    const int size = 10000;
    int source [size]= {};
    int destination [size]= {};

    srand ( time(NULL) );
    for (int i=0; i< size; i++){
        source[i] = rand() % size;
    }
    copyArray(source, destination, size);
    
    std::cout << "input: "; 
    printArray(source, 0, size-1);
    
    mergesort(source, destination, 0, size-1);

    std::cout << "result: "; 
    printArray(destination, 0, size-1);
    return 0;
}
