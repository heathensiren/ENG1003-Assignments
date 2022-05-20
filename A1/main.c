/*
* Name: Mirak Bumnanpol
* Course: ENG1003
* Student number: c3320409
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Calling all functions
void railFence(char *message, char *cipherText, int length, int A);
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir);

//Main code which showcases all menu items and runs all functions
int main()
{
    //Creating file pointers for an input(encryption) and output (decryption)
    FILE *fileInput;
    FILE *fileOutput;

    //Max size of message is 8kB long and menu option variable
    int menu;
    char messageOutput[8192];
    char messageInput[8192];

    //Menu options to choose from for encyrption and decrpytion code
    printf("Welcome to the ciphering menu!\n");
    printf("______________________________\n\n");
    printf("Please choose an option:\n\n");
    printf("Enter 1 for Classic Rail Fence Encryption\n");
    printf("Enter 2 for 2-level Rail Fence Encryption\n");
    printf("Enter 3 for 2-level Rail Fence Decryption\n");
    printf("Enter 0 to exit program\n");
    scanf("%d", &menu);

    //Switch statement for ciphering menu page
    switch(menu)
    {
        case 1:
            fileOutput=fopen("encryption.txt","r");                 //Opening the encryption file and only reading from the file  
            railFence(messageInput, messageOutput, 0, 4);           //Calling classic rail fence encryption function and setting paramenters 
            if(fileOutput == NULL)                                  //If there is no encryption file show an error message 
            {
                printf("No input in file please try again");
                exit (0);
            }
            else if (fgets(messageOutput, 8192, fileOutput)!=NULL)  //Else, get the encryption file info and output the string in it 
            {
                printf("%s", messageOutput);
            }
            fclose(fileOutput);                                     //Closing the encryption file 
            break;
        case 2:
            fileOutput=fopen("encryption.txt","r");                 //Opening the encryption file and only reading from the file 
            railFence2(messageInput, messageOutput, 0, 5, 3, 0);    //Calling 2-level encryption function and setting paramenters including the correctly calling the correct switch case 
            if(fileOutput == NULL)                                  //If there is no encryption file show an error message 
            {
                printf("No input in file please try again");
                exit (0);
            }
            else if (fgets(messageOutput, 8192, fileOutput)!=NULL)  //Else, get the encryption file info and output the string in it
            {
                printf("%s",messageOutput);
            }
            fclose(fileOutput);                                     //Closing the encryption file
            break;
        case 3:
            fileInput=fopen("decryption.txt","r");                  //Opening the decryption file and only reading from the file 
            railFence2(messageInput, messageOutput, 0, 5, 3, 1);    //Calling 2-level decryption function and setting paramenters including the correctly calling the correct switch case
            if(fileInput==NULL)                                     //If there is no decryption file show an error message 
            {
                printf("No input in file please try again");
                exit (0);
            }
            else if (fgets(messageInput, 8192, fileInput)!=NULL)    //Else, get the decryption file info and output the string in it
            {
                printf("%s",messageInput);
            }
            fclose(fileInput);                                      //Closing the decryption file
            break;

        default:                                                    //Default switch statement in case user enters wrong number in console
            printf("Please try again");
    }
    return 0;   //Return the main
}

//Rail fence cipher code function
void railFence(char *message, char *cipherText, int length, int A)
{
    //Calling pointers for files here
    FILE *fileOutput;
    FILE *fileInput;

    fileInput = fopen("decryption.txt", "r");   //Opening the decryption file and only reading from the file  
    fgets(message, 8192, fileInput);            //Getting the message from the decryption file setting the max characters to 8KB 
    fclose(fileInput);                          //Close decryption file 
    length = strlen(message);                   //Setting the length to the string length of the string inside the decryption file

    char code[A][8192];                         //Declaring all variables used within the function -> referenced from website given in assignment overview
    int rails, i=0,  j=0, count=0;
    rails = A;

    printf("File has been opened\n");           //Lets user know that file has been opened 

    for(i=0; i<rails; i++)                      //For loop setting the arrays to 0 so that new message input into decryption isnt overwritten
    {
        for(j=0; j<length; j++)
        {
            code[i][j] = 0;
        }
    }

    count = 0;                                  //Reinitialising count and variable j to 0 to start new loop
    j = 0;

    while(j<length)                           
    {
        if(count%2==0)                          //Checks to see if number divisible by 2 
        {
            for(i=0;i<rails;i++)                //Moves down the grid  
            {
                code[i][j]=(int)message[j];     //Moves each letter in the grid to the i and j location 
                j++;                            //Increments j variable across one  
            }
        }

        else
        {
            for(i=rails-2;i>0;i--)              //Moving down the grid by 1 
            {
                code[i][j]=(int)message[j];     //Moves each letter in the grid to the i and j location
                j++;                            //Increments j variable across one 
            }
        }
        count++;                                //Increments count up one
    }

    //Allows the new encrypted message to be written in the encryption file
    fileOutput = fopen("encryption.txt", "w");
    for(i=0;i<rails;i++)
    {
        for(j=0;j<length;j++)
        {
            if(code[i][j]!=0)
            {
                fputc(code[i][j], fileOutput);
            }

        }
    }
    fclose(fileOutput); //Closing encryption file
}

//Rail fence decryption code function
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir)
{
    //Calling file pointers
    FILE *fileOutput;
    FILE *fileInput;

    //Initialising all variables 
    char code[A][8192];
    int rails, rails2, i=0,  j=0, count=0;
    rails = A;
    rails2 = B;
    printf("File has been opened\n");   //Allows user to know that files have been opened

    
    if(A<B)                             //Ensuring that the first rail is larger than or equal to the second rail otherwise code will not run
    {
        printf("ERROR\nInput for the first rail needs to be bigger than the second rail");
        return;
    }

    
    if (B<1)                            //Ensuring that second rail input is later than 1 in order for the code to run
    {   
        printf("ERROR\nInput for second rail is greater than one");
        return;
    }

    //Switch case for 2-level decryption and encryption
    switch(dir)
    {
        //Case 0 for 2-level encryption which is called in the main() switch statement
        case 0: 
            {fileInput=fopen("decryption.txt", "r");//Opening up decrypted message to be read to be encrypted
            fgets(message, 8192, fileInput);        //Getting the message from the decryption file setting the max characters to 8KB
            fclose(fileInput);                      //Closing decrypted file as it has now been read 
            length = strlen(message);               //Setting the length to the string length of the string inside the decryption file

            //Start of encryption coding. This is the same as the classic rail fence but with a second level
            for(i=0; i<rails; i++)                  //For loop setting the arrays to 0 so that new message input into decryption isnt overwritten
            {
                for(j=0; j<length; j++)
                {
                    code[i][j] = 0;
                }
            }

            count = 0;                              //Reinitialising count and variable j to 0 to start new loop
            j = 0;

            while(j<length)
            {
                if(count%4==0)                      //Checks to see if number divisible by 4 is equivalent to 0 
                {
                    for(i=0;i<rails;i++)            //When i is less than the rail, increment up one 
                    {
                        code[i][j]=(int)message[j]; //Moves each letter in the grid to the i and j location
                        j++;                        //Increments j variable across one 
                    }   

                }
                else if(count%4==1)                 //Checks to see if number divisible by 4 is equivalent to 1
                {
                    for(i=rails-2;i<rails2;i--)     //When the second rail is going past their length limit go back up the grid by one 
                    {
                        code[i][j]=(int)message[j]; //Moves each letter in the grid to the i and j location
                        j++;                        //Increments j variable across one 
                    }

                }
                else if(count%4==2)                 //Checks to see if number divisible by 4 is equivalent to 2
                {
                    for(i=rails2-1;i<rails;i++)     //When the second rail is on the bottom row, go back up the grid by one
                    {
                        code[i][j]=(int)message[j]; //Moves each letter in the grid to the i and j location
                        j++;                        //Increments j variable across one 
                    }

                }

                else
                {
                    for(i=rails-2;i>0;i--)          //When the second rail is going past their length limit go back up the grid by one
                    {
                        code[i][j]=(int)message[j]; //Moves each letter in the grid to the i and j location
                        j++;                        //Increments j variable across one 
                    }

                }
                count++;                            //Increments count up one
            }

            //Writing the now encrypted message in the encryption file
            fileOutput=fopen("encryption.txt", "w"); 
            for(i=0;i<rails;i++)
            {
                for(j=0;j<length;j++)
                {
                    if(code[i][j]!=0)
                    {
                        fputc(code[i][j], fileOutput);
                    }
                }
            }
            fclose(fileOutput);
        break;

       case 1:
            fileOutput=fopen("encryption.txt", "r");    //Opening up encrypted message to be read to be decrypted
            fgets(cipherText, 8192, fileOutput);        //Getting the message from the encrypted file setting the max characters to 8KB
            fclose(fileOutput);                         //Close the encrypted file as it has now been read 
            length = strlen(cipherText);                //Setting the length to the string length of the string inside the encryption file

            for(i=0; i<rails; i++)                      //For loop setting the arrays to 0 so that new message input into encryption file isnt overwritten
            {
                for(j=0; j<length; j++)
                {
                    code[i][j] = 0;
                }
            }

            count = 0;                                  //Reinitialising count and variable j to 0 to start new loop
            j = 0;

            while(j<length)
            {
                if(count%4==0)                          //Checks to see if number divisible by 4 is equivalent to 0 
                {
                    for(i=0;i<rails;i++)                //Looking for 1's within the encryption code within the parameters of the for loop in order to replace with corresponding letters 
                    {
                        code[i][j]=1;                   
                        j++;
                    }
                }
                else if(count%4==1)                     //Checks to see if number divisible by 4 is equivalent to 1
                {
                    for(i=rails-2;i<rails2;i--)         //Looking for 1's within the encryption code within the parameters of the for loop in order to replace with corresponding letters 
                    {
                        code[i][j]=1;
                        j++;
                    }
                }
                else if(count%4==2)                      //Checks to see if number divisible by 4 is equivalent to 2 
                {
                    for(i=rails2-1;i<rails;i++)          //Looking for 1's within the encryption code within the parameters of the for loop in order to replace with corresponding letters 
                    {
                        code[i][j]=1;
                        j++;
                    }
                }

                else
                {
                    for(i=rails-2;i>0;i--)              //Looking for 1's within the encryption code within the parameters of the for loop in order to replace with corresponding letters 
                    {
                        code[i][j]=1;
                        j++;
                    }
                }
                count++;                                    //Increment count up one 
            }

            //Opening the encryption file 
            fileOutput=fopen("encryption.txt", "r");
            for(i=0;i<rails;i++)
            {
                for(j=0;j<length;j++)                   //Looking for 1's within the encryption code within the parameters of the for loop  
                {
                    if(code[i][j]==1)
                    {
                        code[i][j]=fgetc(fileOutput);   //If there are 1's within the code, read within the encryption file 
                    }
                }
            }
            fclose(fileOutput); //Closing file after reading

            //Writing the now decrypted message in the decryption file
            fileInput=fopen("decryption.txt", "w");
            for(i=0;i<rails;i++)
            {
                for(j=0;j<length;j++)                   //Looking for 1's within the encryption code within the parameters of the for loop
                {
                    if(code[i][j]!=0)                   //If there are no 1's or if code is not 0 ->
                    {
                        fputc(code[i][j], fileInput);   //Write characters to the decryption file
                    }
                }
            }
            fclose(fileInput);  //Closing file after writing 
        break;
    }
}
}
