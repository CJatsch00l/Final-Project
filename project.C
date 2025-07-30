#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple structures
typedef struct {
    char id[20];
    char name[50];
    char password[20];
    int has_voted;
    char voted_for[20];
} Student;

typedef struct {
    char id[20];
    char name[50];
    char password[20];
    char manifesto[200];
    int votes;
} Representative;

// Global variables
Student students[50];
Representative reps[10];
int student_count = 0;
int rep_count = 0;
int results_published = 0;

// Function prototypes
void main_menu();
void admin_menu();
void rep_menu();
void student_menu();
void load_data();
void save_data();
void clear_input();

int main() {
    load_data();
    printf("=== STUDENT ELECTION SYSTEM ===\n");
    main_menu();
    save_data();
    return 0;
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main_menu() {
    int choice;
    
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Admin Login\n");
        printf("2. Representative Portal\n");
        printf("3. Student Portal\n");
        printf("4. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clear_input();
        
        switch (choice) {
            case 1: admin_menu(); break;
            case 2: rep_menu(); break;
            case 3: student_menu(); break;
            case 4: 
                printf("Goodbye!\n");
                exit(0);
            default: 
                printf("Invalid choice!\n");
        }
    }
}

void admin_menu() {
    char username[20], password[20];
    
    printf("\n=== ADMIN LOGIN ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    clear_input();
    
    if (strcmp(username, "SCDS") != 0 || strcmp(password, "202504") != 0) {
        printf("Invalid credentials!\n");
        return;
    }
    
    int choice;
    while (1) {
        printf("\n=== ADMIN PANEL ===\n");
        printf("1. View Representatives\n");
        printf("2. View Vote Counts\n");
        printf("3. Publish Results\n");
        printf("4. Display Results\n");
        printf("5. Back to Main Menu\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clear_input();
        
        switch (choice) {
            case 1:
                printf("\n=== REGISTERED REPRESENTATIVES ===\n");
                if (rep_count == 0) {
                    printf("No representatives registered.\n");
                } else {
                    for (int i = 0; i < rep_count; i++) {
                        printf("%d. %s (%s)\n", i+1, reps[i].name, reps[i].id);
                    }
                }
                break;
                
            case 2:
                printf("\n=== VOTE COUNTS ===\n");
                if (rep_count == 0) {
                    printf("No representatives registered.\n");
                } else {
                    for (int i = 0; i < rep_count; i++) {
                        printf("%s: %d votes\n", reps[i].name, reps[i].votes);
                    }
                }
                break;
                
            case 3:
                if (results_published) {
                    printf("Results already published!\n");
                } else {
                    results_published = 1;
                    printf("Results published successfully!\n");
                }
                break;
                
            case 4:
                printf("\n=== ELECTION RESULTS ===\n");
                if (rep_count == 0) {
                    printf("No representatives registered.\n");
                } else {
                    // Simple sorting by votes
                    for (int i = 0; i < rep_count - 1; i++) {
                        for (int j = i + 1; j < rep_count; j++) {
                            if (reps[i].votes < reps[j].votes) {
                                Representative temp = reps[i];
                                reps[i] = reps[j];
                                reps[j] = temp;
                            }
                        }
                    }
                    
                    for (int i = 0; i < rep_count; i++) {
                        printf("%d. %s: %d votes\n", i+1, reps[i].name, reps[i].votes);
                    }
                }
                break;
                
            case 5:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void rep_menu() {
    int choice;
    
    while (1) {
        printf("\n=== REPRESENTATIVE PORTAL ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clear_input();
        
        switch (choice) {
            case 1: {
                if (rep_count >= 10) {
                    printf("Maximum representatives reached!\n");
                    break;
                }
                
                printf("\n=== REPRESENTATIVE REGISTRATION ===\n");
                printf("Student ID: ");
                scanf("%s", reps[rep_count].id);
                
                // Check if ID already exists
                int exists = 0;
                for (int i = 0; i < rep_count; i++) {
                    if (strcmp(reps[i].id, reps[rep_count].id) == 0) {
                        exists = 1;
                        break;
                    }
                }
                
                if (exists) {
                    printf("ID already registered!\n");
                    break;
                }
                
                printf("Name: ");
                clear_input();
                fgets(reps[rep_count].name, 50, stdin);
                reps[rep_count].name[strcspn(reps[rep_count].name, "\n")] = 0; // Remove newline
                
                printf("Password: ");
                scanf("%s", reps[rep_count].password);
                
                strcpy(reps[rep_count].manifesto, "");
                reps[rep_count].votes = 0;
                rep_count++;
                
                printf("Registration successful!\n");
                break;
            }
            
            case 2: {
                char id[20], password[20];
                printf("\n=== REPRESENTATIVE LOGIN ===\n");
                printf("Student ID: ");
                scanf("%s", id);
                printf("Password: ");
                scanf("%s", password);
                clear_input();
                
                int found = -1;
                for (int i = 0; i < rep_count; i++) {
                    if (strcmp(reps[i].id, id) == 0 && strcmp(reps[i].password, password) == 0) {
                        found = i;
                        break;
                    }
                }
                
                if (found == -1) {
                    printf("Invalid credentials!\n");
                    break;
                }
                
                int rep_choice;
                while (1) {
                    printf("\n=== REPRESENTATIVE PANEL ===\n");
                    printf("Welcome, %s!\n", reps[found].name);
                    printf("1. Submit/Update Manifesto\n");
                    printf("2. View My Stats\n");
                    printf("3. Logout\n");
                    printf("Choice: ");
                    
                    scanf("%d", &rep_choice);
                    clear_input();
                    
                    switch (rep_choice) {
                        case 1:
                            printf("Enter your manifesto (max 200 chars):\n");
                            fgets(reps[found].manifesto, 200, stdin);
                            reps[found].manifesto[strcspn(reps[found].manifesto, "\n")] = 0;
                            printf("Manifesto updated!\n");
                            break;
                            
                        case 2:
                            printf("\n=== MY STATISTICS ===\n");
                            printf("Name: %s\n", reps[found].name);
                            printf("ID: %s\n", reps[found].id);
                            printf("Votes: %d\n", reps[found].votes);
                            printf("Manifesto: %s\n", 
                                   strlen(reps[found].manifesto) > 0 ? reps[found].manifesto : "Not submitted");
                            break;
                            
                        case 3:
                            goto rep_logout;
                            
                        default:
                            printf("Invalid choice!\n");
                    }
                }
                rep_logout:
                break;
            }
            
            case 3:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void student_menu() {
    int choice;
    
    while (1) {
        printf("\n=== STUDENT PORTAL ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clear_input();
        
        switch (choice) {
            case 1: {
                if (student_count >= 50) {
                    printf("Maximum students reached!\n");
                    break;
                }
                
                printf("\n=== STUDENT REGISTRATION ===\n");
                printf("Student ID: ");
                scanf("%s", students[student_count].id);
                
                // Check if ID already exists
                int exists = 0;
                for (int i = 0; i < student_count; i++) {
                    if (strcmp(students[i].id, students[student_count].id) == 0) {
                        exists = 1;
                        break;
                    }
                }
                
                if (exists) {
                    printf("ID already registered!\n");
                    break;
                }
                
                printf("Name: ");
                clear_input();
                fgets(students[student_count].name, 50, stdin);
                students[student_count].name[strcspn(students[student_count].name, "\n")] = 0;
                
                printf("Password: ");
                scanf("%s", students[student_count].password);
                
                students[student_count].has_voted = 0;
                strcpy(students[student_count].voted_for, "");
                student_count++;
                
                printf("Registration successful!\n");
                break;
            }
            
            case 2: {
                char id[20], password[20];
                printf("\n=== STUDENT LOGIN ===\n");
                printf("Student ID: ");
                scanf("%s", id);
                printf("Password: ");
                scanf("%s", password);
                clear_input();
                
                int found = -1;
                for (int i = 0; i < student_count; i++) {
                    if (strcmp(students[i].id, id) == 0 && strcmp(students[i].password, password) == 0) {
                        found = i;
                        break;
                    }
                }
                
                if (found == -1) {
                    printf("Invalid credentials!\n");
                    break;
                }
                
                int student_choice;
                while (1) {
                    printf("\n=== STUDENT PANEL ===\n");
                    printf("Welcome, %s!\n", students[found].name);
                    printf("1. View Representatives\n");
                    printf("2. Cast Vote\n");
                    printf("3. View Results\n");
                    printf("4. Logout\n");
                    printf("Choice: ");
                    
                    scanf("%d", &student_choice);
                    clear_input();
                    
                    switch (student_choice) {
                        case 1:
                            printf("\n=== REPRESENTATIVES & MANIFESTOS ===\n");
                            if (rep_count == 0) {
                                printf("No representatives registered.\n");
                            } else {
                                for (int i = 0; i < rep_count; i++) {
                                    printf("\n%d. %s (%s)\n", i+1, reps[i].name, reps[i].id);
                                    printf("Manifesto: %s\n", 
                                           strlen(reps[i].manifesto) > 0 ? reps[i].manifesto : "Not submitted");
                                    printf("---\n");
                                }
                            }
                            break;
                            
                        case 2:
                            if (students[found].has_voted) {
                                printf("You have already voted for: %s\n", students[found].voted_for);
                                break;
                            }
                            
                            if (rep_count == 0) {
                                printf("No representatives to vote for.\n");
                                break;
                            }
                            
                            printf("\n=== CAST VOTE ===\n");
                            printf("Available Representatives:\n");
                            for (int i = 0; i < rep_count; i++) {
                                printf("%d. %s\n", i+1, reps[i].name);
                            }
                            
                            int vote_choice;
                            printf("Enter your choice (1-%d): ", rep_count);
                            scanf("%d", &vote_choice);
                            clear_input();
                            
                            if (vote_choice < 1 || vote_choice > rep_count) {
                                printf("Invalid choice!\n");
                                break;
                            }
                            
                            printf("You selected: %s\n", reps[vote_choice-1].name);
                            printf("Confirm vote? (y/n): ");
                            char confirm;
                            scanf(" %c", &confirm);
                            clear_input();
                            
                            if (confirm == 'y' || confirm == 'Y') {
                                students[found].has_voted = 1;
                                strcpy(students[found].voted_for, reps[vote_choice-1].name);
                                reps[vote_choice-1].votes++;
                                printf("Vote cast successfully!\n");
                            } else {
                                printf("Vote cancelled.\n");
                            }
                            break;
                            
                        case 3:
                            if (!results_published) {
                                printf("Results not published yet!\n");
                            } else {
                                printf("\n=== PUBLISHED RESULTS ===\n");
                                if (rep_count == 0) {
                                    printf("No representatives registered.\n");
                                } else {
                                    // Sort by votes for display
                                    Representative temp_reps[10];
                                    for (int i = 0; i < rep_count; i++) {
                                        temp_reps[i] = reps[i];
                                    }
                                    
                                    for (int i = 0; i < rep_count - 1; i++) {
                                        for (int j = i + 1; j < rep_count; j++) {
                                            if (temp_reps[i].votes < temp_reps[j].votes) {
                                                Representative temp = temp_reps[i];
                                                temp_reps[i] = temp_reps[j];
                                                temp_reps[j] = temp;
                                            }
                                        }
                                    }
                                    
                                    for (int i = 0; i < rep_count; i++) {
                                        printf("%d. %s: %d votes\n", i+1, temp_reps[i].name, temp_reps[i].votes);
                                    }
                                }
                            }
                            break;
                            
                        case 4:
                            goto student_logout;
                            
                        default:
                            printf("Invalid choice!\n");
                    }
                }
                student_logout:
                break;
            }
            
            case 3:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void load_data() {
    FILE *fp;
    
    // Load students
    fp = fopen("students.dat", "rb");
    if (fp) {
        fread(&student_count, sizeof(int), 1, fp);
        fread(students, sizeof(Student), student_count, fp);
        fclose(fp);
    }
    
    // Load representatives
    fp = fopen("representatives.dat", "rb");
    if (fp) {
        fread(&rep_count, sizeof(int), 1, fp);
        fread(reps, sizeof(Representative), rep_count, fp);
        fclose(fp);
    }
    
    // Load system status
    fp = fopen("system.dat", "rb");
    if (fp) {
        fread(&results_published, sizeof(int), 1, fp);
        fclose(fp);
    }
}

void save_data() {
    FILE *fp;
    
    // Save students
    fp = fopen("students.dat", "wb");
    if (fp) {
        fwrite(&student_count, sizeof(int), 1, fp);
        fwrite(students, sizeof(Student), student_count, fp);
        fclose(fp);
    }
    
    // Save representatives
    fp = fopen("representatives.dat", "wb");
    if (fp) {
        fwrite(&rep_count, sizeof(int), 1, fp);
        fwrite(reps, sizeof(Representative), rep_count, fp);
        fclose(fp);
    }
    
    // Save system status
    fp = fopen("system.dat", "wb");
    if (fp) {
        fwrite(&results_published, sizeof(int), 1, fp);
        fclose(fp);
    }
}
