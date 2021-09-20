#include <stdio.h>
#include <string.h>
#include <assert.h>

int validate(char* arr){
    assert(arr); //test if arr is NULL
    int len = strlen(arr); 
    //eg : 0-89237-010-6 -> size 13

    //calculater the sum
    int sum1 = 0; 
    int sum2 = 0;

    for(int j = 0; j < len; j++){
        //'1'  != int 1
        //88 in ASCII represent character 'X'
        //conver from char to int

        int a = *arr - '0';
        //j = 0
        //'0' - '0' -> 48 - 48 -> ascii 0 -> 0 
        //'-' - '0' -> 45 - 48 -> ascii -3
        if((a != -3) && (*arr != 88)){
            sum1 += a;
            sum2 += sum1;
        }
        else if((*arr) == 88){
            //88 in ASCII represent character 'X'
            sum1 += 10;
            sum2 += sum1;
        }
        arr++;
        //move from '0' to next char
    }
    //test if we find a valid sum2
    if(sum2 % 11 == 0) {
         return 1;
    }
    else {
        return 0;
    }
}


int main () {
    char arr[80];
    //create an array of 80
    FILE *fp;
    fp = fopen("ISBN.dat", "r");

    while (feof(fp) != EOF) 
    //end of file
    {
        fgets(arr, 80, fp);
        int len = strlen(arr);
        arr[len-2] = '\0';
        //put a \0 to avoid unexpected errors

        //if we meet "Done!" then end the program
        if(strcmp("Done!", arr) == 0)
            break;
        if(validate(arr)) {
            printf("%s is valid\n", arr);
        }
        else
            printf("%s is invalid\n", arr);
    }
    /*while(scanf(" %[^\n]s", &arr) != EOF){   // step 1 read input
        int result = convertToNumber(arr);   //judge if it's a valid isbn number
        if(result == 1){
            printf("%s is valid\n", arr);
            memset(arr, 0, sizeof arr);//reset arr[80] to null
        }
        else {
            printf("%s is invalid\n", arr);
            memset(arr, 0, sizeof arr);//reset arr[80] to null
        }
    }*/
    return 0;
}