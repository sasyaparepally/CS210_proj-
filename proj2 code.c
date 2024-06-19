#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef SYSTEM_INFO
#define SYSTEM_INFO


#define BOARD               "DE1-SoC"

/* Memory */
#define DDR_BASE            0x40000000
#define DDR_END             0x7FFFFFFF
#define A9_ONCHIP_BASE      0xFFFF0000
#define A9_ONCHIP_END       0xFFFFFFFF
#define SDRAM_BASE          0x00000000
#define SDRAM_END           0x03FFFFFF
#define FPGA_PIXEL_BUF_BASE        0x08000000
#define FPGA_PIXEL_BUF_END     0x0803FFFF
#define FPGA_CHAR_BASE      0x09000000
#define FPGA_CHAR_END       0x09001FFF

/* Cyclone V FPGA devices */
#define LED_BASE            0xFF200000
#define LEDR_BASE           0xFF200000
#define HEX3_HEX0_BASE          0xFF200020
#define HEX5_HEX4_BASE          0xFF200030
#define SW_BASE             0xFF200040
#define KEY_BASE            0xFF200050
#define JP1_BASE            0xFF200060
#define JP2_BASE            0xFF200070
#define PS2_BASE            0xFF200100
#define PS2_DUAL_BASE           0xFF200108
#define JTAG_UART_BASE          0xFF201000
#define IrDA_BASE           0xFF201020
#define TIMER_BASE          0xFF202000
#define TIMER_2_BASE            0xFF202020
#define AV_CONFIG_BASE          0xFF203000
#define RGB_RESAMPLER_BASE      0xFF203010
#define PIXEL_BUF_CTRL_BASE     0xFF203020
#define CHAR_BUF_CTRL_BASE      0xFF203030
#define AUDIO_BASE          0xFF203040
#define VIDEO_IN_BASE           0xFF203060
#define EDGE_DETECT_CTRL_BASE   0xFF203070
#define ADC_BASE            0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE          0xFF709000
#define I2C0_BASE           0xFFC04000
#define I2C1_BASE           0xFFC05000
#define I2C2_BASE           0xFFC06000
#define I2C3_BASE           0xFFC07000
#define HPS_TIMER0_BASE         0xFFC08000
#define HPS_TIMER1_BASE         0xFFC09000
#define HPS_TIMER2_BASE         0xFFD00000
#define HPS_TIMER3_BASE         0xFFD01000
#define FPGA_BRIDGE         0xFFD0501C

#endif
	
void draw_line(int x1, int y1, int y2, int x2, short color);
void plot_pixel(int x, int y, short int line_colour);
void clear_screen();
void clear_screen2();
void draw_line(int x1, int y1, int y2, int x2, short color);
int ran();
void draw_box(int x, int y, int width, int height, short int colour);
void draw_game_over();
void write_char(int x, int y, char c);
void game();
#define VGA_WIDTH 320
#define VGA_HEIGHT 240
#define white 0xffff
#define black 0x0000
#define RED   0xF800
#define LGRAY 0xC618 	
#define NAVY 0x000F
 
short int navy_color = NAVY;

volatile int pixel_buffer_start; 
void game() {
    volatile int *SW_switch_ptr = (int *)SW_BASE; 
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;//location of pixxel buffer controller
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    int a;
    int dx = 1;
    int dy = 1;
    int h = 200; // Initial height for the blocks
    int blockFalling = 0; // Flag to indicate if a block is currently falling
  
    srand(time(NULL));  // Seed the random number generator
    int ab = 0;
    int re = 0;
	int choosen=120;
  
     short color = rand() % 0xFFFF; // Generate a random color
    while (1) {
        if (*SW_switch_ptr & 0x1) { // Switch 1 is on
            if (!blockFalling) { // If no block is currently falling
                blockFalling = 1; // Set flag to indicate block is falling
                dy = 1; // Reset dy for falling do// Generate a random color
                while (20 + dy <= h) { // Move block down till it reaches the bottom
                   if(re==0){ draw_line(a, 19 + dy, 20 + dy, a + choosen, black);
                    draw_line(a, 20 + dy,  40 + dy, a + choosen, color); // Use random color
                    dy += 1;
                }
                else{
                    draw_line(a-choosen, 19 + dy, 20 + dy, a , black);
                    draw_line(a-choosen, 20 + dy,  40 + dy, a , color); // Use random color
                    dy += 1;
                }
                }
                if(re==0){
				if(a<100){
					choosen=choosen+a-100;
				}
				else if(a>100){
					choosen=choosen+100-a;
				}
                }else{
                    if(a<220){
					choosen=a-100;
				}
				else if(a>220){
					choosen=choosen+200-a;
				}
                }
               blockFalling = 0;
			      while(*SW_switch_ptr & 0x1){
					  ;
				  }
            }
         
			clear_screen();
            if(choosen<=5){
				 goto C;
			}
        } 
        
        else{
            printf("%d\n",choosen);
            draw_line(100, 220, 240, 100+choosen, color);
            if (re > 0) {
                draw_line(320 - dx, 20, 40, 321 - dx, black);
                draw_line(320-choosen - dx, 20,  40, 320 - dx, color);
                dx += 1;
				a=320-dx;
					
            } else {
                draw_line(dx - 1,  20, 40, 0 + dx, black);
                draw_line(0 + dx,  20, 40, choosen + dx, color);
                dx += 1;
					a=dx;
					
                
            }
            if (200 - dx == 0 && ab == 0) {
                re++;
                dx = 1;
                ab = 1;
            } else if (dx == 200 && ab == 1) {
                re = 0;
                dx = 1;
                ab = 0;
            }

        }
       
        // Short delay loop
        for (int i = 0; i < 100000; i++) {
            // Adjust the loop count for desired delay
        }
    }   while(!(*SW_switch_ptr & 0x2)){
		C: draw_game_over();
	}
	
	if(*SW_switch_ptr & 0x2){
		int a;
    int dx = 1;
    int dy = 1;
    int h = 200; // Initial height for the blocks
    int blockFalling = 0; // Flag to indicate if a block is currently falling
  
    srand(time(NULL));  // Seed the random number generator
    int ab = 0;
    int re = 0;
	int choosen=120;
  
     short color = rand() % 0xFFFF;
	}

}

int ran() {
    int min = 120;
    int max = 200;
    int random_number = rand() % (max - min + 1) + min;
    return random_number;
}

void write_pixel(int x, int y, short colour) {
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

void clear_screen(){
    // Clear pixel data
    for(int x = 0; x < 320 ; x++) {
        for(int y = 0; y < 240 ; y++) {
            write_pixel(x, y, 0);
        }
    }
    // Clear text area
    for(int x = 0; x < 80 ; x++) {
        for(int y = 0; y < 60 ; y++) {    
            volatile char * char_buffer = (char*)(0x09000000 + (y << 7) + x);
            *char_buffer = 0; // Clear character
        }
    }
}
void clear_screen2() {
    for (int x = 0; x < VGA_WIDTH; x++) {
        for (int y = 0; y < VGA_HEIGHT; y++) {
            write_pixel(x, y, navy_color); // Set pixel to black
        }
    }
}

void draw_line(int x1, int y1, int y2, int x2, short color) {
    for (int i = 0; i <= y2 - y1; i++) {
        for (int x = x1; x <= x2; x++) {
            write_pixel(x + 20, y1 + i, color);
        }
    }
}	
void draw_box(int x, int y, int width, int height, short int colour) {
    int x_in,y_in;
	for ( x_in = 0 ; x_in < width; x_in++) {
		for ( y_in = 0 ; y_in < height; y_in++) {
			plot_pixel(x + x_in, y + y_in, colour);
		}
	}
}
void plot_pixel(int x, int y, short int line_colour) {
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_colour;
}
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char *character_buffer = (volatile char *)(0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

void draw_game_over() {
    // "G"
    draw_box(20, 50, 20, 5, RED);  // Top horizontal line
    draw_box(15, 50, 5, 30, RED);   // Left vertical line
    draw_box(20, 75, 20, 5, RED);   // Bottom horizontal line
    draw_box(35, 65, 5, 15, RED);   // Right vertical line on bottom
    draw_box(25, 65, 10, 5, RED);   // Middle horizontal line

    // "A"
    draw_box(45, 50, 5, 30, RED);   // Left vertical line
    draw_box(50, 50, 15, 5, RED);   // Top horizontal line
    draw_box(65, 50, 5, 30, RED);   // Right vertical line
    draw_box(50, 65, 15, 5, RED);   // Middle horizontal line

    // "M"
    draw_box(75, 50, 5, 30, RED);   // First vertical line
    draw_box(80, 50, 5, 15, RED);   // First slanting line
    draw_box(85, 50, 5, 30, RED);   // Middle vertical line
    draw_box(90, 50, 5, 15, RED);   // Second slanting line
    draw_box(95, 50, 5, 30, RED);   // Last vertical line

    // "E"
    draw_box(105, 50, 5, 30, RED);  // Left vertical line
    draw_box(105, 50, 20, 5, RED);  // Top horizontal line
    draw_box(105, 65, 15, 5, RED);  // Middle horizontal line
    draw_box(105, 75, 20, 5, RED);  // Bottom horizontal line

    // "O"
    draw_box(155, 50, 5, 30, RED);  // Left vertical line
    draw_box(160, 50, 15, 5, RED);  // Top horizontal line
    draw_box(175, 50, 5, 30, RED);  // Right vertical line
    draw_box(160, 75, 15, 5, RED);  // Bottom horizontal line
    
	// "U"
	draw_box(185, 50, 5, 25, RED);  // Left vertical line
	draw_box(195, 50, 5, 25, RED);  // Right vertical line
	draw_box(190, 75, 5, 5, RED);   // Bottom middle horizontal segment, slightly lower to simulate a curve

	// "E"
    draw_box(205, 50, 5, 30, RED);  // Left vertical line
    draw_box(205, 50, 20, 5, RED);  // Top horizontal line
    draw_box(205, 65, 15, 5, RED);  // Middle horizontal line
    draw_box(205, 75, 20, 5, RED);  // Bottom horizontal line

    // "R"
    draw_box(230, 50,  5, 30, RED);   // Left vertical line
    draw_box(235, 50, 15,  5, RED);   // Top horizontal line
    draw_box(250, 50,  5, 30, RED);   // Right vertical line top (approximate the upper curve)
    draw_box(245, 65,  5,  5, RED);    // Middle horizontal line (corner)
    draw_box(235, 65, 10,  5, RED);   // Middle horizontal line (extension to left)

    char* s = "ON SWITCH 2 TO RESTART THE GAME";
    int  m = 20; // Center the message horizontally
    while (*s) {
        write_char(m, 40, *s);
        m++; // Move to the next character position
        s++;
    }

}
int main(){
     volatile int *SW_switch_ptr = (int *)SW_BASE; 
    clear_screen2();
     char* p = "ON SWITCH 3 TO START THE GAME";
    int  n = 20; // Center the message horizontally
    while (*p) {
        write_char(n, 40, *p);
        n++; // Move to the next character position
        p++;
    }

    while(1){
       
        if (*SW_switch_ptr & 0x4) {
        clear_screen();
        game();
    }
    }
}