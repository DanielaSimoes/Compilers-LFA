#include <getopt.h>
#include <stdio.h>
#include <stdint.h>

#include "ast.h"
#include "symtable.h"
#include "parser.h"
#include "lexer.h"
#include "main-data.h"


const char* options =
    "OPTIONS:\n"
    "=======\n"
    " -h            this help\n"
    " -o file-path  output file (default: stdout)\n"
    " -s            syntax only (default)\n"
    " -t            show AST tree\n"
    " -g            generate LSM code\n"
	"\n";


const char* inc =
            "printInt:\n"
            "ipush 28 \n"
"Print1:     dup2 \n"
            "iushr \n"
            "ipush 0xF \n"
            "iand \n"
            "jsr pNibble \n"
            "dup \n"
            "ifeq Print2 \n"
            "ipush 4 \n"
            "isub \n"
            "goto Print1 \n"
"Print2:     pop \n"
            "ret \n";


int main(int argc, char *argv[])
{
    /* instantiate main data structure and init it with default values */
    MainData main_data;

    if (yylex_init(&main_data.scaninfo))
    {
        fprintf(stderr, "Fail initing scanner\n");
        return(EXIT_FAILURE);
    }

    main_data.symtable = new SymTable;
    main_data.ast = NULL;
    main_data.no_of_errors = 0;

	FILE* ofp = stdout;
	bool show = false;
	bool lsm = false;

    /* process command line arguments */
    int op = -1;
    while ((op = getopt(argc, argv, "ho:stg")) != -1)
    {
        switch (op)
        {
            case 'h':
                printf("%s [OPTIONS] path-to-image\n%s\n", argv[0], options);
                return 0;

            case 'o':
                if ((ofp = fopen(optarg, "w")) == NULL)
                {
                    fprintf(stderr, "Fail opening output file %s\n", optarg);
                    return EXIT_FAILURE;
                }
                break;

            case 's':
                break;

            case 'g':
				lsm = true;
                break;

            case 't':
				show = true;
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

    yyset_in(ifp, main_data.scaninfo);

    /* call the parser */
    if (yyparse(&main_data) == 0)
    {
		if (show) main_data.ast->show(0);
		if (lsm) main_data.ast->generateLSM(ofp);
    }

    fprintf(ofp, ";includes\n");
    fprintf(ofp, "%s\n", inc);

    /* clean up and quit */
    yylex_destroy(main_data.scaninfo);
    delete main_data.symtable;
    delete main_data.ast;
    return 0;
}
