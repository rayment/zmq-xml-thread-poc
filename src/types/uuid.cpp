/*
 * uuid.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#include <algorithm>
#include <cstring>
#include <sstream>

#include "types/uuid.hpp"

using namespace piper;

uuid::uuid(const std::uint8_t *bytes)
{
	std::memmove(_bytes, bytes, 16);
}

uuid::uuid(const std::string &uuid)
{
	if (!is_uuid(uuid))
	{
		std::memset(_bytes, 0, 16);
		return;
	}
	std::string hex = uuid;
	hex.erase(std::remove(hex.begin(), hex.end(), '{'), hex.end());
	hex.erase(std::remove(hex.begin(), hex.end(), '}'), hex.end());
	hex.erase(std::remove(hex.begin(), hex.end(), '-'), hex.end());
	for (int i = 0; i < 16; ++i)
	{
		std::string byte_string = hex.substr(i * 2, 2);
		_bytes[i] = static_cast<uint8_t>(std::stoul(byte_string, nullptr, 16));
	}
}

uuid::~uuid()
{}

uuid::operator std::string() const
{
	std::stringstream ss;
	for (int i : _bytes) // this MUST be 'int' for std::hex to work properly
		ss << std::hex << i;
	return ss.str();
}

bool
uuid::operator <(const uuid &other) const
{
	return compare_to(other) < 0;
}

bool
uuid::operator >(const uuid &other) const
{
	return compare_to(other) > 0;
}

bool
uuid::operator <=(const uuid &other) const
{
	return compare_to(other) <= 0;
}

bool
uuid::operator >=(const uuid &other) const
{
	return compare_to(other) >= 0;
}

bool
uuid::operator ==(const uuid &other) const
{
	return compare_to(other) == 0;
}

bool
uuid::operator !=(const uuid &other) const
{
	return compare_to(other) != 0;
}

int
uuid::compare_to(const uuid &other) const
{
	for (int i = 0; i < 16; ++i)
	{
		if (*(_bytes+i) < *(other._bytes+i))
			return -1;
		else if (*(_bytes+i) > *(other._bytes+i))
			return 1;
	}
	return 0;
};

bool
uuid::is_uuid(const std::string &value)
{
	auto len = value.length();
	if (len != 36 && len != 38)
		return false;
	bool brace_start = false;
	for (std::string::size_type i = 0; i < len; ++i)
	{
		char c = value[i];
		if (value.length() == 38)
		{
			if (i == 0)
			{
				if (c != '{')
					return false;
				brace_start = true;
			}
			else if (i == len - 1)
			{
				if (c != '}')
					return false;
			}
		}
		if (i == 8 + (brace_start ? 1 : 0) ||
		    i == 13 + (brace_start ? 1 : 0) ||
		    i == 18 + (brace_start ? 1 : 0) ||
		    i == 23 + (brace_start ? 1 : 0))
		{
			if (c != '-')
				return false;
		}
		else if (!((c >= 'a' && c <= 'f') ||
			       (c >= 'A' && c <= 'F') ||
			       (c >= '0' && c <= '9')))
		{
			return false;
		}
	}
	return true;
}
