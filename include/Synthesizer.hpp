#ifndef __STZRSYNTHESIZER_HPP__
#define __STZRSYNTHESIZER_HPP__

#include <Partition.hpp>

namespace stzr
{
    /**
     * \brief This class mixes the samples given a partition sheet.
     */
    class Synthesizer
    {
    public:

        Synthesizer(
            size_t frequency,
            size_t bytesPerSample,
            size_t numChannels
            );

        ~Synthesizer();

        size_t getFrequency() const { return myFrequency; }

        float getFrequencyInverse() const { return myInvFreq; }

        size_t getBytesPerSample() const { return myBytesPerSample; }

        size_t getNumChannels() const { return myNumChannels; }

        void setPartition( Partition* p ) { myPartition = p;}

        /**
         * \brief Computes the samples from the one indexed by start till start+num-1.
         * \param dst Buffer in which we place the samples
         * \param start First sample to write
         * \param num Number of samples to write
         */
        void getSamples( void* dst, size_t start, size_t num );

    protected:

        size_t myNumChannels;
        size_t myBytesPerSample;
        size_t myFrequency;
        float myInvFreq;

        Partition* myPartition;
    };
}

#endif // __STZRSYNTHESIZER_HPP__