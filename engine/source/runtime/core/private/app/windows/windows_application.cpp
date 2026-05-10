// © 2026 Pawel Mlynarz

#include "app/windows/windows_application.h"

namespace px {

UniquePtr<WindowsApplication> WindowsApplicationFactory::Create() {
    return MakeUnique<WindowsApplication>();
}

} // namespace px
