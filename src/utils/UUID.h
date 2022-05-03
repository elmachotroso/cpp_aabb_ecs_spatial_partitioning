#ifndef Utils_UUID_h
#define Utils_UUID_h

/// UUID is a type to uniquely identify items.
/// UuidGenerator is in charge of generating a new UUID.
/// TODO: replace with a more sophisticated implementation.

namespace Utils
{
    typedef unsigned long long UUID;

    const UUID UUID_INVALID { 0 };

    class UuidGenerator
    {
        public:
            static UUID generate();

        private:
            static unsigned long long s_uuidCounter;
    };
}

#endif // Utils_UUID_h