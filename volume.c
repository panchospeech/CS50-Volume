// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // declaration of an array type uint8_t named header with a size of the const int
    uint8_t header[HEADER_SIZE];
    //read the header from the input file and saving it temp in the array header, size, 1 nmemb (numbers), from input
    fread(header, HEADER_SIZE, 1, input);
    //write the header to the output file
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    //read the sample from the input file
    int16_t buffer;
    //while its reading the input, it uses de address from buffer to save it, reading it 1 sample of 16 bits (2 bytes)
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        //update the volume, by multiplying the sample by the volume factor
        buffer *= factor;
        // write data from the buffer (ask for the address modified by the factor), writing it as above to the output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
