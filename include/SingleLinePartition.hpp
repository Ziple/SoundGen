#ifndef __STZRSINGLELINEPARTITION_HPP__
#define __STZRSINGLELINEPARTITION_HPP__

#include <vector>

namespace stzr
{
    struct Note
    {
        float StartTime;
        float EndTime;
        float Pulsation;
        float Amplitude;
    };

    typedef std::vector<Note> SingleLinePartition;

    template<size_t N>
    void addToPartition( SingleLinePartition& p, Note notes[N] )
    {
        for( size_t i = 0; i < N; i++ )
            p.push_back( notes[i] );
    }
}

#endif // __STZRSINGLELINEPARTITION_HPP__