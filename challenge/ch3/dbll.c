#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL) {
	printf("Memory allocation failed\n");
	return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

void traverse_forward(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
	printf("%d<->", temp->data);
	temp = temp->next;
    }

    printf("NULL\n");
}

void traverse_backward(Node *head) {
    if (head == NULL) {
	return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
	temp = temp->next;
    }

    while (temp != NULL) {
	printf("%d<->", temp->data);
	temp = temp->prev;
    }
    
    printf("NULL\n");
}

void insert_at_front(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;

    if (*head != NULL) {
	(*head)->prev = new_node;
    }
    *head = new_node;
}

void insert_at_end(Node** head, int data) {
    Node* new_node = create_node(data);

    if (head == NULL) {
	*head = new_node;
	return;
    }

    Node* temp = *head;
    while (temp->next != NULL) { 
	temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

void insert_after_node(Node* prev_node, int data) {
    if (prev_node == NULL) {
	printf("node doesn't exist\n");
	return;
    }

    Node* new_node = create_node(data);
    new_node->next = prev_node->next;
    new_node->prev = prev_node;

    if (prev_node->next != NULL) {
	prev_node->next->prev = new_node;
    }

    prev_node->next = new_node;
}

void insert_before_node(Node** head, Node* next_node, int data) {
    if (next_node == NULL) {
	printf("node doens't exist");
	return;
    }

    Node* new_node = create_node(data);
    new_node->next = next_node;
    new_node->prev = next_node->prev;

    if (next_node->prev != NULL) {
	next_node->prev->next = new_node;
    } else {
	*head = new_node;
    }

    next_node->prev = new_node;
}

void remove_beginning(Node** head) {
    if (*head == NULL) {
	printf("the list is already empty");
	return;
    }

    Node* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
	(*head)->prev = NULL;
    }

    free(temp);
}

void remove_end(Node **head) {
    if (*head == NULL) {
	printf("the list is already empty");
	return;
    }

    Node* temp = *head;

    while (temp->next != NULL) {
	temp = temp->next;
    }

    if (temp->prev == NULL) {
	*head = NULL;
    } else {
	temp->prev->next = NULL;
    }

    free(temp);
}

void remove_given_node(Node** head, Node* del) {
    if (*head == NULL || del == NULL) {
	printf("the list or given node is NULL\n");
	return;
    }

    if (*head == del) {
	*head = (*head)->next;
    }

    if (del->next != NULL) {
	del->next->prev = del->prev;
    }

    if (del->prev != NULL) {
	del->prev->next = del->next;
    }

    free(del);
}

Node* find_node(Node *head, int target) {
    Node* temp = head;

    while (temp != NULL) {
	if (temp->data == target) {
	    return temp;
	}
	temp = temp->next;
    }

    return NULL;
}

int get_last_node(Node *head) {
    Node* temp = head;

    while (temp->next != NULL) {
	temp = temp->next;
    }

    return temp->data;
}

int main() {
    Node* head = create_node(1);
    Node* second = create_node(5);
    Node* third = create_node(10);
    Node* fourth = create_node(15);
    Node* fifth = create_node(20);

    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    third->next = fourth;
    fourth->prev = third;
    fourth->next = fifth;
    fifth->prev = fourth;

    // insertion
    printf("insertion\n");
    int data = 0;
    insert_at_front(&head, data);

    printf("After insert %d at front:\n", data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    data = 25;
    insert_at_end(&head, data);

    printf("After insert %d at end:\n", data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    data = 12;
    insert_before_node(&head, second, data);

    printf("insert %d before %d node:\n", data, second->data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    data = 69;
    insert_before_node(&head, head, data);

    printf("insert %d before head:\n", data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    data = 17;
    insert_after_node(fourth, data);

    printf("insert %d after %d node:\n", data, fourth->data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    data = 69;
    insert_after_node(fifth, data);

    printf("insert %d after %d node:\n", data, fourth->data);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    // deletion
    printf("\ndeletion\n");

    printf("delete head %d\n", head->data);
    remove_beginning(&head);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    printf("delete last node %d\n", get_last_node(head));
    remove_end(&head);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    printf("delete given node: %d\n", fifth->next->data);
    remove_given_node(&head, fifth->next);
    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);

    // search
    printf("\ndeletion\n");
    Node* found_node = NULL;

    data = 15;

    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);
    printf("find %d\n", data);
    found_node = find_node(head, data);
    if (found_node == NULL) {
	printf("node not found\n");
    } else {
	printf(
	    "node with data %d exists with prev data %d and next data %d\n",
	    data,
	    found_node->prev->data,
	    found_node->next->data
	);
    }

    data = 69;

    printf("Forward traversal\n");
    traverse_forward(head);
    printf("Backward traversal\n");
    traverse_backward(head);
    printf("find %d\n", data);
    find_node(head, data);
    found_node = find_node(head, data);
    if (found_node == NULL) {
	printf("node not found\n");
    } else {
	printf("node with data %d exists", data);
    }

    free(head);
    free(second);
    free(third);
    free(fourth);
    free(fifth);

    return 0;
}
