#pragma once

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

        explicit SmartPointer(value_type* p = nullptr) :
            core((p == nullptr ? nullptr : new Core(p))) {
        }

        // copy constructor
        SmartPointer(const SmartPointer& other) :
            core(other.core != nullptr ? other.core : nullptr) {
            if (core != nullptr) {
                this->core->owners++;
            }
        }

        // move constructor
        SmartPointer(SmartPointer&& other) :
            core(std::exchange(other.core, nullptr)) { }

        // copy assigment
        SmartPointer& operator=(const SmartPointer& other) {
            this->~SmartPointer();
            this->core = other.core;
            if (this->core != nullptr) this->core->owners++;
            return *this;
        }

        // move assigment
        SmartPointer& operator=(SmartPointer&& other) {
            this->~SmartPointer();
            this->core = std::move(other.core);
            other.core = nullptr;
            return *this;
        }

        //
        SmartPointer& operator=(value_type* p) {
            this->~SmartPointer();
            if (p == nullptr) {
                this->core = nullptr;
            } else {
                this->core = new Core(p);
            }
            return *this;
        }

        ~SmartPointer() {
            if (this->core != nullptr) {
                if (this->core->owners <= 1) {
                    delete this->core;
                } else {
                    this->core->owners--;
                }
            }
        }

        // return reference to the object of class/type T
        // if SmartPointer contains nullptr throw `SmartPointer::exception`
        value_type& operator*() {
            if (this->core == nullptr || this->core->p == nullptr) {
                throw smart_pointer::exception();
            }
            else {
                return *(this->core->p);
            }
        }
        const value_type& operator*() const {
            if (this->core == nullptr || this->core->p == nullptr) {
                throw smart_pointer::exception();
            }
            return *(this->core->p);
        }

        // return pointer to the object of class/type T
        value_type* operator->() const {
            return this->get();
        }

        value_type* get() const {
            if (this->core == nullptr) {
                return nullptr;
            } else {
                return this->core->p;
            }
        }

        // if pointer == nullptr => return false
        operator bool() const {
            if (this->core == nullptr || this->core->p == nullptr) {
                return false;
            }
            else {
                return true;
            }
        }

        decltype(auto) getCore() const {
            return static_cast<void*>(this->core);
        }

        // if pointers points to the same address or both null => true
        template<typename U, typename AnotherAllocator>
        bool operator==(const SmartPointer<U, AnotherAllocator>& other) const {
            return this->getCore() == other.getCore();
        }

        // if pointers points to the same address or both null => false
        template<typename U, typename AnotherAllocator>
        bool operator!=(const SmartPointer<U, AnotherAllocator>& other) const {
            return !(SmartPointer::operator==(other));
        }

        // if smart pointer contains non-nullptr => return count owners
        // if smart pointer contains nullptr => return 0
        std::size_t count_owners() const {
            if (this->core == nullptr) {
                return 0;
            }
            else {
                return this->core->owners;
            }
        }

    private:
        class Core {
        public:
            explicit Core(value_type* p) :
                p(p),
                owners(1) { }
            /*Core(Core& other) :
                p(other.p),
                other(other.owners) {
                owners++;
            }
            Core(Core&& other) :
                p(std::exchange(other.p, nullptr)),
                owners(std::move(other.owners)) { }
            Core& operator= (Core& other) {
                Core& tmp()
            }*/
            ~Core() {
                if (p != nullptr) delete p;
            }

            value_type* p;
            std::size_t owners;
        };
        Core* core;
    };
}