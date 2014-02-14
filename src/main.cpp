#include <Synthesizer.hpp>
#include <SFMLSoundStream.hpp>

#include <SFML/Audio.hpp>

int main( int argc, char** argv )
{
    stzr::SingleLinePartition part;

    stzr::Note notes[] = {
        { 0.f, 2.f, 6.2831853f * 440.f, 0.1f },
        { 1.f, 3.f, 6.2831853f * 329.63f, 0.3f },
        { 2.f, 4.f, 6.2831853f * 349.23f, 0.1f },
        { 3.f, 4.f, 6.2831853f * 440.f, 0.1f }
    };

    stzr::addToPartition<4>( part, notes );

    stzr::Synthesizer* syn = new stzr::Synthesizer( 44100, 2, 2 );
    syn->setPartition( &part );

    stzr::SFMLSoundStream* sndStr = new stzr::SFMLSoundStream( syn );

    sf::Music strM;
    if( strM.openFromStream( *sndStr ) == false )
        return -1;
    strM.play();

    while( strM.getStatus() == sf::Music::Playing  )
        ;

    delete sndStr;
    delete syn;
    return 0;
}
