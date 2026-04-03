#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>


const double LBS_TO_KG = 2.20462;
const double INCHES_TO_METERS = 39.3701;

// BMI Thresholds (Global/Other)
const double BMI_UNDERWEIGHT = 18.5;
const double BMI_NORMAL_MAX = 25.0;
const double BMI_OVERWEIGHT_MAX = 30.0;

// BMI Thresholds (Asia)
const double BMI_ASIA_NORMAL_MAX = 23.0;
const double BMI_ASIA_OVERWEIGHT_MAX = 27.0;

int age_s(void);
char gender_s(void);
char region_s(void);
char unit_s(void);
double height_col(void);
double weight_col(void);
double hipc_col(void);
double waist_col(void);
double bmi_calc(double height, double weight, char unit);
double bai_calc(double height, double hipc, char unit);
double whr_calc(double hipc, double waist, char unit);
double rfm_calc(double height, double waist, char gender);
double whtr_calc(double height, double waist);
const char* bmi_class(char gender, char region, int age, double bmi);
const char* bai_class(char gender, int age, double bai);
const char* whr_class(char gender, int age, double whr);
const char* rfm_class(char gender, double rfm);
const char* whtr_class(double whtr);

void report_gen(void);
void user_error(void);
int end_program(void); // Returns 1 to restart, 0 to exit
void clear_input_buffer(void);

int main(void) {
    int restart = 0;
    do {
        // Introduction
        printf("===========================\n");
        printf("   LemonHealth v1.10\n");
        printf("===========================\n");
        printf("\nSupported Options are:\n");
        printf("BMI: Body Mass Index\n");
        printf("BAI: Body Adiposity Index\n");
        printf("WHR: Waist to Hip Ratio\n");
        printf("RFM: Relative Fat Mass\n");
        printf("WHtR: Waist to Height Ratio\n");
        printf("MM: MultiMeasure (Report of supported functions)\n");

        // Option Selection
        printf("\nChoose an option: ");
        char choice[10];
        if (fgets(choice, sizeof(choice), stdin) == NULL) break;
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
            double height = height_col();
            double weight = weight_col();

            // BMI calculation module run
            double bmi_val = bmi_calc(height, weight, unit);
            printf("Classification: %s\n", bmi_class(gender, region, age, bmi_val));
            restart = end_program();

        }

        else if (strcmp(choice, "BAI") == 0) {
            printf("\n===BAI calculation & classification module===\n");
            // BAI calculation related data collection
            double height = height_col();
            double hipc = hipc_col();

            // BAI calculation module run
            double bai_val = bai_calc(height, hipc, unit);
            printf("Classification: %s\n", bai_class(gender, age, bai_val));
            restart = end_program();

        }

        else if (strcmp(choice, "WHR") == 0) {
            printf("\n===WHR calculation & classification module===\n");
            // WHR calculation related data collection
            double waist = waist_col();
            double hipc = hipc_col();

            // WHR calculation module run
            double whr_val = whr_calc(hipc, waist, unit);
            printf("Classification: %s\n", whr_class(gender, age, whr_val));
            restart = end_program();

        }

        else if (strcmp(choice, "RFM") == 0) {
            printf("\n===RFM calculation & classification module===\n");
            // RFM calculation related data collection
            double height = hipc_col();
            double waist = waist_col();

            // RFM calculation module run
            double rfm_val = rfm_calc(height, waist, gender);
            printf("Classification: %s\n", rfm_class(gender, rfm_val));
            restart = end_program();

        }

        else if (strcmp(choice, "WHtR") == 0) {
            printf("\n===WHtR calculation & classification module===\n");
            // WHtR calculation related data collection
            double waist = waist_col();
            double height = height_col();

            // WHtR calculation module run
            double whtr_val = whtr_calc(height, waist);
            printf("Classification: %s\n", whtr_class(whtr_val));
            restart = end_program();

        }

        else if (strcmp(choice, "MM") == 0) {
            printf("\n===MM calculation & classification module===\n");

            // BAI calculation related data collection
            double height = height_col();
            double weight = weight_col();
            double waist = waist_col();
            double hipc = hipc_col();
            printf("For accurate BMI classification, region is required\n");
            char region = region_s();

            // MM calculation module run
            double bmi_val = bmi_calc(height, weight, unit);
            double bai_val = bai_calc(height, hipc, unit);
            double whr_val = whr_calc(hipc, waist, unit);
            double rfm_val = rfm_calc(height, waist, gender);
            double whtr_val = whtr_calc(height, waist);

            // Get strings for classifications
            const char* bmi_clas = bmi_class(gender, region, age, bmi_val);
            const char* bai_clas = bai_class(gender, age, bai_val);
            const char* whr_clas = whr_class(gender, age, whr_val);
            const char* rfm_clas = rfm_class(gender, rfm_val);
            const char* whtr_clas = whtr_class(whtr_val);

            // MM report on display
            printf("\n=====LemonHealth MultiMeasure Report======\n");
            printf("BMI: %lf\n", bmi_val);
            printf("Classification: %s\n", bmi_clas);
            printf("BAI: %lf\n", bai_val);
            printf("Classification: %s\n", bai_clas);
            printf("WHR: %lf\n", whr_val);
            printf("Classification: %s\n", whr_clas);
            printf("RFM: %lf\n", rfm_val);
            printf("Classification: %s\n", rfm_clas);
            printf("WHtR: %lf\n", whtr_val);
            printf("Classification: %s\n", whtr_clas);

            // File Export Logic
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            char timestamp[20];
            char filename[50];
            strftime(timestamp, sizeof(timestamp), "%Y%m%d-%H%M%S", tm_info);
            sprintf(filename, "lh-mm-report-%s.txt", timestamp);

            FILE *fptr = fopen(filename, "w");
            if (fptr == NULL) {
                printf("\nError: Could not create report file.\n");
            } else {
                fprintf(fptr, "========LemonHealth MultiMeasure Report========\n\n");
                fprintf(fptr, "Provided Inputs:\n");
                fprintf(fptr, "Age: %d\n", age);
                fprintf(fptr, "Gender: %s\n", (gender == 'M' ? "Male" : "Female"));
                fprintf(fptr, "Region: %s\n", (region == 'A' ? "Asia" : "Global/Other"));
                fprintf(fptr, "Units: %s\n", (unit == 'M' ? "Metric" : "Imperial"));
                fprintf(fptr, "Weight: %.2f\n", weight);
                fprintf(fptr, "Height: %.2f\n", height);
                fprintf(fptr, "Waist: %.2f\n", waist);
                fprintf(fptr, "Hip Circumference: %.2f\n\n", hipc);

                fprintf(fptr, "=====Classifications=====\n");
                fprintf(fptr, "BMI Value: %lf\n", bmi_val);
                fprintf(fptr, "BMI Classification: %s\n", bmi_clas);
                fprintf(fptr, "BAI Value: %lf\n", bai_val);
                fprintf(fptr, "BAI Classification: %s\n", bai_clas);
                fprintf(fptr, "WHR Value: %lf\n", whr_val);
                fprintf(fptr, "WHR Classification: %s\n", whr_clas);
                fprintf(fptr, "RFM Value: %lf\n", rfm_val);
                fprintf(fptr, "RFM Classification: %s\n", rfm_clas);
                fprintf(fptr, "WHtR Value: %lf\n", whtr_val);
                fprintf(fptr, "WHtR Classification: %s\n\n", whtr_clas);

                char footer_time[30];
                strftime(footer_time, sizeof(footer_time), "%Y-%m-%d %H:%M:%S", tm_info);
                fprintf(fptr, "Report Generated on: %s\n", footer_time);
                fclose(fptr);
                printf("\nReport successfully exported to: %s\n", filename);
            }

            restart = end_program();
        }


        else {
            printf("\nFunction '%s' not found!\n", choice);
            user_error();
            restart = 1; // Restart after error
        }
    } while (restart);

    return 0;
}

void user_error(void) {
    printf("\n\nThis program ran into an error!\n");
    printf("Restarting Program");
    for (int i = 0; i < 3; i++) {
        Sleep(400);
        printf(".");
    }
    printf("\n");
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char region_s(void) {
    char region = '\0';
    while (1) {
        printf("Please select 'A' if in Asia, or 'O' if in any other region: ");
        if (scanf(" %c", &region) == 1 && (region == 'A' || region == 'O')) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. ");
    }
    return region;
}

char gender_s(void) {
    char gender = '\0';
    while (1) {
        printf("Please select 'M' if Male, or 'F' if Female: ");
        if (scanf(" %c", &gender) == 1 && (gender == 'M' || gender == 'F')) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. ");
    }
    return gender;
}

int age_s(void) {
    int age = 0;
    while (1) {
        printf("Age: ");
        if (scanf("%d", &age) == 1 && age > 0) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. Please enter a positive integer for age.\n");
    }
    return age;
}

char unit_s(void) {
    char unit = '\0';
    while (1) {
        printf("Please select 'M' to use Metric, or 'I' to use Imperial: ");
        if (scanf(" %c", &unit) == 1 && (unit == 'M' || unit == 'I')) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. ");
    }

    printf("For calculation purposes following will be assumed from here onwards,\n");
    printf("1. all lengths in Metric are in Meters\n");
    Sleep(300);
    printf("2. all lengths in Imperial are in Inches\n");
    Sleep(300);
    printf("3. all weight measurements in Metric are in KiloGrams\n");
    Sleep(300);
    printf("4. all weight measurements in Imperial are in Pounds\n");
    printf("Take this time to read this");
    for (int i = 0; i < 3; i++) {
        Sleep(400);
        printf(".");
    }
    printf("\n");
    return unit;
}

double height_col(void) {
    double height = 0.0;
    while (1) {
        printf("Height: ");
        if (scanf("%lf", &height) == 1 && height > 0) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. Please enter a positive number for height.\n");
    }
    return height;
}

double weight_col(void) {
    double weight = 0.0;
    while (1) {
        printf("Weight: ");
        if (scanf("%lf", &weight) == 1 && weight > 0) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. Please enter a positive number for weight.\n");
    }
    return weight;
}

double waist_col(void) {
    double waist = 0.0;
    while (1) {
        printf("Waist Circumference: ");
        if (scanf("%lf", &waist) == 1 && waist > 0) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. Please enter a positive number for waist.\n");
    }
    return waist;
}

double hipc_col(void) {
    double hipc = 0.0;
    while (1) {
        printf("Hip Circumference: ");
        if (scanf("%lf", &hipc) == 1 && hipc > 0) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();
        printf("Invalid input. Please enter a positive number for hip circumference.\n");
    }
    return hipc;
}

double bmi_calc(double height, double weight, char unit) {
    double bmi = 0.0;
    if (unit == 'I') {
        bmi = (weight / LBS_TO_KG) / ((height / INCHES_TO_METERS) * (height / INCHES_TO_METERS));
    }
    else if (unit == 'M') {
        bmi = weight / (height * height);
    }
    else {
        user_error();
    }
    return bmi;
}

double bai_calc(double height, double hipc, char unit) {
    double bai = 0.0;
    if (unit == 'I') {
        bai = ((hipc / INCHES_TO_METERS) * 100.0) / pow(height, 1.5) - 18.0;
    }
    else if (unit == 'M') {
        bai = (hipc * 100.0) / pow(height, 1.5) - 18.0;
    }
    else {
        user_error();
    }
    return bai;
}

double whr_calc(double hipc, double waist, char unit) {
    double whr = 0.0;
    if (unit == 'I' || unit == 'M') {
        if (hipc == 0.0) return 0.0;
        whr = waist / hipc;
    }
    else {
        user_error();
    }
    return whr;
}

const char* bmi_class(char gender, char region, int age, double bmi) {
    if (age <= 18) {
        return "N/A (Classification cannot be done for users below 18)";
    }
    else if (region == 'O') { // Global standards
        if (bmi <= BMI_UNDERWEIGHT) {
            return "Underweight";
        }
        else if (bmi < BMI_NORMAL_MAX && bmi > BMI_UNDERWEIGHT) {
            return "Normal";
        }
        else if (bmi < BMI_OVERWEIGHT_MAX && bmi >= BMI_NORMAL_MAX) {
            return "Overweight";
        }
        else if (bmi >= BMI_OVERWEIGHT_MAX) {
            return "Obese";
        }
        else {
            user_error();
            return "Error";
        }
    }
    else if (region == 'A') { // Asian standards
        if (bmi <= BMI_UNDERWEIGHT) {
            return "Underweight";
        }
        else if (bmi < BMI_ASIA_NORMAL_MAX && bmi > BMI_UNDERWEIGHT) {
            return "Normal";
        }
        else if (bmi < BMI_ASIA_OVERWEIGHT_MAX && bmi >= BMI_ASIA_NORMAL_MAX) {
            return "Overweight";
        }
        else if (bmi >= BMI_ASIA_OVERWEIGHT_MAX) {
            return "Obese";
        }
        else {
            user_error();
            return "Error";
        }
    }
    else {
        user_error();
        return "Error";
    }
}


const char* bai_class(char gender, int age, double bai) {
    if (age <= 18) {
        return "N/A (Classification cannot be done for users below 18)";
    }
    else if (gender == 'M') {
        if (age < 40) {
            if (bai < 8) return "Underweight";
            else if (bai < 21 && bai >= 8) return "Healthy";
            else if (bai < 26 && bai >= 21) return "Overweight";
            else return "Obese";
        }
        else if (age <= 60) {
            if (bai < 11) return "Underweight";
            else if (bai < 23 && bai >= 11) return "Healthy";
            else if (bai < 29 && bai >= 23) return "Overweight";
            else return "Obese";
        }
        else {
            if (bai < 13) return "Underweight";
            else if (bai < 25 && bai >= 13) return "Healthy";
            else if (bai < 31 && bai >= 25) return "Overweight";
            else return "Obese";
        }
    }
    else if (gender == 'F') {
        if (age < 40) {
            if (bai < 21) return "Underweight";
            else if (bai < 33 && bai >= 21) return "Healthy";
            else if (bai < 39 && bai >= 33) return "Overweight";
            else return "Obese";
        }
        else if (age <= 60 && age >= 40) {
            if (bai < 23) return "Underweight";
            else if (bai < 35 && bai >= 23) return "Healthy";
            else if (bai < 41 && bai >= 35) return "Overweight";
            else return "Obese";
        }
        else if (age > 60) {
            if (bai < 25) return "Underweight";
            else if (bai < 38 && bai >= 25) return "Healthy";
            else if (bai < 43 && bai >= 38) return "Overweight";
            else return "Obese";
        }
        else {
            user_error();
            return "Error";
        }
    }
    return "Error";
}


const char* whr_class(char gender, int age, double whr) {
    if (gender == 'M') {
        if (whr <= 0.95) return "Low health risk";
        else if (whr <= 1.0) return "Moderate health risk";
        else return "High health risk";
    }
    else if (gender == 'F') {
        if (whr <= 0.80) return "Low health risk";
        else if (whr <= 0.85) return "Moderate health risk";
        else return "High health risk";
    }
    return "Error";
}


int end_program(void) {
    printf("\nThank you for using LemonHealth!\n");
    printf("Enter 'X' to exit, or enter 'C' to restart program: ");
    char end_choice = '\0';
    if (scanf(" %c", &end_choice) != 1) {
        clear_input_buffer();
        return 0; // Exit on bad input
    }
    clear_input_buffer();
    if (end_choice == 'X' || end_choice == 'x') {
        return 0;
    }
    if (end_choice == 'C' || end_choice == 'c') {
        printf("Restarting Program");
        for (int i = 0; i < 3; i++) {
            Sleep(400);
            printf(".");
        }
        printf("\n\n");
        return 1;
    }
    else {
        user_error();
        return 1;
    }
}

double rfm_calc(double height, double waist, char gender) {
    double rfm;
    if (gender == 'M') {
        rfm = 64 - ((20 * height) / waist);
    }
    else {
        rfm = 76 - ((20 * height) / waist);
    }
    return rfm;
}

const char* rfm_class(char gender, double rfm) {
    if (gender == 'M') {
        if (rfm < 2) return "Extremely low fat";
        else if (rfm < 5) return "Essential fat";
        else if (rfm < 13) return "Athlete";
        else if (rfm < 17) return "Fitness";
        else if (rfm < 24) return "Average fat";
        else return "Obese";
    }
    else if (gender == 'F') {
        if (rfm < 10) return "Extremely low fat";
        else if (rfm < 13) return "Essential fat";
        else if (rfm < 20) return "Athlete";
        else if (rfm < 24) return "Fitness";
        else if (rfm < 31) return "Average fat";
        else return "Obese";
    }
    return "Error";
}


double whtr_calc(double height, double waist) {
    double whtr = height / waist;
    return whtr;
}

const char* whtr_class(double whtr) {
    if (whtr <= 0.4) return "Underweight";
    else if (whtr < 0.5) return "Healthy";
    else return "Overweight";
}
