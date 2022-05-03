#ifndef Utils_Macros_h
#define Utils_Macros_h

/// Convenience macros

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