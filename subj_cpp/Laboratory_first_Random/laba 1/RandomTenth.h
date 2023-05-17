#pragma once
#include <cstdint>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
#include <cmath>
#include <typeinfo>
namespace myr {
    class RandomTenth :
        public IRandomGenerator
    {
    public:
        explicit inline RandomTenth(
            IRandomGenerator* first = (new RandomHardware()),
            IRandomGenerator* second = (new RandomHardware()),
            double a = 35,
            double max = 100
        )
            : first_(first), second_(second), a_(a > 1 ? a : 35), max_(max) {
        }
        inline ~RandomTenth() override {
            delete first_;
            delete second_;
        }

        virtual inline double operator() () const override
        {
            double Y;
            double X;
            do {
                do {
                    do {
                        Y = std::tan(std::acos(-1) * ((*first_)() - first_->min()) / (first_->max() - first_->min()));
                        X = std::sqrt(2 * a_ - 1) * Y + a_ - 1;
                    } while (X <= 0);
                } while ((((*second_)() - second_->min()) / (second_->max() - second_->min())) > ((1+ Y*Y)*std::exp((a_-1)*std::log(X/(a_-1))-std::sqrt(2*a_ -1)*Y)));
            } while ((X < min_) || (max_ < X));
            return X;
        }
        inline bool operator== (RandomTenth const& rval) const {
            return ((*first_) == (*rval.first_)) && ((*second_) == (*rval.second_)) && (a_ == rval.a_) && (max_ == rval.max_);
        }
        inline bool operator!=(RandomTenth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomTenth const&>(rval));;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
        inline void setRandomGenerator1(IRandomGenerator* newrnd) {
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
        inline const double min() const override {
            return min_;
        }
        inline const double max() const override {
            return max_;
        }
        inline void setMax(double const& new_min) {
            max_ = new_min;
        }
        inline void setA(double const& new_A) {
            a_ = new_A;
        }
        inline double getA() const {
            return a_;
        }



    private:
        IRandomGenerator* first_;
        IRandomGenerator* second_;
        double max_;
        double a_;
        static double const min_;

        //restricted:

        RandomTenth& operator= (RandomTenth const&) = delete;
        RandomTenth(RandomTenth const& rval) = delete;
    };
    double const RandomTenth::min_ = 0;
}
