//Walk the absract syntax tree and compile each expression
void compile(){
  FILE *fp;
  fp = fopen("test.assembly", "w");

  fputs("args 0\n", fp);
  fputs("gvar x\n", fp);
  fputs("gvar y\n", fp);

  fputs("gvar =\n", fp);
  fputs("call 2\n", fp);
  fclose(fp);



}

//Read the assembly file and write in bytes, use fread and fwrite
void assembler(){
  //TODO
}
