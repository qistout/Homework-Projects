#include "asdl_parser.h"
FILE *openfile(const char *filename,const char *mode){
    FILE *fp=fopen(filename,mode);
    if (fp==nullptr){
        perror(filename);
        exit(1);
    }
    return fp;
}
int main(int argc,char *argv[]){
    if (argc!=4){
        fprintf(stdout,"usage: %s Python.asdl Python-ast.h Python-ast.c\n",argv[0]);
        return 0;
    }
    FILE *fp;
    const char *asdlfile=argv[1],*asdl_h=argv[2],*asdl_c=argv[3];
    fp=openfile(asdlfile,"r");
    ASDLParser parser;
    auto *mod=parser.ParseFile(fp);
    fclose(fp);

    fp=openfile(asdl_h,"w");
    fprintf(fp,"/*.h generated by asdl*/\n");
    fprintf(fp,"\n");
    fprintf(fp,"#pragma once\n");
    fprintf(fp,"#include \"common.h\"\n");
    fprintf(fp,"#include \"asdl.h\"\n");
    fprintf(fp,"\n");
    mod->PrintDef(fp);
    fclose(fp);

    fp=openfile(asdl_c,"w");
    fprintf(fp,"/*.cc generated by asdl*/\n");
    fprintf(fp,"\n");
    fprintf(fp,"#include \"python_ast.h\"\n");
    fprintf(fp,"\n");
    mod->PrintImplement(fp);
    fclose(fp);

    //printf("asdl main done.\n");
    return 0;
}
