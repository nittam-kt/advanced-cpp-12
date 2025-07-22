#pragma once

#include <tiny_gltf.h>

#include "Renderer.h"


namespace UniDx {

// --------------------
// GltfModelクラス
// --------------------
class GltfModel : public Component
{
public:
    // 画像ファイルを読み込む
    template<typename TVertex>
    bool load(const std::wstring& filePath)
    {
        if (load_(filePath))
        {
            for (auto& sub : submesh)
            {
                sub->createBuffer<TVertex>();
            }
            return true;
        }
        return false;
    }

    // 生成した全ての Renderer にマテリアルを追加
    void addMaterial(std::shared_ptr<Material> material)
    {
        for (auto& r : renderer)
        {
            r->addMaterial(material);
        }
    }

protected:
    std::vector<MeshRenderer*> renderer;
    std::unique_ptr< tinygltf::Model> model;
    std::vector< std::shared_ptr<SubMesh> > submesh;

    bool load_(const std::wstring& filePath);
    void createNodeRecursive(const tinygltf::Model& model, int nodeIndex, GameObject* parentGO);
};


} // namespace UniDx
