#ifndef __STZRPARTITION_HPP__
#define __STZRPARTITION_HPP__

#include <Instrument.hpp>
#include <SingleLinePartition.hpp>

#include <map>

namespace stzr
{
	typedef std::map< Instrument*, SingleLinePartition* > Partition;
}

#endif // __STZRPARTITION_HPP__