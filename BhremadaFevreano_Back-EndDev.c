#include <stdio.h>
#include <string.h>

void calculate(double num1, char operator, double num2);
int isint(double num);
double modulo(double num1, double num2);
void remove_trailing_zeros(char* numStr);
void display_decimal(double num);

#define GREEN_BOLD "\033[1;32m"
#define WHITE_BOLD "\033[1;37m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET_COLOR "\033[0m"

int main() {
    printf(GREEN_BOLD "Kalkulator BNCC\n" RESET_COLOR);
    printf(WHITE_BOLD "Made with love by Bhremada Fevreano\n" RESET_COLOR);
    printf("\n");

    printf("Format: <angka1> <operator> <angka2>, Contoh: 1 + 1\n");
    printf("List operator:\n");
    printf("  + : Penjumlahan\n");
    printf("  - : Pengurangan\n");
    printf("  x : Perkalian\n");
    printf("  / : Pembagian\n");
    printf("  %% : Modulus\n");
    printf("Ketik q untuk keluar\n");
    printf("\n");

    int is_running = 1;

    while (is_running) {
        char input[100];
        double num1, num2;
        char operator;

        printf("> ");

        // read input as string
        fgets(input, sizeof(input), stdin);

        // if input is q, exit the program
        if (strcmp(input, "q\n") == 0) {
            is_running = 0;
            break;
        }

        // if input is empty, continue
        if (strcmp(input, "\n") == 0) {
            continue;
        }

        // parse the user input
        int count = sscanf(input, "%lf %c %lf", &num1, &operator, & num2);  // string scanf, reads from string instead of stdin

        printf("  ");

        if (count != 3) {
            printf(RED "Input tidak valid" RESET_COLOR);
        } else {
            calculate(num1, operator, num2);
        }

        printf("\n");
    }

    return 0;
}

void calculate(double num1, char operator, double num2) {
    double result;

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;

        case '-':
            result = num1 - num2;
            break;

        case 'x':
        case '*':
            result = num1 * num2;
            break;

        case '/':
        case ':':
            if (num2 == 0) {
                printf(RED "Tidak bisa dibagi 0" RESET_COLOR);
                return;
            }
            result = num1 / num2;
            break;

        case '%':
            result = modulo(num1, num2);
            break;

        default:
            printf(RED "%c bukan operator yang valid" RESET_COLOR, operator);
            return;
    }

    printf(GREEN);

    if (isint(result)) {
        printf("%.0lf", result);
    } else {
        display_decimal(result);
    }

    printf(RESET_COLOR);
}

int isint(double num) {
    return num == (int)num;
}

double modulo(double num1, double num2) {
    while (num1 >= num2) {
        num1 -= num2;
    }
    return num1;
}

void remove_trailing_zeros(char* numStr) {
    int length = strlen(numStr);
    int dotIndex = -1;

    // Find the index of the decimal point if it exists
    for (int i = 0; i < length; i++) {
        if (numStr[i] == '.') {
            dotIndex = i;
            break;
        }
    }

    // Remove trailing zeros
    if (dotIndex != -1) {
        int i;
        for (i = length - 1; i > dotIndex; i--) {
            if (numStr[i] != '0') {
                break;
            }
        }
        if (numStr[i] == '.') {
            i--;
        }
        numStr[i + 1] = '\0';
    }
}

void display_decimal(double num) {
    char numStr[20];

    // change decimal number to string
    snprintf(numStr, sizeof(numStr), "%.15f", num);

    remove_trailing_zeros(numStr);
    printf("%s", numStr);
}