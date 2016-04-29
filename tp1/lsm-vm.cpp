#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>
#include <stack>
#include <map>

using namespace std::this_thread; // sleep_for, sleep_until
   using namespace std::chrono; // nanoseconds, system_clock, seconds


class LSMVM
{
public:
    std::stack<uint32_t> ds;
    std::stack<uint32_t> cs;
    uint32_t tos;
    uint16_t ip = 0;
    uint32_t* data = NULL;
    uint8_t* text = NULL;

    uint16_t bss_size = 0;
    uint16_t data_size = 0;
    uint16_t text_size = 0;

    bool debug = true;
    bool good_ = false;
    inline bool good() { return good_; }
    inline bool bad() { return ! good_; }

    uint32_t magic = 0;
    uint16_t major_version = 0,
             minor_version = 0;

    std::string opcodes[0xF3];

    LSMVM() {}
    LSMVM(const char* path);
    bool parse(const char* path);

    void ALU(uint8_t);
    void FPU(uint8_t);
    void JUMP(uint8_t, uint16_t);
    void RET();
    void STACK(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
    void OTHERS(uint8_t);

    uint16_t parse16(uint8_t, uint8_t);
    uint32_t parse32(uint8_t, uint8_t, uint8_t, uint8_t);
    void verifyOperands(std::stack<uint32_t>, unsigned int, std::string);

    void reset();
    void show();
    void step();
    void run();

    union {
        int32_t ivalue;
        uint32_t uivalue;
        float fvalue;
    } word;

    union {
        int8_t ivalue;
        uint8_t uivalue;
    } byte;
};

LSMVM::LSMVM(const char* path)
{
    if ((good_ = parse(path)) == false)
    {
        reset();
    }

}

uint16_t LSMVM::parse16(uint8_t b1, uint8_t b0) {
    return (b1 << 8) | (b0 & 0xFF);
}

uint32_t LSMVM::parse32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0) {
    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

void LSMVM::step()
{
	ip++;
}

void LSMVM::run()
{
    uint8_t opcode;
    uint16_t label;
    uint8_t b0, b1, b2, b3;
    ip = 0;
    while (ip < text_size && text[ip] != 0xf0) {
        opcode = text[ip];

        if (debug)
            fprintf(stdout, "0x%04x - Fetching instruction %-10s ", ip, opcodes[opcode].c_str());

        label = parse16(text[ip+1], text[ip+2]);

        b0 = text[ip+4];
        b1 = text[ip+3];
        b2 = text[ip+2];
        b3 = text[ip+1];

        if(opcode >= 0x10 && opcode <= 0x1b){
            ALU(opcode);
        }
        else if (opcode >= 0x20 && opcode <= 0x27){
            FPU(opcode);
        }
        else if (opcode >= 0x30 && opcode <= 0x37){
            JUMP(opcode, label);
        }
        else if (opcode == 0x40){
            RET();
        }
        else if (opcode >= 0x50 && opcode <= 0x67){
            STACK(opcode, b3, b2, b1, b0);
        }
        else if ((opcode >= 0xF0 && opcode <= 0xF2) || opcode == 0x00){
            OTHERS(opcode);
        }
        else{
            fprintf(stderr, "\033[1m\033[91mError:\033[0m Invalid opcode: 0x%x.\n", opcode);
            exit(EXIT_FAILURE);
        }
        step();

        if (debug) {
            fprintf(stdout, "\n");
            sleep_for(nanoseconds(250000000)); // wait 0.25 secs in case we enter ina endless loop
        }
    }

    if (debug)
        fprintf(stdout, "Execution ended. TOS: %8d decimal\n%30x hexadecimal\n%30.2f float\n", ds.top(), ds.top(), float(ds.top()));
}

void LSMVM::ALU(uint8_t opcode){

    int32_t a, b;

    if(opcode == 0x15){
      verifyOperands(ds, 1, "data");
      a = ds.top();
      ds.pop();
      ds.push(-a);
    }else{
      verifyOperands(ds, 2, "data");
      a = ds.top();
      ds.pop();
      b = ds.top();
      ds.pop();
      if ((opcode == 0x19 || opcode == 0x1a || opcode == 0x1b) && a < 1) {
          fprintf(stderr, "\033[1m\033[91mError:\033[0m Shift by a nonpositive value while executing instruction \"%s\".\n", opcodes[text[ip]].c_str());
          exit(EXIT_FAILURE);
      }
      switch(opcode) {
          case 0x10:
              ds.push(b+a);
              break;
          case 0x11:
              ds.push(b-a);
              break;
          case 0x12:
              ds.push(b*a);
              break;
          case 0x13:
              if (a == 0) {
                  fprintf(stderr, "\033[1m\033[91mError:\033[0m Division by zero while executing instruction \"%s\".\n", opcodes[text[ip]].c_str());
                  exit(EXIT_FAILURE);
              }
              ds.push(b/a);
              break;
          case 0x14:
              ds.push(a%b);
              break;
          case 0x16:
              ds.push(b&a);
              break;
          case 0x17:
              ds.push(b|a);
              break;
          case 0x18:
              ds.push(b^a);
              break;
          case 0x19:
              ds.push(b<<a);
              break;
          case 0x1a:
              ds.push(b>>a);
              break;
          case 0x1b:
              uint32_t ub = b;
              ds.push(ub>>a);
              break;
      }
    }

    if (debug)
        printf("a: 0x%x, b: 0x%x, result: 0x%x", a, b, ds.top());
}

void LSMVM::FPU(uint8_t opcode){

    float a, b;
    bool fneg = opcode == 0x25, i2f = opcode == 0x26, f2i = opcode == 0x27;
    if (fneg) {
      verifyOperands(ds, 1, "data");
      a = ds.top();
      ds.pop();
      ds.push(-a);
    } else if (i2f) {
      verifyOperands(ds, 1, "data");
      a = ds.top();
      ds.pop();
      ds.push((float)a);
    } else if (f2i) {
      verifyOperands(ds, 1, "data");
      a = ds.top();
      ds.pop();
      ds.push((int)a);
    } else {
      verifyOperands(ds, 2, "data");
      a = ds.top();
      ds.pop();
      b = ds.top();
      ds.pop();
      switch(opcode){
        case 0x20:
            ds.push(b+a);
            break;
        case 0x21:
            ds.push(b-a);
            break;
        case 0x22:
            ds.push(b*a);
            break;
        case 0x23:
            if (a == 0) {
                fprintf(stderr, "\033[1m\033[91mError:\033[0m Division by zero while executing instruction \"%s\".\n", opcodes[text[ip]].c_str());
                exit(EXIT_FAILURE);
            }
            ds.push(b/a);
            break;
        case 0x24:
            ds.push(fmod(a, b));
            break;
        }
    }

    if (debug)
        printf("a: %f, b: %f, result: %f", a, b, (float)ds.top());
}

void LSMVM::JUMP(uint8_t opcode, uint16_t label){

  verifyOperands(ds, 1, "data");

  if (debug)
      fprintf(stdout, "label: 0x%04x", label);

    int32_t a = ds.top();
    bool conditionalJump = true;
    switch (opcode) {
        case 0x30:
            conditionalJump = false;
            ip = ip+label-1;
            break;
        case 0x31:
            conditionalJump = false;
            if (debug)
                fprintf(stdout, ", push: 0x%04x", ip+3-1);
            cs.push(ip+3-1);
            if (debug)
                fprintf(stdout, ", go to: ip+0x%04x ", label);
            ip = (ip+label-1);
            break;
        case 0x32:
            ip = (a == 0 ? ip+label-1 : ip+2);
            if (debug)
                printf(", TOS: 0x%x", ds.top());
            break;
        case 0x33:
            ip = (a != 0 ? ip+label-1 : ip+2);
            break;
        case 0x34:
            ip = (a < 0 ? ip+label-1 : ip+2);
            break;
        case 0x35:
            ip = (a >= 0 ? ip+label-1 : ip+2);
            break;
        case 0x36:
            ip = (a > 0 ? ip+label-1 : ip+2);
            break;
        case 0x37:
            ip = (a <= 0 ? ip+label-1 : ip+2);
            break;
    }
    if (conditionalJump) ds.pop();
}

void LSMVM::RET(){

    verifyOperands(cs, 1, "call");

    ip = cs.top();
    cs.pop();

    if (debug)
        printf("%s0x%04x", "IP: ", ip);
}

void LSMVM::STACK(uint8_t opcode, uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0){

    switch (opcode) {
        uint32_t a, b, i, v;

        case 0x50:
            ds.push(b3);
            step();
            break;
        case 0x51:
            ds.push(parse32(b3, b2, b1, b0));
            ip+=4;
            break;
        case 0x52:
            ds.push(parse32(b3, b2, b1, b0));
            ip+=4;
            break;
        case 0x53:
            verifyOperands(ds, 1, "data");
            ds.pop();
            break;
        case 0x54:
            verifyOperands(ds, 1, "data");
            a = ds.top();
            ds.push(a);
            break;
        case 0x55:
            verifyOperands(ds, 1, "data");
            a = ds.top();
            ds.pop();
            b = ds.top();
            ds.pop();
            ds.push(a);
            ds.push(b);
            ds.push(a);
            break;
        case 0x56:
            verifyOperands(ds, 2, "data");
            a = ds.top();
            ds.pop();
            b = ds.top();
            ds.pop();
            ds.push(b);
            ds.push(a);
            ds.push(b);
            ds.push(a);
            break;
        case 0x57:
            verifyOperands(ds, 2, "data");
            a = ds.top();
            ds.pop();
            b = ds.top();
            ds.pop();
            ds.push(a);
            ds.push(b);
            break;
        case 0x60:
            if (debug)
                fprintf(stdout, "label: 0x%04x, ", parse16(b3, b2));
            ds.push(data[parse16(b3, b2)]);
            ip+=2;
            break;
        case 0x61:
            verifyOperands(ds, 1, "data");
            a = ds.top();
            ds.pop();
            if (debug)
                fprintf(stdout, "label: 0x%04x, ", parse16(b3, b2));
            data[parse16(b3, b2)] = a;
            ip+=2;
            break;
        case 0x62:
            verifyOperands(ds, 2, "data");
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            ds.push(data[a+i]);
            break;
        case 0x63:
            verifyOperands(ds, 3, "data");
            v = ds.top();
            ds.pop();
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            data[a+i] = v;
            break;
        case 0x64:
            verifyOperands(ds, 2, "data");
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            ds.push(data[a+i]);
            break;
        case 0x65:
            verifyOperands(ds, 3, "data");
            v = ds.top();
            ds.pop();
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            data[a+i] = v;
            break;
        case 0x66:
            verifyOperands(ds, 2, "data");
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            ds.push(data[a+i]);
            break;
        case 0x67:
            verifyOperands(ds, 3, "data");
            v = ds.top();
            ds.pop();
            i = ds.top();
            ds.pop();
            a = ds.top();
            ds.pop();
            data[a+i] = v;
            break;
    }

    if(debug)
        printf("TOS: 0x%x", ds.top());
}

void LSMVM::OTHERS(uint8_t opcode) {

    switch (opcode) {
        // case 0x00: do nothing
        case 0xF1:
            ds.push(getchar());
            break;
        case 0xF2:
            if (debug)
                fprintf(stdout, "putchar() '");

            verifyOperands(ds, 1, "data");
            fprintf(stdout, "%c", ds.top());
            ds.pop();

            if (debug)
                fprintf(stdout, "'");
            break;
    }
}

bool LSMVM::parse(const char* path)
{

  if (debug)
      fprintf(stdout, "Starting to parse!\n");
    reset();

    /* open binary file */
    FILE* ifp = fopen(path, "r");
    if (ifp == NULL) goto parse_fail;

    /* read and check magic number */
    uint8_t m;
    for (int i = 0; i < 4; i++)
    {
        if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
        magic <<= 8;
        magic |= (m & 0xff);
    }

    if (debug)
        fprintf(stdout, "Reading version...\n");

    /* read version */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    major_version = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    major_version |= (m & 0xff);
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    minor_version = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    minor_version |= (m & 0xff);

    if (debug)
        fprintf(stdout, "Reading bss size...\n");

    /* read bss size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    bss_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    bss_size |= (m & 0xff);

    if (debug)
        fprintf(stdout, "Reading data size... ");

    /* read data size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    data_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    data_size |= (m & 0xff);

    if (debug)
        fprintf(stdout, "(%x)\nCreating data array...\n", data_size + bss_size);

    /* alocate data array */
    data = new(std::nothrow) uint32_t[data_size+bss_size];
    memset(data+data_size, 0x0, 4*bss_size);

    /* read data variables */
    for (int j = 0; j < data_size; j++)
    {
        uint32_t v = 0;
        for (int i = 0; i < 4; i++)
        {
            if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
            v <<= 8;
            v |= (m & 0xff);
        }
        data[j] = v;
    }

    if (debug)
        fprintf(stdout, "Reading text size... ");

    /* read text size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    text_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    text_size |= (m & 0xff);

    if (debug)
        fprintf(stdout, "(%x)\nCreating text array...\n", text_size);

    /* alocate text array */
    text = new(std::nothrow) uint8_t[text_size];

    /* read text instructions */
    for (int j = 0; j < text_size; j++)
    {
        if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
        text[j] = m;
    }

    if (debug)
        fprintf(stdout, "Parsing completed.\n");

    /* fill opcodes array */
    opcodes[0x10] = "iadd"   ;
    opcodes[0x11] = "isub"   ;
    opcodes[0x12] = "imul"   ;
    opcodes[0x13] = "idiv"   ;
    opcodes[0x14] = "irem"   ;
    opcodes[0x15] = "ineg"   ;
    opcodes[0x16] = "iand"   ;
    opcodes[0x17] = "ior"    ;
    opcodes[0x18] = "ixor"   ;
    opcodes[0x19] = "ishl"   ;
    opcodes[0x1a] = "ishr"   ;
    opcodes[0x1b] = "iushr"  ;
    opcodes[0x20] = "fadd"   ;
    opcodes[0x21] = "fsub"   ;
    opcodes[0x22] = "fmul"   ;
    opcodes[0x23] = "fdiv"   ;
    opcodes[0x24] = "frem"   ;
    opcodes[0x25] = "fneg"   ;
    opcodes[0x26] = "i2f"    ;
    opcodes[0x27] = "f2i"    ;
    opcodes[0x40] = "ret"    ;
    opcodes[0x30] = "goto"   ;
    opcodes[0x31] = "jsr"    ;
    opcodes[0x32] = "ifeq"   ;
    opcodes[0x33] = "ifne"   ;
    opcodes[0x34] = "iflt"   ;
    opcodes[0x35] = "ifge"   ;
    opcodes[0x36] = "ifgt"   ;
    opcodes[0x37] = "ifle"   ;
    opcodes[0x50] = "bipush" ;
    opcodes[0x51] = "ipush"  ;
    opcodes[0x52] = "fpush"  ;
    opcodes[0x53] = "pop"    ;
    opcodes[0x54] = "dup"    ;
    opcodes[0x55] = "dup_x1" ;
    opcodes[0x56] = "dup2"   ;
    opcodes[0x57] = "swap"   ;
    opcodes[0x60] = "load"   ;
    opcodes[0x61] = "store"  ;
    opcodes[0x62] = "baload" ;
    opcodes[0x63] = "bastore";
    opcodes[0x64] = "iaload" ;
    opcodes[0x65] = "iastore";
    opcodes[0x66] = "faload" ;
    opcodes[0x67] = "fastore";
    opcodes[0x00] = "nop"    ;
    opcodes[0xF0] = "halt"   ;
    opcodes[0xF1] = "read"   ;
    opcodes[0xF2] = "write"  ;

    return true;

parse_fail:
    reset();
    return false;
}

void LSMVM::reset()
{
    delete [] data;
    delete [] text;
}

void LSMVM::show()
{
    fprintf(stdout, "magic: 0x%08x\n", magic);
    fprintf(stdout, "major_version: %d\n", major_version);
    fprintf(stdout, "minor_version: %d\n", minor_version);
    fprintf(stdout, "data_size: %d (0x%0x)\n", data_size, data_size);
    fprintf(stdout, "bss_size: %d (0x%0x)\n", bss_size, bss_size);
    fprintf(stdout, "data[] = {\n");
    for (int j = 0; j < data_size; j++)
    {
        fprintf(stdout, "  0x%08x", data[j]);
    }
    fprintf(stdout, "\n}\n");

    fprintf(stdout, "text_size: %d (0x%0x)\n", text_size, text_size);
    fprintf(stdout, "text[] = {\n");
    for (int j = 0; j < text_size; j++)
    {
        fprintf(stdout, "  0x%02x", text[j]);
    }
    fprintf(stdout, "\n}\n");
}

void LSMVM::verifyOperands(std::stack<uint32_t> stack, unsigned int n, std::string name) {
    unsigned int size = stack.size();
    if(size < n && n == 1) {
        fprintf(stderr, "\033[1m\033[91mError:\033[0m Incorrect number of operands in the %s stack while executing instruction \"%s\". Should be present at least %d operand, but %d found. \n", name.c_str(), opcodes[text[ip]].c_str(), n-1, size);
        exit(EXIT_FAILURE);
    } else if(size < n) {
        fprintf(stderr, "\033[1m\033[91mError:\033[0m Incorrect number of operands in the %s stack while executing instruction \"%s\". Should be present at least %d operands, but %d found. \n", name.c_str(), opcodes[text[ip]].c_str(), n, size);
        exit(EXIT_FAILURE);
    }
}

static const char* options =
    "OPTIONS:\n"
    "=======\n"
    " -h            this help\n"
    " -x            show contents in ascii-hexa\n";

int main(int argc, char* argv[])
{
    /* mode variables */
    bool show_only = false;

    /* process command line arguments */
    int op = -1;
    while ((op = getopt(argc, argv, "hs")) != -1)
    {
        switch (op)
        {
            case 'h':
                printf("%s [OPTIONS] lsm-file\n%s\n", argv[0], options);
                return 0;

            case 's':
                show_only = true;
                break;

            default:
                fprintf(stderr, "Bad option\n");
                printf("%s [OPTIONS] input-file\n%s\n", argv[0], options);
                return EXIT_FAILURE;
        }
    }

    /* check if mandatory argument is present */
    if (argc - optind != 1)
    {
        fprintf(stderr, "Mandatory argument is not present\n");
        return EXIT_FAILURE;
    }

    /* create virtual machine */
    LSMVM vm(argv[optind]);
    if (vm.bad())
    {
        fprintf(stderr, "LSMVM not good\n");
        return EXIT_FAILURE;
    }

    /* show or execute */
    if (show_only)
    {
        vm.show();
    }
    else
    {
        vm.run();
    }

    /* that's all */
    return 0;
}
