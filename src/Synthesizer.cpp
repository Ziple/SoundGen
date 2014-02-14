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

        memset( myInstruments, 0, sizeof(Instrument*) * Instrument::Count );
        myInstruments[ Instrument::Guitar ] = new stzr::Guitar();

    }

    Synthesizer::~Synthesizer()
    {
        for( size_t i = 0; i < Instrument::Count; i++ )
            if( myInstruments[i] != 0 )
                delete myInstruments[ i ];
    }

    void Synthesizer::getSamples(
        void* dst, 
        size_t start,
        size_t num )
    {
        sf::Int16 *sdst = reinterpret_cast< sf::Int16* >( dst );
        memset( sdst, 0, sizeof(sf::Uint16)*myNumChannels*num);

        float maxVal = 32767.0f;
<<<<<<< HEAD
=======
        float apuls = 6.2831853f * 440.f;
		float epuls = 6.2831853f * 329.63f;

        for( size_t i = 0; i < num; i++ )
        {
            float t = (float)(i+start) *myInvFreq;
			for (size_t j = 0; j < myNumChannels; j++)
			{
				sdst[myNumChannels*i + j] = (sf::Uint16)(0.1f * sin(apuls *  t) * maxVal);
				if ( t > 5.f
					 && t < 10.f )
					 sdst[myNumChannels*i + j] = (sf::Uint16)(0.1f * sin(epuls *  t) * maxVal);
			}
>>>>>>> 62e96c514f12aa0071b2856a5cae0f8e32585058

        for( size_t i = 0; i < Instrument::Count; i++ )
            if( myPartition != 0 && myInstruments[i]!= 0 )
                myInstruments[i]->getSamples( this, myPartition, dst, start, num );
    }
}