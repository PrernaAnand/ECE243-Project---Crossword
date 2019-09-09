/* Color codes: 0x116B(navy blue); 0xC8E3(maroon); 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

volatile int pixel_buffer_start;
volatile int character_buffer_start;
    
void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y<<10) + (x<<1)) = line_color;
}

void plot_character(int x, int y, char letter)
{
    *(short int *)(character_buffer_start + (y<<7) + (x<<0)) = letter;
}

void clear_screen()
{
    for (int row = 0; row < 320; row++) 
    {
        for (int col = 0; col < 240; col++) 
        {
            plot_pixel(row,col,0xC8E3);
        }
    } 
}

void draw_box(int x_pos, int y_pos, int length, int width, short int box_color)
{
    for (int i=0; i<length; i++) {
        for (int j=0; j<width; j++) {
            plot_pixel(x_pos+i, y_pos+j, box_color);
        }
    }
}

int main(void)
{
    int size_of_crossword = 11;
    int count = 0;					// infinite counter that increments 
    int alpha_count = 0;			// every time a key is presssed

    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    volatile int * character_ctrl_ptr = (int *)0xFF203030;
    
	volatile int * KEY_ptr = (int *)0xff200050;
    
    int KEY_value;
    pixel_buffer_start = *pixel_ctrl_ptr;
	character_buffer_start = *character_ctrl_ptr;
        
    clear_screen();
    
    // Drawing the title - CONSTANT
    draw_box(92, 14, 138, 8, 0x116B);

    plot_character(24, 4, 'c');
    plot_character(28, 4, 'r');
    plot_character(32, 4, 'o');
    plot_character(36, 4, 's');
    plot_character(40, 4, 's');
    plot_character(44, 4, 'w');
    plot_character(48, 4, 'o');
    plot_character(52, 4, 'r');
    plot_character(56, 4, 'd');

    // Drawing the crossword - DYNAMIC

    // x and y positions of each inner square of the crossword
    int x_pos_of_square[11] = {60, 76, 92, 108, 108, 108, 108, 108, 92, 108, 124};
    int y_pos_of_square[11] = {92, 92, 92, 76, 92, 108, 124, 140, 156, 156, 156};
    int x_char_position[11] = {16, 20, 24, 28, 28, 28, 28, 28, 24, 28, 32};
    int y_char_position[11] = {24, 24, 24, 20, 24, 28, 32, 36, 40, 40, 40};
        
    char alphabets[11] = {'F', 'P', 'G', 'T', 'A', 'N', 'N', 'E', 'A', 'R', 'M'};
    
    char all_alphabets[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    bool letter_is_right[11] = {false, false, false, false, false, false, false, false, false, false, false};
    
    // plotting the white outline of each square
    for (int it=0; it<size_of_crossword; it++)
    {
        draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0xffffffff);
    }

    // plotting the black square    
    for (int it=0; it<size_of_crossword; it++)
    {
        draw_box(x_pos_of_square[it], y_pos_of_square[it], 12, 12, 0x116B);
        plot_character(x_char_position[it], y_char_position[it], 0);
    }          

    while (KEY_value != 4)
    {
        KEY_value = *(KEY_ptr);
        if (KEY_value == 1)
        {
	    
            for (int it=0; it<size_of_crossword; it++) {
                if (it == count % size_of_crossword) {
                    draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0x118e49);
                    draw_box((x_pos_of_square[it]), (y_pos_of_square[it]), 12, 12, 0x116B);
                }
            }
           
            count++;      
            
            while (*KEY_ptr == 1);

	    if (!letter_is_right[(count-1) % size_of_crossword]) 
	    {
            for (int it=0; it<size_of_crossword; it++) {
                if (it == (count-1) % size_of_crossword) {
            		draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0xffffffff);
                    draw_box((x_pos_of_square[it]), (y_pos_of_square[it]), 12, 12, 0x116B);
                }
            }
	    } else {
            for (int it=0; it<size_of_crossword; it++) {
        		if (it == (count-1) % size_of_crossword) {
                    draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0xc0ff82);
                    draw_box((x_pos_of_square[it]), (y_pos_of_square[it]), 12, 12, 0x116B);
                }
            }
	    }
           
        }
        
        else if(KEY_value == 2)
        {
            plot_character(x_char_position[(count-1) % size_of_crossword], 
                           y_char_position[(count-1) % size_of_crossword], 
                           all_alphabets[alpha_count % 26]);
            
            while (*KEY_ptr == 2);  
            if(all_alphabets[alpha_count%26] == alphabets[(count - 1) % size_of_crossword])
            {
		letter_is_right[(count-1) % size_of_crossword] = true;
                for (int it=0; it<size_of_crossword; it++) 
                {
                    if (it == (count-1) % size_of_crossword) 
                    {
                        draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0xc0ff82);
                        draw_box((x_pos_of_square[it]), (y_pos_of_square[it]), 12, 12, 0x116B);
                    }
                }

            }
            else
            {
	       letter_is_right[(count-1) % size_of_crossword] = false;
               for (int it=0; it<size_of_crossword; it++) 
                {
                    if (it == (count-1) % size_of_crossword) 
                    {
                        draw_box((x_pos_of_square[it]-3), (y_pos_of_square[it]-3), 18, 18, 0xffffffff);
                        draw_box((x_pos_of_square[it]), (y_pos_of_square[it]), 12, 12, 0x116B);
                    }
                }
               
            }
            alpha_count++;
        }
        
    }

    for (int it=0; it<size_of_crossword; it++)
    {
        plot_character(x_char_position[it], y_char_position[it], 0);
    }      
    clear_screen();
    return 0;
}