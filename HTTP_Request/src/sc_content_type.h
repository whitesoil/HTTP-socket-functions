#ifndef _SC_CONTENT_TYPE_H

#define SC_EXTENTION_MAXSIZE 10
#define SC_CONTENT_TYPE_NUM 70
#define SC_MIMETYPE_MAXSIZE 80

typedef struct sc_content_type_t {
    char    extension[SC_EXTENTION_MAXSIZE];
    char    mime_type[SC_MIMETYPE_MAXSIZE];
} sc_content_type_t;

sc_content_type_t sc_content_type_table[] = {
    {".aac", "audio/aac"},
    {".abw","application/x-abiword"},
    {".arc","application/octet-stream"},
    {".avi","video/x-msvideo"},
    {".azw","application/vnd.amazon.ebook"},
    {".bin","application/octet-stream"},
    {".bz","application/x-bzip"},
    {".bz2","application/x-bzip2"},
    {".csh","application/x-csh"},
    {".css","text/css"},
    {".csv","text/csv"},
    {".doc","application/msword"},
    {".docx","application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
    {".eot","application/vnd.ms-fontobject"},
    {".epub","application/epub+zip"},
    {".es","application/ecmascript"},
    {".gif","image/gif"},
    {".htm","text/html"},
    {".html","text/html"},
    {".ico","image/x-icon"},
    {".ics","text/calendar"},
    {".jar","application/java-archive"},
    {".jpg","image/jpeg"},
    {".jpeg","image/jpeg"},
    {".js","application/javascript"},
    {".json","application/json"},
    {".mid","audio/midi"},
    {".midi","audio/midi"},
    {".mpeg","video/mpeg"},
    {".mpkg","application/vnd.apple.installer+xml"},
    {".odp","application/vnd.oasis.opendocument.presentation"},
    {".ods","application/vnd.oasis.opendocument.spreadsheet"},
    {".odt","application/vnd.oasis.opendocument.text"},
    {".oga","audio/ogg"},
    {".ogv","video/ogg"},
    {".ogx","application/ogg"},
    {".otf","font/otf"},
    {".png","image/png"},
    {".pdf","application/pdf"},
    {".ppt","application/vnd.ms-powerpoint"},
    {".pptx","application/vnd.openxmlformats-officedocument.presentationml.presentation"},
    {".rar","application/x-rar-compressed"},
    {".rtf","application/rtf"},
    {".sh","application/x-sh"},
    {".svg","image/svg+xml"},
    {".swf","application/x-shockwave-flash"},
    {".tar","application/x-tar"},
    {".tif","image/tiff"},
    {".tiff","image/tiff"},
    {".ts","application/typescript"},
    {".ttf","font/ttf"},
    {".vsd","application/vnd.util/visio"},
    {".wav","audio/wav"},
    {".weba","audio/webm"},
    {".webm","video/webm"},
    {".webp","image/webp"},
    {".woff","font/woff"},
    {".woff2","font/woff2"},
    {".whml","application/xhtml+xml"},
    {".xls","application/vnd.ms-excel"},
    {".xlsx","application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
    {".xml","application/xml"},
    {".xul","application/vnd.mozilla.xul+xml"},
    {".zip","application/zip"},
    {".3gp","video/3gpp"},
    {".3gp","audio/3gpp"}, // if it doesn't contain video
    {".3g2","video/3gpp2"},
    {".3g2","audio/3gpp2"},// if it doesn't contain video
    {".7z","application/x-7z-compressed"},
    {" ","text/plain"}
};

#endif