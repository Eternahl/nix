#include <regex>

#include "ssh-store-config.hh"

namespace nix {

std::string CommonSSHStoreConfig::extractConnStr(std::string_view scheme, std::string_view _connStr)
{
    if (_connStr.empty())
        throw UsageError("`%s` store requires a valid SSH host as the authority part in Store URI", scheme);

    std::string connStr{_connStr};

    std::smatch result;
    static std::regex v6AddrRegex("^((.*)@)?\\[(.*)\\]$");

    if (std::regex_match(connStr, result, v6AddrRegex)) {
        connStr = result[1].matched ? result.str(1) + result.str(3) : result.str(3);
    }

    return connStr;
}

}
