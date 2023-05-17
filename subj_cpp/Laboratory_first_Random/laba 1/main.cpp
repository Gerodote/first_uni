#include <vector>
#include <iostream>

#include "myrRandom.h"
#include "ContainerTransform.h"

#include "myConsoleProcedures.h"

template <typename T, size_t N>
inline size_t sizeArray(T(&a)[N]) {
    return N;
}

int main()
{ 
    loading();
    size_t quantity_of_generating = 1000000;
    size_t quantity_of_buckets = 10;

    myr::IRandomGenerator* ranGens[] = {
        (static_cast<myr::IRandomGenerator*>(new myr::RandomHardware())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomFirst())) ,
        (static_cast<myr::IRandomGenerator*>(new myr::RandomSecond())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomThird())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomFourth())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomFifth())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomSixth())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomSeventh())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomEighth())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomNinth())),
        (static_cast<myr::IRandomGenerator*>(new myr::RandomTenth()))
    };

    size_t meth_num = introduction();

    ClearConsole();
    while ((0 <= meth_num) && (meth_num < sizeArray(ranGens))) {
        myr::IRandomGenerator* ra = ranGens[meth_num];

        std::vector<double> source;
        for (size_t j = 0; j < quantity_of_generating; ++j) {
            source.push_back((*ra)());
        }
        std::vector<double> histo = toHisto(source, ra->min(), ra->max(), quantity_of_buckets);
        myHistoOutput(histo, ra->min(), ra->max(), quantity_of_generating, quantity_of_buckets, std::cout);
        meth_num = repeat_text();
        ClearConsole();
    }

    for (auto i = std::begin(ranGens); i != std::end(ranGens); ++i) {
        delete* i;
    }
}
