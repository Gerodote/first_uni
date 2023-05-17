#pragma once
#include <cstdint>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
namespace myr {
	class RandomSixth :
		public IRandomGenerator {
    public:
        explicit inline RandomSixth(
            IRandomGenerator* gen = (new RandomHardware())
        )
            : gen_(gen) {
        }
        inline ~RandomSixth() override {
            delete gen_;
        }
        virtual inline double operator() () const override
        {
            double tmp;
            do {
                tmp = -6;
                for (int i = 0; i < 12; ++i) {
                    tmp += ((*gen_)() - gen_->min()) / (gen_->max() - gen_->min());
                }
            } while ((tmp < min_) || (max_ < tmp));
            return tmp;
        }
        inline bool operator== (RandomSixth const& rval) const {
            return ((*gen_) == (*rval.gen_)) ;
        }
        inline bool operator!=(RandomSixth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomSixth const&>(rval));;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
        inline void setRandomGenerator(IRandomGenerator* newrnd) {
            if (gen_ != newrnd) {
                delete gen_;
                gen_ = newrnd;
            }
        }
        inline const double min() const override {
            return min_;
        }
        inline const double max() const override {
            return max_;
        }


    private:
        IRandomGenerator* gen_;
        static double const max_;
        static double const min_;

        //restricted:

        RandomSixth& operator= (RandomSixth const&) = delete;
        RandomSixth(RandomSixth const& rval) = delete;
	};
    double const RandomSixth::max_ = 3;
    double const RandomSixth::min_ = -3;
}