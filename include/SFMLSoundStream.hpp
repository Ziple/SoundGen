#ifndef __STZRSFMLSOUNDSTREAM_HPP__
#define __STZRSFMLSOUNDSTREAM_HPP__

#include <SFML/System/InputStream.hpp>

#include <vector>

namespace stzr
{
    class Synthesizer;

    class SFMLSoundStream: public sf::InputStream
    {
    public:

        SFMLSoundStream(
            Synthesizer* synth
        );

        ~SFMLSoundStream();

        sf::Int64 read (void *data, sf::Int64 size);

        sf::Int64 seek (sf::Int64 position) { myCurPos = position; return myCurPos; }

        sf::Int64 tell() { return myCurPos; }

        sf::Int64 getSize();

    protected:

        std::vector<sf::Uint8> myWAVEHeader;
        size_t myWAVEHeaderSize;
        size_t myDuration;
        sf::Int64 mySize;

        Synthesizer* mySynth;

        sf::Int64 myCurPos;
    };

}

#endif // __STZRSFMLSOUNDSTREAM_HPP__