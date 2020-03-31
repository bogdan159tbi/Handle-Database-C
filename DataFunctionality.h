#include "structures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Data definition    ->Init DB 
				      ->Delete DB -> Free memory
				      ->Create Table

   Data Query         ->Print DB
   					  ->Print table: show data in the table
   				   	  ->Search table: show lines that have value which provides with the required conditions

   Data Manipulation  ->Add table
   					  ->Delete table: free lines that consist of certain value
   					  ->Clear table: free all lines
 */

/* data definition:  ->t_db *initDB(char *name)
					 |
					 -->aloc memorie pt tabele,coloane, linii 
*/

//int query


//NOTE---> aici am functii de initializare creare tabela si afisare linii/coloane pt int si string,float nu inca
// + functie de eliberare memorie pt database ,pt linii si coloane de tip int  si string le am facut recursiv


#ifndef _DATAFUNCTIONALITY_
#define _DATAFUNCTIONALITY_


t_cellType checkType(char *type)
{
	if (!strcmp(type,"STRING"))
		return STRING;
	if (!strcmp(type,"INT"))
		return INT;
	if (!strcmp(type,"FLOAT"))
		return FLOAT;
	printf("unknown type\n");
	return 0;
}

t_db *initDB(char *name)
{
	t_db *db = malloc(sizeof(t_db));
	if(!db)
	{
		printf("failed alocating db\n");
		return NULL;
	}

	strncpy(db->name,name,strlen(name));

	return db;
}

t_table *initTable()
{
	t_table *tables = malloc(sizeof(t_table));
	if (!tables)
	{
		printf("failed aloc table\n");
		return NULL;
	}

	return tables;
}


void deleteColumns(t_column *columns)
{
	while(columns)
	{
		t_column *aux;
		aux = columns;
		columns = columns->next;
		free(aux);
	}

}

void deleteIntCell(t_intCell *cells)
{
	while(cells)
	{
		t_intCell *aux = cells;
		cells = cells->next;
		free(aux);
	}
}
void deleteInt(t_intLine *lines)
{

	while(lines)
	{
		t_intLine *aux = lines;
		lines = lines->next;
		free(aux);
	}
}

void deleteStringCell(t_stringCell *cells)
{

	while(cells)
	{
		t_stringCell *aux = cells;
		cells = cells->next;
		free(aux);
	}
}
void deleteString(t_stringLine *lines)
{
	while(lines)
	{
		t_stringLine *aux = lines;
		lines = lines->next;
		deleteStringCell(lines->cells);
		free(aux);
	}
}

void deleteFloatCell(t_floatCell **cells)
{
	t_floatCell *prev = NULL ,*p = *cells;
	while(p)
	{	
		prev = p;
		p = p->next;
		printf("%f ",p->value);
	
	}
	*cells = NULL;
}

void deleteFloat(t_floatLine **lines)
{	
	t_floatLine *aux ,*l = *lines;
	t_floatCell *auxCell = NULL;
	while(l)
	{
		aux = l;
		t_floatCell *c = l->cells;
		// sterge celule coloane
		l = l->next;
		//deleteFloatCell(&c);
		free(aux);
	}
	*lines = NULL;
}

void deleteTable(t_table *table)
{
	if(table){		
		if(table->type == INT){
			//printf("int\n");
			deleteInt(table->lines);
		}
		
		else if(table->type == STRING){

			deleteString(table->lines);
		}
		//mai am pt float
		else if(table->type == FLOAT){
			t_floatLine *l = table->lines;
			deleteFloat(&l);
		}
		else
		{
			return;
		}
	 	deleteColumns(table->columns);
		table = NULL;
		}
}
void deleteDB(t_db *db)
{
	while(db->tables){
	t_table *aux = db->tables;
	db->tables = db->tables->next;
	deleteTable(aux);
	}
	free(db);
	// opreste executia programului
}

/*insereaza coloane la sfarsit */
t_column *insertColumn(t_table *t,char *colName)
{	
	char *name = strtok(colName,"\n");
	t->columns = malloc(sizeof(t_column));
	name = strtok(NULL," ");
	strcpy(t->columns->name,name);
	if(!t->columns)
		return NULL;
	t_column *c = t->columns;

	while((name = strtok(NULL," ")))
	{
		c->next = malloc(sizeof(t_column));
		if(!c->next)
			return NULL;
		strcpy(c->next->name,name);
		c = c->next;
	}
	
	return NULL;
}

t_table *createTable(t_db *db,char *tableName/*tipul pe care l las int prima oara*/)
{	

	if(!db->tables)
	{
	 db->tables = initTable();
	 if(!db->tables)
	 {
	 	printf("didn t alocate table\n");
	 	free(db);
	 	return NULL;
	 }
	strncpy(db->tables->name,tableName,strlen(tableName));
		return db->tables;
	}
	else
	{	
		t_table *tables = db->tables;
		for(; tables != NULL ; tables = tables->next)
			if (!strcmp(tableName,tables->name))
			{
				printf("%s already exists\n",tableName);
				return NULL;
			}
		for(tables = db->tables; tables->next != NULL; tables = tables->next);

		t_table *aux = initTable();

		if(!aux)
		{	deleteTable(db->tables);
			free(db);
			return NULL;
		}
		if(tables){
		tables->next = aux;
		strncpy(tables->next->name,tableName,strlen(tableName));
		}

		return aux;
	}


}

/*Data Query */
// print whole Database


void printStringCells(t_stringCell *cells)
{	
	
	int celule = 0;

	for( ;cells != NULL ; cells = cells->next)
		{printf("%s",cells->value);
		 for(int j = 0; j < MAX_COLUMN_NAME_LEN - strlen(cells->value) + 1;j++)
		 	 printf(" ");
		}
	printf("\n");

}

void printStringLines(t_stringLine *lines){
	for(; lines != NULL ; lines = lines->next)
		printStringCells(lines->cells);

}
int len(int nr)
{
	int c = 0;
	if(nr == 0)
		return 1;
	while(nr)
	{
		c++;
		nr = nr/10;
	}
	return c;
}
void printFloatCells(t_floatCell *cells)
{
	int celule = 0;
	for( ;cells != NULL ; cells = cells->next){
		printf("%f ",cells->value);
		for(int i = 0; i < MAX_COLUMN_NAME_LEN - 7  - len(cells->value)  ;i++)
			printf(" ");
	}
	printf("\n");

}

void printFloatLines(t_floatLine *lines)
{	
	for(; lines != NULL ; lines = lines->next)
		printFloatCells(lines->cells);

}

void printIntCells(t_intCell *cells)
{	
	int celule = 0;
	t_intCell *c = cells;

	for(;cells != NULL; cells = cells->next){
		printf("%d",cells->value);
		for(int i = 0; i < MAX_COLUMN_NAME_LEN  -len(cells->value) + 1 ;i++)
			printf(" ");
	}
	printf("\n");
}

void printIntLines(t_intLine *lines)
{
	for(; lines != NULL ; lines = lines->next)
		printIntCells(lines->cells);
	
}
void printColumns(t_column *columns)
{	int j,coloane = 0 ;
	for( ;columns != NULL; columns = columns->next){
		
		printf("%s",columns->name);
		for(int i = 0 ; i < MAX_COLUMN_NAME_LEN - strlen(columns->name) + 1; i++)
			printf(" ");
		coloane++;
	}
	printf("\n");

	for(j = 0 ; j < coloane; j++){
	for(int i = 0; i < MAX_COLUMN_NAME_LEN ;i++)
			printf("-");
	printf(" ");
	}
	printf("\n");
	int z;
}



void printTable(t_db *db,char *tableName)
{
	t_table *tb = db->tables;
	for(; tb != NULL; tb = tb->next)
		if ( !strcmp(tb->name,tableName))
		{	printf("TABLE: %s\n",tableName);
			printColumns(tb->columns);
			if( tb->type == INT)		
				printIntLines(tb->lines);
		
			else if( tb->type == STRING)
					printStringLines(tb->lines);	
			else if ( tb->type == FLOAT)
				printFloatLines(tb->lines);
			else
				printf("unknown data type\n");
			break;
		}
		
	if(!tb)
		printf("Table \"%s\" not found in database.\n",tableName);
	else
		printf("\n");
}
void printDB(t_db *db)
{
	if( !db)
	{
		printf("data base doesn't exist\n");
		return ;
	}
	printf("DATABASE: %s\n",db->name);

	t_table *tables = db->tables;
	for( ; tables != NULL; tables = tables->next)
	{	
		printf("TABLE: %s\n",tables->name);
		printColumns(tables->columns);
		if( tables->type == INT)
		printIntLines(tables->lines);

		if( tables->type == STRING)
			printStringLines(tables->lines);
		if( tables->type == FLOAT)
			printFloatLines(tables->lines);
		printf("\n");//sau 2 \n
	}

}


// mai am search

/*Data manipulation*/

// caut linie resp 
//verific daca indepl relatia ceruta
// eliberez pe rand memoria


#endif