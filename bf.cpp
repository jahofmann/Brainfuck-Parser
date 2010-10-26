/* 
 * See license for license informations.
 * 
 * Very simple brainfuck parser.
 * Reads code from file and should work with every brainfuck program out there.
 * This program should work with every C++ conform compiler.
 *
 * Usage:
 *      bf FILE
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h> // Using c but works better compared to cin

#define DATASIZE 255

std::string valid = "<>+-.,[]"; // All valid bf commands
int ptr = 0; // The program pointer
char data[DATASIZE]; // Our data array

// dir = 1 searches for ] dir = -1 searches for [
int jumpPos(std::string code, int pos, int dir)
{
 bool jumpTargetFound = false;
 int bracketCounter = 0;
 while(!jumpTargetFound)
 {
  if(pos >= code.length() || pos < 0)
  {
   std::cout << "Error: [ without ]." << std::endl;
   return -1;
  }
  pos += dir;
  if(code[pos] == ']') bracketCounter--;
  else if(code[pos] == '[') bracketCounter++;
  if(bracketCounter == dir*-1) jumpTargetFound = true;
 } 
 return pos;
}

void processChar(char c)
{
 switch(c)
 {
  case '>': // Move data pointer one higher
        ptr++;
        break;
  case '<': // Move data pointer one lower
        ptr--;
        break;
  case '+': // Add one to data[ptr]
        data[ptr]++;
        break;
  case '-': // Remove one from data[ptr]
        data[ptr]--;
        break;
  case '.': // Print char at ptr position
        std::cout << data[ptr];
        break;
  case ',': // Read one char to ptr position
        data[ptr] = getchar();
        break;
  default:
   std::cout << "Illegal character: " << c << std::endl; // Shouldn't happening due to valid char test
   break;
 }
}

void processCode(std::string code, int pos)
{
 for(pos = 0; pos < code.length(); pos++) // Process the code
 {
  if(valid.find(code[pos]) == std::string::npos) continue; // Not a valid brainfuck char so continue
  switch(code[pos])
  {
  case '[': // Begin a loop
    {
     int bracketPos = jumpPos(code,pos,1);
     std::string loopCode = code.substr(pos+1,bracketPos-(pos+1));
     while(data[ptr]!=0)
     {
       processCode(loopCode, 0);
     }
     pos = bracketPos;
    }
    break;
  default:
    processChar(code[pos]); // All other commands
    break;
  }
 }
}

int main(int argc, char *argv[])
{
 //Read code from file
 std::ifstream in;
 in.open(argv[1]);
 std::string code;
 std::string tmp;
 std::getline(in,tmp);
 while(in)
 {
  code += tmp;
  getline(in,tmp);
 }
 int i;
 for(i = 0; i < DATASIZE; i++) // Init the data array with 0
 {
  data[i] = 0;
 }
 processCode(code,0); 
 return 0;
}

