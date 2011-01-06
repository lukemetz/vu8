#ifndef TSA_VU8_MODULE_HPP
#define TSA_VU8_MODULE_HPP

#include <v8.h>

namespace vu8 {

template <class T> struct Class;

struct Module {
    Module& operator()(char const            *name,
                       v8::InvocationCallback callback)
    {
        obj_->Set(v8::String::New(name), v8::FunctionTemplate::New(callback));
        return *this;
    }

    template <class T>
    Module& operator()(char const *name, Class<T>& clss) {
        obj_->Set(v8::String::New(name),
                v8::FunctionTemplate::New(
                    &Class<T>::singleton_t::ConstructorFunction));

        // clss.FunctionTemplate()->SetClassName(v8::String::New(name));
        return *this;
    }

    // this is a local handle so make it persistent if needs be
    v8::Local<v8::Object> NewInstance() {
        return obj_->NewInstance();
    }

    Module() : obj_(v8::ObjectTemplate::New()) {}
  private:
    v8::Local<v8::ObjectTemplate> obj_;
};

}
#endif
