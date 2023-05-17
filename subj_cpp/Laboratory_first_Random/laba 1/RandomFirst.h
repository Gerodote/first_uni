#pragma once
#include <cstdint>
#include <random>
#include <typeinfo>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
namespace myr {
    class RandomFirst :
        public IRandomGenerator
    {
    public:
        // a: a - 1 = m (mod m); a-1 = 0 |=> a = 1
        // seed: if it is available, take hardware random
        explicit inline RandomFirst(uint_fast64_t a = 1,
            uint_fast64_t c = 1541235125112,
            uint_fast64_t m = 999999937, // a prime, i guarantee
            uint_fast64_t seed = static_cast<uint_fast64_t>(static_cast<double>(999999937) * (static_cast<double>((RandomHardware())() - RandomHardware().min()) / (RandomHardware().max() - RandomHardware().min())))
        )
            : a_(a), c_(c), m_(m), seed_(seed) {}
        inline ~RandomFirst() override {}
        virtual inline double operator() () const override
        {
            this->seed_ = ((a_ * seed_) + c_)% m_;
            return (static_cast<double>(seed_) / static_cast<double>(m_));
        }
        inline bool operator== (RandomFirst const& rval) const {
            return (seed_ == rval.seed_) && (a_ == rval.a_) && (c_ == rval.c_) && (m_ == rval.m_);
        }
        inline bool operator!=(RandomFirst const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomFirst const&>(rval));;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
        inline void setSeed(uint_fast64_t const& newseed){
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
        inline const double  min() const override {
            return min_;
        }
        inline const double max() const  override {
            return max_;
        }


    private:
        uint_fast64_t a_;
        uint_fast64_t c_;
        uint_fast64_t m_;
        mutable uint_fast64_t seed_;
        static double const max_;
        static double const min_;

        //restricted:
        RandomFirst& operator= (RandomFirst const&) = delete;

    };

    double const RandomFirst::max_ = 1;
    double const RandomFirst::min_ = 0;

}