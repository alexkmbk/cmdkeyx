#include <windows.h>
#include <wincred.h>
#include <wchar.h>
#pragma hdrstop

#pragma comment(lib, "advapi32.lib")

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "args.h"

using std::wstring;
using std::cout;
using std::cerr;

bool write(const wstring name, const wstring value) {
  
    CREDENTIALW cred = { 0 };
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = (LPWSTR) name.c_str();
    cred.CredentialBlobSize = value.size() * sizeof(wchar_t);
    cred.CredentialBlob = (LPBYTE)value.data();
    cred.Persist = CRED_PERSIST_SESSION;
    cred.UserName = nullptr;

    return CredWriteW( & cred, 0);
}

wstring read(const wstring name) {
    wstring res;

    PCREDENTIALW pcred;
    if (CredReadW(name.c_str(), CRED_TYPE_GENERIC, 0, &pcred)) {
        res.assign((wchar_t*)pcred->CredentialBlob, pcred->CredentialBlobSize/ sizeof(wchar_t));
        CredFree(pcred);
    }
    return res;    
}

int wmain(int argc, wchar_t* argv[])
{
    std::setlocale(LC_ALL, "");
    auto params = args::parse(argc, argv);

    // Print the parsed arguments.
    for (const auto &param : params) {
        if (param.first == L"add") {
            if (param.second.empty()) {
                std::printf("The name of the targed is not specified, syntax: /add:<target_name>");
                return -1;
            }
            else {
                auto pass = args::find(params, L"pass");
                if (pass.empty()) {
                    std::printf("Password is not specified, syntax: /pass:<password_value>");
                    return -1;
                }
                else {
                    write(param.second, pass);
                    std::wcout << read(param.second) << std::endl;
                }
            }
        }
    }

    return 0;
}
