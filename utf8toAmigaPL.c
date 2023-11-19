#include "utf8toAmigaPL.h"

#include <stdio.h>
#include <string.h>

#define FILE_SUFFIX ".apl"

// UTF-8 BOM
const int UTF8BOM[] = { 0xEF, 0xBB, 0xBF };

#pragma GCC push_options
#pragma GCC optimize("O0")
static const char *VERSION = "$VER: " __PRG_FILE__ " " __PRG_VERSION__;
#pragma GCC pop_options

void skipUTF8BOMIfExists(FILE *fileIn)
{
    int oneChar;
    for (int i = 0; i < sizeof(UTF8BOM) / sizeof(int); i++)
    {
        oneChar = fgetc(fileIn);
        if (feof(fileIn) || oneChar != UTF8BOM[i])
        {
            fseek(fileIn, SEEK_SET, 0);
            return;
        }
    }
}

void help()
{
    printf("Wrong number of parameters!\n");
    printf("usage:\n"
           " " __PRG_FILE__ " [input-file] [output-file]\n"
           " [input-file] - input file to convert (with UTF8 content)\n"
           " [output-file] - optional output file (with AmigaPL content), be default output is [input-file] with '.apl' suffix\n"
           "example:\n"
           " " __PRG_FILE__ " file.UTF8.txt file.AmigaPL.txt\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 2)
    {
        help();
        return 0;
    }

    FILE *fileIn = fopen(argv[1], "r");
    if (fileIn)
    {
        skipUTF8BOMIfExists(fileIn);

        int len = (argc == 3) ? strlen(argv[2]) : (strlen(argv[1]) + strlen(FILE_SUFFIX));
        char outputFileName[len + 1];
        sprintf(outputFileName, "%s%s", argc == 3 ? argv[2] : argv[1], argc == 3 ? "" : FILE_SUFFIX);

        FILE *fileOut = fopen(outputFileName, "w+");
        if (fileOut)
        {
            int oneChar;
            while (1)
            {
                oneChar = fgetc(fileIn);
                if (feof(fileIn))
                    break;

                switch (oneChar)
                {
                    case CR:
                        break; // ignore CR
                    case 0xC3:
                        oneChar = fgetc(fileIn);
                        if (feof(fileIn))
                            break;
                        switch (oneChar)
                        {
                            case UTF8_O: // Ó
                                fputc(AMIGAPL_O, fileOut);
                                break;
                            case UTF8_o: // ó
                                fputc(AMIGAPL_o, fileOut);
                                break;
                        }
                        break;
                    case 0xC4:
                        oneChar = fgetc(fileIn);
                        if (feof(fileIn))
                            break;
                        switch (oneChar)
                        {
                            case UTF8_A: // Ą
                                fputc(AMIGAPL_A, fileOut);
                                break;
                            case UTF8_C: // Ć
                                fputc(AMIGAPL_C, fileOut);
                                break;
                            case UTF8_E: // Ę
                                fputc(AMIGAPL_E, fileOut);
                                break;
                            case UTF8_a: // ą
                                fputc(AMIGAPL_a, fileOut);
                                break;
                            case UTF8_c: // ć
                                fputc(AMIGAPL_c, fileOut);
                                break;
                            case UTF8_e: // ę
                                fputc(AMIGAPL_e, fileOut);
                                break;
                        }
                        break;
                    case 0xC5:
                        oneChar = fgetc(fileIn);
                        if (feof(fileIn))
                            break;
                        switch (oneChar)
                        {
                            case UTF8_L: // Ł
                                fputc(AMIGAPL_L, fileOut);
                                break;
                            case UTF8_N: // Ń
                                fputc(AMIGAPL_N, fileOut);
                                break;
                            case UTF8_S: // Ś
                                fputc(AMIGAPL_S, fileOut);
                                break;
                            case UTF8_Z: // Ż
                                fputc(AMIGAPL_Z, fileOut);
                                break;
                            case UTF8_X: // Ż
                                fputc(AMIGAPL_X, fileOut);
                                break;
                            case UTF8_l: // ł
                                fputc(AMIGAPL_l, fileOut);
                                break;
                            case UTF8_n: // ń
                                fputc(AMIGAPL_n, fileOut);
                                break;
                            case UTF8_s: // ś
                                fputc(AMIGAPL_s, fileOut);
                                break;
                            case UTF8_z: // ż
                                fputc(AMIGAPL_z, fileOut);
                                break;
                            case UTF8_x: // ź
                                fputc(AMIGAPL_x, fileOut);
                                break;
                        }
                        break;
                    case 0xE2:
                        oneChar = fgetc(fileIn);
                        if (feof(fileIn))
                            break;
                        switch (oneChar)
                        {
                            case 0x80:
                                oneChar = fgetc(fileIn);
                                if (feof(fileIn))
                                    break;
                                switch (oneChar)
                                {
                                    case UTF8_LEFT_DOUBLE_QUOTATION_MARK:
                                    case UTF8_RIGHT_DOUBLE_QUOTATION_MARK:
                                    case UTF8_DOUBLE_LOW9_QUOTATION_MARK:
                                    case UTF8_DOUBLE_HIGH_REVERSED9_QUOTATION_MARK:
                                        fputc(AMIGA_DOUBLE_QUOTATION_MARK, fileOut);
                                        break;
                                    case UTF8_HORIZONTAL_ELLIPSIS:
                                        fputs("...", fileOut);
                                        break;
                                }
                                break;
                        }
                        break;
                    default:
                        fputc(oneChar, fileOut);
                }
            }
            fclose(fileOut);
        }
        else
        {
            printf("Open output file '%s' failed!\n", outputFileName);
        }

        fclose(fileIn);
    }
    else
    {
        printf("Open input file '%s' failed!\n", argv[1]);
    }

    return 0;
}
