#include <Synthesizer.hpp>

#include <SFML/Audio.hpp>

#include <cmath>

namespace stzr
{
    Synthesizer::Synthesizer(
        size_t freq,
        size_t bytesPerSample,
        size_t numChannels ):
     myFrequency( freq ),
     myBytesPerSample( bytesPerSample ),
     myNumChannels( numChannels )
    {
        myInvFreq = 1.0f / (float)myFrequency;
    }

    Synthesizer::~Synthesizer()
    {}

    void Synthesizer::getSamples(
        void* dst,
        size_t start,
        size_t num )
    {
        sf::Int16 *sdst = reinterpret_cast< sf::Int16* >( dst );

        float maxVal = 32767.0f;
        float apuls = 6.2831853f * 440.f;

        for( size_t i = 0; i < num; i++ )
        {
            float t = (float)(i+start) *myInvFreq;
            for( size_t j = 0; j < myNumChannels; j++  )
                sdst[ myNumChannels*i + j ] = (sf::Uint16)(0.1f * sin( apuls *  t ) * maxVal);

        }
    }
}