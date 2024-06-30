/*
 * error_message.tpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

template<typename E>
error_message<E>::error_message(E code, const std::string &msg) :
	_code(code), _message(msg)
{}

template<typename E>
error_message<E>::error_message(const error_message<E> &other) :
	_code(other._code), _message(other._message)
{}

template<typename E>
error_message<E> &
error_message<E>::operator =(const error_message<E> &other)
{
	_code = other._code;
	_message = other._message;
	return *this;
}

template<typename E>
E
error_message<E>::code() const
{
	return _code;
}

template<typename E>
const std::string &
error_message<E>::message() const
{
	return _message;
}
