#ifndef LIST_H
#define LIST_H


template<typename T=void  , typename... Tt>
struct List{
	typedef  T head ; 	
	typedef   List<Tt...> next;
	constexpr static int size = 1 + List<Tt...>::size;     
};

template<typename T>
struct List<T>{
	typedef  T head ; 	
	typedef List<> next;
	constexpr static int size = 1;    
};



template<>
struct List<>{
	constexpr static int size = 0;    
};

template< typename  , typename  >
struct PrependList;

template< typename T , typename head, typename... tail >
struct PrependList<T , List<head , tail...>> {
	typedef List<T,head , tail...> list  ; 
};

template< typename T , typename head >
struct PrependList<T , List<head> >{
	typedef List<T, head> list  ; 
};
template< typename T >
struct PrependList<T ,void >{
	typedef List<T> list  ; 
};
template< typename T >
struct PrependList<T ,List<> >{
	typedef List<T> list  ; 
};



template< int size,typename List=void>
struct GetAtIndex{
	typedef typename GetAtIndex<size-1 ,typename List::next>::value value  ; 
};


template<typename List>
struct GetAtIndex<0,List>{
	typedef typename List::head value  ; 
};


template<int size  ,typename S  , typename List >
struct SetAtIndex{
	typedef typename PrependList< typename List::head , typename SetAtIndex<size-1 , S , typename List::next>::list >::list list ; 
};
template<typename S , typename List  >
struct SetAtIndex<0,S,List>{
	
	typedef typename PrependList<S  , typename List::next >::list list  ; 
};


template<typename S >
struct SetAtIndex<0 ,S ,List<> >{
	typedef List<S> list  ; 
};


#endif// PART2_TRANSPOSELIST_H 
