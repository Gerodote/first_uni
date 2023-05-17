#pragma once
#include <cstdint>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
#include <cmath>
#include <typeinfo>
namespace myr {
    class RandomEighth :
        public IRandomGenerator
    {
    public:
        explicit inline RandomEighth(
            IRandomGenerator* first = (new RandomHardware()),
            IRandomGenerator* second = (new RandomHardware()),
            double min = -3,
            double max = 3
        )
            : first_(first), second_(second), min_(min), max_(max) {
        }
        inline ~RandomEighth() override {
            delete first_;
            delete second_;
        }

        virtual inline double operator() () const override
        {
            double X;
            double tmp1;
            double tmp2;
            do {
                do {
                    tmp1 = ((*first_)() - first_->min()) / (first_->max() - first_->min());
                    do {
                        tmp2 = ((*second_)() - second_->min()) / (second_->max() - second_->min());
                    } while (!tmp2);
                    X = std::sqrt(8 / std::exp(1)) * (tmp1 - 0.5) / tmp2;
                } while (X * X > (-4 * std::log(tmp2)));
            } while ((X < min_) || (max_ < X));
            return X;
        }
        inline bool operator== (RandomEighth const& rval) const {
            return ((*first_) == (*rval.first_)) && ((*second_) == (*rval.second_)) && (min_ == rval.min_) && (max_ == rval.max_);
        }
        inline bool operator!=(RandomEighth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomEighth const&>(rval));;
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
        inline void setMin(double const& new_min) {
            min_ = new_min;
        }
        inline void setMax(double const& new_max) {
            max_ = new_max;
        }


    private:
        IRandomGenerator* first_;
        IRandomGenerator* second_;
        double max_;
        double min_;

        //restricted:

        RandomEighth& operator= (RandomEighth const&) = delete;
        RandomEighth(RandomEighth const& rval) = delete;
    };
}
