#include <stdio.h>
#include "libtdms.h"

static const char * FILE_NAME   = "Example";
static const char * FILE_DESC   = "Description";

int main()
{
    TDMSFileHandle file =0;
    printf("hello world\n");
    TDMS_CreateFileEx(  "test.tdms",TDMS_Streaming, TDMS_ByteOrderBigEndian ,0,
                        FILE_NAME, FILE_DESC,"", "", &file);
return 0;
}