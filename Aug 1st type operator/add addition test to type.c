#include <stdio.h>


void test1 (int arr[]){
    printf("test1 %d \n", sizeof(arr));
}



void test2 (char ch[]){
    printf("test2 %d \n", sizeof(ch));
}

void test3(){
    int i = 0, a = 0, b = 2, c = 3, d = 4;
    i = a++ && ++b && d++;
    printf("a = %d \nb = %d \nc = %d \nd = %d \n", a, b, c, d);
    //result is a = 1 b = 2 c = 3 d = d
    printf("i is %d\n", i);
    //i is 0
    //explanation
    //if statement1 && statement2, the statement1 is false, then the rest will not be counted or calculated
    //which means all the rest will stop processing

    //if i = 0, a = 1, b = 2, c = 3, d = 4;
    //result will be 2 3 3 5 since a = 1 means true


    i = 0, a = 1, b = 2, c = 3, d = 4;
    i = a++ || ++b || d++;
    //here a is 1 -> true
    //so what rest is not important
    //cuz 1 || everything will result 1
    //so only a++ is processed

    printf("a = %d \nb = %d \nc = %d \nd = %d \n", a, b, c, d);
    //result is a = 2 b = 2 c = 3 d = 4
    printf("i is %d\n", i);
    //i is 1

}

void test4(){

    int i = 0, a = 0, b = 2, c = 3, d = 4;
    i = a++ || ++b || d++;
    printf("a = %d \nb = %d \nc = %d \nd = %d \n", a, b, c, d);
    //result is a = 1 b = 3 c = 3 d = 4
    printf("i is %d\n", i);
    //here a is false
    //b is true
    //so it will process till b and stop

}



int main() {


    int arr[10] = {0};
    char ch[10] = {0};
    printf("sizeof(arr) is %d \n", sizeof(arr)); // 4 * 10 = 40
    printf("sizeof(ch) is %d \n", sizeof(ch)); // 1 * 10 = 10

    test1(arr);
    test2(ch);


    printf("\n");
    int a = 0;
    int b = 5;
    int c = a && b;
    int d = a || b;
    printf("c = %d\n",c);
    printf("d = %d\n",d);


    printf("\n");
    test3();
    printf("\n");
    test4();
    return 0;
}
