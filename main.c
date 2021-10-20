#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int debugMode;

typedef struct StackStruct
{
 char*    darr;  /* pointer to dynamic array  */
 int     size;  /* amount of space allocated */
 int     inUse; /* top of stack indicator
           - counts how many values are on the stack   */
} Stack;

/** Function prototypes **/
void init(Stack* s);
void push(Stack* s, int val);
int isEmpty (Stack* s);
char top (Stack* s);
void pop (Stack* s);
void clear (Stack* s);


int main (int argc, char** argv)
{ 
    
 debugMode = FALSE;
 int i;
 for ( i = 0 ; i < argc ; i++ )
 {
     if ( strcmp (argv[i], "-d") == 0 )
     {
         debugMode = TRUE; 
     }
 }
 
 
 Stack stk;
 char input[301];

 init(&stk);  // initializes the stack to zero after its created
 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   /*You can remove/move this print statement based on your code structure */
   //printf ("%s\n", input);

   /* run the algorithm to determine is input is balanced */
       
   int error = 0; // to check if there is an error
   for(int k = 0; k < strlen(input); k++) // loops throughout the length of the user input
   {
       /** checks if the users input is an opening symobl **/
       if(input[k] == '(' || input[k] == '{' || input[k] == '[' || input[k] == '<')
       {
           push(&stk, input[k]);   // pushes that symbol in the stack
       }
       /** checks if the users input is a closing symobl **/
       else if(input[k] == ')' || input[k] == '}' || input[k] == ']' || input[k] == '>')
       {
           if(isEmpty(&stk))  // checks if the stack is empty, then gives error 1
           {
               printf("Unbalanced expression. Error 2: missing an opening symbol\n");
               printf("%s\n", input);
               for(int j = 0; j < k; j++ )
               {
                   printf(" ");
               }
               /** uses the up arrow to show where the error is and the missing symbol for each case **/
               if(input[k] == ')')
                   printf("^ missing (");
               else if(input[k] == '}')
                   printf("^ missing {");
               else if(input[k] == ']')
                   printf("^ missing [");
               else if(input[k] == '>')
                   printf("^ missing <");
               
               error = 1; // shows that there is an error when it is 1
               break;
           }
           /** checks if the symbol on the top of the stack is the corresponding opening symbol **/
           else if((input[k] == ')' && top(&stk) == '(') || (input[k] == '}' && top(&stk) == '{') || (input[k] == ']' && top(&stk) == '[') || (input[k] == '>' && top(&stk) == '<'))
               pop(&stk);  // if yes then it pops the stack
           else   // else it gives an error
           {
               printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
               printf("%s\n", input);
               
               for(int x = 0; x < k; x++)
               {
                   printf(" ");
               }
               /** uses the up arrow to show where the error is and shows the expecting opening symbol for each case **/
               if(top(&stk) == '(')
                   printf("^ expecting )");
               else if(top(&stk) == '{')
                   printf("^ expecting }");
               else if(top(&stk) == '[')
                   printf("^ expecting ]");
               else if(top(&stk) == '<')
                   printf("^ expecting >");
               
               error = 1;  // shows that there is an error when it is 1
               break;
           }
                 
       }
   }
     
   if(isEmpty(&stk) && error == 0)  // checks if the stack empty and the error is 0
   { 
       printf("%s\n", input);
       printf("Expression is balanced\n");  // prints the stack is balanced
   }
   else if(!isEmpty(&stk) && error == 0)
   {
       printf("Unbalanced expression. Error 3: missing a closing symbol \n");
       printf("%s\n", input);
       for(int x = 0; x < strlen(input); x++) // loops through the length of the input
       {
            printf(" ");
       }
       /** uses the up arrow to show where the error is and shows the missing closing symbol for each case **/
       if(top(&stk) == '(')  // checks if the top of the stack is an opening symbol
          printf("^ missing )");
       else if(top(&stk) == '{')
          printf("^ missing }");
       else if(top(&stk) == '[')
          printf("^ missing ]");
       else if(top(&stk) == '<')
          printf("^ missing >");
                
   }
     
   clear(&stk);  // uses the clear function to free and init and the stack
 }
 
    
 printf ("\nGoodbye\n");
 free(stk.darr);    // frees the array of the stack
 return 0;
}


void init (Stack* s)  // initializing the stack
{
 s->size = 4;  // sets the aize of the stack
 s->darr = (char*) malloc ( sizeof (char) * s->size );
 s->inUse  = 0;
}

void push (Stack* s, int val)  //pushing/addingan element onto the stack
{
 
  if(s->inUse >= s->size)
    {
        char *tmp ;
        tmp = s->darr; // sets temp as the array of the stack
        
        /*allocate new space for the larger array*/
        s->darr = (char*)malloc(sizeof(char)*(s->size + 4)); // makes the array grow by 4

        /*copy the existing values from the original array to the larger array*/
        for(int k = 0 ; k < s->size; k++)
            s->darr[k] = tmp[k];
      
        if(debugMode == TRUE) // checks if the debugging is applied then prints out the following
            printf("Stack size increased from %d to %d,a total of %d values were copied \n", s->size, s->size+4, s->inUse);
      
        /* return the allocated memory from the original array back to the OS*/
        free(tmp);  // frees the temo array

        s->size = s->size + 4; // makes the array grow by 4
    }
    
    /* add val onto stack */
    s->darr[s->inUse] = val;
    
    if(debugMode == TRUE)  // checks if the debugging is applied then prints out the following
       printf("Character %c was pushed into the stack\n", s->darr[s->inUse]);
    
    s->inUse = s->inUse + 1; // increases the count of the stack by 1
}

int isEmpty (Stack* s) // checking if the stack is empty
{
  if ( s->inUse == 0) // checks if the count of the stack is 0 it shows as empty
    return TRUE;
  else
    return FALSE;
}

char top (Stack* s)  // accessing/returningthe top element on the stack
{
  return (s->darr[s->inUse-1]);
}


void pop (Stack* s)  // popping/removingan element off of the stack
{
  s->inUse = s->inUse - 1;  // reduces the count of the stack
  
  if(debugMode == TRUE)  // checks if the debugging is applied then prints out the following
      printf("Character %c was popped from the stack\n", s->darr[s->inUse]);
}

void clear (Stack* s)  // clear the stack so that it is empty and ready to be used again
{
    free(s->darr);
    init(s);
}

