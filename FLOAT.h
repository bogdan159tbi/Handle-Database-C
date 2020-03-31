#include "DataFunctionality.h"

#ifndef _FLOAT_
#define _FLOAT_

//aloc float cell
t_floatCell *alocFloatCell(float value)
{
	t_floatCell *aux = malloc(sizeof(t_floatCell));
	if(!aux)
	{
		printf("allocation failed\n");
		return NULL;
	}
	aux->value  = value;
	//aux->next = NULL;
	return aux;
}

// insert new float line with certain values knowing the nr of columns
void insertFloatVal(t_table *table,float *values,int nrColumns)
{
	t_floatLine *line = malloc(sizeof(t_floatLine));

	if(!line)
	{
		printf("line didn t alocate\n");
		return;
	}

	t_floatCell *lastCell = NULL;
	t_floatCell *aux;

	for(int i = 0; i < nrColumns ;i++)
	{
	
	aux = alocFloatCell(values[i]);
	
		if(!line->cells)
		{
			line->cells = aux;
			lastCell = line->cells;
		}
		else if(lastCell)
		{
			lastCell->next = aux;
			lastCell = aux;
			lastCell->next = NULL;
		}
		
	}

	if(!table->lines)
		table->lines = line;
	else
	{
		t_floatLine *p;
		for(p = table->lines ; p->next != NULL ; p = p->next);
		p->next = line;
		line->next = NULL;
	}
	
}

//add new values in a certain table

void addFLOAT(t_db *db,char *tableName,float *val,int coloane)
{
	//check if the table already exists
	t_table *tables = db->tables;
	for( ; tables != NULL ;tables = tables->next)
		if (!strcmp(tableName,tables->name))
		   break;

	insertFloatVal(tables,val,coloane);
	//free(val);
}

//check a line if it matches the column's values
int checkFloatLine(t_floatLine *line,int whichColumn,float val,char *rel)
{
	t_floatCell *cell = line->cells;
	for(int column = 0; cell != NULL,column <= whichColumn; cell = cell->next,column++)
	{
	  if(!strcmp(rel,"<"))
	  	if(val < cell->value)
	  		return 1;
	  if(!strcmp(rel,"<="))
	  	if(val < cell->value || val == cell->value)
	  		return 1;
   	  if(!strcmp(rel,">"))
   	  	if(val > cell->value)
   	  		return 1;
   	  if(!strcmp(rel,">="))
   	  	if(val >= cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"!="))
   	  	if(val != cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"=="))
   	  	if(val == cell->value)
   	  		return 1;
	}

	return 0;
}

void findFLOAT(t_db *db,char *tableName,char *columnName,float columnValue,char *rel)
{
	int nrColumn = 0;
	int ok = 0;
	t_table *t;
	for (t = db->tables ; t != NULL ; t = t->next)
		if (!strcmp(tableName,t->name))
			break;
	if(t)
	{
		t_column *c;
		for(c = t->columns ; c != NULL; c = c->next,nrColumn++)
			if (!strcmp(c->name,columnName))
				break;
		if(c)
		{
			t_floatLine *l = t->lines;
			for(; l != NULL; l = l->next)
				if(checkFloatLine(l,nrColumn,columnValue,rel))
				{	ok = 1;
					printf("TABLE: %s\n",tableName);
					printColumns(c);
					printFloatLines(l);
					break;
				}

		}
		else{
			printf("TABLE: %s\n",tableName);
			printColumns(t->columns);
			printf("Table \"%s\" does not contain column \"%s\".\n",tableName,columnName);
		}
	}
	
}

void deleteFloatLine(t_table *table,char *colName,char *rel,char *val)
{
int nrColumn = 0;
//converteste valoarea celulei in float
float value = atof(val);
//verifica existenta coloanei si indicele sau in lista de coloane
t_column *c = table->columns;
for(; c != NULL; c = c->next,nrColumn++)
	if (!strcmp(c->name,colName))
		break;
if( !c){
	printf("Table \"%s\" does not contain column \"%s\".\n",table->name,colName);
	return;
}
//gaseste linie
t_floatLine *lin = table->lines ,*ultim = NULL;
for( ; lin != NULL; lin = lin->next)
	if(checkFloatLine(lin,nrColumn,value,rel))
		break;
if(lin == NULL)
	return;//daca nu exista vreo linie cu valorea ceruta

//refa legaturile in functie de pozitia liniei in lista de linii(urm)

if(!ultim){
	t_floatLine *firstLine = table->lines;
	firstLine = firstLine->next;
	table->lines = firstLine;
}
else
	ultim->next = lin->next;

//delete celule de tip float
t_floatCell *ce = lin->cells;
//deleteFloatCell(&ce); REZOLVA ODATAAAAAA
//elibereaza linie
free(lin);

}


#endif
