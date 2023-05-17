#pragma once
#include "IRandomGenerator.h"
#include <typeinfo>
#include <random>
#include <cstdint>
namespace myr {
    class RandomHardware :
        public IRandomGenerator
    {
    public:
        inline RandomHardware() : rd_(nullptr) {}
        inline RandomHardware(std::random_device * rd) : rd_(rd) {};
        inline ~RandomHardware() override {
            if (rd_) {
                delete rd_;
            }
        }
        inline virtual double operator() () const override {
            if (rd_) {
                return (static_cast<double>((*rd_)()));
            }
            else {
                return (static_cast<double>((std::random_device())()));
            }
        }
        inline virtual double const max() const override {
            return max_;
        }
        inline virtual double const min() const override {
            return min_;
        }
        inline bool operator==(RandomHardware const& rval) const {
            return true;
        }
        inline bool operator!=(RandomHardware const& rval) const {
            return false;
        }
        inline bool operator==(IRandomGenerator const& rval) const override {
            if (typeid(*this) == typeid(rval)) {
                return true;
            }
            else {
                return false;
            }
        }
        inline bool operator!= (IRandomGenerator const& rval) const override {
            return !((*this) == rval);
        }
    private:
        static double const max_;
        static double const min_;
        std::random_device* rd_;

        //restricted:
        RandomHardware& operator= (RandomHardware const&) = delete;

    };

    double const RandomHardware::max_ = std::random_device::max();
    double const RandomHardware::min_ = std::random_device::min();
}
