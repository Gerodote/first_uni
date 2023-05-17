#pragma once
#include <cstdint>
#include <typeinfo>
#include "RandomHardware.h"
#include "IRandomGenerator.h"

namespace myr {
    class RandomFifth :
        public IRandomGenerator
    {
    public:
        explicit inline RandomFifth(
            IRandomGenerator * first = (new RandomHardware()),
            IRandomGenerator * second = (new RandomHardware()),
            uint_fast64_t m = 999999937, // prime
            uint_fast64_t m1 = 777777773 // prime less than m1
        )
            : first_(first), second_(second), m_(m), m1_(m1) {
        }
        inline ~RandomFifth() override {
            delete first_;
            delete second_;
        }
        virtual inline double operator() () const override
        {
            return static_cast<double>((static_cast<int_fast64_t>(((*first_)() - first_->min()) / (first_->max() - first_->min()) *m_)   + static_cast<int_fast64_t>(((*second_)() - second_->min()) / (second_->max() - second_->min()) *m1_) ) % m_ ) / m_;
        }
        inline bool operator== (RandomFifth const& rval) const {
            return ((*first_) == (*rval.first_)) && ((*second_) == (*rval.second_)) && (m_ == rval.m_) && (m1_ == rval.m1_);
        }
        inline bool operator!=(RandomFifth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomFifth const&>(rval));;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
        inline void setRandomGenerator1(IRandomGenerator * newrnd) {
            if (first_ != newrnd) {
                delete first_;
                first_ = newrnd;
            }
        }
        inline void setRandomGenerator2(IRandomGenerator* newrnd) {
            if (second_ != newrnd) {
                delete second_;
                second_ = newrnd;
            }
        }
        inline uint_fast64_t getM() const {
            return m_;
        }
        inline uint_fast64_t getM1() const {
            return m1_;
        }
        inline const double min() const override {
            return min_;
        }
        inline const double max() const override {
            return max_;
        }


    private:
        uint_fast64_t m_;
        uint_fast64_t m1_;
        IRandomGenerator* first_;
        IRandomGenerator* second_;
        static double const max_;
        static double const min_;

        //restricted:

        RandomFifth& operator= (RandomFifth const&) = delete;
        RandomFifth(RandomFifth const&) = delete;
    };
    double const RandomFifth::max_ = 1;
    double const RandomFifth::min_ = 0;
}
