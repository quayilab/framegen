#include <iostream>
#include <argtable3.h>
#include "model.h"

using namespace std;

#define REG_EXTENDED 1
#define REG_ICASE (REG_EXTENDED << 1)

/* _stripSvg implements the actions for strip-svg */
int _stripSvg(int v, const char *outfile, const char *infile)
    {
        if (v > 0) {
            printf("stripSvg syntax matched OK.\n");
            printf("stripSvg matched OK.\n");
            printf("  verbose = %d\n", v);
            printf("  outfile = \"%s\"\n", outfile);
            printf("  infile  = \"%s\"\n", infile);
        }
    stripSvg(string(infile), string(outfile), "0.0.1", v > 0);
    return 0; 
    }

/* _makeYaml implements the actions for make-yaml */
int _makeYaml(int v, const char *outfile, const char *infile)
    {
        if (v > 0) {
            printf("makeYaml syntax matched OK.\n");
            printf("receiving arguments:\n");
            printf("  verbose = %d\n", v);
            printf("  outfile = \"%s\"\n", outfile);
            printf("  infile  = \"%s\"\n", infile);
        }
    saveToYaml(string(infile), string(outfile), "0.0.1", v > 0);
    return 0;
    }

// TODO: create subcommand "render-component" to test rendering component loaded from file

/* _help implements the actions for help */
int _help(int help, int version, const char *progname,
            void **argtable_stripSvg, void **argtable_makeYaml, void **argtable_help)
    {
    /* --help option */
    if (help)
        {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout,argtable_stripSvg,"\n");
        printf("       %s", progname);
        arg_print_syntax(stdout,argtable_makeYaml,"\n");
        printf("       %s", progname);
        arg_print_syntax(stdout,argtable_help,"\n");
        printf("This program demonstrates the use of the argtable2 library\n");
        printf("for parsing multiple command line syntaxes.\n");
        arg_print_glossary(stdout,argtable_stripSvg,"      %-20s %s\n");
        arg_print_glossary(stdout,argtable_makeYaml,"      %-20s %s\n");
        arg_print_glossary(stdout,argtable_help,"      %-20s %s\n");
        return 0;
        }

    /* --version option */
    if (version)
        {
        printf("'%s' example program for the \"argtable\" command line argument parser.\n",progname);
        return 0;
        }

    /* no command line options at all */
    printf("Try '%s --help' for more information.\n", progname);
    return 0;
    }


int main(int argc, char **argv)
    {
    /* SYNTAX 1: insert [-nvR] <file> [file]...  -o <file> */
    struct arg_rex  *cmd_stripSvg     = arg_rex1(NULL,  NULL,  "strip-svg", NULL, REG_ICASE, NULL);
    struct arg_lit  *verbose_stripSvg = arg_lit0("v", "verbose", "verbose messages");
    struct arg_file *infile_stripSvg  = arg_file0(NULL, NULL,  "<input>", "input svg file");
    struct arg_file *outfile_stripSvg = arg_file0("o",  NULL,  "<output>", "output svg file (default is \"-\")");
    struct arg_end  *end_stripSvg     = arg_end(20);
    void* argtable_stripSvg[] = {cmd_stripSvg, verbose_stripSvg, infile_stripSvg, outfile_stripSvg, end_stripSvg};
    int nerrors_stripsvg;

    /* SYNTAX 1: insert [-nvR] <file> [file]...  -o <file> */
    struct arg_rex  *cmd_makeYaml     = arg_rex1(NULL,  NULL,  "make-yaml", NULL, REG_ICASE, NULL);
    struct arg_lit  *verbose_makeYaml = arg_lit0("v", "verbose", "verbose messages");
    struct arg_file *infile_makeYaml  = arg_file0(NULL, NULL,  "<input>", "input svg file");
    struct arg_file *outfile_makeYaml = arg_file0("o",  NULL,  "<output>", "output yaml file (default is \"-\")");
    struct arg_end  *end_makeYaml     = arg_end(20);
    void* argtable_makeYaml[] = {cmd_makeYaml, verbose_makeYaml, infile_makeYaml, outfile_makeYaml, end_makeYaml};
    int nerrors_makeYaml;

    /* SYNTAX 4: [-help] [-version] */
    struct arg_lit  *cmd_help   = arg_lit0(NULL,"help",     "print this help and exit");
    struct arg_lit  *version_help = arg_lit0(NULL,"version",  "print version information and exit");
    struct arg_end  *end_help     = arg_end(20);
    void* argtable_help[] = {cmd_help, version_help, end_help};
    int nerrors_help;

    const char* progname = "ptool";
    int exitcode=0;

    /* verify all argtable[] entries were allocated sucessfully */
    if (arg_nullcheck(argtable_stripSvg)!=0 ||
        arg_nullcheck(argtable_makeYaml)!=0 ||
        arg_nullcheck(argtable_help)!=0 )
        {
        /* NULL entries were detected, some allocations must have failed */
        printf("%s: insufficient memory\n",progname);
        exitcode=1;
        goto exit;
        }

    /* set any command line default values prior to parsing */
    outfile_stripSvg->filename[0]="-";
    outfile_makeYaml->filename[0]="-";

    /* Above we defined a separate argtable for each possible command line syntax */
    /* and here we parse each one in turn to see if any of them are successful    */
    nerrors_stripsvg = arg_parse(argc,argv,argtable_stripSvg);
    nerrors_makeYaml = arg_parse(argc,argv,argtable_makeYaml);
    nerrors_help = arg_parse(argc,argv,argtable_help);

    /* Execute the appropriate main<n> routine for the matching command line syntax */
    /* In this example program our alternate command line syntaxes are mutually     */
    /* exclusive, so we know in advance that only one of them can be successful.    */
    if (nerrors_stripsvg==0)
        exitcode = _stripSvg(verbose_stripSvg->count, *outfile_stripSvg->filename, *infile_stripSvg->filename);
    else if (nerrors_makeYaml==0)
        exitcode = _makeYaml(verbose_makeYaml->count, *outfile_makeYaml->filename, *infile_makeYaml->filename);
    else if (nerrors_help==0)
        exitcode = _help(cmd_help->count, version_help->count, progname,
                           argtable_stripSvg, argtable_makeYaml, argtable_help);
    else
        {
        /* We get here if the command line matched none of the possible syntaxes */
        if (cmd_stripSvg->count > 0)
            {
            /* here the cmd1 argument was correct, so presume syntax 1 was intended target */ 
            arg_print_errors(stdout,end_stripSvg, progname);
            printf("usage: %s ", progname);
            arg_print_syntax(stdout,argtable_stripSvg,"\n");
            }
        else if (cmd_makeYaml->count > 0)
            {
            /* here the cmd1 argument was correct, so presume syntax 1 was intended target */ 
            arg_print_errors(stdout,end_makeYaml, progname);
            printf("usage: %s ", progname);
            arg_print_syntax(stdout,argtable_makeYaml,"\n");
            }
        else
            {
            /* no correct cmd literals were given, so we cant presume which syntax was intended */
            printf("%s: missing <insert|remove|search> command.\n",progname); 
            printf("usage 1: %s ", progname);  arg_print_syntax(stdout,argtable_stripSvg,"\n");
            printf("usage 1: %s ", progname);  arg_print_syntax(stdout,argtable_makeYaml,"\n");
            printf("usage 4: %s",  progname);  arg_print_syntax(stdout,argtable_help,"\n");
            }
        }

exit:
    /* deallocate each non-null entry in each argtable */
    arg_freetable(argtable_stripSvg,sizeof(argtable_stripSvg)/sizeof(argtable_stripSvg[0]));
    arg_freetable(argtable_makeYaml,sizeof(argtable_makeYaml)/sizeof(argtable_makeYaml[0]));
    arg_freetable(argtable_help,sizeof(argtable_help)/sizeof(argtable_help[0]));

    return exitcode;
}