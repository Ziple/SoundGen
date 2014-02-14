#include <Synthesizer.hpp>
#include <Guitar.hpp>

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
     myNumChannels( numChannels ),
     myPartition( 0 )
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
        memset( sdst, 0, sizeof(sf::Uint16)*myNumChannels*num);

		if ( myPartition != 0 )
			for (Partition::iterator it = myPartition->begin();
				it != myPartition->end();
				it++)
			{
				Instrument* instr = it->first;
				if (instr != 0 && it->second != 0 )
					instr->getSamples(this, it->second, dst, start, num);
			}
    }
}