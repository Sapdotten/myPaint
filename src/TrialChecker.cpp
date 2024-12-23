#include "../include/TrialChecker.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

\
std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Can't open file: " + filepath);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

TrialChecker::TrialChecker() {
\
    public_key_pem = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAu9i8/4mU0HIpWy916ZbK
D8GHEf8sHYqJRE/1eW40qwgF9civWMREgjBP6uRGClodpkBPLXZ37L76NIs3Hhp4
5L73zzXM94Z52bVVWly7Fgfsj0zx0A/zD74Lof4Kgvp0uOWiBNiovD7JEGyfM6GW
UcPzQioHJvWJMl9QND7RE6KpUogQsJAKeX0YSeCAdVgQfwF7qBwB4KKLz62czE8Y
0odcMGY8J58V3Y2EP8ctQHDjKMFp6cHihQgu9viVFsRqCwbrSsde5YYNGjxomzNk
zmtNEMTG85Ep3ndC2CWzDFq6eG3XeR1/SY7JmtxSiJfgp0s0t5MTRTYQyaU7Fv7J
2QIDAQAB
-----END PUBLIC KEY-----)";
}


EVP_PKEY* TrialChecker::loadPublicKey(const std::string& pubkey_pem) {
    BIO* bio = BIO_new_mem_buf(static_cast<const void*>(pubkey_pem.data()), static_cast<int>(pubkey_pem.size()));
    if (!bio) {
        std::cerr << "Failed to create BIO\n";
        return nullptr;
    }

    EVP_PKEY* pubkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    if (!pubkey) {
        std::cerr << "Failed to read public key\n";
        ERR_print_errors_fp(stderr);
    }

    BIO_free(bio);
    return pubkey;
}

bool TrialChecker::verifySignature(EVP_PKEY* pubkey, const std::string& data, const std::string& signature) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP context\n";
        return false;
    }

    if (EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pubkey) != 1) {
        std::cerr << "EVP_DigestVerifyInit failed\n";
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return false;
    }

    if (EVP_DigestVerifyUpdate(ctx, data.c_str(), data.size()) != 1) {
        std::cerr << "EVP_DigestVerifyUpdate failed\n";
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return false;
    }

    // Verify the signature
    bool result = EVP_DigestVerifyFinal(ctx,
        reinterpret_cast<const unsigned char*>(signature.c_str()), signature.size()) == 1;

    if (!result) {
        std::cerr << "Signature verification failed\n";
        ERR_print_errors_fp(stderr);
    } else {
        std::cout << "Signature verification succeeded\n";
    }

    EVP_MD_CTX_free(ctx);
    return result;
}

bool TrialChecker::parseAndCheckDate(const std::string& dateStr) {
    std::tm expiration_tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&expiration_tm, "%Y-%m-%d");
    if (ss.fail()) {
        std::cerr << "Failed to parse expiration date\n";
        return false;
    }

    std::time_t expiration_time = std::mktime(&expiration_tm);
    std::time_t current_time = std::time(nullptr);

    if (current_time <= expiration_time) {
        std::cout << "Trial period is valid until " << std::asctime(&expiration_tm);
        return true;
    } else {
        std::cerr << "Trial period has expired.\n";
        return false;
    }
}


bool TrialChecker::isTrialValid() {

    EVP_PKEY* pubkey = loadPublicKey(public_key_pem);
    if (!pubkey) {
        std::cerr << "Failed to load public key\n";
        return false;
    }
    try {
        std::string data = readFile("trial_info.txt");
        std::string signature = readFile("trial_info.sig");
        std::cout << "Data read from trial_info.txt: " << data << "\n";
        std::cout << "Signature size: " << signature.size() << " bytes\n";


        if (verifySignature(pubkey, data, signature)) {
            std::cout << "Signature is valid.\n";

            if (parseAndCheckDate(data)) {

                EVP_PKEY_free(pubkey);
                return true;
            } else {
                EVP_PKEY_free(pubkey);
                return false;
            }
        } else {
            std::cerr << "Invalid signature. The file may have been tampered with.\n";
            EVP_PKEY_free(pubkey);
            return false;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        EVP_PKEY_free(pubkey);
        return false;
    }
}
