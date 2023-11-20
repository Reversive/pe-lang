#ifndef VAR_TYPES
#define VAR_TYPES

typedef enum {
    TYPE_UNKNOWN = 0,
    TYPE_PEFILE,
    TYPE_PESECTION,
    TYPE_PEIMPORT,
    TYPE_PEEXPORT,
    TYPE_PEHEADER,
    TYPE_PERESOURCE,
    TYPE_PESIGNATURE,
    TYPE_PEDIRENTRY,
    TYPE_INT,
    TYPE_STRING,
    TYPE_BYTE
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
        case TYPE_PERESOURCE:
            return "PEResource";
        case TYPE_PESIGNATURE:
            return "PESignature";
        case TYPE_PEDIRENTRY:
            return "PEDirEntry";
        case TYPE_INT:
            return "int";
        case TYPE_STRING:
            return "string";
        case TYPE_BYTE:
            return "byte";
        default:
            return "unknown";
    }
}


#endif