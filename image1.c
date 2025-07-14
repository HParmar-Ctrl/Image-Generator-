#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 80 // max number of columns (characters per row)
#define MAX_HEIGHT 100 // max number of rows (number of lines)

void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels); // Reads a run-length encoded image and expands it into a 2D array
void print_image(int image[MAX_HEIGHT][MAX_WIDTH], int width, int height, int grey_levels); // Prints the image using characters according to grey level rules

int main() { // This whole page of code allows user to generate a image that is created purely from characters as such as (. , : #) by inputting numbers , the user's
    // first three numbers inputted represents the (<width> <height> <grey‑levels>) in order so the first=width and second=height third=number of grey levels the user wants
    // the width and height represent how tall and wide the picture is going to be if we had the first number as 4 and the seocnd number as 5 there will be a total
    // of 20 characters present for the output of this code and it will be 5 rows of 4 charcters, the third numbers tells us how many grey levels we would like the smallest
    // number that can be chosen for this is 2 which means there will be 2 different levels , 3 means there will be three different grey levels , the maximum number
    // that can be chosen is 4 there are 4 grey levels here , (this next part will make sense just keep reading ) if 2 was chosen the the grey levels can either 0 (black) or 1(white)
    // if 3 was chosen as the grey levels can be either 0(black) 1(grey) 2(white) if 4 was chosen as the grey levels can be either 0(black) 1(dark grey) 2(light grey) 3(white),
    // If grey-levels = 2, the character values will be 0 or 1:
    //   0 is printed as '#' (black), and 1 is printed as ' ' (white).
    // If grey-levels = 3, the character values will be 0, 1, or 2:
    //   0 is printed as '#' (black), 1 as '.' (grey), and 2 as ' ' (white).
    // If grey-levels = 4 (the maximum), the character values will be 0, 1, 2, or 3:
    //   0 is printed as '#' (black), 1 as ':' (dark grey), 2 as '.' (light grey), and 3 as ' ' (white).
    // this is the definition of the first 3 numbers , now after that the numbers work in pairs <pix1> <len1>   <pix2> <len2>   <pix3> <len3>
    // Each <pix> is a grey‑level value (0 up to grey‑levels−1), and <len> tells you how many times that character repeats in a row, this repeats until all characters are filled in
    // if width and height was 4 and 5 respectively then the all the lens of the pairs should add up to 20 (4 x 5). the numbers should have a space between them.

    int image[MAX_HEIGHT][MAX_WIDTH];
    int width, height, grey_levels;

    // Read and store the image
    read_image(image, &width, &height, &grey_levels);

    // Print the decoded image
    print_image(image, width, height, grey_levels);

    return 0;
}

// Reads a run-length encoded image and expands it into a 2D array
void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels) { //The function read_image is responsible for decoding the inputted data and
    //storing the result into a image array
    //This peice of code specifically refers to the first 2 lines of code in this programme
    // about the max Height (80) and Max width (100) , here we are decalring a limit on the array that can be produced with the declaration being the array is large enough
    // to hold any image up to 100 rows and 80 columns, as per the assignment's allowed maximum. This is known as static allocation memory.

    int total_characters; // This stores the number of characters in the image which is calculated below with total_characters = (*width) * (*height);
    int character_greylevel, character_count; // character_greylevel = character grey level, character_count = how many times to repeat it
    int row = 0, col = 0; // These keep track of where to place the next character in the array row starts at 0 (top row of image) col starts at 0 (leftmost column)

    scanf("%d %d %d", width, height, grey_levels);
    total_characters = (*width) * (*height);

    for (int i = 0; i < total_characters; ) { // This loop keeps track of how many total characters have been filled so far. i keeps track of how many characters have been written.
        // scanf("%d %d", &character_greylevel, &character_count); reads two numbers: the grey level (character_greylevel) and How many times it is to be repeated (character_count).

        scanf("%d %d", &character_greylevel, &character_count);

        for (int j = 0; j < character_count; j++) { // The inner loop repeats character greylevel exactly character count times.
            image[row][col] = character_greylevel;
            col++;
            if (col >= *width) {
                col = 0;
                row++;
            }
        }

        i += character_count;
    }
}

void print_image(int image[MAX_HEIGHT][MAX_WIDTH], int width, int height, int grey_levels) { // The function takes the image array and prints it to the screen, converting grey level values into its assigned characters
    for (int row = 0; row < height; row++) { // This for loop goes from top to bottom of the image (through every row)
        for (int col = 0; col < width; col++) { // This for loop goes left to right across a row. (through every column)
            int character = image[row][col]; // This considers the grey level of the current character

            if (grey_levels == 2) {
                putchar(character == 0 ? '#' : ' ');
            } else if (grey_levels == 3) {
                if (character == 0) putchar('#');
                else if (character == 1) putchar('.');
                else putchar(' ');
            } else if (grey_levels == 4) {
                if (character == 0) putchar('#');
                else if (character == 1) putchar(':');
                else if (character == 2) putchar('.');
                else putchar(' ');
            }
        }
        putchar('\n');//  this starts a new line after printing a row so that the image appears coorecly as opposed to on one line
    }
}
