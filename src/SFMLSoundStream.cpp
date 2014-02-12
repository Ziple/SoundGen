#include <SFMLSoundStream.hpp>

#include <Synthesizer.hpp>

#include <SFML/Audio.hpp>

struct WAVEHeader
{
    sf::Uint8 FileTypeBlocID[4];
    sf::Uint32 FileSize;
    sf::Uint8 FileFormatID[4];
};

struct WAVEAudioFormat
{
    sf::Uint8 FormatBlocID[4];
    sf::Uint32 BlocSize;
    sf::Uint16 AudioFormat;
    sf::Uint16 NbrCanaux;
    sf::Uint32 Frequence;
    sf::Uint32 BytePerSec;
    sf::Uint16 BytePerBloc;
    sf::Uint16 BitsPerSample;
};

struct WAVEDataBloc
{
    sf::Uint8 DataBlocID[4];
    sf::Uint32 DataSize;
};

namespace stzr
{
    SFMLSoundStream::SFMLSoundStream(
        Synthesizer* synth
        ):
     mySynth( synth ),
     myWAVEHeader( 0 ),
     myWAVEHeaderSize( 44 )
    {
        myWAVEHeader.resize(myWAVEHeaderSize);
        sf::Uint8* headerp = reinterpret_cast< sf::Uint8* >( &myWAVEHeader[0] );

        size_t freq = 44100;
        size_t bytesPerSamples = 2;
        size_t numCanaux = 2;
        myDuration = 90000;//90000 secondes au plus
        size_t numSamples = myDuration * freq;

        WAVEHeader hd;
        hd.FileTypeBlocID[0] = 'R';
        hd.FileTypeBlocID[1] = 'I';
        hd.FileTypeBlocID[2] = 'F';
        hd.FileTypeBlocID[3] = 'F';
        hd.FileSize = 4 + 24 + 8 + numSamples * numCanaux * bytesPerSamples;
        hd.FileFormatID[0] = 'W';
        hd.FileFormatID[1] = 'A';
        hd.FileFormatID[2] = 'V';
        hd.FileFormatID[3] = 'E';

        memcpy( headerp, &hd, 12 );

        WAVEAudioFormat ft;
        ft.FormatBlocID[0] = 'f';
        ft.FormatBlocID[1] = 'm';
        ft.FormatBlocID[2] = 't';
        ft.FormatBlocID[3] = ' ';
        ft.BlocSize = 16;
        ft.AudioFormat = 1;//PCM
        ft.NbrCanaux = numCanaux;
        ft.Frequence = freq;
        ft.BytePerBloc = numCanaux * bytesPerSamples;
        ft.BytePerSec = ft.BytePerBloc * ft.Frequence;
        ft.BitsPerSample = 8 * bytesPerSamples;

        memcpy( headerp + 12, &ft, 24 );

        WAVEDataBloc data;
        data.DataBlocID[0] = 'd';
        data.DataBlocID[1] = 'a';
        data.DataBlocID[2] = 't';
        data.DataBlocID[3] = 'a';
        data.DataSize = numSamples * numCanaux * bytesPerSamples;

        memcpy( headerp + 36, &data, 8 );

        mySize = myWAVEHeaderSize + myDuration * mySynth->getFrequency() * mySynth->getNumChannels() * mySynth->getBytesPerSample();
    }
    
    SFMLSoundStream::~SFMLSoundStream()
    {
    }

    sf::Int64 SFMLSoundStream::read (void *data, sf::Int64 size)
    {
        sf::Uint8* datap = reinterpret_cast< sf::Uint8* >( data );

        sf::Int64 read = 0;

        if( myCurPos < myWAVEHeaderSize )
        {
            sf::Int64 endSize = (myWAVEHeaderSize - myCurPos);
            sf::Int64 toread = endSize < size ? endSize : size;

            size -= toread;
            read += toread;

            memcpy( datap, &myWAVEHeader[myCurPos], toread );
            myCurPos += read;
        }

        if( size > 0 )
        {
            size_t blocSize = mySynth->getBytesPerSample()*mySynth->getNumChannels();
            size_t index = (myCurPos-myWAVEHeaderSize)/blocSize;
            size_t num = size/blocSize;
            mySynth->getSamples( datap+read, index, num );

            read += num * blocSize;
            myCurPos += num * blocSize;
        }

        return read;
    }

    sf::Int64 SFMLSoundStream::getSize()
    {
        return mySize;
    }
}