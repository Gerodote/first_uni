#pragma once
#include <cstdint>
#include <random>
#include <typeinfo>
#include "RandomHardware.h"
#include "IRandomGenerator.h"
namespace myr {
    class RandomThird :
        public IRandomGenerator
    {
    public:
        // seed: if it is available, take hardware random
        explicit inline RandomThird(
            uint_fast64_t m = 999999937, // a prime, i guarantee
            uint_fast64_t seed = static_cast<uint_fast64_t>(static_cast<double>(999999937) * (static_cast<double>((RandomHardware())() - RandomHardware().min()) / (RandomHardware().max() - RandomHardware().min()))),
            uint_fast64_t seed2 = static_cast<uint_fast64_t>(static_cast<double>(999999937) * (static_cast<double>((RandomHardware())() - RandomHardware().min()) / (RandomHardware().max() - RandomHardware().min())))
        )
            :  m_(m), seed_(seed), seed2_(seed2), order_(1) {}
        inline ~RandomThird() override {}
        virtual inline double operator() () const override
        {
            double tmp;
            if (order_)
            {
                this->seed2_ = (seed_ + seed2_) % m_;
                tmp = (static_cast<double>(seed2_) / static_cast<double>(m_));
            }
            else {
                this->seed_ = (seed_ + seed2_) % m_;
                tmp = (static_cast<double>(seed_) / static_cast<double>(m_));
            }
            order_ = !(order_);
            return tmp;
        }
        inline bool operator== (RandomThird const& rval) const {
            return (seed_ == rval.seed_) && (seed2_ == rval.seed2_) && (m_ == rval.m_);
        }
        inline bool operator!=(RandomThird const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomThird const&>(rval));;
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
        inline void setSeed2(uint_fast64_t const& newseed) {
            seed2_ = newseed;
        }
        inline uint_fast64_t getSeed() const {
            return seed_;
        }
        inline uint_fast64_t getSeed2() const {
            return seed2_;
        }
        inline uint_fast64_t getM() const {
            return m_;
        }
        inline const double  min() const override {
            return min_;
        }
        inline const double max() const override {
            return max_;
        }


    private:
        uint_fast64_t m_;
        mutable uint_fast64_t seed_;
        mutable uint_fast64_t seed2_;
        mutable bool order_;
        static double const max_;
        static double const min_;

        //restricted:
        RandomThird& operator= (RandomThird const&) = delete;
        

    };

    double const RandomThird::max_ = 1;
    double const RandomThird::min_ = 0;


}
