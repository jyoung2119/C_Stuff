#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct FileBoi
{
    int* fileContents; 
    int totalInts;
};

struct FileBoi file_stuff(void);
void bubble_sort(struct FileBoi struBubble);
void selection_sort(struct FileBoi struSelect);
void insertion_sort(struct FileBoi struInsert);
void print_output(struct FileBoi struFinal);

void main()
{  
    printf("\e[1;1H\e[2J");                         //Clear the console (faster than system("cls"))
    struct FileBoi s2 = file_stuff();               //Store output of function in new instance of struct
    clock_t timerBoi;
    double timeTaken = 0;
    printf("\nTotal Ints: %d\n", s2.totalInts); 
    for(int i = 0; i < s2.totalInts; i++)
    {
        printf("%d ", s2.fileContents[i]);
    }

    int userChoice = 0;
    printf("\n***********FILE IO INTEGER SORT***********\n");
    printf("*********CHOOSE SORTING ALGORITHM*********\n");
    printf("1. Display as is from file\n");
    printf("2. Bubble Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Insertion Sort\n");
    if(scanf("%d", &userChoice))
    {
        printf("GOOD INPUT\n");
        switch(userChoice)
        {
            case 1:
                print_output(s2);
                break;
            case 2:
                timerBoi = clock();
                bubble_sort(s2);
                timerBoi = clock() - timerBoi;
                timeTaken = ((double)timerBoi)/CLOCKS_PER_SEC;
                printf("\nbubble_sort() took %f seconds to execute \n", timeTaken);
                break;
            case 3:
                timerBoi = clock();
                selection_sort(s2);
                timerBoi = clock() - timerBoi;
                timeTaken = ((double)timerBoi)/CLOCKS_PER_SEC;
                printf("\nselection_sort() took %f seconds to execute \n", timeTaken);
                break;
            case 4:
                timerBoi = clock();
                insertion_sort(s2);
                timerBoi = clock() - timerBoi;
                timeTaken = ((double)timerBoi)/CLOCKS_PER_SEC;
                printf("\ninsertion_sort() took %f seconds to execute \n", timeTaken);
                break;
            default:
                break;
        }
    }
    else
    {
        printf("BAD INPUT");
    }    
}

struct FileBoi file_stuff(void)
{
    struct FileBoi s1;     //Create instance of struct
    char filePath[] = "C:\\Users\\jyoun\\Desktop\\C_Stuff\\FileSort\\numbers.txt";  //File path
    FILE *fptr = fopen(filePath, "r");  //Open file
    
    int intStore = 0;   //Stores ints from file one at a time
    int ptrIndex = 0;   //Pointer index
    s1.totalInts = 0;   //Set total to 0 instead of preset value

    //If file opens
    if(fptr != NULL)
    {   
        //Run until end of file
        //Find total # of ints
        while(!feof(fptr))
        {
            fscanf(fptr, "%d", &intStore);  //Scan int one at a time
            //printf("%d ", intStore);        //Print to check fscanf
            s1.totalInts++;                 //Increment int total for file
        }
        //printf("Total Ints: %d\n", s1.totalInts);
        s1.fileContents = (int*)malloc(s1.totalInts * sizeof(int));     //Allocate memory for ptr based off int total
        rewind(fptr);                                           //Move ptr back to beginning of file

        //Run until end of file
        //Store each int into struct
        while(!feof(fptr))
        {
            fscanf(fptr, "%d", &intStore);  //Scan int one at a time
            s1.fileContents[ptrIndex] = intStore;    //Store ints into ptr
            ptrIndex++;                     //Increment ptr index
        }

        fclose(fptr);      //Close file     
    }
    else
    {
        printf("%s\n", "FILE FAILED TO OPEN\n");
    }
    return s1;
}

void bubble_sort(struct FileBoi struBubble)
{
    printf("BUBBLE HERE\n");
    int n = struBubble.totalInts;
    int holder = 0;
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < n - i; x++)
        {
            if(struBubble.fileContents[x] > struBubble.fileContents[x + 1])
            {
                holder = struBubble.fileContents[x];
                struBubble.fileContents[x] = struBubble.fileContents[x + 1];
                struBubble.fileContents[x + 1] = holder;
            }
        }
    }
    print_output(struBubble);
}

void selection_sort(struct FileBoi struSelect)
{
    int n = struSelect.totalInts;
    int holder = 0;
    int minPosition = 0;
    for(int i = 0; i < n - 1; i++)
    {
        minPosition = i;
        for(int x = i + 1; x < n; x++)
        {
            if(struSelect.fileContents[minPosition] > struSelect.fileContents[x])
            {
                minPosition = x;
            }
        }
        if (minPosition != i)
        {
            holder = struSelect.fileContents[i];
            struSelect.fileContents[i] = struSelect.fileContents[minPosition];
            struSelect.fileContents[minPosition] = holder;
        }     
    }
    print_output(struSelect);
}

void insertion_sort(struct FileBoi struInsert)
{
    int n = struInsert.totalInts;
    int i, holder, x;
    for(i = 1; i < n; i++)
    {
        holder = struInsert.fileContents[i];
        x = i - 1;

        while(x >= 0 && struInsert.fileContents[x] > holder)
        {
            struInsert.fileContents[x + 1] = struInsert.fileContents[x];
            x -= 1;
        }
        struInsert.fileContents[x + 1] = holder;
    }
    print_output(struInsert);
}

void print_output(struct FileBoi struFinal)
{
    for(int i = 0; i < struFinal.totalInts; i++)
    {
        printf("%d ", struFinal.fileContents[i]);
    }
}
