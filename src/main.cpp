#include <Synthesizer.hpp>
#include <SFMLSoundStream.hpp>

#include <SFML/Audio.hpp>

int main( int argc, char** argv )
{
    stzr::Synthesizer* syn = new stzr::Synthesizer( 44100, 2, 2 );
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
