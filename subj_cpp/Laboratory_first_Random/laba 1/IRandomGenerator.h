#pragma once
namespace myr {
	class IRandomGenerator
	{
	public:
		virtual ~IRandomGenerator() = default;
		virtual double operator() () const = 0;
		virtual double const max() const = 0;
		virtual double const min() const = 0;
		virtual bool operator== (IRandomGenerator const&) const = 0;
		virtual bool operator!= (IRandomGenerator const&) const = 0;
	};
}
