#include <iostream>
#include <stdexcept>

/* int main() {
    try {
        try {
            // Some code
            throw std::domain_error("domain error");
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Bad cast
        catch (std::bad_cast& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Runtime error derived classes
        catch (std::overflow_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        catch (std::underflow_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        catch (std::range_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Runtime error
        catch (std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Logic error derived classes
        catch (std::domain_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        catch (std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        catch (std::length_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Logic error
        catch (std::logic_error& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Bad alloc
        catch (std::bad_alloc& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
        // Exception
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }
    catch (...) {
        abort();
    }
    std::cout << "Not printed" << std::endl;
    return 0;
} */

class exceptionType {
   public:
    exceptionType(const std::string& s = "") : msg(s) {}
    const std::string& what() const { return msg; }

   private:
    std::string msg;
};
typedef int EXCPTYPE;

int main() {
    try {
        throw exceptionType("message");
    }
    catch (exceptionType& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        throw std::runtime_error("runtime error");
    }
    catch (...) {
        std::cerr << "anything caught" << std::endl;
    }

    try {
        throw 2;
    }
    catch (EXCPTYPE e) {
        std::cerr << e << std::endl;
    }
    return 0;
}