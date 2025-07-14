#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 80 // max number of columns (characters per row)
#define MAX_HEIGHT 100 // max number of rows (number of lines)

// Function prototypes
void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels);
void compute_gradient(int image[MAX_HEIGHT][MAX_WIDTH], int width, int height, int grey_levels);

int main() { // This programme involves partially the function of the programme in task 1 (file labelled PARMARH-image1.c) it takes in numbers as input
    // and the numbers order results in a specific output of a 2d image made of characters determined by the width , height and grey levels (once again all based on order of numbers)
    // however for task 2, the code creates an outline of the image as opposed to the actual image its self to make it easier to understand: task 1 creates a
    // picture of a mountain whereas task 2 just creates the outline of the mountain , it does this by highlighting sudden changes in grey levels between characters
    // the numbers inputted organise themselves based on the width and height provided so it could be 3x3 or 4x3 and each characters grey level is also represented here by character
    // here like , if the numbers inputted create a 3x3 it could be represented by the following where each numbers is representation of the grey level (as opposed to the characters) :
    //   3 2 1
    //   2 1 0
    //   1 0 0
    // what the code does this is extract as many 2x2 blocks as possible from the 3x3 block so we would have the 4 blocks:
    //
    // block 1:       block 2:        block 3:       block 4:
    //   3 2            2 1            2 1            1 0
    //   2 1            1 0            1 0            1 0
    // each block is now consider for caucaltions using the formulas
    // int gh = abs((p1 - p2 + p3 - p4) / 2);
    //int gv = abs((p1 - p3 + p2 - p4) / 2);
    //int gp = abs(p1 - p4);
    //int gn = abs(p2 - p3);
    //
    //each formula calculates the gradient of the block horizontally  (gh) , vertically (gv) , diagonally (gp) and the opposite direction diagonally (gn)
    // the direction which creates the highest gradient is then selected to represent the whole block
    // keeping in mind the gradients can either 0 1 2 3 if there are 4 grey levels for examples and it differs for lower grey levels
    // the highest gradient selected then changes the 2x2 block of characters into one assigned character
    // the character is assigned through the use of the rules found in the spec "For the sake of clarity, reverse the grey-levels when printing the result"
    // if the grey levels were 4 normally value 0 1 2 3 correspond to # : . (space) however for choosing that one assigned character we reverse this
    // so if the highest gradient was 4 we would use # to represent that 2 x 2 block resulting in the assigned character of # as
    // we reversed the grey levels 3 2 1 0 which corresponds to (space) . : # therefore we choose the hastag , by converting these blocks into
    // a single assigned value we change the image into the outline of image essentially.

        int image[MAX_HEIGHT][MAX_WIDTH];
    int width, height, grey_levels;


    read_image(image, &width, &height, &grey_levels);// This Reads and store the image


    compute_gradient(image, width, height, grey_levels); // Compute and print the gradient image

    return 0;
}

void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels) { // The function read_image is responsible for decoding the inputted data and
    //storing the result into a image array
    //This peice of code specifically refers to the first 2 lines of code in this programme
    //about the max Height (80) and Max width (100) , here we are decalring a limit on the array that can be produced with the declaration being the array is large enough
    //to hold any image up to 100 rows and 80 columns, as per the assignment's allowed maximum. This is known as static allocation memory.

    int total_characters; // This stores the number of characters in the image which is calculated below with total_characters = (*width) * (*height);
    int character_greylevel, character_count; // character_greylevel = character grey level, character_count = how many times to repeat it
    int row = 0, col = 0; // These keep track of where to place the next character in the array row starts at 0 (top row of image) col starts at 0 (leftmost column)

    scanf("%d %d %d", width, height, grey_levels);
    total_characters = (*width) * (*height);

    for (int i = 0; i < total_characters; ) { //This loop keeps track of how many total characters have been filled so far. i keeps track of how many characters have been written.
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

        i += character_count; //This updates the counter so the outer loop knows when we've finished filling the image.


    }
}

void compute_gradient(int image[MAX_HEIGHT][MAX_WIDTH], int width, int height, int grey_levels) { // This function Computes a gradient for each 2×2 pixel block to detect edges.
// It prints a new image, where each pixel shows how much the image changes at that location it uses reversed grey level characters to print: more change = darker character



    int gradient[MAX_HEIGHT][MAX_WIDTH]; // This array stores the calculated gradient values (edges).
    //it is initially empty (0 x 0), and gets filled as values are computed through calculations.
    for (int row = 0; row < height - 1; row++) { // This double for loop goes through each starting point of a 2×2 block.
        for (int col = 0; col < width - 1; col++) {// We stop at height - 1 and width - 1 because we need to safely access each single point in the 2x2 block top and bottom left and right
            // going beyond would simply cause a error as these values would then fall out of bound.
            int p1 = image[row][col]; // these next four lines are used to get the grey level value of each possible character in the 2 x 2 so top and bottom left and right
            int p2 = image[row][col + 1];
            int p3 = image[row + 1][col];
            int p4 = image[row + 1][col + 1];

            int gh = abs((p1 - p2 + p3 - p4) / 2); // This formula measures the change from left to right, p1 - p2 represents the top row horizontal change  p3 - p4 represents the bottom row horizontal change
            // these are then averaged together and made positive with abs()
            int gv = abs((p1 - p3 + p2 - p4) / 2); // This formula measures change top to bottom. p1 - p3 represents the left column vertical change p2 - p4 represents the right column vertical change
            int gp = abs(p1 - p4);// This formula measures the change from top-left to bottom-right it is the diagonal gradient
            int gn = abs(p2 - p3);// This formula measures the change from top-right to bottom-left it is the diagonal gradient

            int max_grad = gh; // we now compare all 4 directions and keep the largest gradient value of the 4 directions we only use the largest value as that represents the strongest edge of that block
            if (gv > max_grad) max_grad = gv;
            if (gp > max_grad) max_grad = gp;
            if (gn > max_grad) max_grad = gn;

            gradient[row][col] = max_grad; // we are storing the grey level value (a number) in the gradient image specifically at a row and a column for example in row 0 column 1
        }
    }


    for (int row = 0; row < height - 1; row++) {// Now the for loop goes through the gradient image to print it.
// Since each gradient was calculated from a 2x2 block,
// the gradient image is one row and one column smaller than the original.
// This loop visits each (row, col) position in the gradient array hence the height -1 and width -1

        for (int col = 0; col < width - 1; col++) {
            int character = gradient[row][col];// This gets the gradient value (0 to 3) at this position.
// it represents how strong the edge is in that 2x2 block.
// this is then converted into a character (like ' ', '.', ':', or '#')


            if (grey_levels == 2) { // This converts the gradient value into a character using reversed grey-level mapping (shown in above main function comments ).
// This allows the edges to be highlighted more clearly.
// 0 → ' ' (no change), 1 → '.', 2 → ':', 3 → '#' (strongest edge).
// The higher the gradient, the darker the symbol according to grey value system.

                putchar(character == 0 ? ' ' : '#');
            } else if (grey_levels == 3) {
                if (character == 0) putchar(' ');
                else if (character == 1) putchar('.');
                else putchar('#');
            } else if (grey_levels == 4) {
                if (character == 0) putchar(' ');
                else if (character == 1) putchar('.');
                else if (character == 2) putchar(':');
                else putchar('#');
            }
        }
        putchar('\n'); // This Moves to the next line after printing one full row of characters.
// This ensures the gradient image is displayed correctly row by row.

    }
}
