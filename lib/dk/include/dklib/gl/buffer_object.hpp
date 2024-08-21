#ifndef DK_GL_BUFFER_HPP
#define DK_GL_BUFFER_HPP

#include <GL/glext.h>
#include <GLES3/gl3.h>
#include <dklib/gl/gltypes.hpp>
#include <spdlog/spdlog.h>
#include <vector>

namespace dk::gl {

enum class BufferUsage : gl::enum32 {
    STATIC_DRAW = GL_STATIC_DRAW,
};

class IBufferObject {
public:
    virtual inline void bind() const noexcept = 0;
    virtual inline void unbind() const noexcept = 0;

    [[nodiscard]] virtual u32 get_id() const noexcept = 0;

private:
    u32 buf_id_;
};

class VertexArray {
public:
    VertexArray() { glGenVertexArrays(1, &vao_); }
    // TODO: add move ctor and then set &vao_ to nullptr
    // NOTE: this is going to need some more work
    ~VertexArray() { glDeleteVertexArrays(1, &vao_); }

    inline void bind() const noexcept { glBindVertexArray(vao_); }

    [[nodiscard]] u32 get_id() const noexcept { return vao_; }

private:
    u32 vao_ { 0 };
};

enum class BufferObjectType : enum32 {
    ARRAY = GL_ARRAY_BUFFER,
    ATOMIC_COUNTER = GL_ATOMIC_COUNTER_BUFFER,
    COPY_READ = GL_COPY_READ_BUFFER,
    COPY_WRITE = GL_COPY_WRITE_BUFFER,
    DISPATCH_INDIRECT = GL_DISPATCH_INDIRECT_BUFFER,
    DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
    ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
    PIXEL_PACK = GL_PIXEL_PACK_BUFFER,
    PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,
    QUERY = GL_QUERY_BUFFER,
    SHADER_STORAGE = GL_SHADER_STORAGE_BUFFER,
    TEXTURE = GL_TEXTURE_BUFFER,
    TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
    UNIFORM = GL_UNIFORM_BUFFER,
};

template <BufferObjectType buf_type>
class Buffer {
public:
    Buffer() { glGenBuffers(1, &id_); };
    template <typename T>
    explicit Buffer(const std::vector<T> &vertices)
        : Buffer(vertices, BufferUsage::STATIC_DRAW) {};

    template <typename T>
    Buffer(const std::vector<T> &vertices, BufferUsage usage)
        : Buffer() {
        setup(vertices, usage);
    }

    virtual ~Buffer() {
        if (id_ != 0) {
            spdlog::info("Deleting Buffer ID: {}", id_);
            glDeleteBuffers(1, &id_);
        }
    }

    // This is a move only type
    Buffer(const Buffer &other) = delete;
    Buffer &operator=(const Buffer &other) = delete;

    Buffer(Buffer &&other) noexcept { *this = std::move(other); }
    Buffer &operator=(Buffer &&other) noexcept {
        if (this != &other) {
            if (id_ != 0) {
                glDeleteBuffers(1, &id_);
            }
            id_ = std::exchange(other.id_, 0);
        }
        return *this;
    }

    virtual void bind() const { glBindBuffer(static_cast<u32>(buf_type), id_); }
    virtual void unbind() const { glBindBuffer(static_cast<u32>(buf_type), 0); }

    template <typename T>
    void setup(const std::vector<T> &objs, BufferUsage usage = BufferUsage::STATIC_DRAW) const {
        glBindBuffer(enum_cast(buf_type), id_);
        glBufferData(enum_cast(buf_type), objs.size() * sizeof(T), objs.data(), enum_cast(usage));
    }

private:
    u32 id_ { 0 };
};

using ElementBuffer = Buffer<BufferObjectType::ELEMENT_ARRAY>;
using VertexBuffer = Buffer<BufferObjectType::ARRAY>;
using TextureBuffer = Buffer<BufferObjectType::TEXTURE>;

} // namespace dk::gl

#endif // DK_GL_BUFFER_HPP
