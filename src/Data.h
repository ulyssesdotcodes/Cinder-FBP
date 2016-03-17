#pragma once

template<class T>
class data {
	T mData;
public:
	T get();
};

template<class T>
inline T data<T>::get()
{
	return mData;
}
