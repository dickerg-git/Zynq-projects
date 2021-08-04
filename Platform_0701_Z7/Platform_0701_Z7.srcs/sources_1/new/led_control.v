`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/09/2021 09:43:49 PM
// Design Name: 
// Module Name: led_control
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module led_control(
    input [3:0] led_state,
    input [3:0] led_en,
    output [3:0] led_out
    );
    
    assign led_out[0] = led_state[0] & ~led_en[0];
    assign led_out[1] = led_state[1] & ~led_en[1];
    assign led_out[2] = led_state[2] & ~led_en[2];
    assign led_out[3] = led_state[3] & ~led_en[3];
    // assign led_out[3:0] = led_state{3:0] & ~led_en[3:0];
    
endmodule
