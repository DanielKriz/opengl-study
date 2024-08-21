#ifndef DK_FILE_BASE_HPP
#define DK_FILE_BASE_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <dklib/gl/model.hpp>

namespace dk {

enum class Colors {
    BLACK,
    RED,
};

// TODO: try to find some good way of wiring this up to the fstream class, so
// that it is more portable and usable
// On the other hand, this class does not have to be so generic and big as
// std fstream, I am just afraid of reinveing the wheel

// FIXME: Use file hierarchy when are you going to need it

/// @brief File abstrac class
///
/// It basically works as a wrapper to the std::fstream
/* class IFile {
public:
    IFile() = default;
    virtual ~IFile() = default;
    [[nodiscard]] virtual bool is_open() const = 0;

    virtual gl::Model read() = 0;
    static gl::Model read(std::string &contents) = 0;
};

class File : public IFile {
public:
    explicit File(std::string &filename)
        : filename_(filename) { }
    virtual ~File() { flush(); }

    void open();
    void close();
    void flush();
    bool eof() const;

    gl::Model read() override;
    static gl::Model read(std::string &filename) override;

protected:
    std::fstream &get_file();

private:
    std::string filename_;
    std::fstream file_;
}; */

} // namespace dk

#endif // DK_FILE_BASE_HPP
