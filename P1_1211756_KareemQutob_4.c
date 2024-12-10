#include <stdio.h>
#include <stdlib.h>

typedef struct node *list;
typedef struct LNode *listOfLists; // names to make naming easier
struct node {
    int Data;
    struct node *Next;
    struct node *Prev;
};
struct LNode { // to make a list of list that stores every integer in a linked list
    list content; // every node contain a list;
    struct LNode *Next;
    int neg; // to identify if the num is negative or positive

};

list add(list l1, list l2, int sign1, int sign2);

list subtract(list l1, list l2, int sign1, int sign2);  // declaration of functions
list reverse(list l);

void DeleteList(list L) { // seleting the list
    struct node *P, *temp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL) {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

void DeleteListOfList(listOfLists L) {
    struct LNode *P, *temp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL) {
        temp = P->Next;
        DeleteList(P->content);
        free(P);
        P = temp;
    }
}

listOfLists MakeEmptyListOfList(listOfLists L) {// constructing an empty list of list
    if (L != NULL)
        DeleteListOfList(L);
    L = (struct LNode *) malloc(sizeof(struct LNode));
    if (L == NULL)
        printf("out of memory\n");
    L->Next = NULL;
    L->neg = 0; // default is positive where 1 is negative
    return L;
}

list MakeEmpty(list L) { //from slide my with modification to make it doubly
    if (L != NULL)
        DeleteList(L);
    L = (struct node *) malloc(sizeof(struct node));
    if (L == NULL)
        printf("out of memory\n");
    L->Next = NULL;
    L->Prev = NULL;
    return L;
}

int isEmpty(list l) {
    return l->Next == NULL;
}

int isLast(struct node *p, list l) {
    return p->Next == NULL;
}

struct node *Find(int X, list L) { // finding the node depending in its content
    struct node *P;
    P = L->Next;
    while (P != NULL && P->Data != X)
        P = P->Next;
    return P;
}

void Delete(int X, list L) {
    struct node *P, *temp;
    P = Find(X, L)->Prev;
    if (!isLast(P, L)) {
        temp = P->Next;
        P->Next = temp->Next;
        temp->Next->Prev = P;
        free(temp);
    }
}

void PrintList(list L) {
    struct node *P = L;
    if (isEmpty(L))
        printf("Empty list\n");
    else
        do {
            P = P->Next;
            printf("%d", P->Data);
        } while (!isLast(P, L));
    printf("\n");
}

int size(list L) { // to know how many nodes in the list
    struct node *p = L->Next;
    int count = 0;
    while (p != NULL) {
        count += 1;
        p = p->Next;
    }
    return count;
}

void Insert(int X, list P, list L) {
    struct node *temp;
    temp = (struct node *) malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = P->Next;
    P->Next = temp;
    temp->Prev = P;
    if (temp->Next != NULL)
        temp->Next->Prev = temp;

}

struct node *findLast(list l) { // return teh last node
    struct node *p;
    p = l;
    while (p->Next != NULL)
        p = p->Next;
    return p;
}

void InsertLast(int x, list l) {
    struct node *temp;
    temp = (struct node *) malloc(sizeof(struct node));
    struct node *p = findLast(l);
    temp->Data = x;
    temp->Next = NULL;
    temp->Prev = p;
    p->Next = temp;

}

void insertLOL(list in, int sign, struct LNode *p, listOfLists L) { // for list of list
    struct LNode *temp;
    temp = (struct LNode *) malloc(sizeof(struct LNode));
    temp->content = in;
    temp->Next = p->Next;
    p->Next = temp;
    temp->neg = sign;

}

void insertLastLOL(list in, int sign, listOfLists l) {// for list of list
    struct LNode *p;
    p = l->Next;
    if (p == NULL)
        insertLOL(in, sign, l, l);
    else {
        while (p->Next != NULL)
            p = p->Next;
        insertLOL(in, sign, p, l);
    }

}




int Bigger(list a, list b) {// to find which number is bigger
    int size1 = size(a);
    int size2 = size(b);
    if (size1 > size2) {
        return 1;
    } else if (size1 < size2) {
        return 0;
    }

    if (size1 == size2) {
        struct node *t1, *t2;

        t1 = findLast(a);
        t2 = findLast(b); // to determine which int is smaller
        int small = 0;
        while (t1 != (a)) {
            if (t1->Data < t2->Data) {
                small = 1;
                break;
            }
            t1 = t1->Prev;
            t2 = t2->Prev;
        }
        if (small)
            return 0;
        else return 1;
    }
}


list add(list l1, list l2, int sign1,
         int sign2) {  // to add we need two list containing digits and there sign to know which case we will do

    list res = MakeEmpty(NULL); // to save the res in it
    struct node *p1, *p2;
    p1 = l1->Next;
    p2 = l2->Next;
    int hand = 0;  // flag to know if there are a one in hand

    if (sign1 == 1 && sign2 == 0) { // in these 2 cases we will need to subtract instead of adding
        return subtract(l2, l1, 0, 0);
    } else if (sign1 == 0 && sign2 == 1) {
        return subtract(l1, l2, 0, 0);
    } else {
        while (p1 != NULL && p2 != NULL) {
            Insert((((p1->Data + p2->Data) + hand) % 10), res, res); // inserting the sum of parellal node with carry
            if ((p1->Data + p2->Data + hand) > 9) {
                hand = 1;
            } else hand = 0;
            p1 = p1->Next;
            p2 = p2->Next;

        }
        if (p1 !=
            NULL) { // in case a number have more digit than the others thr remsaining digits well be inserted without any changes

            Insert((p1->Data + hand) % 10, res, res);

            if ((p1->Data + hand) > 9)
                hand = 1;
            else hand = 0;
            p1 = p1->Next;

            while (p1 != NULL) {

                Insert((p1->Data + hand) % 10, res, res);
                if (p1->Data == 9 && hand == 1)
                    hand = 1;
                else hand = 0;
                p1 = p1->Next;

            }
        } else if (p2 != NULL) { // vice versa when the second digits are more
            Insert((p2->Data + hand) % 10, res, res);
            if (p2->Data + hand > 9)
                hand = 1;
            else hand = 0;
            p2 = p2->Next;

            while (p2 != NULL) {

                Insert((p2->Data + hand) % 10, res, res);
                if (p2->Data + hand > 9)
                    hand = 1;
                else hand = 0;
                p2 = p2->Next;

            }
        }
        if (hand)
            Insert(1, res, res); // when there is hand we insert a one at the end

        if (sign1 == 1 && sign2 == 1) {// if the two number are negative we add normaly we turn it negative
            (res->Next->Data) *= -1;
        }
    }
    return res;
}

int equal(list a, list b) {
    int size1 = size(a);
    int size2 = size(b);// this function to find if 2 list equall each other
    if (size2 > size1) {
        return 0;
    } else if (size2<size1){
        return 0;
    }
    else { // if same number of digits it will compare every parallel int
        struct node *p1 = a->Next;
        struct node *p2 = b->Next;
        int flag = 0;
        while (p1 != NULL && p2 != NULL) {
            if (p1->Data != p2->Data) {
                flag = 1;
                break;
            }
            p1 = p1->Next;
            p2 = p2->Next;
        }
        if (flag)
            return 0;
        else return 1;
    }
}

list subtract(list l1, list l2, int sign1, int sign2) {
    struct node *p1, *p2, *temp;
    p1 = l1->Next;
    p2 = l2->Next;
    list res = MakeEmpty(NULL); // to store the resault
    int neg = 0;
    int hand = 0;
    int size1 = size(l1);
    int size2 = size(l2);
    if (equal(l1, l2) && sign1 == 0 && sign2 == 0) {
        printf("fghjk");
        Insert(0, res, res);
        return res;
    }
    if (sign1 == 1 && sign2 == 1) {
        return subtract(l2, l1, 0, 0);
    } else if (sign1 == 0 && sign2 == 1) { // cases when adding is needed instead of subtracting
        return add(l1, l2, 0, 0);
    } else if (sign1 == 1 && sign2 == 0) {
        return add(l1, l2, 1, 1);
    }

    if (size1 <
        size2) { // to determine which int is bigger than the other to know what order we need to subtract and the sign of the answer
        p2 = l1->Next;
        p1 = l2->Next;
        neg = 1;
    } else if (size1 == size2) {
        struct node *t1, *t2;
        t1 = findLast(l1);
        t2 = findLast(l2); // to determine which int is smaller
        int small = 0;
        while (t1 != (l1)) {
            if (t1->Data < t2->Data) {
                small = 1;
                break;
            }
            t1 = t1->Prev;
            t2 = t2->Prev;
        }
        if (small) {
            p2 = l1->Next;
            p1 = l2->Next;
            neg = 1;
        }
    }

    while (p1 != NULL && p2 != NULL) {
        if ((p1->Data - hand) < p2->Data) {
            Insert((p1->Data + 10) - p2->Data - hand, res, res); // subtracting parallel nodes and carry
            hand = 1;
        } else {
            Insert(p1->Data - p2->Data - hand, res, res);
            hand = 0;

        }
        p1 = p1->Next;
        p2 = p2->Next;
    }
    while (p1 != NULL) { // in case there are digit with parellal nodes
        if (p1->Data == 0) {
            Insert((p1->Data + 10) - hand, res, res);
            hand = 1;
        } else {
            Insert(p1->Data - hand, res, res);
            hand = 0;
        }
        p1 = p1->Next;

    }
    struct node *z = res->Next; /// to remove extra zeros
    while (z->Data == 0 ) {
        z = z->Next;
        Delete(0, res);
    }
    if (neg) {
        res->Next->Data *= -1;
    }

    return res;
}



list reverse(list l) { // thsi function do reverser by cobying every node in reverse in a new list
    list temp = MakeEmpty(NULL);
    struct node *p = l->Next;
    while (p != NULL) {
        Insert(p->Data, temp, temp);
        p = p->Next;
    }
    // =temp;
    return temp;

}



list mul(list l1, list l2, int sign1, int sign2) {
    list res = MakeEmpty(NULL);// // to store resault
    struct node *p1, *p2;
    p2 = l2->Next;
    int neg = sign1 + sign2;
    if (size(l2) > size(l1))
        return mul(l2, l1, sign2, sign1); // to reduce code
    int counter = 0;
    list num1 = res;
    list num2 = MakeEmpty(NULL);
    int hand;
    while (p2 != NULL) { //
        struct node *tempP = l1->Next; // to take one digit at a time

        num2 = MakeEmpty(NULL);
        hand = 0;
        for (int i = 0; i < counter; ++i) {
            Insert(0, num2, num2); // to ad zero in the number when ever we take another digit from higher level
        }
        while (tempP != NULL) {
            if (tempP->Next == NULL) {
                Insert((p2->Data * tempP->Data + hand) % 10, num2, num2); // inserting multiplication
                hand = ((tempP->Data * p2->Data + hand) / 10) % 10;
                Insert(hand, num2, num2);
                tempP = tempP->Next;
            } else {
                Insert((p2->Data * tempP->Data + hand) % 10, num2, num2);
                hand = ((tempP->Data * p2->Data + hand) / 10) % 10;
                tempP = tempP->Next;
            }
        }
        if (!isEmpty(num1)) {
            num1 = reverse(num1);
            num2 = reverse(num2);// because i store my numbers in reverse
            num1 = add(num2, num1, 0, 0);// ading the values of multiplacations

        } else {
            num1 = num2;
        }

        counter++;
        p2 = p2->Next;
    }
    res = num1;
    struct node *z = res->Next;
    while (z->Data == 0 && z->Next != NULL) { // delete extra zeros
        z = z->Next;
        Delete(0, res);
    }
    if (neg == 1)// in negative cases
        res->Next->Data *= -1;
    return res;
}


list division(list l1, list l2, int sign1, int sign2) {
    list res = MakeEmpty(NULL);//to store output
    struct node *p1, *p2;
    p1 = l1;
    p2 = reverse(l2);
    int neg = sign1 + sign2;// to determine size
    int size1 = size(l1);
    int size2 = size(l2);
    if (l2->Next->Data == 0) {
        printf("Error divide by zero");
    } else if (Bigger(l1, l2) == 0) {
        Insert(0, res, res);
        //when number is bigger than the other

    }

    else {

        p1 = reverse(p1);
        int counter = 0;
        list flow = MakeEmpty(NULL);// to take number after number from the most significent
        list op = MakeEmpty(NULL);
        p1 = p1->Next;
        while (p1 != NULL) {

            InsertLast(p1->Data, flow);
            if(flow->Next==0){
                InsertLast(0, res);
                p1=p1->Next;
                continue;

            }
            if (Bigger(flow, p2)) {// thos loop will determine the anser for small division from the long division

                list num = flow;
                counter = 0;

                while (Bigger(num, p2)) {
                    printf("6");
                    PrintList(num);
                    list temp = reverse(num);
                    num = subtract(temp, l2, 0, 0);
                    PrintList(num);
                    printf("hi");
                    counter++;// it will keep subtractiong untill it become less than the othe number
                }

                list count = MakeEmpty(NULL);
                Insert(counter, count, count);// to store answer he will be
                PrintList(count);
                InsertLast(counter, res); //
                PrintList(res);

                op = mul(count, l2, 0, 0);// to multiply like long division
                PrintList(op);
                list temp1 = reverse(op);
                list temp2 = reverse(flow);
                flow = subtract(temp2, temp1, 0, 0);
                PrintList(flow);
                if (size(flow) == 1 && flow->Next->Data == 0 )// if zero iw will delete it
                    flow = MakeEmpty(NULL);
            }
            p1 = p1->Next;
        }
    }

    if (neg == 1) {
        res->Next->Data *= -1;
    }
    return res;
}

listOfLists readFile() {  /*this  will read integers from the file and take every integers and store it in a linked list
 * every node will represent a digit from the integers and the list of integers will be stored in a linked list that stores lists*/

    listOfLists Integers = MakeEmptyListOfList(NULL); // creating an empty list of list
    FILE *fp = fopen("in_1211756_KareemQutob_4.txt", "r"); // opening input file
    int x;
    int neg = 0; // a flag int to determine if number is negative or not
    list temp = MakeEmpty(NULL); // empty list
    while ((x = fgetc(fp)) != EOF) { // we will take digit char after char  until end of line

        if (x == ' ' || x == '\n') {   // we will enter the list of digit everytime we encounter a space
            if (!isEmpty(temp)) {   // because we want to be sure we dont add empty  lists

                insertLastLOL(temp, neg, Integers);
                temp = MakeEmpty(NULL); // emptying it to read another integers
                neg = 0;
            }

        } else if (x == 45) { // to check if the char is the minus sign
            neg = 1;
        } else {
            int digit = x - '0';  // converting char to int

            Insert(digit, temp, temp); // inserting digit
        }
    }

    insertLastLOL(temp, neg, Integers);

    fclose(fp);
    return Integers;
}



void viewNums(listOfLists l) {// to print numbers the main
    int counter = 1;
    listOfLists p = l->Next;

    while (p != NULL) {
        printf("%d)", counter);// numbering them
        if (p->neg) //
            printf("-");
        PrintList(reverse(p->content));
        reverse(p->content);
        counter++;
        p = p->Next;

    }
}

list findInteger(int num, listOfLists l) { // to find the list that contain the integer depending in its number in tghe list
    int counter = 0;
    listOfLists p = l->Next;
    while (p != NULL) {
        counter++;
        if (counter == num)
            return p->content;
        p = p->Next;
    }
    return NULL;
}

int findSign(int num, listOfLists l) {// same but to find the sign of the digit
    int counter = 0;
    listOfLists p = l->Next;
    while (p != NULL) {
        counter++;
        if (counter == num)
            return p->neg;
        p = p->Next;
    }
    return -1;

}
void writeInFile(listOfLists l) {// writing the output int the file
    if (l->Next == NULL) {
        printf("do some op first\n");
    } else {
        struct LNode *p1 = l->Next;
        FILE *fp = fopen("out_1211756_KareemQutob_4.txt", "w"); // opening input file

        while (p1 != NULL) {
            struct node *P=p1->content;
            do {
                P = P->Next;
                fprintf(fp,"%d", P->Data); // printing any node
            } while (!isLast(P, p1->content));
            fprintf(fp,"");
            fprintf(fp,"\n");
            p1 = p1->Next;
        }
        fclose(fp);
    }
}

int main() {
    int choose = 0;
    listOfLists read;
    read = readFile();
    listOfLists out = MakeEmptyListOfList(NULL);// to save teh reasults

    printf("welcome to the big Integer calculator\n");
    while (choose != -1) { // to start the list if -1 is chosen ypu will exit
        printf("\nto read the input file and print it select 1\n");
        printf("to add select 2 \n");
        printf("to subtract select 3 \n");
        printf("to multiply select 4 \n");
        printf("to divide  select 5 \n");
        printf("to print in output file select 6\n");
        printf("to exit press -1\n");
        scanf("%d", &choose);
        if (choose == 1) {
            read = readFile();
            viewNums(read);
        } else if (choose == 2) {
            printf("select first numbers by order\n");
            viewNums(read);
            int num1, num2;
            scanf("%d", &num1);
            printf("select second numbers by order\n");
            scanf("%d", &num2);
            list n1 = findInteger(num1, read);
            list n2 = findInteger(num2, read);// to find the list the user requested
            list res = add(n1, n2, findSign(num1, read), findSign(num2, read));
            int sign = 0;
            if (res->Next->Data < 0)
                sign = 1;
            insertLastLOL(res, sign, out);
            PrintList(res);
            printf("\n");

        } else if (choose == 3) {
            printf("select first numbers by order\n");
            viewNums(read);
            int num1, num2;
            scanf("%d", &num1);
            printf("select second numbers by order\n");
            scanf("%d", &num2);
            list n1 = findInteger(num1, read);
            list n2 = findInteger(num2, read);
            list res = subtract(n1, n2, findSign(num1, read), findSign(num2, read));
            int sign = 0;
            if (res->Next->Data < 0)
                sign = 1;
            insertLastLOL(res, sign, out);
            PrintList(res);
            printf("\n");
        } else if (choose == 4) {
            printf("select first numbers by order\n");
            viewNums(read);
            int num1, num2;
            scanf("%d", &num1);
            printf("select second numbers by order\n");
            scanf("%d", &num2);
            list n1 = findInteger(num1, read);
            list n2 = findInteger(num2, read);
            list res = mul(n1, n2, findSign(num1, read), findSign(num2, read));
            int sign = 0;
            if (res->Next->Data < 0)
                sign = 1;
            insertLastLOL(res, sign, out);
            PrintList(res);
            printf("\n");
        } else if (choose == 5) {
            printf("select first numbers by order\n");
            viewNums(read);
            int num1, num2;
            scanf("%d", &num1);
            printf("select second numbers by order\n");
            scanf("%d", &num2);
            list n1 = findInteger(num1, read);
            list n2 = findInteger(num2, read);
            list res = division(n1, n2, findSign(num1, read), findSign(num2, read));
            int sign = 0;
            if (res->Next->Data < 0)
                sign = 1;
            insertLastLOL(res, sign, out);
            PrintList(res);
            printf("\n");
        } else if (choose == 6) {
            writeInFile(out);
            printf("file updated\n");
        }


    }
    exit(0);// exiting the program

    return 0;
}
