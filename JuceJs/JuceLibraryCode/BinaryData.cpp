/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== packages.config ==================
static const unsigned char temp_binary_data_0[] =
"\xef\xbb\xbf<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
"<packages>\n"
"  <package id=\"v8.redist-v140-x86\" version=\"7.4.288.11\" targetFramework=\"native\" />\n"
"  <package id=\"v8.redist-v141-x64\" version=\"7.4.288.26\" targetFramework=\"native\" />\n"
"  <package id=\"v8.redist-v141-x86\" version=\"7.4.288.28\" targetFramework=\"native\" />\n"
"  <package id=\"v8.redist-v142-x86\" version=\"7.5.288.23\" targetFramework=\"native\" />\n"
"  <package id=\"v8-v140-x86\" version=\"7.4.288.11\" targetFramework=\"native\" />\n"
"  <package id=\"v8-v141-x64\" version=\"7.4.288.26\" targetFramework=\"native\" />\n"
"  <package id=\"v8-v141-x86\" version=\"7.4.288.28\" targetFramework=\"native\" />\n"
"  <package id=\"v8-v142-x86\" version=\"7.5.288.23\" targetFramework=\"native\" />\n"
"</packages>";

const char* packages_config = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x86fe36d4:  numBytes = 708; return packages_config;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "packages_config"
};

const char* originalFilenames[] =
{
    "packages.config"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
