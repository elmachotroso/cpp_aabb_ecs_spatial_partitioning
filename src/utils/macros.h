#ifndef Utils_Macros_h
#define Utils_Macros_h

/// Convenience macros

// Numerical limits aliases
#define LIMIT_MIN_FLOAT std::numeric_limits< float >::lowest()
#define LIMIT_MAX_FLOAT std::numeric_limits< float >::max()
#define LIMIT_MIN_DOUBLE std::numeric_limits< double >::lowest()
#define LIMIT_MAX_DOUBLE std::numeric_limits< double >::max()
#define LIMIT_MIN_INT std::numeric_limits< int >::lowest()
#define LIMIT_MAX_INT std::numeric_limits< int >::max()
#define LIMIT_MIN_UINT std::numeric_limits< unsigned int >::lowest()
#define LIMIT_MAX_UINT std::numeric_limits< unsigned int >::max()
#define LIMIT_MIN_LONG std::numeric_limits< long >::lowest()
#define LIMIT_MAX_LONG std::numeric_limits< long >::max()
#define LIMIT_MIN_ULONG std::numeric_limits< unsigned long >::lowest()
#define LIMIT_MAX_ULONG std::numeric_limits< unsigned long >::max()
#define LIMIT_MIN_ULONGLONG std::numeric_limits< unsigned long long >::lowest()
#define LIMIT_MAX_ULONGLONG std::numeric_limits< unsigned long long >::max()

// Safe delete, release...
#define SAFE_DELETE( instance ) \
    delete (instance); \
    (instance) = nullptr;

#define SAFE_DELETE_ARRAY( arrayInstance ) \
    delete [] (arrayInstance); \
    (arrayInstance) = nullptr;

/// VAR_SYNTHESIZE***
/// Macros to simplify coding of member variables of classes.
/// By default it generates the getter and setter, while _READONLY only generates
/// getter.
/// Note: member variables are protected visibility by default.
#define VAR_SYNTHESIZE( _RET_TYPE, _VAR_NAME ) \
    protected: \
        _RET_TYPE m_##_VAR_NAME; \
    public: \
        _RET_TYPE get##_VAR_NAME() const \
        { return m_##_VAR_NAME; } \
        void set##_VAR_NAME( _RET_TYPE value ) \
        { m_##_VAR_NAME = value; }

#define VAR_SYNTHESIZE_READONLY( _RET_TYPE, _VAR_NAME ) \
    protected: \
        _RET_TYPE m_##_VAR_NAME; \
    public: \
        _RET_TYPE get##_VAR_NAME() const \
        { return m_##_VAR_NAME; }

#endif // Utils_Macros_h