#ifndef STRUCT_CONTAINER_H
#define STRUCT_CONTAINER_H
#include "publication_record.h"


typedef struct Node{
	PublicRec rec;
	struct Node* next;
}Node;

typedef struct{
	Node * top;
	int size;
}PublicStack;

void init(PublicStack * stack);
int get_size(PublicStack* stack);
PublicRec get_element(PublicStack * stack, int index );
Node* get_start(PublicStack *stack);
Node* get_end(PublicStack* stack);
Node* get_next(Node* node);
Node* get_last(PublicStack* stack, Node* node);
void add_begin(PublicStack* stack , PublicRec * record);
void add_end(PublicStack* stack , PublicRec * record);
void add_index(PublicStack* stack , PublicRec * record, int index);
void delete_begin(PublicStack* stack);
void delete_end(PublicStack* stack);
void delete_index(PublicStack* stack, int index);
void swap_elements(PublicStack* stack, int index1, int index2);
PublicStack arr_to_stack(PublicRec* array, int size);
PublicRec* stack_to_array(PublicStack* stack) ;
// Очистка стека
void clear_stack(PublicStack* stack) ;
// Генерация строки
void generate_random_string(char *str, int length);
// Генерация стека
void generate_data(int n, const char *output_file);
// Вывод данных
void print_data(const char *input_file, const char *output_file);
// Функция для слияния двух отсортированных списков в порядке убывания
Node* merge_rev(Node* left, Node* right);
Node* merge(Node* left, Node* right) ;
// Функция для разделения стека на две половины
void split(Node* source, Node** front, Node** back);
// Основная функция сортировки слиянием
void merge_sort(Node** head, int asc);
// Функция для сортировки стека
void sort_stack(PublicStack* stack, int asc);
// Сортировка данных по году выпуска
void sort_data(const char *input_file, const char *output_file, int ascending) ;

#endif