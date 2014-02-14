#ifndef __STZRGUITAR_HPP__
#define __STZRGUITAR_HPP__

#include <Instrument.hpp>

namespace stzr
{

    class Guitar: public Instrument
    {
    public:

        void getSamples(
            Synthesizer* syn,
            SingleLinePartition* part,
            void* dst, 
            size_t start,
            size_t num );
    };
}

#endif // __STZRGUITAR_HPP__