#ifndef stdio_nowarn_h
#define stdio_nowarn_h

#include <stdio.h>

#define fread_nowarn(a,b,c,d)  if(fread(a,b,c,d)) {}
#define fwrite_nowarn(a,b,c,d) if(fwrite(a,b,c,d)) {}

#endif
