#ifndef VAR_TYPES
#define VAR_TYPES

typedef enum {
    TYPE_UNKNOWN = 0,
    TYPE_PEFILE,
    TYPE_PESECTION,
    TYPE_PEIMPORT,
    TYPE_PEEXPORT,
    TYPE_PEHEADER,
    TYPE_PEDIRENTRY,
    TYPE_INT,
    TYPE_STRING,
    TYPE_PEIMPORTS,
    TYPE_PEEXPORTS,
    TYPE_PESECTIONS,
    TYPE_PEFUNCTION,
    TYPE_PEFUNCTIONS,
    TYPE_PEOPTIONALHEADER
} Type;

static char* TypeToString(Type type) {
    switch(type) {
        case TYPE_PEFILE:
            return "PEFile";
        case TYPE_PESECTION:
            return "PESection";
        case TYPE_PEIMPORT:
            return "PEImport";
        case TYPE_PEEXPORT:
            return "PEExport";
        case TYPE_PEHEADER:
            return "PEHeader";
        case TYPE_INT:
            return "int";
        case TYPE_STRING:
            return "string";
        case TYPE_PEIMPORTS:
            return "PEImports";
        case TYPE_PEEXPORTS:
            return "PEExports";
        case TYPE_PESECTIONS:
            return "PESections";
        case TYPE_PEOPTIONALHEADER:
            return "PEOptionalHeader";
        case TYPE_PEFUNCTION:
            return "PEFunction";
        case TYPE_PEFUNCTIONS:
            return "PEFunctions";
        default:
            return "unknown";
    }
}


#endif