#pragma once
#include <string>

/// @brief Interface for serializable objects
/// @details Derived classes must implement the toString method
class ISerializable {
public:
    /// @brief Default destructor
    virtual ~ISerializable() = default;

    /// @brief Pure virtual toString method that derived classes must implement
    /// @return string representation of the object
    virtual std::string toString() const = 0;
}; 