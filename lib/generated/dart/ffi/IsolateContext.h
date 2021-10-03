
#pragma once

#include "Export.h"
#include <cstdint>

namespace ffi
{
class _GLUECODIUM_FFI_EXPORT IsolateContext
{
private:
    const int32_t m_previous_id;
    static thread_local int32_t m_current_id;

public:
    explicit IsolateContext(int32_t isolate_id)
        : m_previous_id(m_current_id)
    {
        m_current_id = isolate_id;
    }

    ~IsolateContext()
    {
        m_current_id = m_previous_id;
    }

    bool static is_current(int32_t isolate_id)
    {
        return m_current_id == isolate_id;
    }
};
}
