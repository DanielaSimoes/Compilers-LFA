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

    /* clean up and quit */
    yylex_destroy(lsm_data.scanner);
    delete lsm_data.lbl_table;
    return 0;
}

