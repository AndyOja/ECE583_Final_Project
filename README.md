# ECE583_Final_Project
ECE583 Final Project 
Joey and Andy

This Repo contains relevant files for our COS583 final project: a 3-bit relay adder based on Shannon's master thesis. Below is a brief description of every relevant file. 

COS583_Arduino_Code.ino : Code uploaded to our Arduino Uno that interfaces with our hardware. Reads in serial data string from laptop (ex: "3+7"), parses input data and outputs digital logic levels to our breadboard/hardware. Additionally, the software uses pins to digitally read the result from our breadboard, synthesizes the data, and converts it to decimal to display on the serial monitor on the laptop.

Adder_Logic_Gates.pdf : PDF circuit diagram representing our adder. Consists of five standalone circuits. The smaller circuits at the bottom represent the way we chose to represent logic gates with our relays and the large circuit is our 3-bit ripple-carry adder (excluding the hardware necessary to interface with the arduino).

583-inverter.pdf : PDF circuit diagram representing the input inverters and the carry chain buffers. Consists of two standalone circuits. The top is a CMOS inverter with a pull-up resistor at the input and an LED at the output, which inverts our input signals (defaults to 0 at the output). The bottom is a CMOS buffer which passes along the carry out signal from one adder to the carry in signal of the next adder. 
