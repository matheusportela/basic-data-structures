/**
 * Implementation of array-based queue, following the approach explained at
 * Introduction to Algorithms - Cormen et. al (Chapter 10), for didactic
 * purposes.
 *
 * Author: Matheus V. Portela (matheus.v.portela@gmail.com)
 */
#include <stdio.h>
#include <stdlib.h>

/* We need a queue with n elements to allow n-1 elements to be stored without
 * using an auxiliary variable to store the queue size. Otherwise, there would
 * be no easy way to determine whether a queue is empty or full.
 *
 * References:
 * - http://stackoverflow.com/q/16395354
 * - Introduction to Algorithms, Cormen et al., Chapter 10, page 234
 * - Pointers on C, Reek, Chapter 17, pages 505-510
 */
#define QUEUE_SIZE 5

struct queue_s {
    unsigned int head;
    unsigned int tail;
    char data[QUEUE_SIZE];
};

/*
 * Print all enqueued elements.
 */
void print_queue(struct queue_s queue);

/*
 * Initialize queue to avoid errors based on different compiler implementations.
 */
void init_queue(struct queue_s* queue);

/*
 * Whether the queue is empty.
 */
int is_empty(struct queue_s queue);

/*
 * Whether the queue is full.
 */
int is_full(struct queue_s queue);

/*
 * Enqueue new data to the queue or raise an error if it is full.
 */
void enqueue(struct queue_s* queue, char data);

/*
 * Dequeue data from the queue or raise an error if it is empty.
 */
void dequeue(struct queue_s* queue);

int main() {
    struct queue_s queue;
    init_queue(&queue);
    print_queue(queue);

    enqueue(&queue, 'a');
    enqueue(&queue, 'b');
    enqueue(&queue, 'c');
    enqueue(&queue, 'd');
    print_queue(queue);

    dequeue(&queue);
    print_queue(queue);

    enqueue(&queue, 'e');
    print_queue(queue);

    for (int i = 0; i < 4; i++)
        dequeue(&queue);
    print_queue(queue);

    enqueue(&queue, 'f');
    print_queue(queue);

    return 0;
}

void print_queue(struct queue_s queue) {
    printf("Queue: ");

    for(int i = queue.head; i != queue.tail; i = (i + 1) % QUEUE_SIZE)
        printf("%c ", queue.data[i]);
    printf("\n");
}

void init_queue(struct queue_s* queue) {
    queue->head = 0;
    queue->tail = 0;
}

int is_empty(struct queue_s queue) {
    return (queue.head == queue.tail);
}

int is_full(struct queue_s queue) {
    return (queue.head == (queue.tail + 1) % QUEUE_SIZE);
}

void enqueue(struct queue_s* queue, char data) {
    if (is_full(*queue)) {
        fprintf(stderr, "Queue error: Cannot enqueue to full queue\n");
        exit(1);
    }

    queue->data[queue->tail] = data;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
}

void dequeue(struct queue_s* queue) {
    if (is_empty(*queue)) {
        fprintf(stderr, "Queue error: Cannot dequeue from empty queue\n");
        exit(1);
    }

    queue->head = (queue->head + 1) % QUEUE_SIZE;
}
