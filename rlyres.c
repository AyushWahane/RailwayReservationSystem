#include <stdio.h>
#include "rlyres.h"
#include "conio2.h"
#include <string.h>
#include <ctype.h>
int enterchoice()
{
    int choice;
    int i;
    textcolor(YELLOW);
    gotoxy(27,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<80;i++)
        printf("-");
    printf("\nSelect an option\n1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket no\n5- View All Bookings\n6- View Train Bookings\n7- Cancel ticket\n8- Cancel Train\n9- Quit");
    printf("\n\nEnter choice: ");
    scanf("%d",&choice);
    return choice;
}
void add_train()
{
    FILE* fp = fopen("d:\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={
        {"123","BPL","GWA",2100,1500},
        {"546","BPL","DEL",3500,2240},
        {"354","HBJ","AGR",1560,1135},
        {"896","HBJ","MUM",4500,3360},
        };
        fp=fopen("d:\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        //printf("File created and saved!\n");
        fclose(fp);
    }
    else
    {
        //printf("File already present\n");
        fclose(fp);
    }
}
void view_train()
{
    int i;
    printf("\nTRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=0;i<80;i++)
        printf("-");
    FILE* fp=fopen("d:\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    //printf("\n\n\n\n");
    fclose(fp);
}
int check_train_no(char *trainno)
{
    FILE *fp=fopen("d:\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while (*p_mob!='\0')
    {
        if (isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}
Passenger* get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(GREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("Enter Passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos = strchr(psn.p_name,'\n');
    *pos = '\0';
    if (strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }

    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if (psn.gender!='M' && psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F (in UPPERCASE)");
            valid = 0;
            getch();
            gotoxy(19,2);
            printf(" \b");
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");

    gotoxy(1,3);
    printf("Enter Train Number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if (strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid = check_train_no(psn.train_no);
        if(valid == 0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Train Number");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");

    gotoxy(1,4);
    printf("Enter travelling Class(First AC-F,Second AC-S):");
    do
    {
        valid = 1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if (psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Travelling class should be F or S (in uppercase)");
            valid=0;
            getch();
            gotoxy(48,4);
            printf(" \b");
            textcolor(YELLOW);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");
    gotoxy(1,5);
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,20,stdin);
    pos = strchr(psn.address,'\n');
    *pos = '\0';
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }

    printf("Enter Age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if (psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if (psn.age<=0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
        }
    }while (valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,7);

    printf("Enter Mobile Number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid = check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if (fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while (fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if (fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==10)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE* fp=fopen("D:\\allbookings.dat","ab");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
int accept_ticket_no()
{
    int valid;
    int ticket_no;
    printf("Enter ticket no:");
    do
    {
        scanf("%d",&ticket_no);
        valid=1;
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Ticket number should be positive");
            valid=0;
            getch();
            gotoxy(17,1);
            printf("\t\t\t\t\t\t");
            gotoxy(17,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}
void view_ticket(int ticket_no)
{
    //int i;
    FILE* fp=fopen("D:\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("NAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRESS: %s\nAGE: %d\nMOBILE NO:%s\nTICKET NO: %d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            printf("\n\n");
            found = 1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no %d found!",ticket_no);
    }
    fclose(fp);
}
char* accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid;
    printf("Enter Mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,11,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}
int* get_ticket_no(char *p_mob_no)
{
    int count=0;
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while (fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_tickets(char *pmob_no, int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("Press any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets Booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("----------");
    for(i=0; *(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
}
char* accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(GREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Train Number: ");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Train No");
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}
void view_booking(char *train_no)
{
    int i,row=3;
    Passenger pr;
    int found=0;
    FILE* fp=fopen("D:\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return;
    }
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=0;i<80;i++)
        printf("-");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            found = 1;
            row++;
        }
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of train no %s found!",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPress any key to continue!");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
int cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("D:\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE *fp2=fopen("D:\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\temp.dat");
    }
    else
    {
        remove("D:\\allbookings.dat");
        rename("D:\\temp.dat","D:\\allbookings.dat");
    }
    return found;
}
int cancel_train(char *train_no)
{
    FILE *fp1=fopen("D:\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE *fp2=fopen("D:\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\temp.dat");
    }
    else
    {
        remove("D:\\allbookings.dat");
        rename("D:\\temp.dat","D:\\allbookings.dat");
    }
    return found;
}
void view_all_bookings()
{
    int i,found=0;
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("NO BOOKINGS DONE YET");
        return;
    }
    textcolor(GREEN);
    gotoxy(29,1);
    printf("ALL BOOKINGS OF TRAINS\n");
    for(i=0;i<80;i++)
        printf("-");
    textcolor(WHITE);
    printf("TICKET NO.\tTRAIN NO\tCLASS\tNAME\tGENDER\tAGE\tMOBILE NO\n");
    for(i=0;i<80;i++)
        printf("-");
    Passenger pr;
    int row=5;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%d\t\t%s\t\t%c\t%s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
        gotoxy(49,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
        found=1;
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details found!");
    }
    //textcolor(WHITE);
    printf("\n\nPress any key to continue!");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
