#pragma once
#include <cstdint>
#include <iostream>
#include <typeinfo>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
namespace myr {
    class RandomFourth :
        public IRandomGenerator
    {
    public:
        // seed: if it is available, take hardware random
        explicit inline RandomFourth(uint_fast64_t a = 61251213, // a % 4 = 1
            uint_fast64_t c = 1541235125114, // c % 4 = 2
            uint_fast64_t m = 1279, // prime
            uint_fast64_t seed = static_cast<uint_fast64_t>(static_cast<double>(1279) * (static_cast<double>((RandomHardware())() - RandomHardware().min()) / (RandomHardware().max() - RandomHardware().min())))
        )
            : a_(a), c_(c), m_(m), seed_(seed) {
            uint_fast64_t* ar = static_cast<uint_fast64_t*>(new uint_fast64_t[static_cast<size_t>(m)]);
            ar[0] = 0;
            bool not_found;
            int_fast64_t x = static_cast<int_fast64_t>(m);
            for (int_fast64_t i = 1; i < x; i++) {
                not_found = true;
                for (int_fast64_t j = 0; j < x; j++) {
                    if ((i * j) % x == 1) {
                        ar[i] = j;
                        not_found = false;
                        break;
                    }
                }

                if (not_found) {
                    std::cerr << "There's no inverse number for: " << i  << " --- method 4 won\'t work, change m, good luck in searching that (-_-)" << std::endl;
                    isAllowableToUse = nullptr;
                    break;
                    
                }
            }
            isAllowableToUse = const_cast<const bool*>(new bool(1));
            table_ = const_cast<uint_fast64_t const *>(ar);
        }
        inline ~RandomFourth() override {
            if (isAllowableToUse) {
                delete isAllowableToUse;
            }
            delete[] table_;
        }
        virtual inline double operator() () const override
        {
            if (isAllowableToUse) {
                if (seed_ == 0)
                    seed_ = c_ % m_;
                else
                    seed_ = static_cast<uint_fast64_t>(static_cast<double>((a_ * table_[seed_] + c_) % m_));

                return static_cast<double>(seed_) / m_;
            }
            else {
                return 0;
            }
        }
        inline bool operator== (RandomFourth const& rval) const {
            return (seed_ == rval.seed_) && (a_ == rval.a_) && (c_ == rval.c_) && (m_ == rval.m_);
        }
        inline bool operator!=(RandomFourth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomFourth const&>(rval));;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
        inline void setSeed(uint_fast64_t const& newseed) {
            seed_ = newseed;
        }
        inline uint_fast64_t getSeed() const {
            return seed_;
        }
        inline uint_fast64_t getA() const {
            return a_;
        }
        inline uint_fast64_t getC() const {
            return c_;
        }
        inline uint_fast64_t getM() const {
            return m_;
        }
        inline const double min() const override {
            return min_;
        }
        inline const double max() const override {
            return max_;
        }


    private:
        uint_fast64_t a_;
        uint_fast64_t c_;
        uint_fast64_t m_;
        mutable uint_fast64_t seed_;
        uint_fast64_t const * table_;
        bool const * isAllowableToUse;
        static double const max_;
        static double const min_;



        //restricted:
        RandomFourth& operator= (RandomFourth const&) = delete;


    };

    double const RandomFourth::max_ = 1;
    double const RandomFourth::min_ = 0;
}
