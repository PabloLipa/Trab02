#ifndef _TINY_OBJ_LOADER_H
#define _TINY_OBJ_LOADER_H

#include <string>
#include <vector>
#include <map>

namespace tinyobj {

typedef struct
{
    std::string name;

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float transmittance[3];
    float emission[3];
    float shininess;
    float ior;                
    float dissolve;           
    int illum;

    std::string ambient_texname;
    std::string diffuse_texname;
    std::string specular_texname;
    std::string normal_texname;
    std::map<std::string, std::string> unknown_parameter;
} material_t;

typedef struct
{
    std::vector<float>          positions;
    std::vector<float>          normals;
    std::vector<float>          texcoords;
    std::vector<unsigned int>   indices;
    std::vector<int>            material_ids;
} mesh_t;

typedef struct
{
    std::string  name;
    mesh_t       mesh;
} shape_t;

class MaterialReader
{
public:
    MaterialReader(){}
    virtual ~MaterialReader(){}

    virtual std::string operator() (
        const std::string& matId,
        std::vector<material_t>& materials,
        std::map<std::string, int>& matMap) = 0;
};

class MaterialFileReader:
  public MaterialReader
{
    public:
        MaterialFileReader(const std::string& mtl_basepath): m_mtlBasePath(mtl_basepath) {}
        virtual ~MaterialFileReader() {}
        virtual std::string operator() (
          const std::string& matId,
          std::vector<material_t>& materials,
          std::map<std::string, int>& matMap);

    private:
        std::string m_mtlBasePath;
};


std::string LoadObj(
    std::vector<shape_t>& shapes,   
    std::vector<material_t>& materials,   
    const char* filename,
    const char* mtl_basepath = NULL);


std::string LoadObj(
    std::vector<shape_t>& shapes,   
    std::vector<material_t>& materials,   
    std::istream& inStream,
    MaterialReader& readMatFn);


std::string LoadMtl (
  std::map<std::string, int>& material_map,
  std::vector<material_t>& materials,
  std::istream& inStream);
}

#endif  
