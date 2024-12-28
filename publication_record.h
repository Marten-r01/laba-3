#ifndef STRUCT_RECORD_H
#define STRUCT_RECORD_H
typedef struct{
	char puplic_name[100];
	char first_author_surname[100];
	char first_author_inic[10];
	char magazen_name[100];
	int puplic_year;
	int magazen_tom;
	int rinc;
	int pages_count;
	int citation_count;
} PublicRec;
#endif