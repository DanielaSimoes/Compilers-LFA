#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#include <stack>
#include <map>

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

    bool good_ = false;
    inline bool good() { return good_; }
    inline bool bad() { return ! good_; }

    uint32_t magic = 0;
    uint16_t major_version = 0,  
             minor_version = 0;

    LSMVM() {}
    LSMVM(const char* path);

    bool parse(const char* path);

    void reset();
    void show();
    void step();
    void run();

    void aaa();
    void bipush();

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

void LSMVM::step()
{
	ip++;
}

void LSMVM::run()
{
    fprintf(stderr, "execution still not implemented\n");
    ip = 0;
    while (ip < text_size && text[ip] != 0xf0) step();
}

bool LSMVM::parse(const char* path)
{
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

    /* read version */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    major_version = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    major_version |= (m & 0xff);
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    minor_version = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    minor_version |= (m & 0xff);

    /* read bss size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    bss_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    bss_size |= (m & 0xff);

    /* read data size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    data_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    data_size |= (m & 0xff);

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

    /* read text size */
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    text_size = (m & 0xff) << 8;
    if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
    text_size |= (m & 0xff);

    /* alocate text array */
    text = new(std::nothrow) uint8_t[text_size];

    /* read text instructions */
    for (int j = 0; j < text_size; j++)
    {
        if (fread(&m, 1, 1, ifp) != 1) goto parse_fail;
        text[j] = m;
    }

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

    fprintf(stdout, "bss_size: %d (0x%0x)\n", bss_size, bss_size);

    fprintf(stdout, "data_size: %d (0x%0x)\n", data_size, data_size);
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
