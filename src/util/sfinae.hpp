/*
 * sfinae.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 11/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_SFINAE_HPP
#define ZMQ_XML_THREAD_POC_SFINAE_HPP

#include <memory>
#include <type_traits>

// https://stackoverflow.com/a/75436916/14999951
template<typename Type, template<typename...> class Args>
struct is_specialization_of : std::false_type {};

template<template<typename...> class Type, typename... Args>
struct is_specialization_of<Type<Args...>, Type> : std::true_type {};

template<typename T>
struct is_shared_ptr : is_specialization_of<T, std::shared_ptr> {};

template<typename T>
struct is_unique_ptr : is_specialization_of<T, std::unique_ptr> {};

template<typename T>
struct is_smart_ptr : std::disjunction<is_shared_ptr<T>, is_unique_ptr<T>> {};

#endif //ZMQ_XML_THREAD_POC_SFINAE_HPP
