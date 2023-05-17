#pragma once
#include <cstdint>
#include "IRandomGenerator.h"
#include "RandomHardware.h"
#include <cmath>
#include <typeinfo>
namespace myr {
    class RandomNinth :
        public IRandomGenerator {
    public:
        explicit inline RandomNinth(
            IRandomGenerator* gen = (new RandomHardware()),
            double scale = 9.5,
            double max = 100
        )
            : gen_(gen), scale_(scale), max_(max)  {
        }
        inline ~RandomNinth() override {
            delete gen_;
        }
        virtual inline double operator() () const override
        {
            double tmp;
            do {
                tmp = -scale_ * std::log(((*gen_)() - gen_->min()) / (gen_->max() - gen_->min()));
            } while (max_ < tmp);
            return tmp < 0 ? 0 : tmp;
        }
        inline bool operator== (RandomNinth const& rval) const {
            return ((*gen_) == (*rval.gen_)) && (scale_ == rval.scale_) && (max_ == rval.max_);
        }
        inline bool operator!=(RandomNinth const& rval) const {
            return !(*this == rval);
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return (*this) == (dynamic_cast<RandomNinth const&>(rval));;
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
        inline void setMax(double const& new_max) {
            max_ = new_max;
        }
        inline void setScale(double const& new_scale) {
            scale_ = new_scale;
        }


    private:
        IRandomGenerator* gen_;
        double scale_;
        double max_;
        static double const min_;


        //restricted:

        RandomNinth& operator= (RandomNinth const&) = delete;
        RandomNinth(RandomNinth const& rval) = delete;
    };
    double const RandomNinth::min_ = 0;
}