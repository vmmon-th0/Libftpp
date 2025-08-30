#include "data_buffer.hpp" // Assuming your DataBuffer is defined in this header
#include <iostream>
#include <string>
#include <exception>

class TestObject {
public:
    int x;
    std::string y;

    friend DataBuffer& operator<<(DataBuffer& p_buffer, const TestObject& p_object) {
        p_buffer << p_object.x << p_object.y;
        return p_buffer;
    }

    friend DataBuffer& operator>>(DataBuffer& p_buffer, TestObject& p_object) {
        p_buffer >> p_object.x >> p_object.y;
        return p_buffer;
    }
};

int main() {
    DataBuffer myBuffer;

    TestObject obj1;
    obj1.x = 42;
    obj1.y = "Hello";

    TestObject obj2;
    obj2.x = 99;
    obj2.y = "World";

    myBuffer << obj1 << obj2;

    TestObject deserializedObj1, deserializedObj2, deserializedObj3;

    // This should work as expected
    try {
        myBuffer >> deserializedObj1 >> deserializedObj2;
        std::cout << "Deserialized obj1: x = " << deserializedObj1.x << ", y = " << deserializedObj1.y << std::endl;
        std::cout << "Deserialized obj2: x = " << deserializedObj2.x << ", y = " << deserializedObj2.y << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        myBuffer.reset(); // Reset the buffer to clear read position and data
        
        std::string str = "Test String";
        myBuffer << str; // Serialize the string into the buffer
        
        std::int16_t strSize = static_cast<std::int16_t>(str.size());
        myBuffer << strSize; // Serialize random 16 bit integer into the buffer

        std::int32_t int32Val = 2147483647;
        myBuffer << int32Val; // Serialize a 32 bit integer into the buffer

        std::string deserializedStr;
        myBuffer >> deserializedStr; // Deserialize the string from the buffer
        std::cout << "Deserialized string: " << deserializedStr << std::endl;
        
        myBuffer >> strSize; // Deserialize the random 16 bit integer
        std::cout << "Deserialized random 16 bit integer: " << strSize << std::endl;

        myBuffer >> int32Val; // Deserialize the 32 bit integer
        std::cout << "Deserialized 32 bit integer: " << int32Val << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // This should not compile due to delete specifier
    // try {
    //     std::vector<std::byte> &rawData = myBuffer.rawData(); // This should not compile due to noexcept
    //     rawData.clear(); // Attempting to modify raw data
    // } catch (const std::exception& e) {
    //     std::cout << "Caught exception: " << e.what() << std::endl;  // This line should be executed
    // }

    // This should throw an exception because there are no more objects to deserialize
    try {
        myBuffer >> deserializedObj3;
        std::cout << "Deserialized obj3: x = " << deserializedObj3.x << ", y = " << deserializedObj3.y << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;  // This line should be executed
    }

    return 0;
}
