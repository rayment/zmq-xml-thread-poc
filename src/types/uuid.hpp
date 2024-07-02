/*
 * uuid.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_UUID_HPP
#define ZMQ_XML_THREAD_POC_UUID_HPP

#include <cstdint>
#include <string>

namespace piper
{

	class uuid
	{
	public:
		uuid(const std::uint8_t bytes[16]);
		uuid(const std::string &uuid);
		~uuid();

		operator std::string() const;
		bool operator  <(const uuid &other) const;
		bool operator  >(const uuid &other) const;
		bool operator <=(const uuid &other) const;
		bool operator >=(const uuid &other) const;
		bool operator ==(const uuid &other) const;
		bool operator !=(const uuid &other) const;

		static bool is_uuid(const std::string &value);

		int  compare_to(const uuid &other) const;

	private:
		std::uint8_t _bytes[16];
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_UUID_HPP
