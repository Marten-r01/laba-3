#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000
#define MAX_FIELDS 9
#include "publication_record.h"
#include "publication_stack.h"

void init(PublicStack * stack){
	stack->top=NULL;
	stack->size=0;
	
}

int get_size(PublicStack* stack){
	return stack->size;
}

PublicRec get_element(PublicStack * stack, int index ){
	Node* curr = stack->top;
	for (int i=0; i<index; i++){
		curr=curr->next;
	}
	return curr->rec;
}

Node* get_start(PublicStack *stack){
	return stack->top;
}

Node* get_end(PublicStack* stack){
	Node* curr = stack->top;
	while (curr->next !=NULL){
		curr=curr->next;
	}
	return curr;
}

Node* get_next(Node* node){
	return node ? node->next : NULL;
}

Node* get_last(PublicStack* stack, Node* node){
	if (node==NULL|| stack->top==NULL ){
		return NULL;
	}
	 Node* curr=stack->top;
	 while (curr && curr->next != node){
		curr=curr->next;
	 }
	 return curr;
}

void add_begin(PublicStack* stack , PublicRec * record){
	Node* new_node = (Node*)calloc(1,sizeof(Node));
	if (! new_node)
		{
		printf("ERROR IN CALLOC NEW_NODE/n");
		abort();
		}
	new_node->next=stack->top;
	stack->top=new_node;
	stack->size++;
}
void add_end(PublicStack* stack , PublicRec * record){
	Node* new_node = (Node*)calloc(1,sizeof(Node));
	if (! new_node)
		{
		printf("ERROR IN CALLOC NEW_NODE/n");
		abort();
		}
	new_node->next=NULL;
	if (stack->top==NULL){
		stack->top=new_node;
	}
	else{
		Node* tail = get_tail(stack);
		tail->next = new_node;
	}
	stack->size++;
}

void add_index(PublicStack* stack , PublicRec * record, int index){
	if (index==0){
		add_begin(stack, record);
		return;
	}
	Node* new_node = (Node*)calloc(1,sizeof(Node));
	if (! new_node)
		{
		printf("ERROR IN CALLOC NEW_NODE/n");
		abort();
		}
	new_node->rec=record;
	Node* current = stack->top;
    for (int i = 0; i < index - 1; i++) {
        current = current->next; 
    }
    
    new_node->next = current->next;
    current->next = new_node;
    stack->size++;
}

void delete_begin(PublicStack* stack){
	Node*temp=stack->top;
	stack->top=stack->top->next;
	free(temp);
	stack->size--;
}

void delete_end(PublicStack* stack){
	if (stack->size == 1){
		free(stack->top);
		stack->top=NULL;
	}
	else{
		Node* second_last = stack->top;
		while (second_last->next && second_last->next->next){
			second_last = second_last->next;
		}
		free(second_last->next);
		second_last->next=NULL;
	}
	stack->size--;
}

void delete_index(PublicStack* stack, int index){
	if (index==0){
		delete_begin(stack);
		return;
	}
	Node* curr=stack->top;
	for(int i=0; i<index-1;i++){
		curr=curr->next;
	}
	Node* to_del = curr->next;
	curr->next = to_del->next;
	free(to_del);
	stack->size--;
}

void swap_elements(PublicStack* stack, int index1, int index2){
	PublicRec rec1 = get_element(stack, index1);
	PublicRec rec2 = get_element(stack, index2);
	delete_index(stack, index1);
	if(index2>index1){
		index2--;
	}
	delete_index(stack, index2);
	add_index(stack,rec1,index2);
	add_index(stack,rec2,index1);
}

PublicStack arr_to_stack(PublicRec* array, int size){
	PublicStack stack;
	init_stack(&stack);
	for (int i=0; i<size;i++){
		add_end(&stack, array[i]);
	}
	return stack;
}

PublicRec* stack_to_array(PublicStack* stack) {
    PublicRec* array = (PublicRec*)malloc(stack->size * sizeof(PublicRec));
    
    Node* current = stack->top;
    for (int i = 0; i < stack->size; i++) {
        array[i] = current->record;
        current = current->next;
    }
    
    return array;
}


// Очистка стека
void clear_stack(PublicStack* stack) {
    while (stack->size > 0) {
        remove_from_beginning(stack);
    }
}

void print_help() {
    printf("  --generate N | -g N\n");
    printf("  --sort | -s --in=data.csv --out=output.csv --type=asc|desc\n");
    printf("  --print | -P --in=data.csv --out=output.txt\n");
}

// Генерация строки
void generate_random_string(char *str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '0';
}

// Генерация стека
void generate_data(int n, const char *output_file) {
    FILE *file = output_file ? fopen(output_file, "w") : stdout;
    if (!file) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < n; i++) {
        PublicRec pub;
        generate_random_string(pub.puplic_name, 20);
        generate_random_string(pub.first_author_surname, 10);
        generate_random_string(pub.first_author_inic, 5);
        generate_random_string(pub.magazen_name, 15);
        pub.puplic_year = 2000 + rand() % 24;
        pub.magazen_tom = rand() % 10 + 1;
        pub.rinc = rand() % 2;
        pub.pages_count = rand() % 100 + 1; 
        pub.citation_count = rand() % 100;

        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
                pub.puplic_name,
                pub.first_author_surname,
                pub.first_author_inic,
                pub.magazen_name,
                pub.puplic_year,
                pub.magazen_tom,
                pub.rinc,
                pub.pages_count,
                pub.citation_count);
    }

    if (output_file) fclose(file);
}

// Вывод данных
void print_data(const char *input_file, const char *output_file) {
    FILE *file = input_file ? fopen(input_file, "r") : stdin;
    if (!file) {
        perror("Error opening input file");
        return;
    }
    
    FILE *out_file = output_file ? fopen(output_file, "w") : stdout;
    fprintf(out_file, "%-20s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s\n",
            "Title", "Author last name", "Initials", "Journal Title", "Year",
            "Volume", "In RINC", "Pages", "Citations");

    char line[MAX_LINE_LENGTH];
    PublicRec pub;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token) strncpy(pub.puplic_name, token, sizeof(pub.puplic_name));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.first_author_surname, token, sizeof(pub.first_author_surname));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.first_author_inic, token, sizeof(pub.first_author_inic));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.magazen_name, token, sizeof(pub.magazen_name));
        token = strtok(NULL, ",");
        if (token) pub.puplic_year = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.magazen_tom = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.rinc = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.pages_count = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.citation_count = atoi(token);

        fprintf(out_file, "%-20s %-20s %-10s %-20s %-10d %-10d %-10d %-10d %-10d\n",
                pub.puplic_name,
                pub.first_author_surname,
                pub.first_author_inic,
                pub.magazen_name,
                pub.puplic_year,
                pub.magazen_tom,
                pub.rinc,
                pub.pages_count,
                pub.citation_count);
    }

    fclose(file);
    if (output_file) fclose(out_file);
}

// Функция для слияния двух отсортированных списков в порядке убывания
Node* merge_rev(Node* left, Node* right) {
    Node* result = NULL;

    if (!left) return right;
    if (!right) return left;

    // Изменено условие на "больше или равно" для сортировки по убыванию
    if (left->rec.puplic_year >= right->rec.puplic_year) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
} 

Node* merge(Node* left, Node* right) {
    Node* result = NULL;

    if (!left) return right;
    if (!right) return left;

    if (left->rec.puplic_year <= right->rec.puplic_year) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Функция для разделения стека на две половины
void split(Node* source, Node** front, Node** back) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Основная функция сортировки слиянием
void merge_sort(Node** head, int asc) {
    Node* current = *head;
    Node* left;
    Node* right;

    if (current == NULL || current->next == NULL) {
        return;
    }

    split(current, &left, &right);

    merge_sort(&left);
    merge_sort(&right);

    *head = merge(left, right);
}

// Функция для сортировки стека
void sort_stack(PublicStack* stack, int asc) {
    merge_sort(&stack->top, asc);
}
// Сортировка данных по году выпуска
void sort_data(const char *input_file, const char *output_file, int ascending) {
    FILE *file = input_file ? fopen(input_file, "r") : stdin;

    PublicStack A;
    init_stack(&A);
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        PublicRec pub;
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token) strncpy(pub.puplic_name, token, sizeof(pub.puplic_name));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.first_author_surname, token, sizeof(pub.first_author_surname));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.first_author_inic, token, sizeof(pub.first_author_inic));
        token = strtok(NULL, ",");
        if (token) strncpy(pub.magazen_name, token, sizeof(pub.magazen_name));
        token = strtok(NULL, ",");
        if (token) pub.puplic_year = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.magazen_tom = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.rinc = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.pages_count = atoi(token);
        token = strtok(NULL, ",");
        if (token) pub.citation_count = atoi(token);
        insert_at_beginning(&A, pub);
    }
    fclose(file);
    
    ort_stack(&A, ascending);
   

    file = output_file ? fopen(output_file, "w") : stdout;
    if (!file) {
        perror("Error opening output file");
        return;
    }

    for (int i = 0; i < get_size(&A); i++) {
        stack_to_array(&A);
        PublicRec B; 
        B = get_element(&A,i);
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
                B.puplic_name,
                B.first_author_surname,
                B.first_author_inic,
                B.magazen_name,
                B.puplic_year,
                B.magazen_tom,
                B.rinc,
                B.pages_count,
                B.citation_count);
    }
    free(A.top);
    fclose(file);
}