/*

||-------------------------------||
||      Mohiul Islam Miraz       ||
||-------------------------------||

*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include <errno.h>

char user;
struct details
{
    int bus_number;
    char route[200];
    char busdriver[100];
    char drivercontact[11];
    char seat[32][14];
    char departure_time[10];
};
void login(void);
void login_user(void);
void bus(void);
void record(void);
void update_pass(void);
void delete_record(void);
void reservation(void);
void reservation_admin(void);
void cancel(void);
void exit_program(void);
void admin(void);
void student(void);

int main()
{
    system("color F8");
    printf("\n\t\t\t\t\t\t\t\tWELCOME TO TRANSTECH\n\n\t\t\t\t\t\t\tIIUC DIGITAL TRANSPORTATION SYSTEM\n");
    printf("\n\n\n\n   Press 'A' for accessing admin options and 'S' for accessing students options : ");
    scanf(" %c", &user);
    system("cls");

    switch(user)
    {
    case 'a':
    case 'A':
        login();
        system("cls");
        admin();
        break;
    case 's':
    case 'S':
        login_user();
        system("cls");
        student();
        break;
    default:
        printf("Wrong option...\n");
    }
    return 0;
}
void admin()
{
    int choice;
    do
    {
        printf("\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n");
        printf("\n\t\t[1] Install new bus\n");
        printf("\n\t\t[2] Bus Details\n");
        printf("\n\t\t[3] Seat Details\n");
        printf("\n\t\t[4] Cancel Reservation\n");
        printf("\n\t\t[5] Delete Bus Record\n");
        printf("\n\t\t[6] Update password\n");
        printf("\n\t\t[7] Exit ");
        printf("\n\n\t\t");
        printf("\n\t\tYour choice: ");
        scanf("%d", &choice);
        system("cls");

        switch(choice)
        {
        case 1:
            bus();
            break;
        case 2:
            record();
            break;
        case 3:
            reservation_admin();
            break;
        case 4:
            cancel();
            break;
        case 5:
            delete_record();
            break;
        case 6:
            update_pass();
            break;
        case 7:
            exit_program();
        default:
            printf("Wrong option");
        }
    }
    while(choice!=5);
}
void student()
{
    int choice;
    do
    {
        printf("\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n");
        printf("\n\t\t[1] View Bus Details\n");
        printf("\n\t\t[2] View Seats\n");
        printf("\n\t\t[3] Seat Reservation\n");
        printf("\n\t\t[4] Exit ");
        printf("\n\n\t\t");
        printf("\n\t\tYour choice: ");
        scanf("%d", &choice);
        system("cls");

        switch(choice)
        {
        case 1:
            record();
            break;
        case 2:
            reservation_admin();
            break;
        case 3:
            reservation();
            break;
        case 4:
            exit_program();
            break;
        default:
            printf("Wrong option");

        }
    }
    while(choice!=4);
}
int count=0;
void login()
{
    system("cls");
    printf("\n\t\t\t-------ADMIN LOGIN FORM-------");

    char array[3][20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c;
    int result_name, result_pass, option;

    FILE*fptr;

    printf("\n\n\t\t\tSelect a number:\n");
    printf("\n\t\t\t 1. Register\n");
    printf("\n\t\t\t 2. Sign in\n");
    printf("\n\t\t\tYour choice: ");
    scanf("%d", &option);

    if(option==1)
    {
        fptr=fopen("Signin_details.txt", "r+");
        if(fptr!=NULL && (ch=getc(fptr))!=EOF)
        {
            printf("\n\t\t\tA user already exists. Please sign in to the system with your email.\n");
            printf("\n\t\t\tPress any key to continue ... ");
            getch();
            fclose(fptr);
            login();
        }

        else
        {
            fptr=fopen("Signin_details.txt", "w+");
            printf("\n\t\t\tUsername: ");
            fflush(stdin);
            gets(user);
            printf("\t\t\tPassword: ");
            fflush(stdin);

            int i=0;
            while(i<20)
            {
                pass[i]=getch();
                c=pass[i];
                if(c==13) break;
                else printf("*");
                i++;
            }
            pass[i]='\0';

            printf("\n\n\t\t\tYou have successfully registered!");
            fprintf(fptr, "%s\n%s\n", user, pass);
            fclose(fptr);

            printf("\n\t\t\tPress any key to continue ... ");
            getch();
            bus();
        }
    }
    if(option==2)
    {
        fptr=fopen("Signin_details.txt", "r+");
        if((ch=getc(fptr))==EOF)
        {
            printf("\n\t\t\tPlease register yourself first\n");
            printf("\n\t\t\tPress any key to continue...");
            getch();
            login();
        }
        else
        {
            printf("\n\t\t\tUsername: ");
            fflush(stdin);
            gets(sign_name);
            printf("\n\t\t\tPassword: ");
            fflush(stdin);
            int a=0;
            while(a<20)
            {
                sign_pass[a]=getch();
                c=sign_pass[a];
                if(c==13) break;
                else printf("*");
                a++;
            }
            sign_pass[a]='\0';
            int i=0;
            rewind(fptr);
            while(!feof(fptr))
            {
                fgets(array[i], sizeof(array[i]), fptr);
                i++;
            }
            strcat(sign_name, "\n");
            strcat(sign_pass, "\n");
            result_name=strcmp(array[0], sign_name);
            result_pass=strcmp(array[1], sign_pass);
            if(result_pass!=0 || result_name!=0)
            {
                count++;
                if(count==3)
                {
                    printf("\n\t\t\t3 wrong attempts on credentials.");
                    exit(0);
                }
                printf("\n\t\t\tWrong attempts on credentials.");
                getch();
                login();
            }

            else if(result_name==0 && result_pass==0)
            {
                printf("\n\n\t\t\tWelcome %s\n\t\t\tPress any key to continue ...", array[0]);
                getch();
            }
        }
    }
    fclose(fptr);
}

void login_user()
{
    system("cls");
    printf("\n\t\t\t-------STUDENTS & TEACHERS LOGIN FORM-------");

    char array[3][20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c;
    int result_name, result_pass, option;

    FILE*fptru;

    printf("\n\n\t\t\tSelect a number:\n");
    printf("\n\t\t\t 1. Register\n");
    printf("\n\t\t\t 2. Sign in\n");
    printf("\n\t\t\tYour choice: ");
    scanf("%d", &option);

    if(option==1)
    {
        fptru=fopen("Signin_details_user.txt", "a+");

        fptru=fopen("Signin_details_user.txt", "a+");
        printf("\n\t\t\tEmail: ");
        fflush(stdin);
        gets(user);
        printf("\t\t\tPassword: ");
        fflush(stdin);


        int i=0;
        while(i<20)
        {
            pass[i]=getch();
            c=pass[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pass[i]='\0';

        printf("\n\n\t\t\tYou have successfully registered!");
        fprintf(fptru, "%s %s\n", user, pass);
        fclose(fptru);

        printf("\n\t\t\tPress any key to continue ... ");
        getch();
    }
    if(option==2)
    {
        fptru=fopen("Signin_details_user.txt", "r");
        if((ch=getc(fptru))==EOF)
        {
            printf("\n\t\t\tPlease register yourself first\n");
            printf("\n\t\t\tPress any key to continue...");
            getch();
            login_user();
        }
        else
        {
            printf("\n\t\t\tEmail: ");
            fflush(stdin);
            gets(sign_name);
            printf("\n\t\t\tPassword: ");
            fflush(stdin);
            int a=0;
            while(a<20)
            {
                sign_pass[a]=getch();
                c=sign_pass[a];
                if(c==13) break;
                else printf("*");
                a++;
            }
            sign_pass[a]='\0';
            int i=0;
            rewind(fptru);
            while (!feof(fptru))
            {
                fscanf(fptru, "%s %s\n", array[0], array[1]);
                if (strcmp(array[0], sign_name) == 0 && strcmp(array[1], sign_pass) == 0)
                {
                    printf("\n\n\t\t\tWelcome %s\n\t\t\tPress any key to continue ...\n", sign_name);
                    getch();
                }
            }
        }
    }
    fclose(fptru);
}

void bus(void)
{
    system("cls");
    FILE *bptr;
    int no;
    printf("Enter the number of buses: ");
    scanf("%d", &no);
    struct details array[no];
    int busno;
    FILE* fptr[no];
    FILE* ptr[no];
    char buffer[11];
    char bus[99999][6];
    long int exist[99999];
    char string3[11];

    for(int i=0; i<no; i++)
    {
        printf("Enter the bus number: ");
        scanf("%d", &busno);
        sprintf(string3, "%d_num.txt", busno);
        ptr[i]=fopen(string3, "w+");
        fprintf(ptr[i], "32");
        fclose(ptr[i]);
        bptr=fopen("buses.txt", "a+");

        for(int j=0; j<i; j++)
        {
            if(busno==array[j].bus_number)
            {
                while(busno==array[j].bus_number)
                {
                    printf("Bus data already exists. Enter another point number: ");
                    scanf("%d", &busno);
                }
                break;
            }
        }

        fseek(bptr, 0, SEEK_SET);
        int p=0, q=0;
        while(!feof(bptr))
        {
            bus[p][q]=fgetc(bptr);
            if(bus[p][q]==' ')
            {
                bus[p][q]='\0';
                p++;
                q=0;
            }
            else q++;
        }


        int r=p;
        for(int s=0; s<r; s++)
        {
            exist[s]=atoi(bus[s]);
        }

        int count=0, s=0;
        for(; ;)
        {
            for(s=0; s<r; s++)
            {
                if(busno==exist[s])
                {
                    count++;
                    while(busno==exist[s])
                    {
                        printf("Bus data already exists. Enter another bus number: ");
                        scanf("%d", &busno);
                    }
                }
            }
            if(count==0)
            {
                break;
            }
            else
            {
                s=0;
                count=0;
            }
        }
        fprintf(bptr, "%d ", busno);
        fclose(bptr);

        array[i].bus_number=busno;
        sprintf(buffer, "%d.txt", busno);
        fptr[i]=fopen(buffer, "w+");
        printf("Enter departure time: ");
        fflush(stdin);
        gets(array[i].departure_time);
        printf("Enter bus driver's contact: ");
        scanf("%s", array[i].drivercontact);
        printf("Enter route of the bus: ");
        fflush(stdin);
        gets(array[i].route);

        fprintf(fptr[i],"Bus number: %d\t\tDriver's contact number: %s\t\tDeparture time: %s\t\tRoute: %s\n", busno, array[i].drivercontact, array[i].departure_time, array[i].route);


        for(int n=0; n<32; n++)
        {
            char s2[6]="Empty";
            strcpy(array[i].seat[n], s2);
        }

        int l=0;
        for(int j=0; j<8; j++)
        {
            for(int k=0; k<4; k++)
            {
                fprintf(fptr[i], "%2d. %-25s", ++l, array[i].seat[l]);
            }
            fprintf(fptr[i], "\n");
        }

        fclose(fptr[i]);
    }

    printf("Press any key to continue ... ");
    getch();
    system("cls");
}

void reservation()
{
    int seats[32];
    FILE*fptr;
    FILE* fptr2;
    FILE*temporary;
    FILE* ptr;
    FILE*ptr2;
    char line[200], line1[200], line2[3], buffer[11];;
    int num, no_seats;
    int seat_num;
    char new_name[20], file[13], file2[13];
    char number[32][3], name[32][20], string[3], string3[11];

    printf("Choose the bus number: ");
    scanf("%d", &num);
    system("cls");

    sprintf(string3, "%d_num.txt", num);

    fptr2=fopen(string3, "r+");
    fgets(line2, 3, fptr2);
    no_seats=atoi(line2);
    fclose(fptr2);


    if(no_seats==0)
    {
        printf("No seats available\n");
    }
    else if(no_seats==32)
    {
        char temp[33][20]= {"Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty"};

        printf("Available seats: %d\n", no_seats);
        fptr2=fopen(string3, "w+");
        no_seats-=1;
        fprintf(fptr2, "%d", no_seats);
        fclose(fptr2);

        sprintf(buffer, "%d.txt", num);
        fptr= fopen(buffer, "r+");

        for(int i=1; i<=9; i++)
        {
            fgets(line1, sizeof(line1), fptr);
            if(i>=2)
            {
                printf("%s\n", line1);
            }
        }
        fclose(fptr);
        printf("Please enter the seat number: ");
        scanf("%d", &seat_num);

        if(seat_num>32)
        {
            admin();
        }

        else
        {
            printf("Please enter id: ");
            fflush(stdin);
            gets(new_name);

            sprintf(file, "%d_booked.txt", num);
            sprintf(file2, "%d_names.txt", num);
            ptr=fopen(file,"a+");
            ptr2=fopen(file2, "a+");
            if (ptr2 == NULL)
            {
                printf("Could not Access File.");
            }

            fprintf(ptr, "%d\n", seat_num);
            fprintf(ptr2, "%s\n", new_name);
            fclose(ptr);
            fclose(ptr2);

            strcpy(temp[seat_num], new_name);

            fptr= fopen(buffer, "r+");
            rewind(fptr);
            temporary=fopen("temp.txt", "a+");
            fgets(line, 200, fptr);
            fprintf(temporary, "%s", line);

            int l=1;
            for(int j=0; j<8; j++)
            {
                for(int k=0; k<4; k++)
                {
                    fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
                    l++;
                }
                fprintf(temporary, "\n");
            }
            fclose(fptr);
            fclose(temporary);
            remove(buffer);
            rename("temp.txt", buffer);

            printf("\n\n\n\t\tSeat reserved!");
        }
    }

    else
    {
        char temp[33][20]= {'\0'};
        printf("Available seats: %d\n", no_seats);

        sprintf(buffer, "%d.txt", num);
        fptr= fopen(buffer, "r+");
        for(int i=1; i<=9; i++)
        {
            fgets(line1, sizeof(line1), fptr);
            if(i>=2)
            {
                printf("%s\n", line1);
            }
        }
        fclose(fptr);
        printf("Please enter the seat number: ");
        scanf("%d", &seat_num);

        if(seat_num>32)
        {
            admin();
        }

        else
        {
            printf("Please enter id: ");
            fflush(stdin);
            gets(new_name);

            sprintf(file, "%d_booked.txt", num);
            sprintf(file2, "%d_names.txt", num);
            ptr=fopen(file,"a+");
            ptr2=fopen(file2, "a+");


            int i=0, j=0;
            while(!feof(ptr2))
            {
                name[i][j]=fgetc(ptr2);
                if(name[i][j]=='\n')
                {
                    name[i][j]='\0';
                    i++;
                    j=0;
                }
                else j++;
            }

            i=0, j=0;
            while(!feof(ptr))
            {
                number[i][j]=fgetc(ptr);
                if(number[i][j]=='\n')
                {
                    number[i][j]='\0';
                    i++;
                    j=0;
                }
                else j++;
            }

            int m=i;

            for(int i=0; i<m; i++)
            {
                seats[i]=atoi(number[i]);
            }

            for(int i=0; i<m; i++)
            {
                if(seat_num==seats[i])
                {
                    while(seat_num==seats[i])
                    {
                        printf("Seat booked. Enter another seat number: \n");
                        scanf("%d", &seat_num);
                    }
                }
            }

            fprintf(ptr, "%d\n", seat_num);
            fprintf(ptr2, "%s\n", new_name);
            fclose(ptr);
            fclose(ptr2);

            fptr2=fopen(string3, "w+");
            no_seats-=1;
            fprintf(fptr2, "%d", no_seats);
            fclose(fptr2);

            ptr=fopen(file,"r+");
            ptr2=fopen(file2, "r+");


            i=0, j=0;
            while(!feof(ptr2))
            {
                name[i][j]=fgetc(ptr2);
                if(name[i][j]=='\n')
                {
                    name[i][j]='\0';
                    i++;
                    j=0;
                }
                else j++;
            }

            i=0, j=0;
            while(!feof(ptr))
            {
                number[i][j]=fgetc(ptr);
                if(number[i][j]=='\n')
                {
                    number[i][j]='\0';
                    i++;
                    j=0;
                }
                else j++;
            }

            fclose(ptr);
            fclose(ptr2);

            m=i;

            for(int i=0; i<m; i++)
            {
                seats[i]=atoi(number[i]);
            }


            for(int n=1; n<=32; n++)
            {
                for(int o=0; o<m; o++)
                {
                    if(n==seats[o])
                    {
                        strcpy(temp[n], name[o]);
                        break;
                    }
                    else strcpy(temp[n], "Empty");
                }
            }
            fptr= fopen(buffer, "r+");
            temporary=fopen("temp.txt", "a+");
            fgets(line, 200, fptr);
            fprintf(temporary, "%s", line);

            int l=1;
            for(int j=0; j<8; j++)
            {
                for(int k=0; k<4; k++)
                {
                    fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
                    l++;
                }
                fprintf(temporary, "\n");
            }
            fclose(fptr);
            fclose(temporary);
            remove(buffer);
            rename("temp.txt", buffer);
            printf("\n\n\n\t\tSeat reserved!");
        }
    }
    printf("\n\n\n\t\tPlease enter any key to continue...");
    getch();
}

void reservation_admin()
{
    int num;

    printf("Enter the bus number: ");
    scanf("%d", &num);

    char buffer[11];
    sprintf(buffer, "%d.txt", num);

    FILE *fptr = fopen(buffer, "r");
    if (fptr == NULL)
    {
        printf("Error accessing seat data.\n");
        return;
    }

    char line[200];


    int seat_num = 1;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        printf("\n%s", line);
        seat_num++;
    }
    fclose(fptr);

    printf("\n\nPress any key to continue...");
    getch();
    system("cls");
}
void cancel()
{
    system("cls");
    char temp[33][20]= {'\0'};
    int seats[32];
    FILE *pass;
    FILE*bptr;
    FILE* fptr1;
    FILE* fptr2;
    FILE* fptr3;
    FILE*temporary;
    FILE* ptr;
    FILE*ptr2;
    FILE *un;
    char line[200], line1[200], line3[3], buffer[11], user_id[20];
    int seat_num, num, no_seats;
    char file[13], file2[13], file3[13];
    char user_name[20], pass_name[20], sign_name[20],number[32][3], name[32][20], string3[11];

    printf("Please enter bus number: ");
    scanf("%d", &num);
    system("cls");
    sprintf(buffer, "%d.txt", num);
    bptr= fopen(buffer, "r+");

    for(int i=1; i<=9; i++)
    {
        fgets(line1, sizeof(line1), bptr);
        if(i>=2)
        {
            printf("%s\n", line1);
        }
    }
    fclose(bptr);
    printf("Please enter the seat number: ");
    fflush(stdin);
    scanf("%d", &seat_num);

    printf("\nSeat reservation canceled successfully\n");
    sprintf(file, "%d_booked.txt", num);
    sprintf(file2, "%d_names.txt", num);
    ptr=fopen(file,"r+");
    ptr2=fopen(file2, "r+");

    int i=0, j=0;
    while(!feof(ptr2))
    {
        name[i][j]=fgetc(ptr2);
        if(name[i][j]=='\n')
        {
            name[i][j]='\0';
            i++;
            j=0;
        }
        else j++;
    }

    i=0, j=0;
    while(!feof(ptr))
    {
        number[i][j]=fgetc(ptr);
        if(number[i][j]=='\n')
        {
            number[i][j]='\0';
            i++;
            j=0;
        }
        else j++;
    }
    int m=i;
    for(int i=0; i<m; i++)
    {
        seats[i]=atoi(number[i]);
    }

    fclose(ptr);
    fclose(ptr2);

    fptr1=fopen("temp_name.txt", "a+");
    fptr2=fopen("temp_booked.txt", "a+");

    for(int n=1; n<=32; n++)
    {
        for(int o=0; o<m; o++)
        {
            if(n==seat_num)
            {
                strcpy(temp[n], "Empty");
                break;
            }
            else if(n==seats[o])
            {
                strcpy(temp[n], name[o]);
                fprintf(fptr1, "%s\n", name[o]);
                fprintf(fptr2, "%d\n", seats[o]);
                break;
            }
            else strcpy(temp[n], "Empty");
        }
    }

    fclose(fptr1);
    fclose(fptr2);

    int status=remove(file);
    if (status) printf("Warning: %s\n", strerror(errno));
    status=remove(file2);
    if (status) printf("Warning: %s\n", strerror(errno));

    rename("temp_name.txt", file2);
    rename("temp_booked.txt", file);

    bptr= fopen(buffer, "r+");
    temporary=fopen("temp.txt", "a+");
    fgets(line, 200, bptr);
    fprintf(temporary, "%s", line);

    int l=1;
    for(int j=0; j<8; j++)
    {
        for(int k=0; k<4; k++)
        {
            fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
            l++;
        }
        fprintf(temporary, "\n");
    }
    fclose(bptr);
    fclose(temporary);
    remove(buffer);
    rename("temp.txt", buffer);

    sprintf(file3, "%d_num.txt", num);
    fptr3=fopen(file3, "r+");
    fgets(line3, 3, fptr3);
    no_seats=atoi(line3);
    fclose(fptr3);

    fptr3=fopen(file3, "w+");
    no_seats+=1;
    fprintf(fptr3, "%d", no_seats);
    fclose(fptr3);
}


void update_pass(void)
{
    system("cls");
    char array[3][20],sign_name[20], sign_pass[20],new_pass[20],username[20];
    int result_name, result_pass, option;
    FILE*fptr;

    fptr=fopen("Signin_details.txt", "r+");
    rewind(fptr);

    printf("\n\t\t\tEnter Username: ");
    fflush(stdin);
    gets(sign_name);
    strcpy(username,sign_name);
    printf("\t\t\tEnter previous Password: ");
    fflush(stdin);
    gets(sign_pass);

    int i=0;
    rewind(fptr);
    while(!feof(fptr))
    {
        fgets(array[i], sizeof(array[i]), fptr);
        i++;
    }
    strcat(sign_name, "\n");
    strcat(sign_pass, "\n");

    result_name=strcmp(array[0], sign_name);
    result_pass=strcmp(array[1], sign_pass);

    if(result_name==0 && result_pass==0)
    {

        fptr=fopen("Signin_details.txt", "w+");
        printf("\n\t\t\tEnter new password: ");
        fflush(stdin);
        gets(new_pass);

        printf("\n\t\t\tPassword updated!\n\n");
        fprintf(fptr, "%s\n%s\n", username, new_pass);
        fclose(fptr);
    }
    else
    {
        printf("\n\t\t\tWrong username or password");
        printf("\n\t\t\tPlease enter correct Information ");
        getch();
        update_pass();
    }
    fclose(fptr);
}

void record()
{
    FILE*fptr;
    char buffer[11];
    char line[500];
    for(int i=1; i<=999; i++)
    {
        sprintf(buffer, "%d.txt", i);
        if((fptr= fopen(buffer, "r+"))!=NULL)
        {
            fgets(line, sizeof(line), fptr);
            printf("%s\n\n", line);
            fclose(fptr);
        }
    }
    printf("\nPress any key to continue...");
    getch();
    system("cls");
}

void delete_record(void)
{


    int number;
    char file1[15], file2[15], file3[15], file4[15], bus[99999][6], exist[99999];
    FILE* bptr;
    FILE*fptr;
    FILE*file[4];

    system("cls");

    printf("Enter the bus number you want to delete records of: ");
    scanf("%d", &number);
    sprintf(file1, "%d.txt", number);
    sprintf(file2, "%d_booked.txt", number);
    sprintf(file3, "%d_names.txt", number);
    sprintf(file4, "%d_num.txt", number);

    file[0]=fopen(file1, "r+");
    if(file[0]!=NULL) fclose(file[0]);
    int status=remove(file1);
    if (status) printf("Warning: %s\n", strerror(errno));
    file[1]=fopen(file2, "r+");
    if(file[1]!=NULL) fclose(file[1]);
    remove(file2);
    file[2]=fopen(file3, "r+");
    if(file[2]!=NULL) fclose(file[2]);
    remove(file3);
    file[3]=fopen(file4, "r+");
    if(file[3]!=NULL) fclose(file[3]);
    remove(file4);
    printf("Records successfully deleted!\n");
    printf("Press any key to continue ... ");
    getch();
    bptr=fopen("buses.txt", "r+");
    fseek(bptr, 0, SEEK_SET);
    int p=0, q=0;
    while(!feof(bptr))
    {
        bus[p][q]=fgetc(bptr);
        if(bus[p][q]==' ')
        {
            bus[p][q]='\0';
            p++;
            q=0;
        }
        else q++;
    }
    fclose(bptr);

    int r=p;
    for(int i=0; i<r; i++)
    {
        exist[i]=atoi(bus[i]);
        if(exist[i]!=number)
        {
            fptr=fopen("temp_bus.txt", "a+");
            fprintf(fptr, "%d ", exist[i]);
            fclose(fptr);
        }
    }
    remove("buses.txt");
    rename("temp_bus.txt", "buses.txt");
    system("cls");
}

void exit_program()
{
    system("cls");
    printf("\n\n\n\t\t\tThank you for using TransTech!\n\n\n\n");
    exit(0);
}
