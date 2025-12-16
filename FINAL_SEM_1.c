#include <stdio.h>
#include <string.h>

typedef struct {
    char date_str[20]; 
    int d, m, y;      
    float temp_c;   
    float temp_f;     
} Record;


void input_data( Record arr[], int *count, char *unit_choice);
void process_data( Record arr[], int count, char unit_choice);
void write_file( Record arr[], int count);

int main() {
     Record logs[100]; 
    int n = 0;              
    char unit;               

    printf(" Weather Data Logger Started \n");

    input_data(logs, &n, &unit);

    process_data(logs, n, unit);

    write_file(logs, n);

    return 0;
}

void input_data( Record arr[], int *count, char *unit_choice) {
    char temp_input[50];
    float temp_val;

    printf("Choose Input Format for this session (c/f): ");
    scanf(" %c", unit_choice);
    getchar(); 

    printf("\nType (exit) to stop.\n");

    while (1) { 
        if (*count >= 100) {
            printf("You have used up all available space , Memory Full !.\n");
            break;
        }
        printf("\nEnter Date (DD.MM.YY): ");
        fgets(temp_input, 50, stdin);
        
        temp_input[strcspn(temp_input, "\n")] = 0;
        if (strcmp(temp_input, "exit") == 0) {
            break;
        }
//*count provides the index number by looking inside the pointer to see the current count
        strcpy(arr[*count].date_str, temp_input);

        sscanf(temp_input, "%d.%d.%d", &arr[*count].d, &arr[*count].m, &arr[*count].y);

        printf("Enter Temperature: ");
        scanf("%f", &temp_val);
        getchar();

        if (*unit_choice == 'c' || *unit_choice == 'C') {
            arr[*count].temp_c = temp_val;
        } else {
            arr[*count].temp_f = temp_val;
        }

   
        (*count)++; 
    }
}

void process_data( Record arr[], int count, char unit_choice) {
    
    for(int i = 0; i < count; i++) {
        if (unit_choice == 'c' || unit_choice == 'C') {
          
            arr[i].temp_f = (arr[i].temp_c * 1.8) + 32;
        } else {
      
            arr[i].temp_c = (arr[i].temp_f - 32) / 1.8;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            
            int swap_needed = 0;

            if (arr[j].y > arr[j+1].y) {
                swap_needed = 1;
            } 
           
            else if (arr[j].y == arr[j+1].y && arr[j].m > arr[j+1].m) {
                swap_needed = 1;
            }
            
            else if (arr[j].y == arr[j+1].y && arr[j].m == arr[j+1].m && arr[j].d > arr[j+1].d) {
                swap_needed = 1;
            }

            if (swap_needed) {
              
                 Record temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void write_file( Record arr[], int count) {
    FILE *fptr = fopen("weather_logger_file.txt", "w");

    if (fptr == NULL) {
        printf("Error creating file!\n");
        return;
    }

    fprintf(fptr, " ____________________________________________________ \n");
    fprintf(fptr, "|    S.No    |      Date      |      Temperature     |\n");
    fprintf(fptr, "|----------------------------------------------------|\n");

  
    for (int i = 0; i < count; i++) {
       
        fprintf(fptr, "|     %-7d|    %-12s|  %6.1f*c / %6.1f*f |\n", 
                i + 1, 
                arr[i].date_str, 
                arr[i].temp_c, 
                arr[i].temp_f);
        
        
        fprintf(fptr, "|            |                |                      |\n");
    }

   
    fprintf(fptr, "|____________________________________________________|\n");

    fclose(fptr);
    printf("\nData successfully processed and written to 'weather_logger_file.txt'.\n");
}