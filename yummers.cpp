#include <node_api.h>
#include <iostream>
#include <vector>

class Yummers
{
private:
        std::vector<uint64_t> buffer; // aint using malloc this time you fucking coward? >:3<
        size_t chunk;
        size_t count;

public:
        Yummers(size_t chunk)
        {
                this->chunk = chunk;
        }

        void set_chunk(size_t chunk)
        {
                this->chunk = chunk;
        }

        void set_count(size_t count)
        {
                this->count = count;
        }

        size_t get_chunk()
        {
                return this->chunk;
        }

        size_t get_count()
        {
                return this->count;
        }

        size_t memsize()
        {
                return this->buffer.size();
        }

        void refeed(size_t chunk)
        {
                this->set_chunk(chunk);
                this->set_count(0);

                this->buffer.clear();

                if (this->get_chunk() > 0)
                {
                        this->buffer.resize(this->get_chunk());
                        this->set_count(1);
                }
        }

        void feed()
        {
                if (this->get_chunk() == 0)
                        return;

                this->buffer.resize(this->buffer.size() + this->get_chunk());

                size_t count = this->get_count();

                this->set_count(++count);
        }

        void flush()
        {
                this->buffer.clear();
                this->set_count(0);
        }

        static void deconstructor(napi_env env, void *data, void *hint)
        {
                Yummers *yummers = (Yummers *)data;

                delete yummers;
        }
};

napi_value class_constructor(napi_env env, napi_callback_info info)
{
        size_t argc = 1;
        napi_value argv[argc];
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, &argc, argv, &js_obj, nullptr);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "cannot get constructor args.");

                return nullptr;
        }

        if (argc != 1)
        {
                napi_throw_error(env, nullptr, argc > 0 ? "too many args." : "too few args.");

                return nullptr;
        }

        int64_t chunk = 0;
        status = napi_get_value_int64(env, argv[0], &chunk);

        if (status != napi_ok || chunk < 0)
        {
                napi_throw_error(env, nullptr, "invalid constructor arg.");

                return nullptr;
        }

        Yummers *yummers = new Yummers((size_t)chunk);
        status = napi_wrap(env, js_obj, yummers, Yummers::deconstructor, nullptr, nullptr);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "failed to wrap object.");

                return nullptr;
        }

        return js_obj;
}

napi_value feed(napi_env env, napi_callback_info info)
{
        size_t argc = 0;
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, &argc, nullptr, &js_obj, nullptr);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "failed to get callback info.");

                return nullptr;
        }

        Yummers *yummers;
        status = napi_unwrap(env, js_obj, (void **)&yummers);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "cannot unwrap object.");

                return nullptr;
        }

        yummers->feed();

        return nullptr;
}

napi_value refeed(napi_env env, napi_callback_info info)
{
        size_t argc = 1;
        napi_value argv[argc];
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, &argc, argv, &js_obj, nullptr);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "cannot get args.");

                return nullptr;
        }

        if (argc != 1)
        {
                napi_throw_error(env, nullptr, argc > 0 ? "too many args." : "too few args.");

                return nullptr;
        }

        int64_t chunk = 0;
        status = napi_get_value_int64(env, argv[0], &chunk);

        if (status != napi_ok || chunk < 0)
        {
                napi_throw_error(env, nullptr, "invalid arg.");

                return nullptr;
        }

        Yummers *yummers;
        status = napi_unwrap(env, js_obj, (void **)&yummers);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "cannot unwrap args.");

                return nullptr;
        }

        yummers->refeed((size_t)chunk);

        return nullptr;
}

napi_value hog(napi_env env, napi_callback_info info)
{
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &js_obj, nullptr);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot get object.");

                return nullptr;
        }

        Yummers *yummers;
        status = napi_unwrap(env, js_obj, (void **)&yummers);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot unwrap object");

                return nullptr;
        }

        std::vector<uint8_t> buffer;
        size_t chunk = yummers->get_chunk() == 0 ? 4098 : yummers->get_chunk();
        size_t count = 0;

        while (1 == 1)
        {
                ++count;
                buffer.resize(chunk * count);
        }

        return nullptr;
}

napi_value flush(napi_env env, napi_callback_info info)
{
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &js_obj, nullptr);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot get object.");

                return nullptr;
        }

        Yummers *yummers;
        status = napi_unwrap(env, js_obj, (void **)&yummers);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot unwrap object.");

                return nullptr;
        }

        yummers->flush();

        return nullptr;
}

napi_value memsize(napi_env env, napi_callback_info info)
{
        napi_value js_obj;
        napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &js_obj, nullptr);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot get object.");

                return nullptr;
        }

        Yummers *yummers;
        status = napi_unwrap(env, js_obj, (void **)&yummers);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot unwrap object.");

                return nullptr;
        }

        napi_value allocated_bytes;

        status = napi_create_int64(env, yummers->memsize(), &allocated_bytes);

        if (status != napi_ok)
        {
                napi_throw_error(env, nullptr, "cannot get memesize.");

                return nullptr;
        }

        return allocated_bytes;
}

napi_value init(napi_env env, napi_value exports)
{
        napi_property_descriptor properties[] = {
            {"hog", nullptr, hog, nullptr, nullptr, nullptr, napi_enumerable, nullptr},
            {"feed", nullptr, feed, nullptr, nullptr, nullptr, napi_enumerable, nullptr},
            {"flush", nullptr, flush, nullptr, nullptr, nullptr, napi_enumerable, nullptr},
            {"refeed", nullptr, refeed, nullptr, nullptr, nullptr, napi_enumerable, nullptr},
            {"memsize", nullptr, memsize, nullptr, nullptr, nullptr, napi_enumerable, nullptr}};

        napi_value js_obj;
        napi_status status = napi_define_class(env, "Yummers", NAPI_AUTO_LENGTH, class_constructor, nullptr, sizeof(properties) / sizeof(napi_property_descriptor), properties, &js_obj);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot define class.");

                return nullptr;
        }

        status = napi_set_named_property(env, exports, "Yummers", js_obj);

        if (status != napi_ok)
        {
                throw napi_throw_error(env, nullptr, "cannot set class properties.");

                return nullptr;
        }

        return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)