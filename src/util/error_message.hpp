/*
 * error_message.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_ERROR_MESSAGE_HPP
#define ZMQ_XML_THREAD_POC_ERROR_MESSAGE_HPP

#include <string>

namespace piper
{

	template<typename E>
	class error_message
	{
	public:
		error_message(E code, const std::string &msg);
		error_message(const error_message &other);
		~error_message() = default;

		error_message<E> &operator =(const error_message<E> &other);

		E                  code       () const;
		virtual const std::string
		                   code_string() const = 0;
		const std::string &message    () const;

	protected:
		E           _code;
		std::string _message;
	};

#include "util/error_message.tpp"

} // piper

#endif //ZMQ_XML_THREAD_POC_ERROR_MESSAGE_HPP
