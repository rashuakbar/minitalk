#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<string.h> 

char bin_to_char(int** ptr)
{
    char c = 0;
    int byte_idx = 0;
    int bit_idx;
    
    while (ptr[byte_idx] != NULL) // While there are more bytes
    {
        c = 0; // Reset character for each byte
        bit_idx = 0;

        while (bit_idx < 8) // Process each bit in the byte
        {
            if (ptr[byte_idx][bit_idx] == 1)
                c = (c << 1) | 1;
            else
                c <<= 1;
            bit_idx++;
        }
        printf("Character: %c\n", c); // Display the reconstructed character
        byte_idx++;
    }
    return c;
}

int** char_to_bin(char* str)
{
    int** ptr;
    int byte_index = 0;
    int bit_index;
    int i;

    // Find the length of the string
    while (str[byte_index] != '\0')
        byte_index++;
    
    // Allocate memory for the array of pointers
    ptr = (int**)calloc(byte_index + 1, sizeof(int*));
    if (!ptr) return NULL;
    
    byte_index = 0;
    while (str[byte_index] != '\0') // While there are more characters
    {
        ptr[byte_index] = (int*)calloc(8, sizeof(int));
        if (!ptr[byte_index])
        {
            // Free previously allocated memory on failure
            int j = 0;
            while (j < byte_index)
            {
                free(ptr[j]);
                j++;
            }
            free(ptr);
            return NULL;
        }

        bit_index = 7;
        i = 0;
        while (bit_index >= 0) // Convert each character to binary
        {
            ptr[byte_index][i++] = (str[byte_index] >> bit_index) & 1;
            printf("%d -> %d\n",
                str[byte_index] >> bit_index,
                (str[byte_index] >> bit_index) & 1);
            bit_index--;
        }
        printf(" : ");
        byte_index++;
    }
    
    ptr[byte_index] = NULL;
    return ptr;
}

int main(int argc, char **argv ) {
    //char str[5] = "🌍"; // -16:-97:-116:-115 or 11110000 : 10011111 : 10001100 : 10001101
   //char str[2] = "H"; // 72 01001000
   int** ptr;
    if (argc == 2)
    {
        ptr = char_to_bin(argv[1]);
        bin_to_char(ptr);
    }
    else 
    {
        ptr = char_to_bin("H");
        bin_to_char(ptr);
    }
    return(0);
}
