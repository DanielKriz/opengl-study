#include "hello_world_app.hpp"

namespace dk {
HelloWorldApplication::HelloWorldApplication()
    : Application("Hello World") {};

} // namespace dk

DECLARE_MAIN(dk::HelloWorldApplication);
