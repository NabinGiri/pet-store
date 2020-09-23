/*
			From: Nabin Giri
			Email : nvngiri2@gmail.com
*/


//Problem says there is enough memory but the processor is slow. 
//A node in linked list taked more memory than array because it has to store pointer to next node.
// The pointer takes 4 bytes in memory. Since, we have enough memory we can use pointers.
//using linked list because insertion and deletion in linked list is faster. 

#include<stdio.h>
#include<stdlib.h> //needed for exit calls
#include<stdbool.h>  //needed to check True or False

#define MAX_BUNNIES INT_MAX; // maximum bunnies in the cage at a time.

//lets create a structure which consists of bunny id, bunny color, bunny size, 
//structure is by default public in type, so we donot need to specify explicitly. 
//we are creating a struct node which contains member variables- id,color and size of bunny - heterogenous datatypes. 
// struct creates space in memory for all data types but union creates space in memory for only the largest datatype; 
// using union causes risk of altering all the variables if we modify one member.
typedef struct
{
	int id;		//id of a bunny
	char color; //color of the bunny
	int size; //size of the bunny
	struct node* next
} node;



void clear(node* nodepointer)
{ 
	//removes all the bunnies as the game is terminating. we call removebunny function as long as there are bunnies in cage.
	while (nodepointer != NULL)
	{
		nodepointer = removebunny(nodepointer);
	}
}


void showtime(node* nodepointer)
{
	if (nodepointer == NULL)
	{
		printf("The cage is empty");
	}
	else
	{
		while (nodepointer != NULL)
		{
			printf("%d", nodepointer->id);
			nodepointer = nodepointer->next;
		}
	}
}


node* remove_by_id(node* nodepointer, int val)
{
	node* curr, * pre;
	pre = nodepointer;
	curr = pre->next;
	while (curr)
	{
		if (curr->id == val)
		{
			pre->next = curr->next;
			free(curr);
			printf("Bunny removed is: %d", val);
			return nodepointer;
		}
		pre = curr;
		curr = curr->next;

	}
	
}

node* removebunny(node* nodepointer)
{
	node* temp; //creating a temp node;
	temp == nodepointer->next; 
	pritnf("Bunny removed is: %d", nodepointer->next);
	free(nodepointer);
	return temp; //returns the new node with all the node links.
}



node* additem(node* nodepointer, int data)
{
	if (nodepointer != NULL) // if there is already a node present in linkedlist
	{
		printf("Enter 1 to create bunny on the top of list\n");
		printf("Enter 2 to create bunny at the end of list\n");
		int location;
		scanf("%d", &location);
		if (location == 1) //if the player wants to add the bunny on top of list, we create a node and in next, we keep memory address of next node in the list.
		{
			node* head;
			head = (struct node*)malloc(sizeof(node));// creating a node with member variables and allocating memory.
			if (head == 0) return -1; // if malloc is unable to create space. terminate.
			head->next = nodepointer; //the next of head stores memory address of the next node.
			head->id = data; //the id of bunny is stored on the id variable.
			free(nodepointer); // we are returning head, as the head->next contains the nodepointer now.
			// if we donot free then it causes memory leakage.
			return head; // returning head node.

		}
		if (location == 2) // if player wants to add the bunny on the end of the list,
		{
			node* np = nodepointer;
			while (nodepointer->next != NULL)
			{
				nodepointer = nodepointer->next;
				nodepointer->next = (struct node*)malloc(sizeof(nodepointer));
				if (nodepointer->next == 0) return -1;
				nodepointer = nodepointer->next;
				nodepointer->next = NULL;
				nodepointer->id = data;
				//free(nodepointer);
			return np;
			}
		
		}
		else return -1;
	}
	else
	{
		//if there is no node in the linkedlist, we create a new node.
		nodepointer = (struct node*)malloc(sizeof(node));
		if (nodepointer == 0) return -1;
		nodepointer->id = data;
		nodepointer->next = NULL;
		return nodepointer;

	}
}


void menu(int* choice)
{
	char vals;
	printf("\n\t\t\tWelcome to Bunny Cage Game!!\n");
	printf("\nEnter \t1 to create bunnies, \n\t2 to remove bunnies, \n\t3 to display bunnies, \n\t4 to quit\n");
	//using do while loop as when the game starts we need input from the player and then we check for the condition.
	do
	{
		vals = getchar(); //reads the stdin value
		//checking if the user input is interger or any other character to select among the choices.
		if ((isdigit(vals) == false) && (vals != '\n')) //need stdbool.h library
		{
			printf("\nNeed an iteger value!\n");
			printf("\nEnter \t1 to create bunnies, \n\t2 to remove bunnies, \n\t3 to display bunnies, \n\t4 to quit\n");
		}
	} while (isdigit((char)vals) == false); //run until we get integer value
	*choice = (int)vals - '0'; //store integer type value into choice. this is accessed by menu function.
	// note: the function can also be int type and return the choice value, but here we have pointer type and its void(not returning anything).
}


int main() // returns 0 on successful so, main type is integer.
{
	node nodemember; //creating nodemember from struct node.
	node* nodepointer; // defining a pointer type for nodepointer.
	int data;
	int choice;
	nodepointer = NULL; //the list is NULL at first.
	do
	{
		menu(&choice); //reads the choice
		// while creating pointer we use datatype* ptrname; while accessing memory value/address of pointer we use &valname
		//lets use switch case to control the flow of program.
		switch (choice)
		{
		case 1:
			printf("Welcome to the bunny creation section");
			printf("Enter the id to add: ");
			scanf("%d", &data);
			// a. if linkedlist is empty -> create a new node.
			//b. if there is node -> add bunny on top or end.
			nodepointer = addbunny(nodepointer, data);
			break;

		case 2:
			printf("Welcome to the bunny removal section");
			printf("Children, remove the bunny as you desire");
			//if the cage does not have any bunny then the case if empty.
			if (nodepointer == NULL) // if there is no node on the list
			{
				printf("\n There are no bunnies in the cage");
			}
			else
			{
				// operations to peform : 
					// 1. Queue : First in First Out. (add bunny on list and remove the top bunny from list).
					//2. Stack : Last in First Out. (add bunny on the list and remove the last bunny added).
				int val;
				printf("Enter the id to remove:\n");
				scanf("%d", &val);
				if (nodepointer->id == val) // lets check if the bunny is on the top, out pointer points the top for now.. 
				{
					//removing the top bunny 
					//Queue operation. - FIFO.
					nodepointer = removebunny(nodepointer);


				}
				else
				{
					nodepointer = remove_by_id(nodepointer, val);
					// the list has to travel till it finds the val, 
					// TODO: need to keep the pointer to end node, so that removing end node is easier.
					// TODO: point the end node next to head, so removal of head and end is on O(1) time.




				}


			}
			break;

		case 3:
			printf("Welcome to bunny display wizard! ");
			showtime(nodepointer);
			break;

		case 4:
			break; //if exit then exit the program.


		default:
			printf("Invalid choice");
			break;
		}


	} while (choice != 4);
	clear(nodepointer);


}

