#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book 
{
    char catalog_num[20];
    char title[80];
    char author[50];
    double price;
    int publish_year;
    char publisher[80];
}book;
    
typedef struct Node
{
    book properties;
    struct Node *next;
}node;
    
node *head = NULL;
       
void add_new_book(FILE *file_pointer);
void bin_to_node (FILE *file_pointer);
void actualize_by_catNumber (FILE *file_pointer);
struct Book overwrite_by_catNumber (int node_counter, FILE *file_pointer);
void search_by_title ();
void search_by_author ();
void print_list ();



int main(int argc, char** argv) 
{
    char filename[20];
    printf("Enter file you wish to open: ");
    if (scanf("%s", filename) != 1)
    {
        printf("Error scanning file name!");
        exit (-1);
    }
    
    FILE *file_pointer;
    if ((file_pointer = fopen (filename, "rb+")) == NULL)
    {
        if ((file_pointer = fopen (filename, "wb+")) == NULL)
        {
            printf("Error in opening files in both modes!");
            exit (-1);
        }
    }
    bin_to_node (file_pointer);
    
    int option;
       
    do 
    {
        printf("\n1. Add a new book");
        printf("\n2. Actualize book data by catalog number");
        printf("\n3. Search book by title");
        printf("\n4. Search book by author");
        printf("\n5. Print list");
        printf("\n6. Exit menu\n");
        printf("\nChoose an option from the menu: ");
        if (scanf("%d", &option) != 1)
        {
            printf("Error scanning option!");
            return (-1);
        }
        if (option<1 || option>6) { printf("\nInvalid input, please choose between 1-6\n"); }
       
        switch (option)
        {
            case 1 :
                add_new_book(file_pointer);
                break;  
            case 2 :
                actualize_by_catNumber (file_pointer);
                break;
            case 3 :
                search_by_title ();
                break;
            case 4 :
                search_by_author ();
                break;
            case 5 :
                print_list ();
                break;  
            case 6 :
                break;
            default :
                printf("\nInvalid input ! Please enter a number between 1-6");
                break;
        }
    } 
    while (!(option == 6));
    
    fclose(file_pointer);

    return (EXIT_SUCCESS);
}

void add_new_book(FILE *file_pointer)
{
    book new_book;
    
    printf("Enter catalog number: ");
    if (scanf("%s", new_book.catalog_num) != 1)
    {
        printf("Error in scanning *new_book.catalog_num*");
        return;
    }
    node *cycle_through_list = head;
    
    while(cycle_through_list != NULL)
    {
        if (!(strcmp(new_book.catalog_num, cycle_through_list->properties.catalog_num)))
        {
            printf("The catalog number you wish to enter already exists\n");
            printf("Please enter different catalog number !\n");
            return;
        }
        cycle_through_list = cycle_through_list->next;    
    }
    
    printf("Enter book title: ");
    if (scanf("%s", new_book.title) != 1)
    {
        printf("Error in scanning *new_book.title*");
        return;
    }
    printf("Enter book author: ");
    if (scanf("%s", new_book.author) != 1)
    {
        printf("Error in scanning *new_book.author*");
        return;
    }
    printf("Enter book price: ");
    if (scanf("%lf", &new_book.price) != 1)
    {
        printf("Error in scanning *new_book.price*");
        return;
    }
    printf("Enter book publish year: ");
    if (scanf("%d", &new_book.publish_year) != 1)
    {
        printf("Error in scanning *new_book.publish_year*");
        return;
    }
    printf("Enter book publisher: ");
    if (scanf("%s", new_book.publisher) != 1)
    {
        printf("Error in scanning *new_book.publisher*");
        return;
    }
   
    if (fwrite(&new_book, sizeof(book), 1, file_pointer) != 1)
    {
        printf("Error in writing to file");
        return;
    }
    if (head == NULL)
    {
        head = (node*)malloc(sizeof(node));
        head->properties = new_book;
        head->next = NULL;
    }
    else 
    {
        node *temp = (node*)malloc(sizeof(node));
        temp->properties = new_book;
        temp->next = head;
        head = temp;
    }
}

void bin_to_node (FILE *file_pointer)
{
    if (!(head == NULL))
    {
        printf("Error head is not equal to NULL");
        return;
    }
    rewind(file_pointer);
   
    book temp;
    while (1)
    {
        if (fread (&temp, sizeof(book), 1, file_pointer)!=1)
        {
            break;
        }
        if (head == NULL)
        {
            head = (node*)malloc(sizeof(node));
            head -> properties = temp;
            head -> next = NULL;
        }
        else 
        {
            node *temp_node = (node*)malloc(sizeof(node));
            temp_node->properties = temp;
            temp_node->next = head;
            head = temp_node;          
        }
    }  
}

void actualize_by_catNumber (FILE *file_pointer)
{
    char book_catNum[20];
    printf("Enter book catalog number: ");
    if (scanf("%s", book_catNum) != 1)
    {
        printf("Error in scanning *book_catNum*");
        return;
    }
    
    node *cycle_through_list;
    cycle_through_list = head;
    int node_counter = 0;
    
    while (cycle_through_list != NULL)
    { 
        if (!(strcmp(book_catNum, cycle_through_list->properties.catalog_num)))
        {
            cycle_through_list->properties = overwrite_by_catNumber(node_counter, file_pointer);
            break;
        }   
        cycle_through_list = cycle_through_list->next;
        node_counter ++;
    }
}

struct Book overwrite_by_catNumber (int node_counter, FILE *file_pointer)
{   
    book overwrite_book;
    
    printf("Enter new book information!\n");
    printf("\nEnter catalog number: ");
    if (scanf("%s", overwrite_book.catalog_num) != 1)
    {
        printf("Error in scanning *overwrite_book.catalog_num*");
        exit(-1);
    }
    printf("Enter book title: ");
    if (scanf("%s", overwrite_book.title) != 1)
    {
        printf("Error in scanning *overwrite_book.title*");
        exit(-1);
    }
    printf("Enter book author: ");
    if (scanf("%s", overwrite_book.author) != 1)
    {
        printf("Error in scanning *overwrite_book.author*");
        exit(-1);
    }
    printf("Enter book price: ");
    if (scanf("%lf", &overwrite_book.price) != 1)
    {
        printf("Error in scanning *overwrite_book.price*");
        exit(-1);
    }
    printf("Enter book publish year: ");
    if (scanf("%d", &overwrite_book.publish_year) != 1)
    {
        printf("Error in scanning *overwrite_book.publish_year*");
        exit(-1);
    }
    printf("Enter book publisher: ");
    if (scanf("%s", overwrite_book.publisher) != 1)
    {
        printf("Error in scanning *overwrite_book.publisher*");
        exit(-1);
    }
    
    fseek (file_pointer, sizeof(book)*node_counter, SEEK_SET);
    if (fwrite (&overwrite_book, sizeof(book), 1, file_pointer) != 1)
    {
        printf("Error in overwriting book by catalog number!");
        exit(-1);
    }
    
    return overwrite_book;
}

void search_by_title ()
{ 
    char title[80];
    printf("Enter title you would like to search: ");
    if (scanf("%s", title) != 1)
    {
        printf("Error in scanning *title*");
        return;
    }
    
    node *cycle_through_list = head;
    
    while(cycle_through_list != NULL)
    {
        if (!(strcmp(title, cycle_through_list->properties.title)))
        {
            printf("\nBook catalog number is %s", cycle_through_list->properties.catalog_num);
            printf("\nBook title is %s", cycle_through_list->properties.title);
            printf("\nBook author is %s", cycle_through_list->properties.author);
            printf("\nBook price is %.2lf", cycle_through_list->properties.price);
            printf("\nBook year of print is %d", cycle_through_list->properties.publish_year);
            printf("\nBook publisher is %s\n", cycle_through_list->properties.publisher);   
            return;
        }
        cycle_through_list = cycle_through_list->next;    
    }
    printf("There is no book with such a title !\n");
}

void search_by_author ()
{   
    char author[50];
    printf("Enter author/authors ( for multiple authors enter format: author1 & author2 ): ");
    if (scanf("%s", author) != 1)
    {
        printf("Error in scanning *author*");
        return;
    }
    
    node *cycle_through_list = head;
    
     while(cycle_through_list != NULL)
    {
        if (!(strcmp(author, cycle_through_list->properties.title)))
        {
            printf("\nBook catalog number is: %s", cycle_through_list->properties.catalog_num);
            printf("\nBook title is: %s", cycle_through_list->properties.title);
            printf("\nBook author is: %s", cycle_through_list->properties.author);
            printf("\nBook price is: %.2lf", cycle_through_list->properties.price);
            printf("\nBook year of print is: %d", cycle_through_list->properties.publish_year);
            printf("\nBook publisher is: %s\n", cycle_through_list->properties.publisher);   
            return;
        }
        cycle_through_list = cycle_through_list->next;    
    }
    printf("There is no book with such an author !\n");
}

void print_list ()
{
    book print_book;
    node *temp = head;
    
    while (temp != NULL)
    {
        print_book = temp->properties;
        printf("\nBook catalog number is: %s", print_book.catalog_num);
        printf("\nBook title is: %s", print_book.title);
        printf("\nBook author is: %s", print_book.author);
        printf("\nBook price is: %.2lf", print_book.price);
        printf("\nBook year of print is: %d", print_book.publish_year);
        printf("\nBook publisher is: %s", print_book.publisher);  
        printf("\n");
        temp = temp->next;
    }
}