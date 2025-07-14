README - How to Use the Image Display Programs (image1.c, image2.c, image3.c)

These C programs display images using run-length encoded (RLE) input. Each program builds
on the last, adding more image processing features such as edge detection and smoothing.

GREY LEVELS AND CHARACTER MAPPINGS
Each pixel in the image is represented by a number corresponding to a grey level.
These grey levels are then converted into ASCII characters for visual display.

For grey_levels = 2:
0 -> '#' (black or darkest)
1 -> ' ' (white or lightest)

For grey_levels = 3:
0 -> '#' (black)
1 -> '.' (grey)
2 -> ' ' (white)

For grey_levels = 4:
0 -> '#' (black)
1 -> ':' (dark grey)
2 -> '.' (light grey)
3 -> ' ' (white)

Note: image3.c always uses grey_levels = 4 for display, even if the input has only 2 grey
levels, because it performs pixel averaging.

image1.c – Basic Image Decoder
Description:
This program takes RLE input and decodes it into a 2D image array. It then prints the image
using ASCII characters that represent different grey levels.

Input format:
<width> <height> <grey_levels>
<pix1> <len1> <pix2> <len2> <pix3> <len3> ...

width and height define the size of the image in pixels.

grey_levels specifies how many brightness levels are used (2, 3, or 4).

pixN is a grey level value (from 0 up to grey_levels - 1).

lenN is how many times that grey level should repeat in sequence.

Example input:
78 26 3 1 364 0 4 1 7 0 3 1 43 2 7 1 12 0 7 1 4 0 6 1 33 2 28 0 2 2 2 0 2 1 5 0 1 2 2 0 1 1 31 2
27 0 6 2 14 1 28 2 28 0 7 2 5 0 4 2 4 0 2 2 1 1 26 2 29 0 7 2 4 0 4 2 6 0 2 2 1 1 27 2 26 0 9 2
15 1 29 2 25 0 9 2 9 0 4 2 1 1 29 2 27 0 9 2 12 1 28 0 5 2 24 0 11 2 4 0 3 1 30 0 11 2 19 0 12
2 2 0 8 1 25 0 17 2 15 0 10 2 1 0 17 1 17 0 21 1 13 0 9 1 3 0 14 1 17 0 11 1 2 0 8 1 15 0 9 1
10 0 4 1 19 0 9 1 4 0 7 1 18 0 9 1 31 0 8 1 5 0 6 1 21 0 9 1 28 0 8 1 6 0 5 1 25 0 7 1 28 0 7
1 5 0 8 1 24 0 3 1 333

What it outputs:
This input produces a visual ASCII image of a panda.

image2.c – Edge Gradient Detection
Description:
This program reads an RLE-encoded image like image1.c, but instead of printing the raw
image, it calculates edge gradients based on 2x2 pixel blocks. It prints the result using
characters that emphasize stronger changes between pixel values.

The image is scanned block by block, and for each 2x2 area, four gradient calculations are
done (horizontal, vertical, and two diagonal). The maximum of these is used to represent
the edge strength.

Input format:
Same format as image1.c

Example input:
69 31 4 1 227 3 2 0 1 3 2 0 3 3 3 0 3 3 2 1 50 3 1 0 3 3 3 0 4 3 4 0 5 3 2 1 44 3 2 0 3 3 4 0
5 3 5 0 5 3 3 1 41 3 2 0 3 3 4 0 6 3 6 0 5 3 3 1 39 3 2 0 4 3 4 0 6 3 6 0 6 3 3 1 37 3 2 0 4 3
5 0 6 3 7 0 6 3 3 1 7 2 7 1 22 3 2 0 4 3 5 0 6 3 7 0 6 3 3 1 5 2 17 1 14 3 2 0 4 3 5 0 6 3 7 0
6 3 3 1 5 2 17 1 15 3 2 0 3 3 6 0 5 3 7 0 5 3 3 1 4 2 20 1 14 3 2 0 3 3 6 0 5 3 6 0 6 3 3 1 5 2
19 1 15 3 2 0 3 3 5 0 5 3 6 0 5 3 3 1 9 2 14 1 18 3 2 0 4 3 4 0 4 3 5 0 5 3 3 1 43 3 2 0 4 3 3
0 3 3 5 0 5 3 3 1 46 3 2 0 3 3 2 0 3 3 4 0 4 3 2 1 51 3 1 0 3 3 2 0 2 3 3 0 3 3 2 1 55 3 1 0 2
3 1 0 2 3 2 0 3 3 1 1 45 2 14 3 1 0 1 3 1 0 1 3 1 0 2 3 1 1 45 2 16 0 1 2 2 0 1 1 3 0 1 1 45 2
16 0 1 2 2 0 1 1 3 0 1 1 47 2 13 0 10 1 44 2 16 0 8 1 48 2 13 0 8 1 51 2 13 1 107 2 5 1 58 2 11
1 57 2 12 1 55 2 14 1 53 2 16

What it outputs:
This input produces an ASCII image of a balloon with stronger edges shown in darker
characters.

image3.c – Image Doubling and Smoothing
Description:
This program takes an RLE-encoded image with 2 grey levels and performs the following:

Converts pixel value 1 to 3 (for compatibility with 4-grey-level output).

Doubles the image size. The new width is (2 * width - 1), and the new height is
(2 * height - 1). New pixels are inserted between original pixels.

New pixels are calculated using horizontal, vertical, or diagonal averages of nearby
original values.

Three passes of smoothing are applied using a weighted average filter over a 3x3 grid.

The final smoothed image is printed using reverse grey level characters.

Input format:
Same format as image1.c. Only 2 grey levels (0 and 1) are supported for input.

Example input:
39 26 2 1 89 0 14 1 22 0 21 1 16 0 26 1 13 0 6 1 3 0 7 1 3 0 7 1 13 0 6 1 3 0 7 1 3 0 7 1 13 0
12 1 1 0 12 1 16 0 9 1 3 0 9 1 23 0 12 1 23 0 3 1 14 0 3 1 20 0 18 1 26 0 6 1 21 0 4 1 25 0 4 1
5 0 6 1 22 0 7 1 8 0 5 1 16 0 5 1 16 0 5 1 10 0 5 1 22 0 5 1 4 0 5 1 28 0 8 1 31 0 8 1 28 0 5 1
4 0 5 1 21 0 6 1 10 0 6 1 11 0 9 1 16 0 8 1 8 0 5 1 20 0 5 1 83

What it outputs:
This input produces a smoothed, double-resolution ASCII rendering of a skull.

General Notes
Make sure that the sum of all lenX values equals width × height.

For image3.c, the input image must use only grey levels 0 and 1.

All output is printed directly to the terminal using ASCII characters.

Use a wide terminal window to avoid line wrapping.

Input can be pasted manually or redirected from a file.

End of README.