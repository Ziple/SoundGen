#include <Guitar.hpp>
#include <Synthesizer.hpp>

#include <SFML/Audio.hpp>

namespace stzr
{
    void Guitar::getSamples(
            Synthesizer* syn,
            SingleLinePartition* part,
            void* dst, 
            size_t start,
            size_t num )
    {
        sf::Uint16* sdst = reinterpret_cast< sf::Uint16* >( dst );
        float invFreq = 1.0f / syn->getFrequency();

        float maxVal = 32767.0f;

        for( size_t i = 0; i < num; i++ )
        {
            float t = (float)(i+start) *invFreq;

            size_t numNotes = part->size();
            for( size_t j = 0; j < numNotes; j++ )
            {
                stzr::Note& note = (*part)[j];
                if( note.StartTime < t
                    && note.EndTime > t )
                {
                    size_t numChannels = syn->getNumChannels();
                    for( size_t k = 0; k < numChannels; k++  )
                    {
                        float rt = t - note.StartTime;
                        float w = note.Pulsation;
                        float f = cos(0.251f*w*rt);
                        float y  = 0.5f*cos(1.0f*w*rt+3.14*f)*exp(-0.0007f*w*rt);
                        y += 0.2f*cos(2.0f*w*rt+3.14*f)*exp(-0.0009f*w*rt);
                        y += 0.2f*cos(4.0f*w*rt+3.14*f)*exp(-0.0016f*w*rt);
                        y += 0.1f*cos(8.0f*w*rt+3.14*f)*exp(-0.0020f*w*rt);
                        y *= 0.9f + 0.1f*cos(70.0f*rt);
                        y = 2.0f*y*exp(-22.0f*rt) + y;

                        sdst[ numChannels*i + k ] += (sf::Uint16)(note.Amplitude * y * maxVal);
                    }
                }
            }
        }
    }
}