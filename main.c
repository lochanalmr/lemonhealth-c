#include <stdio.h>
#include <string.h>
#include <windows.h>

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
int bmi_class(char gender, char region, int age, float bmi);
int bai_class(char gender, int age, float bai);
int whr_class(char gender, int age, float whr);
void report_gen(void);
void user_error(void);

int main(void) {
    // Introduction
    printf("====== LemonHealth v1 =======\n");
    printf("\nSupported Options are BMI/ BAI/ WHR/ MM\n");
    printf("BMI: Body Mass Index\n");
    printf("BAI: Body Mass Index\n");
    printf("WHR: Waist to Hip Ratio\n");
    printf("MM: MultiMeasure for an overall health summary\n");

    // Option Selection
    printf("\nChoose an option: ");
    char choice[4];
    fgets(choice, 4, stdin);
    choice[strlen(choice) - 1] = '\0';

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
        int bmi_c = bmi_class(gender, region, age, bmi_val);
    }

    else if (strcmp(choice, "BAI") == 0) {
        printf("\n===BAI calculation & classification module===\n");
        // BAI calculation related data collection
        float height = height_col();
        float hipc = hipc_col();
    }

    else if (strcmp(choice, "WHR") == 0) {
        printf("\n===WHR calculation & classification module===\n");
        // WHR calculation related data collection
        float waist = waist_col();
        float hipc = hipc_col();
    }

    else if (strcmp(choice, "MM") == 0) {
        printf("\n===MultiMeasure calculation & classification module===\n");
        // MM related data collection
        float height = height_col();
        float weight = weight_col();
        float hipc = hipc_col();
        float waist = waist_col();

        // Additional fundamental data collection
        printf("For accurate BMI classification, region is required\n");
        char region = region_s();
    }

    else {
        user_error();
    }
    return 0;
}

void user_error(void) {
    printf("\nInvalid Input!\n");
    printf("Reloading Program...\n");
    Sleep(2000);
    main();
}

char region_s(void) {
    char region = '\0';
    printf("Please select 'A' if in Asia, or 'O' if in any other region: ");
    scanf("%c", &region);
    if (region != 'A' || region != 'O') {
        user_error();
    }
    return region;
}

char gender_s(void) {
    char gender = '\0';
    printf("Please select 'M' if Male, or 'F' if Female: ");
    scanf("%c", &gender);
    if (gender != 'M' || gender != 'F') {
        user_error();
    }
    return gender;
}

char unit_s(void) {
    char unit = '\0';
    printf("Please select 'M' to use Metric, or 'I' to use Imperial: ");
    scanf("%c", &unit);
    if (unit != 'M' || unit != 'F') {
        user_error();
    }
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
    if (unit == 'M') {
        bmi = weight / (height * height);
    }
    else if (unit == 'I') {
        bmi = height / (weight * weight);
    }
    return bmi;
}