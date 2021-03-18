#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <map>

using namespace std;

std::map<int, std::string> Rtype; 
std::map<int, std::string> Itype;

int binaryToDecimal(int n);
void RtypeInitializeInstructions();
void ItypeInitializeInstructions();
std::string getRegister(int decimal);
std::string getOpcode(std::string Binarycode);

void getTargetAddress(std::string Binarycode);
void getImmediate(std::string Binarycode);

void getRS(std::string Binarycode);
void getRT(std::string Binarycode);
void getRD(std::string Binarycode);
void getShamt(std::string Binarycode);
int getFunct(std::string Binarycode);

void getRtypeDetails(std::string Binarycode);
void getJtypeDetails(std::string Binarycode);
void getItypeDetails(std::string Binarycode);
void getInstructionDetails(std::string Binarycode, std::string Instruction_type);
std::string getInstructionType(std::string str);


void RtypeInitializeInstructions(){

    Rtype.insert(pair<int, std::string>(32, "add")); 
    Rtype.insert(pair<int, std::string>(33, "addu"));
    Rtype.insert(pair<int, std::string>(36, "and"));
    Rtype.insert(pair<int, std::string>(13, "break"));
    Rtype.insert(pair<int, std::string>(27, "div"));
    Rtype.insert(pair<int, std::string>(28, "divu"));
    Rtype.insert(pair<int, std::string>(9, "jalr"));
    Rtype.insert(pair<int, std::string>(8, "jr"));
    Rtype.insert(pair<int, std::string>(16, "mfhi"));
    Rtype.insert(pair<int, std::string>(18, "mflo"));
    Rtype.insert(pair<int, std::string>(17, "mfthi"));
    Rtype.insert(pair<int, std::string>(24, "mult"));
    Rtype.insert(pair<int, std::string>(25, "multu"));
    Rtype.insert(pair<int, std::string>(39, "nor"));
    Rtype.insert(pair<int, std::string>(37, "or")); 
    Rtype.insert(pair<int, std::string>(0, "sll"));
    Rtype.insert(pair<int, std::string>(4, "sllv"));
    Rtype.insert(pair<int, std::string>(42, "slt"));
    Rtype.insert(pair<int, std::string>(43, "sltu"));
    Rtype.insert(pair<int, std::string>(3, "sra"));
    Rtype.insert(pair<int, std::string>(7, "srav"));
    Rtype.insert(pair<int, std::string>(6, " srlv"));
    Rtype.insert(pair<int, std::string>(2, "srl"));
    Rtype.insert(pair<int, std::string>(34, "sub")); 
    Rtype.insert(pair<int, std::string>(35, "subu")); 
    Rtype.insert(pair<int, std::string>(12, "syscal")); 
    Rtype.insert(pair<int, std::string>(38, "xor")); 
}
    

void ItypeInitializeInstructions(){
    Itype.insert(pair<int, std::string>(8, "addi")); 
    Itype.insert(pair<int, std::string>(9, "addiu")); 
    Itype.insert(pair<int, std::string>(12, "andi")); 
    Itype.insert(pair<int, std::string>(4, "beq")); 
    Itype.insert(pair<int, std::string>(7, "bgtz")); 
    Itype.insert(pair<int, std::string>(6, "blez")); 
    Itype.insert(pair<int, std::string>(5, "bne")); 
    Itype.insert(pair<int, std::string>(32, "lb")); 
    Itype.insert(pair<int, std::string>(36, "lbu")); 
    Itype.insert(pair<int, std::string>(33, "lh")); 
    Itype.insert(pair<int, std::string>(37, "lhu")); 
    Itype.insert(pair<int, std::string>(15, "lui")); 
    Itype.insert(pair<int, std::string>(35, "lw")); 
    Itype.insert(pair<int, std::string>(49, "lwc1")); 
    Itype.insert(pair<int, std::string>(13, "ori")); 
    Itype.insert(pair<int, std::string>(40, "sb")); 
    Itype.insert(pair<int, std::string>(10, "slti")); 
    Itype.insert(pair<int, std::string>(11, "sltiu")); 
    Itype.insert(pair<int, std::string>(41, "sh")); 
    Itype.insert(pair<int, std::string>(43, "sw")); 
    Itype.insert(pair<int, std::string>(57, "swc1")); 
    Itype.insert(pair<int, std::string>(14, "xori")); 
}



int binaryToDecimal(int n){
    int val = 0;
    int base = 1;
    int itterator = n;

    while (itterator) {
        int last_digit = itterator % 10;
        itterator /= 10;
        val += last_digit * base;
        base *= 2;
    }
    return val;
}

string getOpcode(std::string Binarycode){
    string opcode_string;
    int i = 0;
    while(i < 6){
        opcode_string += Binarycode[i];
        i++;
    }
    // convert opcode from string to integer
    return opcode_string;
}

void getTargetAddress(std::string Binarycode){
    int i = 6; // end of opcode
    string TA_string;
    while(i < 32){
        TA_string += Binarycode[i];
        i++;
    }
    int TA_int_binary = stoi(TA_string); // convert opcode from string to integer
    int TA_decimal = binaryToDecimal(TA_int_binary);
    cout << "Immediate: " << TA_decimal << endl;
}

void getImmediate(std::string Binarycode){
    int i = 16; // end of opcode
    string I_string;
    while(i < 32){
        I_string += Binarycode[i];
        i++;
    }
    int I_int_binary = stoi(I_string); // convert opcode from string to integer
    int I_decimal = binaryToDecimal(I_int_binary);
    cout << "Immediate: " << I_decimal << endl;

}

std::string getRegister(int decimal){
    string reg; 
    string temp; 
      if((decimal >= 8 && decimal <= 15)) {
        temp = to_string(decimal-8); 
        reg = "$t" + temp; 
    } 
      if(decimal >= 24 && decimal <= 25) {
        temp = to_string(decimal-16); 
        reg = "$t" + temp; 
      }
      if((decimal >= 16 && decimal <= 23)) { 
        temp = to_string(decimal-16); 
        reg = "$s" + temp;  
      } 
      if(decimal == 1) { 
        reg= "$at"; 
      }
      if(decimal == 0) {
        reg="$zero"; 
      }
      if(decimal >= 4 && decimal <= 7) { 
        temp = to_string(decimal-4); 
        reg = "$a" + temp;  
      }
      if(decimal >= 2 && decimal <= 3) { 
        temp = to_string(decimal-2); 
        reg = "$v" + temp; 
      } 
      if (decimal >= 26 && decimal <= 27) { 
        temp = to_string(decimal-26); 
        reg = "$k" + temp; 
      }
      if(decimal == 28) {
        reg="$gp"; 
      }
      if(decimal == 29) {
        reg="$sp"; 
      }
      if(decimal == 30) {
        reg="$fp"; 
      }
      if(decimal == 31) {
        reg="$ra"; 
      }

return reg;
}


void getRS(std::string Binarycode){
    int i = 6; // end of opcode
    string rs_string;
    while(i < 11){
        rs_string += Binarycode[i];
        i++;
    }
    int rs_int_binary = stoi(rs_string); // convert opcode from string to integer
    int rs_decimal = binaryToDecimal(rs_int_binary);
    string Reg = getRegister(rs_decimal);
    cout << "Rs: " << Reg << " (R" << rs_decimal << ")"<< endl;
}

void getRT(std::string Binarycode){
    int i = 11; // end of opcode
    string rt_string;
    while(i < 16){
        rt_string += Binarycode[i];
        i++;
    }
    int rt_int_binary = stoi(rt_string); // convert opcode from string to integer
    int rt_decimal = binaryToDecimal(rt_int_binary);
    string Reg = getRegister(rt_decimal);
    cout << "Rt: " << Reg << " (R" << rt_decimal << ")"<< endl;
}

void getRD(std::string Binarycode){
    int i = 16; // end of opcode
    string rd_string;
    while(i < 21){
        rd_string += Binarycode[i];
        i++;
    }
    int rd_int_binary = stoi(rd_string); // convert opcode from string to integer
    int rd_decimal = binaryToDecimal(rd_int_binary);
    string Reg = getRegister(rd_decimal);
    cout << "Rd: " << Reg << " (R" << rd_decimal << ")"<< endl;
}

void getShamt(std::string Binarycode){
    int i = 21; // end of opcode
    string shamt_string;
    while(i < 26){
        shamt_string += Binarycode[i];
        i++;
    }
    int shamt_int_binary = stoi(shamt_string); // convert opcode from string to integer
    int shamt_decimal = binaryToDecimal(shamt_int_binary);
    cout << "Shamt: " << shamt_decimal << endl;
}

int getFunct(std::string Binarycode){
    int i = 26; // end of opcode
    string funct_string;
    while(i < 32){
        funct_string += Binarycode[i];
        i++;
    }
    int funct_int_binary = stoi(funct_string); // convert opcode from string to integer
    int funct_decimal = binaryToDecimal(funct_int_binary);
    return funct_decimal;
}



void getRtypeDetails(std::string Binarycode, std::string instruction){
    //getInstruction
    cout << "Operation: " << instruction << endl;
    //rs
    getRS(Binarycode);
    //rt
    getRT(Binarycode);
    //rd
    getRD(Binarycode);
    //shamt
    getShamt(Binarycode);
    //funct
    int funct = getFunct(Binarycode);
    cout << "Funct: " << funct << endl;
}

void getJtypeDetails(std::string Binarycode){
    //opcode
    std::string Opcode = getOpcode(Binarycode);
    std::cout << "Opcode: " << Opcode << std::endl;
    //target address
    getTargetAddress(Binarycode);
}

void getItypeDetails(std::string Binarycode, std::string instruction){
    //getInstruction
    cout << "Operation: " << instruction << endl;
    //rs
    getRS(Binarycode);
    //rt
    getRT(Binarycode);
    //immediate
    getImmediate(Binarycode);
}


void getInstructionDetails(std::string Binarycode, std::string Instruction_type){
    std::string instruction;
    if(Instruction_type == "R"){
        instruction = Rtype[getFunct(Binarycode)];
        getRtypeDetails(Binarycode,instruction);
    }
    else if(Instruction_type == "J"){
        getJtypeDetails(Binarycode);
    }
    else{
        string opcode_string = getOpcode(Binarycode);
        int opcode_int = stoi(opcode_string); 
        int opcode_decimal = binaryToDecimal(opcode_int);
        instruction = Itype[opcode_decimal];
        getItypeDetails(Binarycode,instruction);
    }
}


//#include <stdio.h>
string getInstructionType(string Binarycode){
    string opcode_string = getOpcode(Binarycode);
    int opcode_int = stoi(opcode_string); 
    int opcode_decimal = binaryToDecimal(opcode_int);

    if(opcode_decimal == 0){
        return "R";
    }
    else if(opcode_decimal == 2 || opcode_decimal == 3){
        return "J";
    }
    else{
        return "I";
    }

    return opcode_string;
}

int main(){

    string Binarycode;
    string Instruction_type;
    RtypeInitializeInstructions();
    ItypeInitializeInstructions();

    cout << "Enter an instruction in Machine Code: ";
    cin >> Binarycode;
    Instruction_type = getInstructionType(Binarycode);
    cout << "Your instruction type is a: " << Instruction_type << endl;

    getInstructionDetails(Binarycode,Instruction_type);

}
