#include "json.h"

// Return an integer value in the json file
int Json::get_int(std::string file_name, std::string key)
{
    std::ifstream ifstream(file_name);
    rapidjson::IStreamWrapper isw(ifstream);
    rapidjson::Document document;

    document.ParseStream(isw);
    if (document.HasMember(key.c_str()) && document[key.c_str()].IsNumber())
    {

        return document[key.c_str()].GetInt();
    }
    std::cout << "Error: JSON key (" << key << ") not found ..." << std::endl;
    exit(1);
}

// Return an integer value in the json file
int Json::get_int_from_object(rapidjson::Value *object, std::string key)
{
    if (!object->IsObject())
    {
        std::cout << "Error: JSON object is not valid ..." << std::endl;
        exit(1);
    }

    if (!object->HasMember(key.c_str()))
    {
        std::cout << "Error: JSON key (" << key << ") not found ..." << std::endl;
        exit(1);
    }

    if (!(*object)[key.c_str()].IsInt())
    {
        std::cout << "Error: JSON value for key (" << key << ") is not an integer ..." << std::endl;
        exit(1);
    }

    return (*object)[key.c_str()].GetInt();
}

// Update an integer value in the json file
void Json::set_int(std::string file_name, std::string key, int value)
{
    std::ifstream ifstream(file_name);
    rapidjson::IStreamWrapper isw(ifstream);
    rapidjson::Document document;

    document.ParseStream(isw);

    document[key.c_str()].SetInt(value);

    std::ofstream ofstream(file_name);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);

    document.Accept(writer);
}

// Return a string value in the json file
std::string Json::get_string(std::string file_name, std::string key)
{
    std::ifstream ifstream(file_name);
    rapidjson::IStreamWrapper isw(ifstream);
    rapidjson::Document document;

    document.ParseStream(isw);
    if (document.HasMember(key.c_str()) && document[key.c_str()].IsString())
    {
        return document[key.c_str()].GetString();
    }
    std::cout << "Error: JSON key (" << key << ") not found ..." << std::endl;
    exit(1);
}

// Return a string from a given json object
std::string Json::get_string_from_object(rapidjson::Value *object, std::string key)
{
    if (object->HasMember(key.c_str()))
    {
        return (*object)[key.c_str()].GetString();
    }
    std::cout << "Error: JSON key (" << key << ") not found ..." << std::endl;
    exit(1);
}

// Return the document root from a given json file
rapidjson::Document *Json::get_document(std::string file_name)
{
    std::ifstream ifstream(file_name);
    rapidjson::IStreamWrapper isw(ifstream);
    rapidjson::Document *document = new rapidjson::Document;
    document->ParseStream(isw);
    return document;
}

// Return an object value from a given document
rapidjson::Value *Json::get_object(rapidjson::Document *document, std::string key)
{
    if (!document->HasMember(key.c_str()))
    {
        std::cout << "Error: JSON key (" << key << ") not found ..." << std::endl;
        exit(1);
    }
    else if (!(*document)[key.c_str()].IsObject())
    {
        std::cout << "Error: JSON object (" << key << ") is not an object ..." << std::endl;
        exit(1);
    }

    rapidjson::Value *value = new rapidjson::Value;
    value = &((*document)[key.c_str()]);
    return value;
}
