#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bookdetails {
    char name[100];
    char id[10];
    int pages;
    float price;
    char genre[100];
};

struct books {
    struct bookdetails details;
    char authorname[100];
};

struct names {
    char firstname[100];
    char lastname[100];
};

struct addresses {
    char temp[100];
    char perma[100];
};

struct contacts {
    char phoneno[15];
    char email[100];
};

struct students {
    struct names name;
    struct addresses address;
    char id[10];
    struct contacts contact;
};

void addbook() {
    FILE *fp = fopen("books.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    int n;
    printf("How many books do you want to add? ");
    scanf("%d", &n);
    getchar();  // consume newline character
    struct books book;

    	system("color FD");
    	system("cls");
    for (int i = 0; i < n; i++) {
        printf("Book %d:\n", i + 1);

        printf("\tName: ");
        fgets(book.details.name, sizeof(book.details.name), stdin);
        book.details.name[strcspn(book.details.name, "\n")] = 0;

        printf("\tID: ");
        fgets(book.details.id, sizeof(book.details.id), stdin);
        book.details.id[strcspn(book.details.id, "\n")] = 0;

        printf("\tPages: ");
        scanf("%d", &book.details.pages);
        getchar();  // consume newline character

        printf("\tPrice: ");
        scanf("%f", &book.details.price);
        getchar();  // consume newline character

        printf("\tGenre: ");
        fgets(book.details.genre, sizeof(book.details.genre), stdin);
        book.details.genre[strcspn(book.details.genre, "\n")] = 0;

        printf("\tAuthor Name: ");
        fgets(book.authorname, sizeof(book.authorname), stdin);
        book.authorname[strcspn(book.authorname, "\n")] = 0;

        fprintf(fp, "%s %s %d %.2f %s %s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname);
	}
    	system("cls"); 

    fclose(fp);
}

void addstudent() {
    struct students student;
    FILE *fp = fopen("StudentDetails.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    	system("cls");
        system("color FC");
    while (1) {
        printf("\tStudent ID: ");
        fgets(student.id, sizeof(student.id), stdin);
        student.id[strcspn(student.id, "\n")] = 0;

        printf("Name:\n");
        printf("\tFirst Name: ");
        fgets(student.name.firstname, sizeof(student.name.firstname), stdin);
        student.name.firstname[strcspn(student.name.firstname, "\n")] = 0;

        printf("\tLast Name: ");
        fgets(student.name.lastname, sizeof(student.name.lastname), stdin);
        student.name.lastname[strcspn(student.name.lastname, "\n")] = 0;

        printf("Address:\n");
        printf("\tTemporary: ");
        fgets(student.address.temp, sizeof(student.address.temp), stdin);
        student.address.temp[strcspn(student.address.temp, "\n")] = 0;

        printf("\tPermanent: ");
        fgets(student.address.perma, sizeof(student.address.perma), stdin);
        student.address.perma[strcspn(student.address.perma, "\n")] = 0;

        printf("Contact:\n");
        printf("\tPhone No.: ");
        fgets(student.contact.phoneno, sizeof(student.contact.phoneno), stdin);
        student.contact.phoneno[strcspn(student.contact.phoneno, "\n")] = 0;

        printf("\tEmail: ");
        fgets(student.contact.email, sizeof(student.contact.email), stdin);
        student.contact.email[strcspn(student.contact.email, "\n")] = 0;

        fprintf(fp, "%s %s %s %s %s %s %s\n", student.id, student.name.firstname, student.name.lastname, student.address.temp, student.address.perma, student.contact.phoneno, student.contact.email);

        printf("Do you want to add another student? (1 for Yes, 0 for No): ");
        int choice;
        scanf("%d", &choice);
        getchar();  // consume newline character
        if (choice != 1) {
            break;
        }
    }

    fclose(fp);
    system("cls");
}

int borrow(const char id[], const char sid[]) {
    struct books book;
    struct students student;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("books.txt", "r");
    fp2 = fopen("StudentDetails.txt", "r");
    fp3 = fopen("borrowed.txt", "a");
    fp4 = fopen("temp.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        perror("Error opening file");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        if (fp3) fclose(fp3);
        if (fp4) fclose(fp4);
        return 0;
    }

    int studentFound = 0;
    while (fscanf(fp2, "%s %s %s %s %s %s %s\n", student.id, student.name.firstname, student.name.lastname, student.address.temp, student.address.perma, student.contact.phoneno, student.contact.email) != EOF) {
        system("cls");
        system("color FE");
		if (strcmp(sid, student.id) == 0) {
            studentFound = 1;
            break;
        }
    }

    if (!studentFound) {
        printf("Student not found.\n");
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        return 0;
    }

    int bookFound = 0;
    while (fscanf(fp1, "%s %s %d %f %s %s\n", book.details.id, book.details.name, &book.details.pages, &book.details.price, book.details.genre, book.authorname) != EOF) {
        if (strcmp(book.details.id, id) == 0) {
            bookFound = 1;
            fprintf(fp3, "%s %s %d %.2f %s %s %s %s %s %s %s %s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname, student.id, student.name.firstname, student.name.lastname, student.address.temp, student.address.perma, student.contact.phoneno, student.contact.email);
        } else {
            fprintf(fp4, "%s %s %d %.2f %s %s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    if (!bookFound) {
        printf("Book not found.\n");
        return 0;
    }

    if (remove("books.txt") != 0) {
        perror("Error removing books.txt");
        return 0;
    }

    if (rename("temp.txt", "books.txt") != 0) {
        perror("Error renaming temp.txt to books.txt");
        return 0;
    }

    return 1;
}

void books() {
	system("cls");
    system("color F8");
    struct books book;
    printf("BookID\tName\tPages\tPrice\tGenre\tAuthorName\n");
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(fp, "%s %s %d %f %s %s\n", book.details.id, book.details.name, &book.details.pages, &book.details.price, book.details.genre, book.authorname) != EOF) {
        printf("%s\t%s\t%d\t%.2f\t%s\t%s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname
        , book.authorname);
    }

    fclose(fp);

    printf("Do you want to borrow a book? (y/n): ");
    char ch;
    ch = getchar();
    getchar(); // consume newline character

    if (ch == 'y' || ch == 'Y') {
        printf("Enter the book ID: ");
        char id[10];
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0; // remove newline character

        printf("Enter the student ID: ");
        char sid[10];
        fgets(sid, sizeof(sid), stdin);
        sid[strcspn(sid, "\n")] = 0; // remove newline character

        if (borrow(id, sid) == 1) {
            system("cls");
            printf("Successfully borrowed the book.\n");
        } else {
            printf("Failed to borrow the book.\n");
        }
    }
}void Return() {
    system("cls");
	char id[10];
    char sid[10];

    printf("Enter book id: ");
    scanf("%s", id);
    printf("Enter student id: ");
    scanf("%s", sid);

    struct books book;
    struct students student;
    
    FILE *fp1 = fopen("borrowed.txt", "r+");
    if (fp1 == NULL) {
        perror("Error opening borrowed.txt");
        return;
    }
    
    FILE *fp2 = fopen("temp.txt", "w");
    if (fp2 == NULL) {
        perror("Error opening temp.txt");
        fclose(fp1);
        return;
    }

    int found = 0;
    while (fscanf(fp1, "%s %s %d %f %s %s %s %s %s %s %s %s\n", book.details.id, book.details.name, &book.details.pages, &book.details.price, book.details.genre, book.authorname, student.id, student.name.firstname, student.name.lastname, student.address.temp, student.address.perma, student.contact.phoneno, student.contact.email) != EOF) {
        if (strcmp(sid, student.id) == 0 && strcmp(id, book.details.id) == 0) {
            found = 1;
            // Write the returned book to books.txt
            FILE *fp = fopen("books.txt", "a");
            if (fp == NULL) {
                perror("Error opening books.txt");
                fclose(fp1);
                fclose(fp2);
                return;
            }
            fprintf(fp, "%s %s %d %.2f %s %s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname);
            fclose(fp);
        } else {
            fprintf(fp2, "%s %s %d %.2f %s %s %s %s %s %s %s %s\n", book.details.id, book.details.name, book.details.pages, book.details.price, book.details.genre, book.authorname, student.id, student.name.firstname, student.name.lastname, student.address.temp, student.address.perma, student.contact.phoneno, student.contact.email);
        }
    }

    fclose(fp1);
    fclose(fp2);

    if (!found) {
        printf("Book with id %s borrowed by student with id %s not found.\n", id, sid);
        remove("temp.txt");
        return;
    }

    if (remove("borrowed.txt") != 0) {
        perror("Error removing borrowed.txt");
        return;
    }

    if (rename("temp.txt", "borrowed.txt") != 0) {
        perror("Error renaming temp.txt to borrowed.txt");
        return;
    }

    printf("Book with id %s returned successfully.\n", id);
}


int main() {
    system("cls");
    
    int choice;
    do {
    	system("color F1");
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Add Student\n");
        printf("3. List Books\n");
        printf("4. Return Book \n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	system("cls");
            	system("color F2");
                addbook();
                break;
            case 2:
                system("cls");
            	system("color F3");
				addstudent();
                break;
            case 3:
            	system("cls");
            	system("color F4");
                books();
                break;
            case 4:
            	system("cls");
            	system("color F5");
                Return();
                break;
            case 5:
            	system("cls");
            	system("color F6");
                printf("Exiting...\n");
                break;
            default:
            	system("cls");
            	system("color F7");
                printf("Invalid choice. Please try again.\n");
                break;
                
        }
    } while (choice != 5);

    return 0;
}
