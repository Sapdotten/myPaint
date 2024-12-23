#ifndef TRIALCHECKER_H
#define TRIALCHECKER_H

#include <string>
#include <openssl/evp.h>

class TrialChecker {
public:
    TrialChecker();
    ~TrialChecker() = default;

    bool isTrialValid();

private:
    EVP_PKEY* loadPublicKey(const std::string& pubkey_pem);
    bool verifySignature(EVP_PKEY* pubkey, const std::string& data, const std::string& signature);
    bool parseAndCheckDate(const std::string& dateStr);
    std::string public_key_pem;
};

std::string readFile(const std::string& filepath);

#endif // TRIALCHECKER_H
