#include <stdio.h>
#include <stdbool.h>

short program[256][8] = {
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 1, 0, 0},
    {1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

char selecter_name[8][4] = {
    {'r', 'e', 'g', '0'},
    {'r', 'e', 'g', '1'},
    {'r', 'e', 'g', '2'},
    {'r', 'e', 'g', '3'},
    {'r', 'e', 'g', '4'},
    {'r', 'e', 'g', '5'},
    {'i', 'n', 'p', '6'},
    {'o', 'u', 't', '6'}
};

short memory[6][8];

short counter = 0;

short get_program_length(void);

bool find_error(short code, short type);

bool run(void);

short decode(short[], short min, short max, bool sign);

int main(void) {
    short program_length = get_program_length();
    if (find_error(program_length, 0)) return -1;
    bool error = false;
    int limiter = 0;
    while ((counter >= 0 && counter < program_length) && limiter < 65536) {
        limiter++;
        if (run()) {
            error = true;
            break;
        };
    };
    if (limiter == 65536) {
        printf("Error: The number of executions has reached the maximum of 65536\n");
        return -1;
    };
    if (error) return -1;
    return 0;
};

short get_program_length(void) {
    bool end_code = false;
    bool one_only = true;
    short length = 0;
    for (short i = 0; i < 256; i++) {
        bool one_only = true;
        for (short j = 0; j < 8; j++) {
            if (find_error(program[i][j], 1)) return -2;
            if (program[i][j] == 0) one_only = false;
            if (j >= 7 && one_only) {
                end_code = true;
                length = i;
            };
        };
    };
    if (end_code == true) return ++length;
    return -1;
};

bool find_error(short code, short type) {
    switch (type) {
        case 0:
            if (code == -1) {
                printf("Error: End code not found\n");
                return true;
            } else if (code < -1) {
                return true;
            };
            break;
        case 1:
            if (code != 0 && code != 1) {
                printf("Error: Invalid code\n");
                return true;
            };
            break;
        case 2:
            if (code == 7) {
                printf("Error: Invalid selecter\n");
                return true;
            };
            break;
        default:
            printf("Error: Invalid error type\n");
            return true;
    };
    return false;
};

bool run(void) {
    short decoded = decode(program[counter], 0, 7, true);
    short first_selecter = decode(program[counter], 2, 4, false);
    short second_selecter = decode(program[counter], 5, 7, false);
    if (decoded == -1) {
        counter = -1;
        return false;
    };
    switch (decode(program[counter], 0, 1, false)) {
        case 0:
            for (short i = 0; i < 8; i++) memory[0][i] = program[counter][i];
            break;
        case 1:
            switch (second_selecter) {
                case 0:
                    for (short i = 0; i < 8; i++) {
                        if (memory[1][i] == 1 || memory[2][i] == 1) memory[3][i] = 1;
                        else memory[3][i] = 0;
                    };
                    break;
                case 1:
                    for (short i = 0; i < 8; i++) {
                        if (!(memory[1][i] == 1 && memory[2][i] == 1)) memory[3][i] = 1;
                        else memory[3][i] = 0;
                    };
                    break;
                case 2:
                    for (short i = 0; i < 8; i++) {
                        if (!(memory[1][i] == 1 || memory[2][i] == 1)) memory[3][i] = 1;
                        else memory[3][i] = 0;
                    };
                    break;
                case 3:
                    for (short i = 0; i < 8; i++) {
                        if (memory[1][i] == 1 && memory[2][i] == 1) memory[3][i] = 1;
                        else memory[3][i] = 0;
                    };
                    break;
                case 4:
                    for (short i = 0; i < 8; i++) memory[3][i] = 0;
                    for (short i = 7; i >= 0; i--) {
                        if (memory[1][i] == 1 && memory[2][i] == 1) {
                            if (memory[3][i] == 1) {
                                if (i != 0) memory[3][i-1] = 1;
                            } else {
                                memory[3][i] = 0;
                                if (i != 0) memory[3][i-1] = 1;
                            };
                        } else if (memory[1][i] == 1 || memory[2][i] == 1) {
                            if (memory[3][i] == 1) {
                                memory[3][i] = 0;
                                if (i != 0) memory[3][i-1] = 1;
                            } else memory[3][i] = 1;
                        };
                    };
                    break;
                case 5:
                    short complement[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                    short one[8] = {0, 0, 0, 0, 0, 0, 0, 1};
                    for (short i = 0; i < 8; i++) memory[3][i] = 0;
                    for (short i = 7; i >= 0; i--) {
                        if (one[i] == 1 && memory[2][i] == 0) {
                            if (complement[i] == 1) {
                                if (i != 0) complement[i-1] = 1;
                            } else {
                                complement[i] = 0;
                                if (i != 0) complement[i-1] = 1;
                            };
                        } else if (one[i] == 1 || memory[2][i] == 0) complement[i] = 1;
                    };
                    for (short i = 7; i >= 0; i--) {
                        if (memory[1][i] == 1 && complement[i] == 1) {
                            if (memory[3][i] == 1) {
                                if (i != 0) memory[3][i-1] = 1;
                            } else {
                                memory[3][i] = 0;
                                if (i != 0) memory[3][i-1] = 1;
                            };
                        } else if (memory[1][i] == 1 || complement[i] == 1) {
                            if (memory[3][i] == 1) {
                                memory[3][i] = 0;
                                if (i != 0) memory[3][i-1] = 1;
                            } else memory[3][i] = 1;
                        };
                    };
                    break;
            };
            break;
        case 2:
            if (find_error(first_selecter, 2) || find_error(second_selecter, 2)) return true;
            short first[8];
            short second[8];
            if (first_selecter == 6) {
                short selecter_index = second_selecter;
                char second_char[8];
                if (selecter_index == 6) selecter_index = 7;
                printf("%c%c%c%c?: ", selecter_name[selecter_index][0], selecter_name[selecter_index][1], selecter_name[selecter_index][2], selecter_name[selecter_index][3]);
                scanf(" %c%c%c%c%c%c%c%c", &second_char[0], &second_char[1], &second_char[2], &second_char[3], &second_char[4], &second_char[5], &second_char[6], &second_char[7]);
                for (short i = 0; i < 8; i++) {
                    if (second_char[i] == '0') second[i] = 0;
                    else if (second_char[i] == '1') second[i] = 1;
                    else {
                        printf("Error: Invalid number\n");
                        return true;
                    };
                };
                if (second_selecter == 6) {
                    printf("%c%c%c%c: %d%d%d%d%d%d%d%d, %d\n", selecter_name[first_selecter][0], selecter_name[first_selecter][1], selecter_name[first_selecter][2], selecter_name[first_selecter][3], second[0], second[1], second[2], second[3], second[4], second[5], second[6], second[7], decode(second, 0, 7, true));
                } else {
                    for (short i = 0; i < 8; i++) memory[second_selecter][i] = second[i];
                };
            } else {
                if (second_selecter == 6) {
                    printf("%c%c%c%c: %d%d%d%d%d%d%d%d, %d\n", selecter_name[first_selecter][0], selecter_name[first_selecter][1], selecter_name[first_selecter][2], selecter_name[first_selecter][3], memory[first_selecter][0], memory[first_selecter][1], memory[first_selecter][2], memory[first_selecter][3], memory[first_selecter][4], memory[first_selecter][5], memory[first_selecter][6], memory[first_selecter][7], decode(memory[first_selecter], 0, 7, true));
                } else {
                    for (short i = 0; i < 8; i++) memory[second_selecter][i] = memory[first_selecter][i];
                };
            };
            break;
        case 3:
            short jump = decode(memory[0], 0, 7, false);
            short value = decode(memory[3], 0, 7, true);
            switch (second_selecter) {
                case 1:
                    if (value == 0) counter = jump - 1;
                    break;
                case 2:
                    if (value < 0) counter = jump - 1;
                    break;
                case 3:
                    if (value <= 0) counter = jump - 1;
                    break;
                case 4:
                    counter = jump - 1;
                    break;
                case 5:
                    if (value != 0) counter = jump - 1;
                    break;
                case 6:
                    if (value >= 0) counter = jump - 1;
                    break;
                case 7:
                    if (value > 0) counter = jump - 1;
                    break;
            };
            break;
    };
    counter++;
    return false;
};

short decode(short code[], short min, short max, bool sign) {
    short result = 0;
    for (short i = min; i <= max; i++) {
        short power = 0;
        short cash = 0;
        for (short j = 0; j <= max - i; j++) {
            if (j == 0) power++; else power *= 2;
        };
        result += code[i] * power;
    };
    if (sign && result >= 128) result -= 256;
    return result;
};