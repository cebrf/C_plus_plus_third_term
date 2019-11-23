#include <memory>
#include "Test.hpp"

namespace smart_pointer {
    // `exception` class definition
    class exception : std::exception {
        using base_class = std::exception;
        using base_class::base_class;
    };

    // `SmartPointer` class declaration
    template<
        typename T,
        typename Allocator
    >
        class SmartPointer {
        // don't remove this macro
        ENABLE_CLASS_TESTS;
        public:
            using value_type = T;

            SmartPointer(value_type* p = nullptr) : core(new Core(p)) {
                if (p == nullptr) {
                    delete core;
                    core = nullptr;
                }
            }

            // copy constructor
            SmartPointer(const SmartPointer& other) :core(other.core) {
                if (core != nullptr) {
                    (*core->owners)++;
                }
            }

            // move constructor
            SmartPointer(SmartPointer&& other) : 
                core(std::exchange(other.core, nullptr)) { }

            // copy assigment
            SmartPointer& operator=(const SmartPointer& other) {
                /*this->~SmartPointer();
                core = other.core;
                (*core->owners)++;*/
                SmartPointer tmp(other);
                std::swap(*this, tmp);
                return *this;
            }

            // move assigment
            SmartPointer& operator=(SmartPointer&& other) {
                ~SmartPointer();
                core = std::move(other.core);
                return *this;
            }

            //
            SmartPointer& operator=(value_type* val) {
                SmartPointer tmp(val);
                std::swap(*this, tmp);
                return *this;
            }

            ~SmartPointer() {
                if (*(core->owners) <= 1) {
                    core->~Core();
                }
                else {
                    (*core->owners)--;
                }
            }

            // return reference to the object of class/type T
            // if SmartPointer contains nullptr throw `SmartPointer::exception`
            value_type& operator*() {
                if (core->p == nullptr) {
                    throw smart_pointer::exception();
                }
                return *(core->p);
            }
            const value_type& operator*() const {
                if (core->p == nullptr) {
                    throw smart_pointer::exception();
                }
                return *(core->p);
            }

            // return pointer to the object of class/type T
            value_type* operator->() const {
                return core->p;
            }

            value_type* get() const {
                return core->p;
            }

            // if pointer == nullptr => return false
            operator bool() const {
                if (core->p == nullptr) {
                    return false;
                }
                return true;
            }

            // if pointers points to the same address or both null => true
            template<typename U, typename AnotherAllocator>
            bool operator==(const SmartPointer<U, AnotherAllocator>& other) const {
                if (this->core->p == nullptr && other->core->p == nullptr) {
                    return true;
                } else if(this->core->p == nullptr || other->core->p == nullptr) {
                    return false;
                } else {
                    return *(this->core->p) == *(other->core->p);
                }
            }

            // if pointers points to the same address or both null => false
            template<typename U, typename AnotherAllocator>
            bool operator!=(const SmartPointer<U, AnotherAllocator>& other) const {
                return !SmartPointer::operator==(other);
            }

            // if smart pointer contains non-nullptr => return count owners
            // if smart pointer contains nullptr => return 0
            std::size_t count_owners() const {
                if (core->p == nullptr) {
                    return 0;
                }
                return *(core->owners);
            }

        private:
            class Core {
             public:
                Core(value_type* p = nullptr) : p(p), owners(new std::size_t) {
                    *owners = 1;
                }
                ~Core() {
                    delete owners;
                    delete p;
                }
                std::size_t* owners;
                value_type* p;
            };
            Core* core;
    };
}