
#include "IsolateContext.h"

namespace ffi
{
thread_local int32_t IsolateContext::m_current_id = -1;
}
