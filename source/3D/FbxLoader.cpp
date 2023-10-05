#include "header/3D/FbxLoader.h"
using namespace DirectX;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
const std::string FbxLoader::baseDirectory = "Resources/";
const std::string FbxLoader::defaultTextureFileName = "white1x1.png";

void FbxLoader::ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src)
{
    //行
    for (int i = 0; i < 4; i++) {
        //列
        for (int j = 0; j < 4; j++) {
            dst->r[i].m128_f32[j] = (float)src.Get(i, j);
        }
    }
}

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
    //最初期チェック
    assert(fbxManager == nullptr);
    //メンバに代入
    this->device = device;
    //FBXマネージャー生成
    fbxManager = FbxManager::Create();
    //入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    //FBXインポーターの生成
    fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize()
{
    //各インスタンスの破棄
    fbxImporter->Destroy();
    fbxManager->Destroy();
}

FbxModel* FbxLoader::LoadModelFromFile(const string& modelName)
{
    //モデルと同じ名前のフォルダを読み込む
    const string directoryPath = baseDirectory + modelName + "/";
    //拡張子
    const string fileName = modelName + ".fbx";
    //連結後フルパスを取得
    const string fullpath = directoryPath + fileName;

    //ファイル名指定&読み込み
    if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings())) {
        assert(0);
    }

    //シーン生成
    FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

    //ファイルからロードしたFBXの情報をシーンにインポート
    fbxImporter->Import(fbxScene);

    //モデル生成
    FbxModel* model = new FbxModel();
    model->name = modelName;
    //FBXノードの数を取得
    int nodeCount = fbxScene->GetNodeCount();
    //必要数分のメモリを確保、アドレスがずれるのを予防
    model->nodes.reserve(nodeCount);
    //ルートノード空解析モデルに流す
    ParseNodeRecursive(model, fbxScene->GetRootNode());
    //Fbxシーンの解放
    //fbxScene->Destroy();
    model->fbxScene = fbxScene;
    //バッファ生成
    model->CreateBuffers(device);

    return model;
}

void FbxLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent)
{
    //ノード名取得
    string name = fbxNode->GetName();

    //モデルにノード追加
    model->nodes.emplace_back();
    Node& node = model->nodes.back();
    //ノード名を取得
    node.name = fbxNode->GetName();

    //FBXノードのローカル移動情報
    FbxDouble3 rotation = fbxNode->LclRotation.Get();
    FbxDouble3 scaling = fbxNode->LclScaling.Get();
    FbxDouble3 translation = fbxNode->LclTranslation.Get();

    //形式変化して代入
    node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
    node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
    node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };

    //回転角をDegree(度)からラジアンに変換
    node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
    node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
    node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);

    //スケール,回転平行移動行列の計算
    XMMATRIX matScaling, matRotation, matTranslation;
    matScaling = XMMatrixScalingFromVector(node.scaling);
    matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
    matTranslation = XMMatrixTranslationFromVector(node.translation);

    //ローカル変形行列の計算
    node.transform = XMMatrixIdentity();
    node.transform *= matScaling;
    node.transform *= matRotation;
    node.transform *= matTranslation;

    //グローバル変数系の計算
    node.globalTransform = node.transform;
    if (parent) {
        node.parent = parent;
        //親の変形を乗算
        node.globalTransform *= parent->globalTransform;
    }
    FbxNodeAttribute* fbxNodeAtrribute = fbxNode->GetNodeAttribute();

    if (fbxNodeAtrribute) {
        if (fbxNodeAtrribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
            model->meshNode = &node;
            ParseMesh(model, fbxNode);
        }
    }

    //再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
    }
}

void FbxLoader::ParseMesh(FbxModel* model, FbxNode* fbxNode)
{
    //ノードメッシュ取得
    FbxMesh* fbxMesh = fbxNode->GetMesh();

    //頂点座標読み取り
    ParseMeshVertices(model, fbxMesh);
    //面の構成データ読み取り
    ParseMeshFaces(model, fbxMesh);
    //マテリアルの読み取り
    ParseMaterial(model, fbxNode);
    //スキニング情報の読み取り
    ParseSkin(model, fbxMesh);
}

void FbxLoader::ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh)
{
    auto& vertices = model->vertices;

    //頂点データの数
    const int ControlPointCount = fbxMesh->GetControlPointsCount();
    //必要数だけ配列を確定する
    FbxModel::VertexPosNormalUvSkin vert{};
    model->vertices.resize(ControlPointCount, vert);

    //FBXメッシュの頂点座標配列を取得
    FbxVector4* pCoord = fbxMesh->GetControlPoints();
    //メッシュの全頂点座標をモデル内部にコピーする
    for (int i = 0; i < ControlPointCount; i++) {
        FbxModel::VertexPosNormalUvSkin& vertex = vertices[i];
        //座標コピー
        vertex.pos.x = (float)pCoord[i][0];
        vertex.pos.y = (float)pCoord[i][1];
        vertex.pos.z = (float)pCoord[i][2];
    }
}

void FbxLoader::ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh)
{
    auto& vertices = model->vertices;
    auto& indices = model->indices;

    //1ファイルに複数メッシュのモデルは非対応
    const int polygonCount = fbxMesh->GetPolygonCount();
    //UVデータの数
    const int textureUVCount = fbxMesh->GetTextureUVCount();
    //UV名リスト
    FbxStringList uvNames;
    fbxMesh->GetUVSetNames(uvNames);

    //面ごとの情報読み取り
    for (int i = 0; i < polygonCount; i++) {
        //面を構成する頂点の数を取得
        const int polygonSize = fbxMesh->GetPolygonSize(i);
        assert(polygonSize <= 4);

        //1頂点ずつ対応
        for (int j = 0; j < polygonSize; j++) {
            //頂点配列
            int index = fbxMesh->GetPolygonVertex(i, j);
            assert(index >= 0);

            FbxModel::VertexPosNormalUvSkin& vertex = vertices[index];
            FbxVector4 normal;
            if (fbxMesh->GetPolygonVertexNormal(i, j, normal))
            {
                vertex.normal.x = (float)normal[0];
                vertex.normal.y = (float)normal[1];
                vertex.normal.z = (float)normal[2];
            }
            //テクスチャUV読み込み
            if (textureUVCount > 0) {
                FbxVector2 uvs;
                bool lUnmappedUV;
                //0番を決め打ちで代入
                if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
                    vertex.uv.x = (float)uvs[0];
                    vertex.uv.y = (float)uvs[1];
                }
            }
            //インデックス配列に頂点インデックス追加
            //3頂点までなら
            if (j < 3) {
                //1点追加 他2点と三角形を構築する
                indices.push_back(index);
            }
            else
            {
                int index2 = indices[indices.size() - 1];
                int index3 = index;
                int index0 = indices[indices.size() - 3];
                indices.push_back(index2);
                indices.push_back(index3);
                indices.push_back(index0);
            }
        }
    }
}

void FbxLoader::ParseMaterial(FbxModel* model, FbxNode* fbxNode)
{
    const int materialCount = fbxNode->GetMaterialCount();
    if (materialCount > 0) {
        FbxSurfaceMaterial* material = fbxNode->GetMaterial(0);

        bool textureLoaded = false;
        if (material) {
            FbxSurfaceLambert* lambert = static_cast<FbxSurfaceLambert*>(material);

            FbxPropertyT<FbxDouble3> ambient = lambert->Ambient;
            model->ambient.x = (float)ambient.Get()[0];
            model->ambient.y = (float)ambient.Get()[1];
            model->ambient.z = (float)ambient.Get()[2];

            FbxPropertyT<FbxDouble3>diffuse = lambert->Diffuse;
            model->diffuse.x = (float)diffuse.Get()[0];
            model->diffuse.y = (float)diffuse.Get()[1];
            model->diffuse.z = (float)diffuse.Get()[2];
            //ディフューズテクスチャ呼び出し
            const FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (diffuseProperty.IsValid())
            {
                const FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>();
                if (texture) {
                    const char* filepath = texture->GetFileName();

                    string path_str(filepath);
                    string name = ExtractFileName(path_str);

                    LoadTexture(model, baseDirectory + model->name + "/" + name);
                    textureLoaded = true;
                }
            }
        }
        //テクスチャが無い場合こっち白画像
        if (!textureLoaded) {
            LoadTexture(model, baseDirectory + defaultTextureFileName);
        }
    }
}

void FbxLoader::LoadTexture(FbxModel* model, const std::string& fullpath)
{
    HRESULT result = S_FALSE;

    TexMetadata& metadata = model->metadata;
    ScratchImage& scratchImg = model->scratchImag;

    wchar_t wfilepath[128];
    MultiByteToWideChar(CP_ACP, 0, fullpath.c_str(), -1, wfilepath, _countof(wfilepath));
    result = LoadFromWICFile(
        wfilepath, WIC_FLAGS_NONE,
        &metadata, scratchImg);
    if (FAILED(result)) {
        assert(0);
    }
}

void FbxLoader::ParseSkin(FbxModel* model, FbxMesh* fbxMesh)
{
    //スキニング情報
    FbxSkin* fbxSkin = static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));
    //スキニング情報が無ければ終了
    if (fbxSkin == nullptr) {

        //各頂点について
        //for (int i = 0; i < model->vertices.size(); i++) {
        //    //最初のボーン(単位行列)の影響100%にする
        //    model->vertices[i].boneIndex[0] = 0;
        //    model->vertices[i].boneWeight[0] = 1.0f;
        //}
        return;
    }

    //ボーン配列の参観
    std::vector<FbxModel::Bone>& bones = model->bones;

    //ボーンの数
    int clusterCount = fbxSkin->GetClusterCount();
    bones.reserve(clusterCount);

    //全てのボーンについて
    for (int i = 0; i < clusterCount; i++) {
        //FBXボーン情報
        FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
        //ボーン自体のノードの名前を取得
        const char* boneName = fbxCluster->GetLink()->GetName();
        //新しくボーンを追加,追加したボーンの参照を得る
        bones.emplace_back(FbxModel::Bone(boneName));
        FbxModel::Bone& bone = bones.back();
        //自作ボーンとFBXのボーンを紐づける
        bone.fbxCluster = fbxCluster;
        //FBXから初期姿勢制御を取得
        FbxAMatrix fbxMat;
        fbxCluster->GetTransformLinkMatrix(fbxMat);
        //XMMATRIX型に変換
        XMMATRIX initiaPose;
        ConvertMatrixFromFbx(&initiaPose, fbxMat);
        //初期姿勢制御の逆行列を得る
        bone.invInitialPose = XMMatrixInverse(nullptr, initiaPose);
    }

    //ボーン番号とスキンウェイトのペア
    struct WeightSet
    {
        UINT index;
        float weight;
    };
    std::vector<std::list<WeightSet>>weightLists(model->vertices.size());

    //全てのボーンについて
    for (int i = 0; i < clusterCount; i++) {
        //FBXボーン情報
        FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
        //このボーンに影響を受ける頂点の数
        int controlPointIndicesCount = fbxCluster->GetControlPointIndicesCount();
        //このボーンが影響を受ける頂点配列
        int* controlPointIndices = fbxCluster->GetControlPointIndices();
        double* controlPointWeights = fbxCluster->GetControlPointWeights();
        //影響を受ける全長点について
        for (int j = 0; j < controlPointIndicesCount; j++) {
            //頂点番号
            int vertIndex = controlPointIndices[j];
            //スキンウェイト
            float weight = (float)controlPointWeights[j];
            //その他の影響を受けるボーンリストに,ボーンウェイトのペアを追加
            weightLists[vertIndex].emplace_back(WeightSet{ (UINT)i,weight });
        }
    }

    //頂点配列書き換え用
    auto& vertices = model->vertices;
    //各頂点について処理
    for (int i = 0; i < vertices.size(); i++) {
        //頂点のウェイトから最も大きい4つを選択
        auto& weightList = weightLists[i];
        //大小比較用のラムダ式を指定し降順にソート
        weightList.sort([](auto const& lhs, auto const& rhs) {
            //左の要素の方が大きければtrue それでなければfalseを返す
            return lhs.weight > rhs.weight;
            });

        int weightArrayIndex = 0;
        //降順ソート済みのウェイトリストから
        for (auto& weightSet : weightList) {
            //頂点データに書き込み
            vertices[i].boneIndex[weightArrayIndex] = weightSet.index;
            vertices[i].boneWeight[weightArrayIndex] = weightSet.weight;
            //4つにしたら終了
            if (++weightArrayIndex >= FbxModel::MAX_BONE_INDICES) {
                float weight = 0.0f;
                //2番目以降のウェイトを合計
                for (int j = 1; j < FbxModel::MAX_BONE_INDICES; j++) {
                    weight += vertices[i].boneWeight[j];
                }
                //合計で1.0f(100%)になるように調整
                vertices[i].boneWeight[0] = 1.0f - weight;
                break;
            }
        }
    }
}

std::string FbxLoader::ExtractFileName(const std::string& path)
{
    size_t pos1;
    //区切り文字検索
    pos1 = path.rfind('\\');
    if (pos1 != string::npos) {
        return path.substr(pos1 + 1, path.size() - pos1 - 1);
    }

    pos1 = path.rfind('/');
    if (pos1 != string::npos) {
        return path.substr(pos1 + 1, path.size() - pos1 - 1);
    }
    return path;
}