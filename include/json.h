#ifndef _JSON_
#define _JSON_

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <string>
#include <iostream>

class Json
{
public:
    static int get_int(std::string file_name, std::string key);
    static int get_int_from_object(rapidjson::Value *object, std::string key);
    static void set_int(std::string file_name, std::string key, int value);
    static std::string get_string(std::string file_name, std::string key);
    static std::string get_string_from_object(rapidjson::Value *object, std::string key);
    static rapidjson::Document *get_document(std::string file_name);
    static rapidjson::Value *get_object(rapidjson::Document *document, std::string key);
    static void add_int_to_array(std::string file_name, rapidjson::Document *document, rapidjson::Value *array, int value);
    static void remove_int_from_array(std::string file_name, rapidjson::Document *document, rapidjson::Value *array, int value);
};

#endif