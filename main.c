#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

const float LBS_TO_KG = 2.205f;
const float INCHES_TO_METERS = 39.37f;

int age_s(void);
char gender_s(void);
char region_s(void);
char unit_s(void);
float height_col(void);
float weight_col(void);
float hipc_col(void);
float waist_col(void);
float bmi_calc(float height, float weight, char unit);
float bai_calc(float height, float hipc, char unit);
float whr_calc(float hipc, float waist, char unit);
void bmi_class(char gender, char region, int age, float bmi);
void bai_class(char gender, int age, float bai);
void whr_class(char gender, int age, float whr);
void report_gen(void);
void user_error(void);
void end_program(void);

int main(void) {
    // Introduction
    printf("======================\n");
    printf("   LemonHealth v1\n");
    printf("======================\n");
    printf("\nSupported Options are BMI/ BAI/ WHR/ MM\n");
    printf("BMI: Body Mass Index\n");
    printf("BAI: Body Mass Index\n");
    printf("WHR: Waist to Hip Ratio\n");
    //printf("MM: MultiMeasure for an overall health summary\n");

    // Option Selection
    printf("\nChoose an option: ");
    char choice[10];
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';

    // Unit Selection
    char unit = unit_s();

    // Gender Selection
    char gender = gender_s();

    // Age Selection
    int age = age_s();

    // Program Logic
    if (strcmp(choice, "BMI") == 0) {
        printf("\n===BMI calculation & classification module===\n");
        // Additional fundamental data collection
        printf("For accurate BMI classification, region is required\n");
        char region = region_s();

        // BMI calculation related data collection
        float height = height_col();
        float weight = weight_col();

        // BMI calculation module run
        float bmi_val = bmi_calc(height, weight, unit);
        bmi_class(gender, region, age, bmi_val);
        end_program();
    }

    else if (strcmp(choice, "BAI") == 0) {
        printf("\n===BAI calculation & classification module===\n");
        // BAI calculation related data collection
        float height = height_col();
        float hipc = hipc_col();

        // BAI calculation module run
        float bai_val = bai_calc(height, hipc, unit);
        bai_class(gender, age, bai_val);
        end_program();
    }

    else if (strcmp(choice, "WHR") == 0) {
        printf("\n===WHR calculation & classification module===\n");
        // WHR calculation related data collection
        float waist = waist_col();
        float hipc = hipc_col();

        // WHR calculation module run
        float whr_val = whr_calc(hipc, waist, unit);
        whr_class(gender, age, whr_val);
        end_program();
    }

    // else if (strcmp(choice, "MM") == 0) {
    //     printf("\n===MultiMeasure calculation & classification module===\n");
    //     // MM related data collection
    //     float height = height_col();
    //     float weight = weight_col();
    //     float hipc = hipc_col();
    //     float waist = waist_col();
    //
    //     // Additional fundamental data collection
    //     printf("For accurate BMI classification, region is required\n");
    //     char region = region_s();
    // }

    else {
        printf("Function not found!\n");
        user_error();
    }
    return 0;
}

void user_error(void) {
    printf("\nThis program ran into an error!\n");
    printf("Restarting Program");
    for (int i = 0; i < 3; i++) {
        Sleep(400);
        printf(".");
    }
    printf("\n");
    main();
}

char region_s(void) {
    char region = '\0';
    printf("Please select 'A' if in Asia, or 'O' if in any other region: ");
    scanf(" %c", &region);
    if (region != 'A' && region != 'O') {
        user_error();
    }
    return region;
}

char gender_s(void) {
    char gender = '\0';
    printf("Please select 'M' if Male, or 'F' if Female: ");
    scanf(" %c", &gender);
    if (gender != 'M' && gender != 'F') {
        user_error();
    }
    return gender;
}

int age_s(void) {
    int age = 0;
    printf("Age: ");
    scanf("%d", &age);
    if (age == 0) {
        user_error();
    }
    return age;
}

char unit_s(void) {
    char unit = '\0';
    printf("Please select 'M' to use Metric, or 'I' to use Imperial: ");
    scanf(" %c", &unit);
    if (unit != 'M' && unit != 'I') {
        user_error();
    }
    printf("For calculation purposes following will be assumed from here onwards,\n");
    printf("1. all lengths in Metric are in Meters\n");
    Sleep(300);
    printf("2. all lengths in Imperial are in Inches\n");
    Sleep(300);
    printf("3. all weight measurements in Metric are in KiloGrams\n");
    Sleep(300);
    printf("4. all weight measurements in Imperial are in Pounds\n");
    Sleep(2000);
    return unit;
}

float height_col(void) {
    float height = 0.0f;
    printf("Height: ");
    scanf("%f", &height);
    if (height == 0.0f) {
        user_error();
    }
    return height;
}

float weight_col(void) {
    float weight = 0.0f;
    printf("Weight: ");
    scanf("%f", &weight);
    if (weight == 0.0f) {
        user_error();
    }
    return weight;
}

float waist_col(void) {
    float waist = 0.0f;
    printf("Waist Circumference: ");
    scanf("%f", &waist);
    if (waist == 0.0f) {
        user_error();
    }
    return waist;
}

float hipc_col(void) {
    float hipc = 0.0f;
    printf("Hip Circumference: ");
    scanf("%f", &hipc);
    if (hipc == 0.0f) {
        user_error();
    }
    return hipc;
}

float bmi_calc(float height, float weight, char unit) {
    float bmi = 0.0f;
    if (unit == 'I') {
        bmi = (weight/LBS_TO_KG) / ((height/INCHES_TO_METERS) * (height/INCHES_TO_METERS));
    }
    else if (unit == 'M') {
        bmi = weight / (height * height);
    }
    else {
        user_error();
    }
    return bmi;
}

float bai_calc(float height, float hipc, char unit) {
    float bai = 0.0f;
    if (unit == 'I') {
        bai = ((hipc/INCHES_TO_METERS)*100.0f) / pow(height, 1.5) - 18.0f;
    }
    else if (unit == 'M') {
        bai = (hipc*100.0f) / pow(height, 1.5f) - 18.0f;
    }
    else {
        user_error();
    }
    return bai;
}

float whr_calc(float hipc, float waist, char unit) {
    float whr = 0.0f;
    if (unit == 'I' || unit == 'M') {
        whr = waist / hipc;
    }
    else {
        user_error();
    }
    return whr;
}

void bmi_class(char gender, char region, int age, float bmi) {
    if (age <= 18) {
        printf("No classification can be done for users below 18\n");
    }
    else if (region == 'G') {
        if (bmi <= 18.5) {
            printf("You are classified as Underweight\n");
        }
        else if (bmi < 25 && bmi >= 18.5) {
            printf("You are classified as Normal\n");
        }
        else if (bmi < 30 && bmi >= 25) {
            printf("You are classified as Overweight\n");
        }
        else if (bmi >= 30) {
            printf("You are classified as Obese\n");
        }
        else {
            user_error();
        }
    }
    else if (region == 'A') {
        if (bmi <= 18.5) {
            printf("You are classified as Underweight\n");
        }
        else if (bmi < 23 && bmi >= 18.5) {
            printf("You are classified as Normal\n");
        }
        else if (bmi < 27 && bmi >= 23) {
            printf("You are classified as Overweight\n");
        }
        else if (bmi >= 27) {
            printf("You are classified as Obese\n");
        }
        else {
            user_error();
        }
    }
    else {
        user_error();
    }
}

void bai_class(char gender, int age, float bai) {
    if (age <= 18) {
        printf("No classification can be done for users below 18\n");
    }
    else if (gender == 'M') {
        if (age < 40) {
            if (bai < 8) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 21 && bai >= 8) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 26 && bai >= 21) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else if (age < 60) {
            if (bai < 11) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 23 && bai >= 11) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 29 && bai >= 23) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else if (age > 60) {
            if (bai < 13) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 25 && bai >= 13) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 31 && bai >= 25) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else {
            user_error();
        }
    }
    else if (gender == 'F') {
        if (age < 40) {
            if (bai < 21) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 33 && bai >= 21) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 39 && bai >= 33) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else if (age < 60) {
            if (bai < 23) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 35 && bai >= 23) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 41 && bai >= 35) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else if (age > 60) {
            if (bai < 25) {
                printf("You are classified as Underweight\n");
            }
            else if (bai < 38 && bai >= 25) {
                printf("You are classified as Healthy\n");
            }
            else if (bai < 43 && bai >= 38) {
                printf("You are classified as Overweight\n");
            }
            else {
                printf("You are classified as Obese\n");
            }
        }
        else {
            user_error();
        }
    }
}

void whr_class(char gender, int age, float whr) {
    char *label = "Default";
    if (gender == 'M') {
        if (whr <= 0.95) {
            label = "low health risk";
        }
        else if (whr <= 1.0) {
            label = "moderate health risk";
        }
        else {
            label = "high health risk";
        }
    }
    else if (gender == 'F') {
        if (whr <= 0.80) {
            label = "low health risk";
        }
        else if (whr <= 0.85) {
            label = "moderate health risk";
        }
        else {
            label = "high health risk";
        }
    }
    printf("You are classified as having a '%s'\n", label);
}

void end_program(void) {
    printf("Thank you for using LemonHealth!\n");
    printf("Enter 'X' to exit, or enter 'C' to restart program:  ");
    char end_choice = '\0';
    scanf(" %c", &end_choice);
    if (end_choice == 'X' || end_choice == 'x') {
        exit(0);
    }
    if (end_choice == 'C' || end_choice == 'c') {
        printf("Restarting Program");
        for (int i = 0; i < 3; i++) {
            Sleep(400);
            printf(".");
        }
        printf("\n");
        main();
    }
    else {
        user_error();
    }
}