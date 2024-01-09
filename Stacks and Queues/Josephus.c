#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.c"

int josephus(Queue* q, int k){

    while(queue_size(q) > 1){
        for(int i = 1; i<k; i++){
            int person = dequeue(q);
            enqueue(q, person);
        }
    
        int executed = dequeue(q);
        printf("%d was executed.\n", executed);
    }
    return dequeue(q);

}

int main(){
    int n;
    int k;
    printf("Enter the number of people: ");
    scanf("%d", &n);
    printf("Enter the number of people to be skipped: ");
    scanf("%d", &k);
    Queue* people_q = new_queue(n);
    for(int person_num = 1; person_num < n + 1; person_num++){
        enqueue(people_q, person_num);
    }
    print_queue(people_q);
    int survived = josephus(people_q, k);
    printf("%d survived!\n", survived);
    return 0;
}
