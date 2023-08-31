#pragma once
#include <exception>
#include <string>

class IpException : std::exception{
public:
    enum class ErrorCode {
        //TODO: codes
    };

    IpException(ErrorCode code, std::string_view mes) : code_(code), mes_(mes) {}

    std::string_view What() const noexcept {
        return mes_;
    }

    ErrorCode getErrorCode() const noexcept {
        return code_;
    }

private:
    ErrorCode code_;
    std::string_view mes_;
};

