#pragma once
#include <cstdint>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
#include <cmath>
namespace myr {
    class RandomSeventh :
        public IRandomGenerator
    {
    public:
        explicit inline RandomSeventh(
            IRandomGenerator* first = (new RandomHardware()),
            IRandomGenerator* second = (new RandomHardware()),
            double min = -3,
            double max = 3
        )
            : first_(first), second_(second), min_(min), max_(max), isEvenExecution_(false), secondValue_(0) {
        }
        inline ~RandomSeventh() override {
            delete first_;
            delete second_;
        }
        
        virtual inline double operator() () const override
        {
            if (!isEvenExecution_ || (secondValue_ < min_) || (secondValue_ > max_)) {
                double S;
                double tmp1;
                double tmp2;
                double firstValue;
                do {
                    do {
                        tmp1 = 2 * ((*first_)() - first_->min())/ (first_->max() - first_->min() ) - 1;
                        tmp2 = 2 * ((*second_)() - second_->min()) / (second_->max() - second_->min() )- 1;
                        S = tmp1 * tmp1 + tmp2 * tmp2;
                    } while (!(S < 1));
                    secondValue_ = tmp2 * std::sqrt((-2) * std::log(S) / S);
                    firstValue = tmp1 * std::sqrt((-2) * std::log(S) / S);
                } while ((firstValue < min_) || (firstValue > max_));
                return firstValue;
            }
            else {
                return secondValue_;
            }
        }
        inline bool operator== (RandomSeventh const& rval) const {
            return ((*first_) == (*rval.first_)) && ((*second_) == (*rval.second_)) && (min_ == rval.min_) && (max_ == rval.max_);
        }
        inline bool operator!=(RandomSeventh const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomSeventh const&>(rval));;
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
        mutable bool isEvenExecution_;
        mutable double secondValue_;
        double max_;
        double min_;

        //restricted:

        RandomSeventh& operator= (RandomSeventh const&) = delete;
        RandomSeventh(RandomSeventh const& rval) = delete;
    };
}
