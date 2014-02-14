#ifndef __STZRINSTRUMENT_HPP__
#define __STZRINSTRUMENT_HPP__

#include <SingleLinePartition.hpp>

namespace stzr
{
    class Synthesizer;


    /**
     * \brief Base class for every instrument.
     * Every instrument must implement the getSamples function.
     */
    class Instrument
    {
    public:
        enum Instruments
        {
            Guitar = 0,
            Drum = 1,

            Count// Automatically set to the number of instruments in the enum
        };

        virtual ~Instrument() {}

        virtual void getSamples(
            Synthesizer* syn,
            SingleLinePartition* part,
            void* dst, 
            size_t start,
            size_t num ) = 0;
    };
}

#endif //