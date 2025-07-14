#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 100
#define MAX_DOUBLE_WIDTH (2 * MAX_WIDTH - 1)
#define MAX_DOUBLE_HEIGHT (2 * MAX_HEIGHT - 1)

// Function prototypes
void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels);
void print_image(int image[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height, int grey_levels);
void double_image(int original[MAX_HEIGHT][MAX_WIDTH], int doubled[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height);
void smooth_image(int image[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height);

int main() {// This programme overall doubles the image it takes a smaller version of the image and doibles the size of the image so that it is stretched equally in all
    //directions , this occurs by the programme smoothing the image by changing grey values of some pixels so that it is more similar to the surrounding pixels using
    // a formula that is provided , then the final grey values are printed using reversed mapping for grey characters so that the brighter pixels appear
    //ligter and the dark appear darker so that it is almost like outlines so as opposed to 0= blank space and 1 = # we have 0= # and 1 = space
    // the programme involves the read image function from part 1 this simply reads the input and sorts the numbers into width height grey levels and type of character
    // and number of those charaters needed , the input is doubled through the function double image this essentially takes the dimensions of the image in to consideration
    // if we had a 4x4 image for example it will be doubled by adding rows between each value and columns between each value this eventually creates
    // a 9 x 9 image where there are empty spaces between the original values of the 4 by 4.
    // the blank (new) values in the doubled image are calculated by averaging surrounding original pixels:
    // horizontal blanks (even row, odd col) are averaged from the left and right original pixels.
    // vertical blanks (odd row, even col) are averaged from the pixels directly above and below.
    // diagonal blanks (odd row, odd col) are averaged from the four diagonal original pixels using (a + b + c + d + 1) / 4.
    // this order ensures that all new pixels are filled only after their surrounding values are already placed and we end up with a 9 x 9 image
    // once the image has been doubled to a 9x9 grid, it is smoothed to reduce harsh transitions between pixel grey values.
    // smoothing is done by applying a weighted average filter to each pixel (excluding the edges).
    // in each smoothing pass, a pixel is replaced by a weighted combination of its own value and its 8 surrounding neighbors (think of the pixel as the centre of a 3 x 3)
    // with more weight given to the center and adjacent pixels. This formula is applied three times,
    // gradually softening the image and making the transitions appear more natural when displayed as characters.
    // after the three smoothing iterations are complete, the final 9x9 image is printed to the screen.
    // each pixel's grey level (0 to 3) is converted into a corresponding ASCII character using reverse grey-level mapping:
    // '#' for 0 (darkest), ':' for 1, '.' for 2, and ' ' (space) for 3 (brightest).




    int image[MAX_HEIGHT][MAX_WIDTH];
    int doubled[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH];
    int width, height, grey_levels;


    read_image(image, &width, &height, &grey_levels); // Reads the original image (2 grey levels)


    double_image(image, doubled, width, height); // Doubles the image and convert to 4 grey levels


    for (int i = 0; i < 3; i++) {
        smooth_image(doubled, 2 * width - 1, 2 * height - 1);// Applies 3 iterations of smoothing
    }


    print_image(doubled, 2 * width - 1, 2 * height - 1, 4);// Prints the final smoothed image

    return 0;
}

void read_image(int image[MAX_HEIGHT][MAX_WIDTH], int *width, int *height, int *grey_levels) {// The function read_image is responsible for decoding the inputted data and
   // storing the result into a image array
   // this peice of code specifically refers to the first 2 lines of code in this programme
   // about the max Height (80) and Max width (100) , here we are decalring a limit on the array that can be produced with the declaration being the array is large enough
   // to hold any image up to 100 rows and 80 columns, as per the assignment's allowed maximum. This is known as static allocation memory.
    int total_characters; //  This stores the number of characters in the image which is calculated below with total_characters = (*width) * (*height);
    int character_greylevel, character_count;// character_greylevel = character grey level, character_count = how many times to repeat it
    int row = 0, col = 0;// These keep track of where to place the next character in the array row starts at 0 (top row of image) col starts at 0 (leftmost column)

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

void double_image(int original[MAX_HEIGHT][MAX_WIDTH], int doubled[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height) {
    int new_width = 2 * width - 1; // this code calculates the new dimensions for the doubled image by inserting a space between each original row and column.
// This results in a new image size of (2 × width − 1) by (2 × height − 1).

    int new_height = 2 * height - 1;

    for (int row = 0; row < height; row++) { // This Copies the original pixels into the doubled image at even row and column positions.
      // pixels with grey level value 1 are converted to 3 to match the 4-grey-level system; zeros remain unchanged.

        for (int col = 0; col < width; col++) {
            int value = original[row][col];
            if (value == 1) value = 3;
            doubled[2 * row][2 * col] = value;
        }
    }


    for (int row = 0; row < new_height; row += 2) { // These for loops Fill in the horizontal gaps by averaging the values of the left and right neighboring pixels.
    // these are positioned at even-numbered rows and odd-numbered columns in the doubled image.
    //it also fills in the vertical gaps by averaging the values of the pixels directly above and below.
   // these values are placed at odd-numbered rows and even-numbered columns in the doubled image.


        for (int col = 1; col < new_width; col += 2) {
            doubled[row][col] = (doubled[row][col - 1] + doubled[row][col + 1]) / 2;
        }
    }


    for (int row = 1; row < new_height; row += 2) {
        for (int col = 0; col < new_width; col++) {
            doubled[row][col] = (doubled[row - 1][col] + doubled[row + 1][col]) / 2;
        }
    }


    for (int row = 1; row < new_height; row += 2) { // this for loops fills in the remaining diagonal gaps by averaging the four surrounding corner pixels.
// these are located at odd-numbered rows and odd-numbered columns the +1 in the formula helps with rounding during integer division.

        for (int col = 1; col < new_width; col += 2) {
            int a = doubled[row - 1][col - 1];
            int b = doubled[row - 1][col + 1];
            int c = doubled[row + 1][col - 1];
            int d = doubled[row + 1][col + 1];
            doubled[row][col] = (a + b + c + d + 1) / 4;
        }
    }
}

void smooth_image(int image[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height) {
    int temp[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH]; // this creates a temporary image array to store the smoothed values this ensures original values are preserved during calculation.



    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) { // this loops through every pixel in the image to apply smoothing.

            if (row == 0 || row == height - 1 || col == 0 || col == width - 1) { // if the pixel is on the edge the code copies it directly without smoothing.
// edge pixels cannot create a 3 x 3 environment .

                temp[row][col] = image[row][col];
            } else { //The code applies weighted averaging to the 3x3 around the current pixel more weight is given to the center and adjacent pixels.
// The +7 helps round the result during integer division.

                int sum = image[row - 1][col - 1] + 2 * image[row - 1][col] + image[row - 1][col + 1]
                        + 2 * image[row][col - 1] + 4 * image[row][col] + 2 * image[row][col + 1]
                        + image[row + 1][col - 1] + 2 * image[row + 1][col] + image[row + 1][col + 1] + 7;
                temp[row][col] = sum / 16;
            }
        }
    }


    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            image[row][col] = temp[row][col];
        }
    }
}

void print_image(int image[MAX_DOUBLE_HEIGHT][MAX_DOUBLE_WIDTH], int width, int height, int grey_levels) { // this function converts the numerical pixel values into characters and prints the image row by row.
// the characters used depend on the grey level: darker values are mapped to symbols like # or : lighter values are represented by spaces.

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int character = image[row][col];
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
        putchar('\n');
    }
}
