#ifndef UTILITIES_H
#define UTILITIES_H 





template<bool exp , typename A , typename B >
struct Conditional{
typedef A value ; 
};

template<typename A , typename B >
struct Conditional<false , A ,B>{
typedef B value ; 
};


template<bool exp , int a , int b  >
struct ConditionalInteger{
	constexpr static int value = a  ; 
};

template<int a , int b>
struct ConditionalInteger<false ,a,b > {
	constexpr static int value = b  ; 
};

#endif //UTILITIES_H 
