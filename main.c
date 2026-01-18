#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
    char id[10];
    char name[30];
    float score;
} student;

typedef struct studentnode {
    student data;
    struct studentnode *next;
} studentnode;

typedef struct classnode {
    char class_name[100];
    struct studentnode *list;
    struct classnode *next;
} classnode;

classnode* find_class(classnode **head, char *name);
void add_student_to_class(classnode *target_class, student user_data);
void display(classnode *head, char *target_class);
void search_student(classnode *head, char *target_id);
void delete_student_from_class(classnode *head, char *target_id, char *class_name);
void class_average(classnode *head, char *class_name);
int get_rank(classnode *head, char *target_id, char *class_name);

int main() {
    classnode *head = NULL;
    student temp_student;
    char class_name_buffer[100];
    char target_id[10];
    int choice;

    while (1) {
        printf("==========\n");
        printf("Welcome to the students manage system\n");
        printf("1. Add\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Class statistics\n");
        printf("6. Exit\n");
        printf("==========\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar()!='\n');

        switch (choice) {
            case 1: {
                printf("Name(english): ");
                fgets(temp_student.name, 30, stdin);
                temp_student.name[strcspn(temp_student.name,"\n")]=0; // 切掉最後的換行

                printf("School ID: ");
                scanf("%s", temp_student.id);
                while (getchar()!='\n');

                printf("Class name: ");
                fgets(class_name_buffer, 100, stdin);
                class_name_buffer[strcspn(class_name_buffer,"\n")]=0;

                printf("Score: ");
                scanf("%f", &temp_student.score);
                while (getchar()!='\n');

                classnode *target_class = find_class(&head, class_name_buffer);
                add_student_to_class(target_class, temp_student);
                break;
            }
            case 2: {
                printf("Enter the class you want to display: ");
                fgets(class_name_buffer, 100, stdin);
                class_name_buffer[strcspn(class_name_buffer,"\n")]=0;
                display(head, class_name_buffer);
                break;
            }
            case 3: {
                printf("Student's school ID: ");
                scanf("%s", target_id);
                while (getchar()!='\n');
                search_student(head, target_id);
                break;
            }
            case 4: {
                printf("Student's school ID: ");
                scanf("%s", target_id);
                while (getchar()!='\n');
                printf("Class name: ");
                fgets(class_name_buffer,100,stdin);
                class_name_buffer[strcspn(class_name_buffer,"\n")]=0;
                delete_student_from_class(head, target_id, class_name_buffer);
                break;
            }
            case 5: {
                printf("Student's school ID: ");
                scanf("%s", target_id);
                while (getchar()!='\n');
                printf("Class name: ");
                fgets(class_name_buffer,100,stdin);
                class_name_buffer[strcspn(class_name_buffer,"\n")]=0;

                class_average(head, class_name_buffer);
                int rank = get_rank(head, target_id, class_name_buffer);
                printf("Student %s ranking in class %s is NO.%d.\n"
                ,target_id, class_name_buffer, rank);
                break;
            }
            case 6: return 0; 
        }
    }
    return 0;
}

classnode* find_class(classnode **head, char *name) {
    classnode *cur = *head;
    while (cur!=NULL) {
        if (strcmp(cur->class_name, name)==0) {
            return cur;
        }
        cur = cur->next;
    }
    if (cur==NULL) {
        classnode *newnode = malloc(sizeof(classnode));
        strcpy(newnode->class_name, name);
        newnode->list = NULL;
        newnode->next = *head;
        *head = newnode;
        printf("New class created!\n");
        return newnode;
    }
}

void add_student_to_class(classnode *target_class, student user_data) {
    studentnode *newnode = malloc(sizeof(studentnode));
    if (newnode==NULL) exit(1);
    newnode->data = user_data;
    newnode->next = target_class->list;
    target_class->list = newnode;
    printf("Student %s added to class %s.\n", user_data.name, target_class->class_name);
}

void display(classnode *head, char *target_class) {
    classnode *cur_class = head;
    studentnode *cur_student;
    while (cur_class!=NULL) {
        if (strcmp(cur_class->class_name,target_class)==0) {
            printf("=== Class: %s ===\n", cur_class->class_name);
            if (cur_class->list==NULL) {
                printf("No students in class!\n");
                return;
            }
            for (cur_student=cur_class->list;cur_student!=NULL;cur_student=cur_student->next) {
                printf("ID: %s | Name: %s | Score: %.2f\n",
                cur_student->data.id, cur_student->data.name, cur_student->data.score);
            }
            printf("==========\n");
            return;
        }
        cur_class = cur_class->next;
    }
    printf("Class: %s not found!\n", target_class);
}

void search_student(classnode *head, char *target_id) {
    classnode *cur_class;
    studentnode *cur_student;
    int found = 0;
    if (head==NULL) {
        printf("Class: %s not found!\n", head);
        return;
    }
    for (cur_class=head;cur_class!=NULL;cur_class=cur_class->next) {
        if (cur_class->list==NULL) {
            continue;
        }
        for (cur_student=cur_class->list;cur_student!=NULL;cur_student=cur_student->next) {
            if (strcmp(cur_student->data.id, target_id)==0) {
                printf("Name: %s | Class name: %s | Score: %.2f\n",
                    cur_student->data.name, cur_class->class_name, cur_student->data.score);
                found = 1;
                break;
            }
        }
    }
    if (found==0) {
        printf("ID: %s is not found in any class!\n", target_id);
    }
}

void delete_student_from_class(classnode *head, char *target_id, char *class_name) {
    classnode *cur_class = head;
    while (cur_class!=NULL) {
        if (strcmp(cur_class->class_name, class_name)==0) {
            break;
        }
        cur_class = cur_class->next;
    }  
    if (cur_class==NULL) {
        printf("Class: %s not found!\n", class_name);
        return;
    }

    studentnode *cur = cur_class->list;
    studentnode *pre = NULL;
    while (cur!=NULL) {
        if (strcmp(cur->data.id, target_id)==0) {
            if (pre==NULL) {  // delete the first one
                cur_class->list = cur->next;
            }
            else {
                pre->next = cur->next;
            }
            free(cur);
            printf("Student %s has been deleted from class %s./n",target_id,class_name);
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    printf("Student %s not found in class %s.\n", target_id, class_name);
}

void class_average(classnode *head, char *class_name) {
    classnode *cur_class = head;
    while (cur_class!=NULL) {
        if (strcmp(cur_class->class_name, class_name)==0) {
            break;
        }
        cur_class = cur_class->next;
    }
    if (cur_class==NULL) {
        printf("Class: %s not found!\n", class_name);
        return;
    }
    studentnode *cur_student = cur_class->list;
    float sum = 0;
    int count = 0;
    while (cur_student!=NULL) {
        sum = sum+cur_student->data.score;
        count++;
        cur_student = cur_student->next;
    }
    if (count==0) {
        printf("Class %s has no students.\n", class_name);
    }
    else {
        float result = sum/count;
        printf("Class %s average score is %.2f.\n", class_name, result);
    }
}

int get_rank(classnode *head, char *target_id, char *class_name) {
    classnode *cur_class = head;
    // 1. find the class
    while (cur_class!=NULL) {
        if (strcmp(cur_class->class_name, class_name)==0) {
            break;
        }
        cur_class = cur_class->next;
    }
    if (cur_class==NULL) {
        printf("Class: %s not found!\n", class_name);
        return -1;
    }

    // 2. find the student and store the score
    studentnode *cur_student = cur_class->list;
    float my_score = -1.0;
    while (cur_student!=NULL) {
        if (strcmp(cur_student->data.id, target_id)==0) {
            my_score = cur_student->data.score;
            break;
        }
        cur_student = cur_student->next;
    }
    if (my_score==-1.0) {
        printf("Student %s not found in class %s.\n", target_id, class_name);
        return -1;
    }

    // 3. calculate ranking
    int rank = 0;
    cur_student = cur_class->list;
    while (cur_student!=NULL) {
        if (cur_student->data.score>my_score) {
            rank++;
        }
        cur_student = cur_student->next;
    }
    return rank+1;
}
