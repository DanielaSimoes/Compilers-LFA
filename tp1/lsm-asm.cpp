#include <stdint.h>
#include "lsm-parser.h"
#include "lsm-lexer.h"
#include "lsm-data.h"


static const char* options =
    "OPTIONS:\n"
    "=======\n"
    " -h            this help\n"
    " -o file-path  output file (default: stdout)\n"
    " -s            syntax only\n";


int yyparse(LSMData*);

int main(int argc, char *argv[])
{
    /* instantiate main data structure and init it with default values */
    LSMData lsm_data;
    FILE* ofp = NULL;

    if (yylex_init(&lsm_data.scanner))
    {
        fprintf(stderr, "Fail initing scanner\n");
        return(EXIT_FAILURE);
    }

    lsm_data.lbl_table = new LabelTable;

    lsm_data.syntax_only = false;
    lsm_data.error_cnt = 0;
    lsm_data.bss_size = 0;
    lsm_data.text_size = 0;
    lsm_data.first_time = true;

    /* process command line arguments */
    int op = -1;
    while ((op = getopt(argc, argv, "ho:s")) != -1)
    {
        switch (op)
        {
            case 'h':
                printf("%s [OPTIONS] lsm-file\n%s\n", argv[0], options);
                return 0;

            case 'o':
                if ((ofp = fopen(optarg, "w")) == NULL)
                {
                    fprintf(stderr, "Fail opening output file %s\n", optarg);
                    return EXIT_FAILURE;
                }
                break;

            case 's':
                lsm_data.syntax_only = true;
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

    /* set up input stream */
    FILE* ifp = fopen(argv[optind], "r");
    if (ifp == NULL)
    {
        fprintf(stderr, "Fail opening input file %s\n", argv[optind]);
        return EXIT_FAILURE;
    }

    yyset_in(ifp, lsm_data.scanner);

    /* set up output file, case option -o is not given */
    if (ofp == NULL)
    {
        char* p = argv[optind];
        char* q;
        int n = strlen(p);
        if ((q = strrchr(p, '.')) != NULL)
        {
            n = q - p;
        }
        char ofname[n+1];
        strncpy(ofname, p, n);
        strcpy(ofname+n, ".bsm");
        if ((ofp = fopen(ofname, "w")) == NULL)
        {
            fprintf(stderr, "Fail opening output file %s\n", ofname);
            return EXIT_FAILURE;
        }
    }

    /* call the parser */
    yyparse(&lsm_data);

    lsm_data.first_time = false;

    /* reset the scanner */
    ifp = fopen(argv[optind], "r");
    yyset_in(ifp, lsm_data.scanner);

    /* call the parser a second time */
    yyparse(&lsm_data);

    /* check for errors */
    if (lsm_data.error_cnt) {
        fprintf(stdout, "\n%d errors found. Binary file not generated.\n", lsm_data.error_cnt);
    }
    else {
        /* print data vector for debug */
        int address = 0;
        fprintf(stdout, "\n");
        fprintf(stdout, "Data Vector content:");
        if (!lsm_data.data.size()) {
            fprintf(stdout, " Empty");
        }
        else {
            fprintf(stdout, "\n");
            for(std::vector<uint8_t>::iterator it = lsm_data.data.begin(); it != lsm_data.data.end(); ++it) {
                if (address % 4 == 0)
                    fprintf(stdout, "\n %5x:\t", address);
                address++;
                fprintf(stdout, "%x\t", *it);
            }
        }
        printf("\n\n");
        
        /* print text vector for debug */
        address = 0;
        fprintf(stdout, "Text Vector content:");
        if (!lsm_data.text.size()) {
            fprintf(stdout, " Empty");
        }
        else {
            fprintf(stdout, "\n\ntext_size: %5d\n", lsm_data.text_size);
            for(std::vector<uint8_t>::iterator it = lsm_data.text.begin(); it != lsm_data.text.end(); ++it) {
                if (address % 4 == 0)
                    fprintf(stdout, "\n %5x:\t", address);
                address++;
                fprintf(stdout, "%x\t", *it);
            }
        }
        printf("\n\n");
        
        /* print symbol table for debug */
        fprintf(stdout, "Symbol table:\n\n");
        fprintf(stdout, "%20s%20s%20s\n", "Name", "Tipo", "Value");
        for(auto p: lsm_data.lbl_table->table) {
            fprintf(stdout, "%20s%20s%20d\n", p.first.c_str(), std::get<0>(p.second).c_str(), std::get<1>(p.second));
        }
        printf("\n");

    /* clean up and quit */
    yylex_destroy(lsm_data.scanner);
    delete lsm_data.lbl_table;
    return 0;
}
