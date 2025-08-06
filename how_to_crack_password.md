 #comands:
    1. readelf -l ./runfile
         watch for first LOAD then get your virtual address and subtruct base address from it.(0x40125c - 0x400000 = 0x125c).
    2. hexedit ./runfile
         press 'ctrl' + 'g' then enter the address: 0x125c.
         ==================================
            HEX EDITING:
                jnz( jump if not zero ) // 75 is hexadecimal opcode for jnz instuction.
                0c is argument for jnz it's singed as 8-bit value what tells the processor how much bytes to jump forward or backward. in our case we have 0x0c is 12 in hexadecimal means "jump 12 bytes forward from current position."
                ---------------------------
                90 is opcode for NOP(no operation) instruction. it tells processor to do nothing and simply move to the next instruction. A NOP instuction is a single byte.
                we use 2nd 90 because when we replace jnz(75 0c) with NOP's we need to use 2 nop instructions (90 90) if we dont use it it will most likely crash.
         ==================================
         change curent bytes with your own.
         press 'ctrl' + 'x' close and save.
         conntinue with 'y'.
         and run program './runfile'.

#special words meaning:
    opcode is a number for instuction example: JNZ = 75, NOP = 90.
    operand = argument.
      
#instructions what can confiuse you:
    LEA: helps to find the variable within that space.
    RBP: is a bookmark what is static and which you can access any time goin back by current amount of bytes.
    RSP: is a always top page in a book where you can add pages.
    jnz: jump if not zero flag is not set.
    test: performs a bitwise AND operation but discards the result. its only purpose to update the CPU's flags.
    nop: no operation just move to next instruction.
    
                HOW TO CARCK?
  First we need to run our file in ghidra: clik 'file' -> 'new project' -> 'non-Shared Project' , name it and click next.
  Drag the run file in ghidra and double click on your it. 
  Then ghidra might ask if we want to analyze code click 'yes'. now we in CodeBrowser. 
  first lets look at the changes from GDB:
    // ghidra uses INTEL sytax when gdb uses AT&T.
    1. in GDB we read like this: mov $0x10, %eax meanwhile in ghidra we do like this MOV EAX, 10.
    2. ghidra will help you with addreses example: 004004ad  48 8d 45 e0        LEA        RAX=>password,[RBP + -0x20] // ghidra is helping us showig what we need to find RAX(password) with rbp + -0x20(32 in decimal).

  lets look at this snippet:
                  004004c3  48 8d 45 e0             LEA                 RAX=>password,[RBP + -0x20]
                  004004c7  be 5c 12 40 00          MOV                 ESI,s_echidna_0040125c                                                                   = "echidna"
                  004004cc  48 89 c7                MOV                 RDI,RAX
                  004004cf  e8 cc fe ff             CALL                <EXTERNAL>::strcmp                                                                         int strcmp(char * __s1, char * __s2)
what can we see here LEA is helping to find variable with space [RBP + -0x20] then we copy s_echidna_0040125c to ESi this is our password as u can see 's_' means a string 'echidna' is the string and '_0040125c' is the address.
then we copy RAX to RDI and call strcmp
                HOW TO CHANGE THE PASSWORD?
first lets cout the address, in your terminal write: 'readelf -l ./password' now find the firs LOAD it should be 0x400000.
now subtract 0x400000 from 0x40125c. 0x4125c - 0x400000 = 0x125c.
in terminal write 'hexedit ./password' if not intalled 'sudo *your pacage manager* install hexedit'.
press 'ctrl' + 'g' then enter the address: 0x125c.
and type 68 61 63 6b 65 64 and 00 at the end. in **ASCII** 'hacked'.
press 'ctrl' + 'x' cofirm with 'y' and run program: ./password
