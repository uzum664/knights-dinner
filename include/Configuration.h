#ifndef Configuration_H_
#define Configuration_H_
// -------------------------------------------------------------------------
// вспомогательный define для вывода логов..
#define PRELOG myname << "(" << __FUNCTION__ << "): "
#define PRELOG_PF myname << "(" << __PRETTY_FUNCTION__ << "): "
// -------------------------------------------------------------------------
namespace knights
{
	// -----------------------------------------------------------------------------
	inline long sign( const long v )
	{
		if( v < 0 )
			return -1;

		if( v > 0 )
			return 1;

		return 0;
	}
	// -----------------------------------------------------------------------------
	template<typename _T, typename... _Args>
	_T multimin( _T __first )
	{
		return __first;
	}
	template<typename _T, typename... _Args>
	_T multimin( _T __first ,_Args ...__args )
	{
		if( sizeof...(_Args) == 0 )
		{
			return __first;
		}

		_T __tmp = multimin(__args...);
		return __first < __tmp ? __first : __tmp;
	}
	// -----------------------------------------------------------------------------
}
// -------------------------------------------------------------------------
#endif // Configuration_H_
